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
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header$
--------------------------------------------------------------------------*/


#ifndef PROCDECS_INCLUDED
#define PROCDECS_INCLUDED

#include "addrtypes.h"
#include "proctypes.h"
#include "exptypes.h"

struct proc_state {
  ans procans ;
  bool leaf_proc ;
  baseoff mem_temp0 ;
  int rscope_level ;
  int rscope_label ;
  int result_label ;
  long params_offset ;
  long frame_size ;
  long locals_offset ;
  long locals_space ;
  long maxargs ;
  long callee_size;
};

extern bool Has_vcallees;
extern bool Has_no_vcallers;
extern bool in_general_proc;
extern int callee_size;
#ifdef GENCOMPAT
extern bool May_have_callees;
#endif

extern struct proc_state proc_state ;

extern baseoff mem_temp PROTO_S ( ( int ) ) ;
extern makeans make_proc_tag_code PROTO_S ( ( exp, space, where, int ) ) ;
extern makeans make_rscope_tag_code PROTO_S ( ( exp, space, where, int ) ) ;
extern makeans make_res_tag_code PROTO_S ( ( exp, space, where, int ) ) ;
extern makeans make_apply_tag_code PROTO_S ( ( exp, space, where, int ) ) ;
extern makeans make_apply_general_tag_code PROTO_S ((exp,space,where,int)) ;
extern makeans make_make_callee_list_tag PROTO_S ((exp,space,where,int));
extern makeans make_make_dynamic_callee_tag PROTO_S ((exp,space,where,int));
extern makeans make_same_callees_tag PROTO_S ((exp,space,where,int));
extern makeans make_tail_call_tag PROTO_S ((exp,space,where,int));

#define PARAMS_OFFSET (16+1)*32

#endif /* PROCDECS_INCLUDED */
