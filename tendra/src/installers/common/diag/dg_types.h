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
 *$Revision$
 *$Log$
 *Revision 1.2  2002/11/21 22:31:05  nonce
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
 * Revision 1.2  1998/03/11  11:03:31  pwe
 * DWARF optimisation info
 *
 * Revision 1.1.1.1  1998/01/17  15:55:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.8  1998/01/11  18:44:58  pwe
 * consistent new/old diags
 *
 * Revision 1.7  1998/01/09  09:29:50  pwe
 * prep restructure
 *
 * Revision 1.6  1997/12/04  19:36:34  pwe
 * ANDF-DE V1.9
 *
 * Revision 1.5  1997/11/06  09:17:46  pwe
 * ANDF-DE V1.8
 *
 * Revision 1.4  1997/10/28  10:12:35  pwe
 * local location support
 *
 * Revision 1.3  1997/10/23  09:21:12  pwe
 * ANDF-DE V1.7 and extra diags
 *
 * Revision 1.2  1997/10/10  18:16:42  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.1  1997/08/23  13:26:56  pwe
 * initial ANDF-DE
 *
 ***********************************************************************/
#ifndef dg_types_key
#define dg_types_key 1

#include "dg_first.h"



typedef dg_info dg;
#define nildiag (dg_info)0

typedef struct dg_tag_t * dg_tag;
typedef struct dg_comp_t * dg_compilation;

typedef dg_name dg_name_list;
typedef dg dg_list;

typedef dg_tag dg_tag_option;
typedef dg_type dg_type_option;
typedef dg_name dg_name_option;
typedef dg_filename dg_filename_option;

typedef struct
{
	dg_name_list		list;
	dg_tag		tg;
} dg_namelist;

typedef struct
{
	int			len;
	dg_type *		array;
} dg_type_list;

typedef dg_type_list dg_type_list_option;

typedef struct
{
	int			len;
	dg_tag *		array;
} dg_tag_list;


typedef struct
{
	int			len;
	char **		array;
} string_list;


struct file_t
{
	long			file_dat;
	char *		file_host;
	char *		file_path;
	char *		file_name;
	struct file_t *	another;
	int			index;
};

typedef enum
{
	SP_NULL = 0,
	SP_SHORT,
	SP_SPAN,
	SP_FILE,
	SP_GLOB
} dg_sourcepos_key;

typedef struct
{
	dg_sourcepos_key	sp_key;
	dg_filename		file;
	dg_filename		to_file;
	long			from_line;
	long			to_line;
	short			from_column;
	short			to_column;
} dg_sourcepos;

typedef struct
{
	dg_filename		file;
	long			line;
	short			column;
} short_sourcepos;

typedef dg_sourcepos dg_sourcepos_option;

typedef struct dg_dflt
{
	exp			val;
	dg_sourcepos		span;
	long			lab;
	struct dg_dflt *	next;
} dg_default;

typedef dg_default *	dg_default_option;

typedef struct dg_con
{
	dg_tag		refmem;
	int			is_val;
	union {
		dg_type		typ;
		exp			val;
	} u;
	struct dg_con *	next;
} * dg_constraint;

typedef dg_constraint	dg_constraint_list;
typedef dg_constraint	dg_constraint_list_option;


typedef enum
{
	DG_ACC_NONE = 0,
	DG_ACC_PUB,
	DG_ACC_PROT,
	DG_ACC_PRIV,
	DG_ACC_LOC
} dg_accessibility;
typedef dg_accessibility dg_accessibility_option;

typedef enum
{
	DG_VIRT_NONE = 0,
	DG_VIRT_VIRT,
	DG_VIRT_PURE
} dg_virtuality;
typedef dg_virtuality dg_virtuality_option;


typedef enum
{
	DG_ID_NONE = 0,
	DG_ID_SRC,
	DG_ID_EXT,
	DG_ID_ANON,
	DG_ID_ARTFL,
	DG_ID_INST
} dg_idname_key;

