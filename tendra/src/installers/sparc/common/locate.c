/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *    
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *    
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *    
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *    
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *    
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */




/*
 *			    VERSION INFORMATION
 *			    ===================
 *
 *--------------------------------------------------------------------------
 *$Header$
 *--------------------------------------------------------------------------*/

#define SPARCTRANS_CODE
#include "config.h"
#include "common_types.h"
#include "myassert.h"
#include "addrtypes.h"
#include "expmacs.h"
#include "tags.h"
#include "inst_fmt.h"
#include "regmacs.h"
#include "sparcins.h"
#include "bitsmacs.h"
#include "exp.h"
#include "procrec.h"
#include "guard.h"
#include "eval.h"
#include "regexps.h"
#include "shapemacs.h"
#include "comment.h"
#include "getregs.h"
#include "move.h"
#include "regable.h"
#include "codehere.h"
#include "proc.h"
#include "locate.h"
#include "flags.h"
#include "translat.h"

int call_base_reg = R_SP;

/*
 *  DECODE x INTO A BASE REGISTER PLUS OFFSET
 */

baseoff
boff(exp e)
{
	int n = no (e);
	int b = REG_PART(n);
	baseoff an;
	if (isglob (e)) {
		/* bro is index in main_globals */
		dec *gl = brog (e);
		long sno = gl->dec_u.dec_val.sym_number;
		an.base = (int) (-(sno + 1));
		an.offset = 0;
	} 
	else if (isparam (e) && name(son(e)) != formal_callee_tag) {
		/* parameter, positive offset from %fp */
		/* assert (name (son (e)) == clear_tag) ;*/
		an.base = R_FP;
		an.offset = BITS2BYTES(no (son (e)) + proc_state.params_offset);
		assert (an.offset >= BITS2BYTES(proc_state.params_offset));
	} 
	else if (isparam(e) && name(son(e)) == formal_callee_tag){
		an.base = R_SP;
		an.offset = BITS2BYTES(no(son(e)));
#if 1
		if (Has_vcallees){
			an.base = local_reg;
			an.base = callee_start_reg;
			an.offset = BITS2BYTES(no(son(e)));
		}
		else{
/*
 *      an.base = R_FP;
 *      an.offset = BITS2BYTES(no(son(e)) - proc_state.callee_size);
 */
			an.base = callee_start_reg;
			an.offset = BITS2BYTES(no(son(e)));
		}
#endif
	}
	else if (name(son(e)) == caller_name_tag){
		/* caller name tag is located at [%sp+paramsoffset] */
		an.base = R_SP;
		an.base = call_base_reg;
		an.offset = BYTE_OFFSET_PART(n) + BITS2BYTES(PARAMS_OFFSET);
		
	}	
	else if (b == R_FP) {
		/* locally declared things, negative offset from %fp */
		an.base = R_FP;
		an.offset = -(BITS2BYTES(proc_state.locals_space)) +
			BYTE_OFFSET_PART(n) + BITS2BYTES(proc_state.locals_offset) /*-
																		*      BITS2BYTES(proc_state.callee_size)*/;
		assert (an.offset <= 0);
		assert (an.offset >= -(BITS2BYTES(proc_state.locals_space /*+ 
																   *				       proc_state.callee_size*/)));
	} 
	else if (b == R_SP) {
		/* on stack temps */
		an.base = R_SP;
		an.offset = BYTE_OFFSET_PART(n);
	} 
#if 0
	else if (b == local_reg && Has_vcallees){
		an.base = b;
		an.offset = -(BITS2BYTES(proc_state.locals_space)) +
			BYTE_OFFSET_PART(n) + BITS2BYTES(proc_state.locals_offset);
	}	
#endif
	else if (b <= 31) {
		/* other base register and offset */
		an.base = b;
		an.offset = BYTE_OFFSET_PART(n);
	}	
	
#if 1
	/* obsolete */
	else if (b == 32) {
		/* global names */
		an.base = - ADDR_PART(n);
		an.offset = 0;
	} 
	else if (b == 33) {
		/* local data label : LDNNNN */
		an.base = ADDR_PART(n);
		an.offset = 0;
	}
#endif
	else {
		fail ("not a baseoff in boff");
	}
	return (an);
}

