/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org>
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
 *    		 Crown Copyright (c) 1996
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
 *--------------------------------------------------------------------------
 *$Log$
 *Revision 1.2  2002/11/21 22:30:45  nonce
 *Remove ossg prototypes.  This commit is largely whitespace changes,
 *but is nonetheless important.  Here's why.
 *
 *I.  Background
 *=========================
 *
 *    The current TenDRA-4.1.2 source tree uses "ossg" prototype
 *conventions, based on the Open Systems Software Group publication "C
 *Coding Standards", DRA/CIS(SE2)/WI/94/57/2.0 (OSSG internal document).
 *The goal behind ossg prototypes remains admirable: TenDRA should
 *support platforms that lack ANSI compliant compilers.  The explicit
 *nature of ossg's prototypes makes macro substition easy.
 *
 *    Here's an example of one function:
 *
 *    static void uop
 *	PROTO_N ( ( op, sha, a, dest, stack ) )
 *	PROTO_T ( void ( *op ) PROTO_S ( ( shape, where, where ) ) X
 *		  shape sha X exp a X where dest X ash stack )
 *    {
 *
 *tendra/src/installers/680x0/common/codec.c
 *
 *  The reasons for removing ossg are several, including:
 *
 *  0) Variables called 'X' present a problem (besides being a poor
 *variable name).
 *
 *  1) Few platforms lack ANSI-compliant compilers.  ISO-compliant
 *prototypes are easily handled by most every compiler these days.
 *
 *  2) Although TenDRA emphasizes portability, standards compliance is
 *the primary goal of the current project.  We should expect no less
 *from the compiler source code.
 *
 *  3) The benefits of complex prototypes are few, given parameter
 *promotion rules.  (Additionally, packing more types into int-sized
 *spaces tends to diminish type safety, and greatly complicates
 *debugging and testing.)
 *
 *  4) It would prove impractical to use an OSSG internal style document
 *in an open source project.
 *
 *  5) Quite frankly, ossg prototypes are difficult to read, but that's
 *certainly a matter of taste and conditioning.
 *
 *II.  Changes
 *=========================
 *
 *   This commit touches most every .h and .c file in the tendra source
 *tree.  An emacs lisp script (http://www.tendra.org/~nonce/tendra/rmossg.el)
 *was used to automate the following changes:
 *
 *   A.  Prototype Conversions.
 *   --------------------------------------------------
 *
 *   The PROTO_S, PROTO_Z, PROTO_N, PROTO_T, and PROTO_V macros were
 *rewritten to ISO-compliant form.  Not every file was touched.  The
 *files named ossg.h, ossg_api.h, code.c, coder.c and ossg_std.h were
 *left for hand editing.  These files provide header generation, or have
 *non-ossg compliant headers to start with.  Scripting around these
 *would take too much time; a separate hand edit will fix them.
 *
 *   B.  Statement Spacing
 *   --------------------------------------------------
 *
 *   Most of the code in the TenDRA-4.1.2 used extra spaces to separate
 *parenthetical lexemes.  (See the quoted example above.)  A simple
 *text substitution was made for:
 *
 *     Before            After
 *===================================
 *
 *   if ( x )            if (x)
 *   if(x)               if (x)
 *   x = 5 ;             x = 5;
 *   ... x) )            ... x))
 *
 *All of these changes are suggested by style(9).  Additional, statement
 *spacing considerations were made for all of the style(9) keywords:
 *"if" "while" "for" "return" "switch".
 *
 *A few files seem to have too few spaces around operators, e.g.:
 *
 *      arg1*arg2
 *
 *instead of
 *
 *      arg1 * arg2
 *
 *These were left for hand edits and later commits, since few files
 *needed these changes.  (At present, the rmossg.el script takes 1 hour
 *to run on a 2GHz P4, using a ramdisk.  Screening for the 1% that
 *needed change would take too much time.)
 *
 *   C.  License Information
 *   --------------------------------------------------
 *
 *After useful discussion on IRC, the following license changes were
 *made:
 *
 *   1) Absent support for $License::BSD$ in the repository, license
 *and copyright information was added to each file.
 *
 *   2) Each file begins with:
 *
 *   Copyright (c) 2002, The Tendra Project <http://www.tendra.org>
 *   All rights reserved.
 *
 *   Usually, copyright stays with the author of the code; however, I
 *feel very strongly that this is a group effort, and so the tendra
 *project should claim any new (c) interest.
 *
 *   3) The comment field then shows the bsd license and warranty
 *
 *   4) The comment field then shows the Crown Copyright, since our
 *changes are not yet extensive enough to claim any different.
 *
 *   5) The comment field then closes with the $TenDRA$ tag.
 *
 *   D.  Comment Formatting
 *   --------------------------------------------------
 *
 *The TenDRA-4.1.2 code base tended to use comment in this form:
 *
 *    /*
 *       Statement statement
 *       statement
 *     */
 *
 *while style(9) suggests:
 *
 *    /*
 *     * Statement statement
 *     * statement
 *     */
 *
 *Not every comment in -4.1.2 needed changing.  A parser was written to
 *identify non-compliant comments.  Note that a few comments do not
 *follow either the TenDRA-4.1.2 style or style(9), or any style I can
 *recognize.  These need hand fixing.
 *
 *   E.  Indentation
 *   --------------------------------------------------
 *
 *   A elisp tendra-c-mode was created to define how code should be
 *indented.  The structure follows style(9) in the following regards:
 *
 *  (c-set-offset 'substatement-open 0)
 *  (setq c-indent-tabs-mode t
 *	c-indent-level 4
 *	c-argdecl-indent t
 *	c-tab-always-indent t
 *	backward-delete-function nil
 *	c-basic-offset 4
 *	tab-width 4))
 *
 *This means that substatement opening are not indented.  E.g.:
 *
 *   if (condition)
 *   {
 *
 *instead of
 *
 *   if (condition)
 *     {
 *
 *or even
 *
 *   if (condition) {
 *
 *Each statement is indented by a tab instead of a spaces.  Set your tab
 *stop to comply with style(9); see the vim resources in the tendra
 *tree.  I'll add the emacs mode support shortly.
 *
 *No doubt, a function or two escaped change because of unusual
 *circumstances.  These must be hand fixed as well.
 *
 *III.  Things Not Changed
 *=========================
 *
 *    A large number of style(9) deficiencies remain.  These will
 *require a separate effort.  I decided to stop with the changes noted
 *above because:
 *
 *   0)  The script currently takes hours to run to completion even on
 *high-end consumer machines.
 *
 *   1)  We need to move on and fix other substantive problems.
 *
 *   2) The goal of this commit was *just* ossg removal; I took the
 *opportunity to get other major white-space issues out of the way.
 *
 *    I'll also note that despite this commit, a few ossg issues remain.
 *These include:
 *
 *   0) The ossg headers remain.  They contain useful flags needed by
 *other operations.  Additionally, the BUILD_ERRORS perl script still
 *generates ossg-compliant headers.  (This is being removed as we change
 *the build process.)
 *
 *   1) A few patches of code check for ossg flags: "if (ossg) etc."
 *These can be hand removed as well.
 *
 *   2) No doubt, a few ossg headers escaped the elisp script.  We can
 *address these seriatim.
 *
 *IV.  Testing
 *=========================
 *
 *    Without a complete build or test suite, it's difficult to
 *determine if these changes have introduced any bugs.  I've identified
 *several situations where removal of ossg caused bugs in sid and
 *calculus operations.  The elisp script avoids these situations; we
 *will hand edit a few files.
 *
 *    As is, the changes should behave properly; the source base builds
 *the same before and after the rmossg.el script is run.  Nonetheless,
 *please note that this commit changes over 23,000 PROTO declarations,
 *and countless line changes.  I'll work closely with any developers
 *affected by this change.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:49  release
 * First version to be checked into rolling release.
 *
 *Revision 1.1.1.1  1997/10/13 12:42:54  ma
 *First version.
 *
 *Revision 1.3  1997/09/25 06:45:13  ma
 *All general_proc tests passed
 *
 *Revision 1.2  1997/05/13 11:30:36  ma
 *Introduced make_comment for debug.
 *
 *Revision 1.1.1.1  1997/03/14 07:50:14  ma
 *Imported from DRA
 
 * Revision 1.1.1.1  1996/09/20  10:56:55  john
 *
 * Revision 1.2  1996/07/05  14:21:38  john
 * Changes for spec 3.1
 *
 * Revision 1.1.1.1  1996/03/26  15:45:13  john
 *
 * Revision 1.3  93/03/03  14:47:23  14:47:23  ra (Robert Andrews)
 * Regenerated file with overflow jumps added.
 * 
 * Revision 1.2  93/02/23  15:44:40  15:44:40  ra (Robert Andrews)
 * Regenerated file (it is automatically generated), adding instructions
 * for binary coded decimal and extended arithmetic
 * 
 * Revision 1.1  93/02/23  15:42:19  15:42:19  ra (Robert Andrews)
 * Initial revision
 * 
 *--------------------------------------------------------------------------
 */