typedef struct
{
	dg_idname_key		id_key;
	union
	{
		char *		nam;
		struct dg_inst_t *	instance;
	} idd;
} dg_idname;
typedef dg_idname dg_idname_option;

typedef struct dg_inst_t
{
	dg_idname		nam;
	dg_idname		spec;
	short_sourcepos	whence;
	dg_name_list		params;
} dg_instantn;

typedef union
{
	dg_tag	tg;
	exp		x;
} tg_or_exp;

typedef struct
{
	int		is_ref;
	tg_or_exp	u;
	shape		sha;
} dg_bound;

typedef enum
{
	DG_DIM_NONE,
	DG_DIM_TYPE,
	DG_DIM_BOUNDS
} dg_dim_key;

typedef struct
{
	int			d_key	: 8;
	int			low_ref	: 1;
	int			hi_ref	: 1;
	int			hi_cnt	: 1;
	long			count;
	dg_type		d_typ;
	shape			sha;
	tg_or_exp		lower;
	tg_or_exp		upper;
	dg_tag		tg;
} dg_dim;

typedef dg_dim dg_dim_option;

typedef struct
{
	int			len;
	dg_dim *		array;
} dg_dim_list;

typedef struct
{
	char *		enam;
	short_sourcepos	pos;
	exp			value;
	int			is_chn	: 1;
	int			chn	: 8;
	dg_tag		tg;
} dg_enum;

typedef struct
{
	int			len;
	dg_enum *		array;
} dg_enum_list;

typedef enum
{
	DG_CM_FIELD,
	DG_CM_FN,
	DG_CM_INDIRECT,
	DG_CM_STAT
} dg_cm_key;

typedef struct
{
	dg_cm_key		cm_key;
	union
	{
		struct
		{
			char *		fnam;
			short_sourcepos	f_pos;
			dg_type		f_typ;
			exp		f_offset;
			struct dg_dflt *	dflt;
			int		acc	: 4;
			int		discr	: 1;
		} cm_f;
		struct
		{
			dg_name		fn;
			exp		slot;
		} cm_fn;
		struct
		{
			char *		nam;
			short_sourcepos	pos;
			dg_type		typ;
			exp		ind_loc;
		} cm_ind;
		dg_name		cm_stat;
	} d;
	dg_tag		tg;
} dg_classmem;

typedef struct
{
	int			len;
	dg_classmem *		array;
} dg_classmem_list;

typedef struct
{
	exp			lower;
	exp			upper;
} dg_discrim;

typedef struct
{
	int			len;
	dg_discrim *		array;
} dg_discrim_list;

typedef struct
{
	dg_discrim_list	discr;
	dg_classmem_list	fields;
} dg_variant;

typedef struct
{
	int			len;
	dg_variant *		array;
} dg_variant_list;

typedef enum
{
	DG_V_D,
	DG_V_S,
	DG_V_T
} dg_v_key;

typedef struct
{
	dg_v_key		v_key;
	union
	{
		dg_classmem		d;
		dg_tag		s;
		dg_type		t;
	} u;
	dg_variant_list	vnts;
} dg_varpart;

typedef dg_varpart * dg_varpart_option;


typedef enum
{
	DG_NO_MODE = 0,
	DG_IN_MODE,
	DG_OUT_MODE,
	DG_INOUT_MODE
} dg_param_mode;
typedef dg_param_mode dg_param_mode_option;

typedef struct
{
	char *		pnam;
	short_sourcepos	ppos;
	dg_param_mode		pmode;
	dg_type		p_typ;
	dg_default *		p_dflt;
} dg_param;

typedef struct
{
	int			len;
	dg_param *		array;
} dg_param_list;

typedef struct
{
	dg_tag		base;
	short_sourcepos	pos;
	exp			location;
	int			acc	: 8;
	int			virt	: 8;
} dg_class_base;