int
boff_env_offset(exp e)
{
	/* used ONLY for envoffsets as init values for globals. 
	 *   cf make_proc_tag_code */
	int n = no (e);
	/*int b = REG_PART(n);*/
	int offset = 0x7fffffff;/* if not set should be outside stack seg */
	/*int this_callee_size = 0;*/
	exp x = e;
	assert (! isglob (e));
	/*assert (b == R_FP);*/
	
#define VAL_params_offset ((16 + 1) * 32)
#define VAL_locals_offset (0)
	while (name(x) != proc_tag && name(x)!=general_proc_tag){
		x = father(x);
		assert (x != nilexp);
	}
	if (isparam (e)) {
		/* parameter, positive offset from %fp */
		/*    assert (name (son (e)) == clear_tag) ;*/
		if (name(son(e)) == formal_callee_tag) {
			offset =  no(son(e))>>3;
		}
		else {
			offset = BITS2BYTES(no (son (e)) + VAL_params_offset);
			assert (offset >= BITS2BYTES(VAL_params_offset));
		}
	} 
	else {
		/* locally declared things, negative offset from %fp */
		/* Now we need the stack size from the procrec, so find the proc */
		long locals_space;
		
		locals_space = procrecs[no(x)].spacereqproc.stack;
		locals_space = (locals_space +63) &~63; /* 8 byte aligned */
		offset = -(BITS2BYTES(locals_space)) +
			BYTE_OFFSET_PART(n) + BITS2BYTES(VAL_locals_offset);
		assert (offset < 0);
		assert (offset >= -(BITS2BYTES(locals_space)));
	}
	return (offset);
}	


/*
 *  AUXILLIARY LOCATION ROUTINE
 *
 *  Finds the address of the expression e using shape s.  sp gives the
 *  available t-registers for any inner evaluation.  dreg is 
 *  historical.
 */

