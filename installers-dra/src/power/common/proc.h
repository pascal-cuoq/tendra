/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
/*
    Copyright (c) 1993 Open Software Foundation, Inc.


    All Rights Reserved


    Permission to use, copy, modify, and distribute this software
    and its documentation for any purpose and without fee is hereby
    granted, provided that the above copyright notice appears in all
    copies and that both the copyright notice and this permission
    notice appear in supporting documentation.


    OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING
    ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
    PARTICULAR PURPOSE.


    IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
    CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
    LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
    NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
    WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

/*
    		 Crown Copyright (c) 1997

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/



/**********************************************************************
$Author: release $
$Date: 1998/02/04 15:49:04 $
$Revision: 1.2 $
$Log: proc.h,v $
 * Revision 1.2  1998/02/04  15:49:04  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:57  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:03:34  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#ifndef PROCDECS_H
#define PROCDECS_H


#include "config.h"

#include "installtypes.h"
#include "addresstypes.h"
#include "procrectypes.h"
#include "exptypes.h"



/*
 * The following is the global state for compiling a procedure.
 * It needs to be saved and restored if nested procedures allowed.
 */
extern bool last_caller_param(exp);
extern baseoff mem_temp(int);

extern void make_proc_tag_code(exp, space);
extern makeans make_ident_tag_code(exp, space, where, int);
extern void make_res_tag_code(exp, space);
extern makeans make_apply_tag_code(exp, space, where, int);
extern makeans make_apply_general_tag_code(exp,space,where,int);
extern void make_callee_list_tag_code(exp,space);
extern void make_dynamic_callee_tag_code(exp,space);
extern void make_tail_call_tag_code(exp,space);
extern void make_untidy_return_tag_code(exp,space);
extern void make_same_callees_tag_code(exp,space);
extern void make_return_to_label_tag_code(exp,space);
extern void byte_memory_copy(int,int);
extern void word_memory_copy(int,int);
extern long aritherr_lab;
extern long stackerr_lab;

#endif