typedef struct
{
	int			len;
	dg_class_base *	array;
} dg_class_base_list;

typedef struct
{
	dg_class_base_list	inherits;
	dg_classmem_list	members;
	dg_tag_list		friends;
	dg_tag		vt_s;
	dg_tag		vt_d;
	dg_tag		rtti_s;
	dg_tag		rtti_d;
} class_data;

typedef struct
{
	dg_name_list		entries;
	dg_tag		id;
	dg_tag		cb;
	dg_classmem_list	members;
} task_data;			/* task or synchronised type */


typedef union
{
    long	l;
    char *	s;
} lab_union;

typedef enum
{
	NO_LAB = 0,
	LAB_STR,
	LAB_CODE,
	LAB_D
} dg_lab_key;

typedef struct
{
	lab_union		u;
	int			k;
} ext_lab;

typedef enum
{
	NO_WH = 0,
	WH_STR,
	WH_CODELAB,
	WH_REG,
	WH_REGOFF
} dg_where_key;

typedef struct
{
	lab_union		u;
	long			o;
	dg_where_key		k;
} dg_where;


typedef enum
{
	DGT_TAGGED,
	DGT_BASIC,
	DGT_QUAL,	/* ptr, ref and qual */
	DGT_ARRAY,
	DGT_SUBR,
	DGT_ENUM,
	DGT_STRUCT,	/* includes union */
	DGT_CLASS,
	DGT_A_TASK,
	DGT_A_SYNCH,
	DGT_PMEM,
	DGT_CONS,	/* set and file */
	DGT_PROC,
	DGT_BITF,
	DGT_FIXED,
	DGT_FLDIG,
	DGT_MOD,
	DGT_STRING,
	DGT_UNKNOWN
} dg_type_key;

typedef enum
{
	DG_ADR_T,
	DG_BOOL_T,
	DG_CHAR_T,
	DG_INT_T,
	DG_FLOAT_T
} dg_basic_type_key;

typedef enum
{
	DG_PTR_T = 0,
	DG_HPPTR_T,
	DG_REF_T,
	DG_PACK_T,
	DG_CONST_T,
	DG_VOL_T,
	DG_ALIAS_T,
	DG_CLWID_T,
	DG_LIM_T,
	N_DG_QUAL_TYPES
} dg_qual_type_key;

typedef dg_qual_type_key dg_qualifier;

typedef enum
{
	DG_SET_T,
	DG_FILE_T
} dg_cons_type_key;

struct dg_type_t
{
	dg_type_key		key;
	ext_lab		outref;
	union
	{
		dg_tag		t_tag;
		struct
		{
			dg_basic_type_key	b_key;
			char *		tnam;
			shape		b_sh;
		} t_bas;
		struct
		{
			dg_qual_type_key	q_key;
			dg_type		typ;
			dg_type		another; /* list q_keys to avoid repeat */
		} t_qual;
		struct
		{
			dg_type		elem_type;
			exp		stride;
			bool		rowm;
			dg_dim_list	dims;
		} t_arr;
		dg_dim		t_subr;
		struct
		{
			char *		tnam;
			short_sourcepos	tpos;
			dg_enum_list	values;
			shape		sha;
		} t_enum;
		struct
		{
			dg_idname		idnam;
			short_sourcepos	tpos;
			bool		is_union;
			shape		sha;
			union
			{
				dg_classmem_list  fields;
				class_data *	cd;
				task_data *	td;
			} u;
			dg_varpart_option	vpart;
		} t_struct;
		struct
		{
			dg_tag		pclass;
			dg_type		memtyp;
			shape		sha;
		} t_pmem;
		struct
		{
			dg_cons_type_key	c_key;
			dg_type		typ;
			shape		sha;
		} t_cons;
		struct
		{
			dg_param_list	params;
			dg_type		res_type;
			procprops		prps;
			unsigned int	lang	: 16;
			unsigned int	ccv	: 8;
			int		knowpro	: 1;
			int		yespro	: 1;
		} t_proc;
		struct
		{
			dg_type		expanded;
			shape		sha;
			bitfield_variety	bv;
			dg_type		another; /* list all bitfields to avoid repeat */
		} t_bitf;
		struct
		{
			dg_type		rept;
			exp		small;
			exp		delta;
			exp		digits;	/* or size of modular type */
		} t_adanum;
		struct
		{
			dg_tag		ct;
			exp		lb;
			exp		length;
		} t_string;
	} data;
	struct dg_more_t *	mor;
	dg_type		type_queue;
};