where
locate1(exp e, space sp, shape s, int dreg)
{
	ash a;
	ans aa;
	where wans;
	a = ashof (s);
	
	switch (name (e)) {
    case name_tag : {
		/* this a locally declared name ... */
		exp dc = son (e);
		bool var = (bool) isvar (dc);
		if (props (dc) & defer_bit) {
			/* ... it has been identified with a simple expression
			 *	   which is better evaluated every time */
			where w;
			w = locate (son (dc), sp, sh (son (dc)), dreg);
			if (no (e) == 0) {
				aa = w.answhere;
			} 
			else {
				instore is;
				switch (discrim (w.answhere)) {
				case notinreg : {
					is = insalt (w.answhere);
					is.b.offset += (no (e) / 8);
					break;
				}
				default : {
					fail ("name not deferable");
				}
				}
				setinsalt (aa, is);
			}
		} 
		else if (props (dc) & inreg_bits) {
			/* ... it has been allocated in a fixed point register */
			if (var) {
				setregalt (aa, no (dc));
			} 
			else {
				instore b;
				b.b.base = no (dc);
				b.b.offset = 0;
				b.adval = 1;
				setinsalt (aa, b);
			}
		} 
		else if (props (dc) & infreg_bits) {
			/* ... it has been allocated in a floating point register */
			freg fr;
			fr.fr = no (dc);
			fr.dble = (bool) ((a.ashsize == 64) ? 1 : 0);
			setfregalt (aa, fr);
		} 
		else {
			/* ... it is in memory */
			instore is;
			if (var || (name (sh (e)) == prokhd &&
						(son (dc) == nilexp ||
						 name (son (dc)) == proc_tag ||
						 name(son(dc)) == general_proc_tag))) {
				is.adval = 1;
			} 
			else {
				is.adval = 0;
			}
			is.b = boff (dc);
			is.b.offset += BITS2BYTES(no(e));
			setinsalt(aa,is);
		}
		wans.answhere = aa;
		wans.ashwhere = a;
		return (wans);
    }
    case addptr_tag : {
		exp sum = son (e);
		where wsum;
		int addend;
		space nsp;
		int reg;
		int ind = R_NO_REG;
		instore is;
		ans asum;
		
		wsum = locate (sum, sp, sh (sum), 0);
		asum = wsum.answhere;
		
		/* answer is going to be wsum displaced by integer result of
		 *       evaluating bro (sum) */
		switch (discrim (asum)) {
		case notinreg : {
			is = insalt (asum);
			if (is.adval) {
				/* wsum is a literal address in store ... */
				baseoff b;
				b = is.b;
				if (!IS_FIXREG (b.base)) {
					/* ... it is not a base-offset, so make it one */
					reg = getreg (sp.fixed);
					set_ins (b, reg);
					keepreg (sum, reg);
					b.base = reg;
					b.offset = 0;
				}
				nsp = guardreg (b.base, sp);
				addend = reg_operand (bro (sum), nsp);
				
				/* evaluate the displacement ... */
				if (dreg == 0) dreg = getreg (nsp.fixed);
				rrr_ins (i_add, b.base, addend, dreg);
				clear_reg (dreg);
				
				/* ... add it to the base register into new reg */
				b.base = dreg;
				is.b = b;
				setinsalt (aa, is);
				wans.answhere = aa;
				wans.ashwhere = a;
				
				/* ...and use it as base a literal base-offset result */
				keepexp (e, aa);
				return (wans);
			} 
			else {
				/* wsum represents an actual pointer in store ... */
				/* ... so load it into a good register */
				ind = getreg (sp.fixed);
				ld_ins (i_ld, is.b, ind);
			}
			break;
		}
		case inreg : {
			/* wsum is already in reg */
			ind = regalt (asum);
			break;
		}
		default : {
			fail ("locate ? reg");
		}
		}
		/*register ind contains the evaluation of 1st operand of addptr*/
		if (name (bro (sum)) == env_offset_tag || 
			name (bro(sum)) == general_env_offset_tag) {
			is.b.base = ind;
			is.b.offset = boff_env_offset(son(bro(sum)));
		}
		nsp = guardreg (ind, sp);
		addend = reg_operand (bro (sum), nsp);
		/* evaluate displacement, add it to ind in new reg */
		if (dreg == 0) dreg = getreg (nsp.fixed);
		rrr_ins (i_add, ind, addend, dreg);
		clear_reg (dreg);
		is.b.base = dreg;
		is.b.offset = 0;
		is.adval = 1;
		setinsalt (aa, is);
		wans.answhere = aa;
		wans.ashwhere = a;
		/* ... and deliver literal base_offset */
		keepexp (e, aa);
		return (wans);
    }
    case subptr_tag : {
		/* shouldn't occur */
		exp sum = son (e);
		int ind = reg_operand (sum, sp);
		instore isa;
		isa.adval = 1;
		sum = bro (sum);
		if (name (sum) == val_tag) {
			isa.b.base = ind;
			isa.b.offset = -no (e);
			setinsalt (aa, isa);
		} 
		else {
			if (dreg == 0) dreg = getreg (sp.fixed);
			rrr_ins (i_sub, ind,
					 reg_operand (sum, guardreg (ind, sp)), dreg);
			isa.b.base = dreg;
			isa.b.offset = 0;
		}
		setinsalt (aa, isa);
		wans.answhere = aa;
		wans.ashwhere = a;
		keepexp (e, aa);
		return (wans);
    }
    case reff_tag : {
		/* answer is going to be wans displaced by no (e) */
		wans = locate (son (e), sp, sh (son (e)), 0);
		switch (discrim (wans.answhere)) {
		case notinreg : {
			instore isa;
			isa = insalt (wans.answhere);
			if (!isa.adval) {
				/* wans is an actual pointer in store, so make it
				 *	       into a literal address ...  */
				int reg = getreg (sp.fixed);
				ld_ins (i_ld, isa.b, reg);
				isa.b.offset = 0;
				isa.b.base = reg;
				isa.adval = 1;
			}
			/* ... and add appropriate displacement to give result */
			isa.b.offset += BITS2BYTES(no (e));
			setinsalt (wans.answhere, isa);
			keepexp (e, wans.answhere);
			break;
		}
		case inreg : {
			/* wans is a pointer in a register */
			instore isa;
			
			isa.b.base = regalt (wans.answhere);
			isa.adval = 1;
			isa.b.offset = BITS2BYTES(no (e));
			setinsalt (wans.answhere, isa);
			break;
		}
		default : {
			fail ("locate ? reg ");
		}
		}
		wans.ashwhere = a;
		return (wans);
    }
    case cont_tag :
    case contvol_tag : {
		exp se = son (e);
		ans ason;
		instore isa;
		int reg;
		where fc;
		/* answer is contents of address represented by fc */
		fc = locate (se, sp, sh (e), 0);
		ason = fc.answhere;
		switch (discrim (ason)) {
		case notinreg : {
			isa = insalt (ason);
			if (isa.adval) {
				/* literal store address, make it a direct one */
				isa.adval = 0;
				setinsalt (aa, isa);
			} 
			else {
				/* actual pointer in store so load it into reg and
				 *	       deliver direct base-offset (reg, 0) */
				reg = getreg (sp.fixed);
				ld_ins (i_ld, isa.b, reg);
				isa.b.base = reg;
				isa.b.offset = 0;
				setinsalt (aa, isa);
				if (name (e) != contvol_tag &&
					fc.ashwhere.ashalign != 1) {
					keepexp (e, aa);
				}
			}
			goto breakson;
		}
		case inreg : {
			/* this one is fraught - it depends on only being used
			 *	     in lh-value positions from vars - take care */
			isa.b.base = regalt (ason);
			isa.b.offset = 0;
			isa.adval = 1;
			setinsalt (aa, isa);
			/* fc is in register, so deliver literal base-offset */
			goto breakson;
		}
		case infreg : {
			/* ditto caveat above */
			aa = ason;
			goto breakson;
		}
		default : {
			fail ("locate ? reg");
		}
		}
		breakson :
			wans.answhere = aa;
		wans.ashwhere = a;
		return (wans);
    }
    case top_tag : {
		/* does this ever happen? */
		setregalt (aa, 0);
		wans.answhere = aa;
		wans.ashwhere = a;
		return (wans);
    }
    case field_tag : {
		/* answer is wans displace literally by no (e) ; it should
		 *	 always be a literal store address */
		wans = locate (son (e), sp, sh (son (e)), 0);
		switch (discrim (wans.answhere)) {
		case notinreg : {
			instore isa;
			isa = insalt (wans.answhere);
			isa.b.offset += BITS2BYTES(no (e));
			setinsalt(wans.answhere,isa);
			break;
		}
		default : {
			fail ("field should be transformed");
		}
		}
		wans.ashwhere = a;
		return (wans);
    }
    default : {
		/* general catch all ; evaluate e into register and deliver
		 *	 it as a literal store address */
		int r = reg_operand (e, sp);
		instore is;
		/* Is this needed on SPARC??? */
		if (r == R_O0) {
			/* guard possible result from proc - can do better */
			r = getreg (sp.fixed);
			if (r != R_O0) rr_ins (i_mov, R_O0, r);
		}
		is.b.base = r;
		is.b.offset = 0;
		is.adval = 1;
		setinsalt (aa, is);
		wans.answhere = aa;
		wans.ashwhere = a;
		return (wans);
    }
	}
}


/*
 *  MAIN LOCATION ROUTINE
 *
 *  This is similar to locate1, but firstly checks if e is kept in a
 *  register.
 */

where
locate(exp e, space sp, shape s, int dreg)
{
	ans ak;
	where w;
	ak = iskept (e);
	if (discrim (ak) == inreg && regalt (ak) == 0) {
		w = locate1 (e, sp, s, dreg);
	} 
	else {
		w.answhere = ak;
		w.ashwhere = ashof (s);
	}
	return (w);
}