/*
 *    THIS FILE IS AUTOMATICALLY GENERATED
 */


#ifndef INSTRUCTIONS_INCLUDED
#define INSTRUCTIONS_INCLUDED

#define  LPREFIX		'L'
#define  is_local(X)		(*(X) == LPREFIX)

#define  m_label_ins		0
#define  m_extern_ins		1
#define  m_ignore_ins		2
#define  m_as_align4		3
#define  m_as_assign		4
#define  m_as_byte		5
#define  m_as_short		6
#define  m_as_long		7
#define  m_as_float		8
#define  m_as_double		9
#define  m_as_space		10
#define  m_as_global		11
#define  m_as_common		12
#define  m_as_local		13
#define  m_as_text		14
#define  m_as_data		15
#define  m_as_bss		16
#define  m_abcd			17
#define  m_addb			18
#define  m_addw			19
#define  m_addl			20
#define  m_addqb		21
#define  m_addqw		22
#define  m_addql		23
#define  m_addxb		24
#define  m_addxw		25
#define  m_addxl		26
#define  m_andb			27
#define  m_andw			28
#define  m_andl			29
#define  m_aslb			30
#define  m_aslw			31
#define  m_asll			32
#define  m_asrb			33
#define  m_asrw			34
#define  m_asrl			35
#define  m_bclr			36
#define  m_bfexts		37
#define  m_bfextu		38
#define  m_bfins		39
#define  m_bset			40
#define  m_btstb		41
#define  m_btst			42
#define  m_btstl		43
#define  m_call			44
#define  m_clrb			45
#define  m_clrw			46
#define  m_clrl			47
#define  m_cmpb			48
#define  m_cmpw			49
#define  m_cmpl			50
#define  m_cmpmb		51
#define  m_cmpmw		52
#define  m_cmpml		53
#define  m_dbf			54
#define  m_divsl		55
#define  m_divsll		56
#define  m_divul		57
#define  m_divull		58
#define  m_dont_know		59
#define  m_eorb			60
#define  m_eorw			61
#define  m_eorl			62
#define  m_extw			63
#define  m_extl			64
#define  m_extbl		65
#define  m_fabss		66
#define  m_fabsd		67
#define  m_fabsx		68
#define  m_fadds		69
#define  m_faddd		70
#define  m_faddx		71
#define  m_fcmps		72
#define  m_fcmpd		73
#define  m_fcmpx		74
#define  m_fdivs		75
#define  m_fdivd		76
#define  m_fdivx		77
#define  m_fints		78
#define  m_fintd		79
#define  m_fintx		80
#define  m_fintrzs		81
#define  m_fintrzd		82
#define  m_fintrzx		83
#define  m_fmovel		84
#define  m_fmoves		85
#define  m_fmoved		86
#define  m_fmovex		87
#define  m_fmovemx		88
#define  m_fmuls		89
#define  m_fmuld		90
#define  m_fmulx		91
#define  m_fnegx		92
#define  m_fsubs		93
#define  m_fsubd		94
#define  m_fsubx		95
#define  m_ftstx		96
#define  m_jmp			97
#define  m_lea			98
#define  m_linkw		99
#define  m_linkl		100
#define  m_lslb			101
#define  m_lslw			102
#define  m_lsll			103
#define  m_lsrb			104
#define  m_lsrw			105
#define  m_lsrl			106
#define  m_movb			107
#define  m_movw			108
#define  m_movl			109
#define  m_moveml		110
#define  m_moveq		111
#define  m_mulsw		112
#define  m_mulsl		113
#define  m_muluw		114
#define  m_mulul		115
#define  m_nbcd			116
#define  m_negb			117
#define  m_negw			118
#define  m_negl			119
#define  m_negxb		120
#define  m_negxw		121
#define  m_negxl		122
#define  m_nop			123
#define  m_notb			124
#define  m_notw			125
#define  m_notl			126
#define  m_orb			127
#define  m_orw			128
#define  m_orl			129
#define  m_pack			130
#define  m_pea			131
#define  m_rolb			132
#define  m_rolw			133
#define  m_roll			134
#define  m_rorb			135
#define  m_rorw			136
#define  m_rorl			137
#define  m_roxlb		138
#define  m_roxlw		139
#define  m_roxll		140
#define  m_roxrb		141
#define  m_roxrw		142
#define  m_roxrl		143
#define  m_rts			144
#define  m_sbcd			145
#define  m_subb			146
#define  m_subw			147
#define  m_subl			148
#define  m_subqb		149
#define  m_subqw		150
#define  m_subql		151
#define  m_subxb		152
#define  m_subxw		153
#define  m_subxl		154
#define  m_tstb			155
#define  m_tstw			156
#define  m_tstl			157
#define  m_unlk			158
#define  m_unpk			159
#define  m_dd_normal		160
#define  m_dd_special		161
#define  m_dd_exit		162
#define  m_dd_start		163
#define  m_dd_vt		164
#define  m_dd_lntt		165
#define  m_dd_gntt		166
#define  m_dd_vtbytes		167
#define  m_dd_align		168
#define  m_dd_array		169
#define  m_dd_begin		170
#define  m_dd_const		171
#define  m_dd_dvar		172
#define  m_dd_end		173
#define  m_dd_entry		174
#define  m_dd_enum		175
#define  m_dd_field		176
#define  m_dd_file		177
#define  m_dd_fparam		178
#define  m_dd_function		179
#define  m_dd_functype		180
#define  m_dd_import		181
#define  m_dd_label		182
#define  m_dd_memenum		183
#define  m_dd_module		184
#define  m_dd_pointer		185
#define  m_dd_set		186
#define  m_dd_srcfile		187
#define  m_dd_struct		188
#define  m_dd_subrange		189
#define  m_dd_svar		190
#define  m_dd_tagdef		191
#define  m_dd_typedef		192
#define  m_dd_union		193
#define  m_dd_variant		194
#define  m_stabs		195
#define  m_stabd		196
#define  m_stabn		197
#define  m_bcc			198
#define  m_bcs			199
#define  m_beq			200
#define  m_bge			201
#define  m_bgt			202
#define  m_bhi			203
#define  m_ble			204
#define  m_bls			205
#define  m_blt			206
#define  m_bne			207
#define  m_bra			208
#define  m_bvc			209
#define  m_bvs			210
#define  m_fbeq			211
#define  m_fbge			212
#define  m_fbgt			213
#define  m_fble			214
#define  m_fblt			215
#define  m_fbne			216
#define  m_fbnge		217
#define  m_fbngt		218
#define  m_fbnle		219
#define  m_fbnlt		220
#define  m_bccb			221
#define  m_bcsb			222
#define  m_beqb			223
#define  m_bgeb			224
#define  m_bgtb			225
#define  m_bhib			226
#define  m_bleb			227
#define  m_blsb			228
#define  m_bltb			229
#define  m_bneb			230
#define  m_brab			231
#define  m_bvcb			232
#define  m_bvsb			233
#define  m_fbeqb		234
#define  m_fbgeb		235
#define  m_fbgtb		236
#define  m_fbleb		237
#define  m_fbltb		238
#define  m_fbneb		239
#define  m_fbngeb		240
#define  m_fbngtb		241
#define  m_fbnleb		242
#define  m_fbnltb		243
#define  m_bccw			244
#define  m_bcsw			245
#define  m_beqw			246
#define  m_bgew			247
#define  m_bgtw			248
#define  m_bhiw			249
#define  m_blew			250
#define  m_blsw			251
#define  m_bltw			252
#define  m_bnew			253
#define  m_braw			254
#define  m_bvcw			255
#define  m_bvsw			256
#define  m_fbeqw		257
#define  m_fbgew		258
#define  m_fbgtw		259
#define  m_fblew		260
#define  m_fbltw		261
#define  m_fbnew		262
#define  m_fbngew		263
#define  m_fbngtw		264
#define  m_fbnlew		265
#define  m_fbnltw		266
#define  m_bccl			267
#define  m_bcsl			268
#define  m_beql			269
#define  m_bgel			270
#define  m_bgtl			271
#define  m_bhil			272
#define  m_blel			273
#define  m_blsl			274
#define  m_bltl			275
#define  m_bnel			276
#define  m_bral			277
#define  m_bvcl			278
#define  m_bvsl			279
#define  m_fbeql		280
#define  m_fbgel		281
#define  m_fbgtl		282
#define  m_fblel		283
#define  m_fbltl		284
#define  m_fbnel		285
#define  m_fbngel		286
#define  m_fbngtl		287
#define  m_fbnlel		288
#define  m_fbnltl		289