typedef enum
{
	DGN_OBJECT,
	DGN_PROC,
	DGN_MODULE,
	DGN_NSP,
	DGN_SUBUNIT,
	DGN_IMPORT,
	DGN_TYPE,
	DGN_ENTRY
} dg_name_key;

struct dg_name_t
{
	dg_name_key		key;
	dg_idname		idnam;
	short_sourcepos	whence;
	union
	{
		struct
		{
			dg_type		typ;
			exp		obtain_val;
			dg_param *	p; 
		} n_obj;
		struct
		{
			dg_type		typ;
			exp		obtain_val;
			dg_info		params;		/* DGA_PARAMS */
		} n_proc;
		struct
		{
			dg_name_list	members;
			exp		init;
		} n_mod;
		struct
		{
			dg_tag		parent;
			dg_name		sub;
			int		acc	: 8;
			int		child	: 1;
			int		split	: 1;
		} n_sub;
		struct
		{
			dg_tag		import;
			int		ik;
			dg_type		i_typ;
		} n_imp;
		struct
		{
			dg_type		raw;
			dg_type		named;
			dg_constraint	constraints;
		} n_typ;
	} data;
	struct dg_more_t *	mor;
	dg_name		next;
};

typedef struct dg_more_t
{
	dg_tag		this_tag;
	dg_tag		inline_ref;
	dg_tag		refspec;
	dg_tag		elabn;
	dg_type_list		exptns;		/* proc_name */
	short_sourcepos	end_pos;	/* proc_name */
	dg_dim *		en_family;	/* proc_name */
	exp			vslot;		/* proc_name */
	exp			repn;
	int			acc	: 4;
	int			virt	: 4;	/* proc_name */
	int			isinline : 1;	/* proc_name */
	int			prognm	: 1;	/* proc_name */
	int			isconst	: 1;	/* obj_name */
	int			isspec	: 1;
	int			issep	: 1;
	int			isnew	: 1;	/* types */
	int			aderiv	: 1;	/* types */
} * dg_more_name;


typedef struct ret_t
{
	long			lab;
	long			over;
	struct ret_t *	next;
} retrec;

typedef struct ob_s
{
	dg_tag		tg;
	int			ass;
	struct ob_s *		next;
} objset;


typedef enum	/* These are optimisation kinds */
{
	DGD_NONE = 0,
	DGD_DEAD,		/* 1 OpK_Unreachable */
	DGD_REM,		/* 2 OpK_Copy_Propagation */
	DGD_RDND,		/* 3 OpK_Redundant - no side effect */
	DGD_CNST,		/* 4 OpK_Const_Eval */
	DGD_MOVD,		/* 5 OpK_Structural */
	DGD_EXTRACT		/* 6 OpK_Loop_Const */
	/* 7 OpK_Loop_Invariant assignments */
	/* 8 OpK_Index_Reduction */
	/* 9 OpK_Loop_Unroll */
} dg_detch_key;

typedef struct dgt_s
{
	dg_detch_key		why;
	dg_info		info;
	dg_tag		tg;
	struct dgt_s *	next;
	struct dgt_s *	sub;
} detch_info;


