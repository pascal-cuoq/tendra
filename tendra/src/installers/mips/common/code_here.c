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


/**********************************************************************
 *$Author$
 *$Date$
 *$Revision$*/
/******************************************************************
 *		code_here
 *
 *This contains procedures :-
 *
 *regofval, fregofval : to see if an exp is a load_tag that has been allocated to a register.
 *
 *regoperand, freoperand : to evaluate an exp into a register using make_code
 *
 *code_here :  calls make_code and ensures that any internal exit labels are tied up after the call
 *
 *
 *	The procedures regoperand and fregoperand evaluate their
 *exp parameter into a single register using make_code. This register is
 *returned. An initial test with regofval checks to see if the exp is already
 *in a register.

******************************************************************/

#include "config.h"
#include "common_types.h"
#include "addrtypes.h"
#include "procrectypes.h"
#include "labels.h"
#include "expmacs.h"
#include "tags.h"
#include "new_code.h"
#include "exp.h"
#include "bitsmacs.h"
#include "locate.h"
#include "regexps.h"
#include "inst_fmt.h"
#include "mips_ins.h"
#include "shapemacs.h"
#include "special.h"
#include "handle_sregs.h"
#include "code_here.h"


/*********************************************************************
 *regofval
 *The procedure regofval checks to see if an exp is a load_tag
 *that has been allocated into a fixpnt register and if so return it or else 100.
 *********************************************************************/
int
regofval(exp e)
{
	exp decx = son (e);
	if (name (e) == name_tag && name (decx) == ident_tag) {/* ident tag */
		if ((props (decx) & defer_bit) != 0) {
			return regofval (son (decx));
		}
		if ((props (decx) & inreg_bits) != 0) {
			return ((isvar (decx)) ? (-no (decx)) : (no (decx)));
		}
		return 100;
	}
	else
		if ((name (e) == val_tag && no (e) == 0) ||
			name(e) == clear_tag || name(e)== top_tag) {
			return 0;
		}
		else {
			return 100;
		}
}

int
fregofval(exp e)
{
	exp decx = son (e);
	if (name (e) == name_tag && name (decx) == ident_tag) {
		if ((props (decx) & infreg_bits) != 0) {
			return no (decx);
		}
		return 100;
	}
	else
		if (name(e)==clear_tag || name(e)==top_tag) {
			return 0;
		}
		else {
			return 100;
		}
}

/**********************************************************************
 *code_here
 *The procedure code_here calls make_code and ensures that
 *any internal exit labels are tied up after the call.
 **********************************************************************/

int
code_here(exp e, space sp, where dest)
{
	makeans mka;
	mka = make_code (e, sp, dest, 0);
	if (mka.lab != 0) {
		set_label (mka.lab);
	}
	return mka.regmove;
}

ash ash0 = {
	0, 0
};
ash ash32 = {
	32, 32
};


int
reg_operand(exp e, space sp)
{
	int   x = regofval (e);
	ans aa;
	where w;
	if (x >= 0 && x < 100) {
		return x;
	}				/* x is a register for e */
	if (name (e) == cont_tag) {
		x = regofval (son (e));
		if (x < 0) {
			return (-x);
		}
	}
	else
		if (name (e) == apply_tag && specialfn (son (e)) == 0) {
			/* apply proc */
			setregalt (aa, 0);
			w.answhere = aa;
			w.ashwhere = ash0;
			make_code (e, sp, w, 0);
			return 2;			/* simple proc calls give result in reg 2
								 */
		}
	
	aa = iskept (e);
	if (aa.discrim == inreg && regalt (aa) != 0) {
		/* the same expression has already been
		 *				   evaluated into a reg */
		return regalt (aa);
	}
	if (aa.discrim == notinreg) {
		instore is;
		is = insalt (aa);
		if (is.adval && is.b.offset == 0) {
			int   r = is.b.base;
			/* the same expression has already been evaluated into a reg */
			return r;
		}
	}
	
	{
		int   reg = -1;
		setsomeregalt (aa, &reg);
		/* allow code_here to evaluate e into reg of its choice */
		w.answhere = aa;
		w.ashwhere = ashof (sh (e));
		code_here (e, sp, w);
		keepreg (e, reg);
		return reg;
	}
}

int
freg_operand(exp e, space sp)
{
	int   x = fregofval (e);
	ans aa;
	where w;
	freg fr;
	w.ashwhere = ashof (sh (e));
	if (x >= 0 && x < 100) {
		return x;
	}
	if (name (e) == cont_tag) {
		x = fregofval (son (e));
		if (x < 100) {
			return (x);
		}
	}
	else
		if (name (e) == apply_tag) {
			setregalt (aa, 0);
			w.answhere = aa;
			w.ashwhere = ash0;
			make_code (e, sp, w, 0);
			return 0;
		}
	
	aa = iskept (e);
	if (aa.discrim == infreg) {	/* e already evaluated in fl reg */
		return regalt (aa) /* cheat */;
	}
	
	{ int reg = -1;
	somefreg sfr;
	sfr.fr = &reg;
	sfr.dble = fr.dble = (w.ashwhere.ashsize == 64) ? 1 : 0;
	setsomefregalt (aa, sfr);
	w.answhere = aa;
	/* evaluate e into reg ... */
	code_here (e, sp, w);
	fr.fr = reg;
	setfregalt(aa, fr);
	keepexp (e, aa);
	return reg;
	}
}