#ifndef tdf3
#define  m_trap                 290
#define  m_trapcc               291
#define  m_trapcs               292
#define  m_trapeq               293
#define  m_trapge               294
#define  m_trapgt               295
#define  m_traphi               296
#define  m_traple               297
#define  m_trapls               298
#define  m_traplt               299
#define  m_trapne               300
#define  m_trapt                301
#define  m_trapvc               302
#define  m_trapvs               303
#define  m_trapv                304
#define  m_comment              305
#endif

#define  ml_add			m_addb, m_addw, m_addl
#define  ml_addq		m_addqb, m_addqw, m_addql
#define  ml_addx		m_addxb, m_addxw, m_addxl
#define  ml_and			m_andb, m_andw, m_andl
#define  ml_asl			m_aslb, m_aslw, m_asll
#define  ml_asr			m_asrb, m_asrw, m_asrl
#define  ml_clr			m_clrb, m_clrw, m_clrl
#define  ml_cmp			m_cmpb, m_cmpw, m_cmpl
#define  ml_cmpm		m_cmpmb, m_cmpmw, m_cmpml
#define  ml_eor			m_eorb, m_eorw, m_eorl
#define  ml_fabs		m_fabss, m_fabsd, m_fabsx
#define  ml_fadd		m_fadds, m_faddd, m_faddx
#define  ml_fcmp		m_fcmps, m_fcmpd, m_fcmpx
#define  ml_fdiv		m_fdivs, m_fdivd, m_fdivx
#define  ml_fint		m_fints, m_fintd, m_fintx
#define  ml_fintrz		m_fintrzs, m_fintrzd, m_fintrzx
#define  ml_fmove		m_fmoves, m_fmoved, m_fmovex
#define  ml_fmul		m_fmuls, m_fmuld, m_fmulx
#define  ml_fsub		m_fsubs, m_fsubd, m_fsubx
#define  ml_lsl			m_lslb, m_lslw, m_lsll
#define  ml_lsr			m_lsrb, m_lsrw, m_lsrl
#define  ml_mov			m_movb, m_movw, m_movl
#define  ml_neg			m_negb, m_negw, m_negl
#define  ml_negx		m_negxb, m_negxw, m_negxl
#define  ml_not			m_notb, m_notw, m_notl
#define  ml_or			m_orb, m_orw, m_orl
#define  ml_rol			m_rolb, m_rolw, m_roll
#define  ml_ror			m_rorb, m_rorw, m_rorl
#define  ml_roxl		m_roxlb, m_roxlw, m_roxll
#define  ml_roxr		m_roxrb, m_roxrw, m_roxrl
#define  ml_sub			m_subb, m_subw, m_subl
#define  ml_subq		m_subqb, m_subqw, m_subql
#define  ml_subx		m_subxb, m_subxw, m_subxl
#define  ml_tst			m_tstb, m_tstw, m_tstl

#define  is_jump(X)		((X) >= m_bcc && (X) <= m_fbnltl)
#define  is_unsized(X)	((X) < m_bccb)
#define  byte_jump		(m_bccb - m_bcc)
#define  word_jump		(m_bccw - m_bcc)
#define  long_jump		(m_bccl - m_bcc)
#define  bra2trap(X)          (X + (m_trapcc - m_bcc))
#define  is_simple(X)		((X) < m_dd_normal)

#endif