typedef enum
{
	DGR_SEL,
	DGR_ACC,
	DGR_RTS,
	DGR_ALT,
	DGR_SGD,
	DGR_TRIG,
	DGR_ABTL,
	DGR_REQUE
} dg_rvs_key;


typedef enum
{
	DGA_NONE = 0,
	DGA_PARAMS,		/* params_dg */
	DGA_COMP,		/* compilation_dg, source_language_dg */
	DGA_SRC,		/* sourcepos_dg, singlestep_dg */
	DGA_SCOPE,		/* lexical_block_dg */
	DGA_EXTRA,		/* lexical_fragment */
	DGA_LAB,		/* label_dg */
	DGA_NAME,		/* name_decl_dg */
	DGA_WITH,		/* with_dg */
	DGA_CALL,		/* call_dg, apply_(gen)_tag */
	DGA_INL_CALL,		/* inline_call_dg */
	DGA_INL_RES,		/* inline_result_dg */
	DGA_X_TRY,		/* exception_scope_dg */
	DGA_X_CATCH,		/* exception_handler_dg */
	DGA_X_RAISE,		/* raise_dg */
	DGA_BRANCH,		/* branch_dg, case_tag */
	DGA_TEST,		/* test_dg, test_tag */
	DGA_JUMP,		/* jump_dg, goto_tag */
	DGA_LJ,		/* long_jump_dg, long_jump_tag, goto_lv_tag,
				 *				return_to_label_tag, tail_call_tag */
	DGA_BEG,		/* statement_part_dg */
	DGA_DEST,		/* destructor_dg */
	DGA_RVS,		/* Ada rendevous (various) */
	DGA_BAR,		/* barrier_dg */
	DGA_DETCH,		/*   detached_dg ? */
	DGA_MOVD,		/*    ditto */
	DGA_HOIST,		/*  (as MOVD but no ref to it) */
	DGA_OPTIM,		/*   optimisation_dg ? */
	
	DGA_PRC,		/* used when outputting proc */
	DGA_REMVAL		/* removed assign constants */
} dg_info_key;

struct dg_info_t
{
	dg_info_key		key;
	union
	{
		struct
		{
			dg_name_list	args;
			exp		o_env;
			long		b_start;
		} i_param;
		struct
		{
			bool		is_tag;
			union
			{
				dg_tag		comp_tag;
				long		comp_lang;
			} corl;
			long		lo_pc;
			long		hi_pc;
		} i_comp;
		struct
		{
			bool		is_stmt;
			short_sourcepos	startpos;
			short_sourcepos	endpos;
			long		start;
			long		end;
		} i_src;
		struct
		{
			char *		lexname;
			short_sourcepos	lexpos;
			short_sourcepos	endpos;
			long		start;
			long		begin_st;
			long		end;
		} i_scope;
		struct
		{
			dg_name		dnam;
			long		scope_start;
		} i_nam;
		struct
		{
			dg_type		w_typ;
			exp		w_exp;
			long		lo_pc;
			long		hi_pc;
		} i_with;
		struct
		{
			char *		clnam;
			short_sourcepos	pos;
			int		ck;
			long		brk;
			dg_where		p;
		} i_call;
		struct
		{
			dg_tag		proc;
			dg_name_list	args;
			int		ck;
			long		lo_pc;
			long		hi_pc;
			dg_info		resref;
		} i_inl;
		struct
		{
			dg_tag		call;
			long		brk;
			dg_where		res;
			dg_info		next;
		} i_res;
		struct
		{
			dg_tag_list	hl;
			long		lo_pc;
			long		hi_pc;
		} i_try;
		struct
		{
			dg_name		ex;
			long		lo_pc;
			long		hi_pc;
		} i_catch;
		struct
		{
			short_sourcepos	pos;
			dg_type		x_typ;
			exp		x_val;
		} i_raise;
		struct
		{
			short_sourcepos	pos;
			long		brk;
			exp		val;
		} i_dest;
		struct
		{
			short_sourcepos	pos;
			long		brk;
			long		cont;
		} i_brn;
		struct
		{
			short_sourcepos	pos;
			long		brk;
			ext_lab		jlab;
			long		cont;
			int		inv;
		} i_tst;
		struct
		{
			short_sourcepos	pos;
			long		brk;
			dg_where		j;
		} i_lj;
		struct
		{
			short_sourcepos	pos;
			dg_tag		entry;
			long		lo_pc;
			long		hi_pc;
		} i_bar;
		struct
		{
			long		prc_start;
			long		prc_end;
			retrec *		returns;
			dg_info		p;	/* DGA_PARAMS */
			dg_info           barrier;
		} i_prc;
		struct
		{
			int		rvs_key	: 8;
			int		n_code	: 2;
			int		has_iv	: 2;
			int		holder	: 1;
			int		alt	: 1;
			int		w_abort	: 1;
			int		async	: 1;
			int		kind	: 16;
			short_sourcepos	pos;
			long		lo_pc;
			long		hi_pc;
			union {
				dg_tag		tg;
				dg_info		iv;
			} u;
			exp		info_e;
			dg_tag		en;
			union {
				dg_name_list	p;
				exp		e;
			} u2;
		} i_rvs;
		dg_tag		i_tg;
		struct
		{
			int		posn;	/* pre <0, post >0 */
			detch_info *	dl;
		} i_detch;
		struct
		{
			int		reason;
			int		lost;
			dg_tag		tg;
			long		lo_pc;
			long		hi_pc;
		} i_movd;
		struct
		{
			int		reason;
			objset *		objs;
			long		lo_pc;
			long		hi_pc;
		} i_optim;
		struct
		{
			exp		var;	/* detached */
			exp		val;
			long		lo_pc;
		} i_remval;
	} data;
	dg_tag		this_tag;
	dg_info		more;
};


typedef enum
{
	DGK_NONE = 0,
	DGK_TYPE,
	DGK_NAME,
	DGK_INFO,
	DGK_COMP,
	DGK_CLASSMEM,
	DGK_DIM,
	DGK_ENUM,
	DGK_NAMELIST
} dg_tag_key;

typedef struct dg_tag_t
{
	union
	{
		dg_type		typ;
		dg_name		nam;
		dg_info		info;
		dg_compilation	comp;
		dg_name_list *	nl;
	} p;
	ext_lab		outref;
	long			abstract_lab;
	int			key	: 8;
	int			done	: 1;
	int			needed	: 1;
	int			any_inl	: 1;
	dg_tag		copy;
#if 0
	exp			e;
#endif
} dgtag_struct;


typedef string_list dg_idname_list;

typedef enum
{
	DGM_FN,
	DGM_OBJ,
	DGM_UNDEF,
	DGM_INC
} dg_mac_key;

typedef struct
{
	int			len;
	struct dg_mac_t *	array;
} dg_macro_list;

typedef struct dg_mac_t
{
	dg_mac_key		key;
	short_sourcepos	pos;
	union
	{
		struct
		{
			char *		nam;
			char *		defn;
			string_list	pms;
		} d;
		struct
		{
			dg_filename	file;
			dg_macro_list	macs;
		} i;
	} u;
} dg_macro;


struct dg_comp_t
{
	dg_filename		prim_file;
	string_list		comp_deps;
	long			date;
	short			language;
	short			id_case;
	char *		producer;
	dg_filename		comp_dir;
	string_list		options;
	dg_name_list		dn_list;
	dg_macro_list		macros;
	dg_compilation	another;
};



typedef struct
{
	int			present;	
	bool			val;
} bool_option;

typedef struct
{
	int			present;	
	shape			val;
} shape_option;

typedef struct
{
	int			present;	
	struct tok_define_t *	val;
} token_option;


typedef int dg_comp_props;
typedef int dg_append;
typedef dg_append dg_append_list;


#endif
