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


/*** main.c --- tld program main routine.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file contains the main routine for the TDF linker.  It performs
 * argument parsing, and then calls one of "builder_main", "contents_main",
 * "extract_main" or "linker_main" to do the actual work.  See the files in
 * the "frontends" directory for more details.
 *
 *** Change Log:
 * $Log$
 * Revision 1.2  2002/11/21 22:31:25  nonce
 * Remove ossg prototypes.  This commit is largely whitespace changes,
 * but is nonetheless important.  Here's why.
 *
 * I.  Background
 * =========================
 *
 *     The current TenDRA-4.1.2 source tree uses "ossg" prototype
 * conventions, based on the Open Systems Software Group publication "C
 * Coding Standards", DRA/CIS(SE2)/WI/94/57/2.0 (OSSG internal document).
 * The goal behind ossg prototypes remains admirable: TenDRA should
 * support platforms that lack ANSI compliant compilers.  The explicit
 * nature of ossg's prototypes makes macro substition easy.
 *
 *     Here's an example of one function:
 *
 *     static void uop
 * 	PROTO_N ( ( op, sha, a, dest, stack ) )
 * 	PROTO_T ( void ( *op ) PROTO_S ( ( shape, where, where ) ) X
 * 		  shape sha X exp a X where dest X ash stack )
 *     {
 *
 * tendra/src/installers/680x0/common/codec.c
 *
 *   The reasons for removing ossg are several, including:
 *
 *   0) Variables called 'X' present a problem (besides being a poor
 * variable name).
 *
 *   1) Few platforms lack ANSI-compliant compilers.  ISO-compliant
 * prototypes are easily handled by most every compiler these days.
 *
 *   2) Although TenDRA emphasizes portability, standards compliance is
 * the primary goal of the current project.  We should expect no less
 * from the compiler source code.
 *
 *   3) The benefits of complex prototypes are few, given parameter
 * promotion rules.  (Additionally, packing more types into int-sized
 * spaces tends to diminish type safety, and greatly complicates
 * debugging and testing.)
 *
 *   4) It would prove impractical to use an OSSG internal style document
 * in an open source project.
 *
 *   5) Quite frankly, ossg prototypes are difficult to read, but that's
 * certainly a matter of taste and conditioning.
 *
 * II.  Changes
 * =========================
 *
 *    This commit touches most every .h and .c file in the tendra source
 * tree.  An emacs lisp script (http://www.tendra.org/~nonce/tendra/rmossg.el)
 * was used to automate the following changes:
 *
 *    A.  Prototype Conversions.
 *    --------------------------------------------------
 *
 *    The PROTO_S, PROTO_Z, PROTO_N, PROTO_T, and PROTO_V macros were
 * rewritten to ISO-compliant form.  Not every file was touched.  The
 * files named ossg.h, ossg_api.h, code.c, coder.c and ossg_std.h were
 * left for hand editing.  These files provide header generation, or have
 * non-ossg compliant headers to start with.  Scripting around these
 * would take too much time; a separate hand edit will fix them.
 *
 *    B.  Statement Spacing
 *    --------------------------------------------------
 *
 *    Most of the code in the TenDRA-4.1.2 used extra spaces to separate
 * parenthetical lexemes.  (See the quoted example above.)  A simple
 * text substitution was made for:
 *
 *      Before            After
 * ===================================
 *
 *    if ( x )            if (x)
 *    if(x)               if (x)
 *    x = 5 ;             x = 5;
 *    ... x) )            ... x))
 *
 * All of these changes are suggested by style(9).  Additional, statement
 * spacing considerations were made for all of the style(9) keywords:
 * "if" "while" "for" "return" "switch".
 *
 * A few files seem to have too few spaces around operators, e.g.:
 *
 *       arg1*arg2
 *
 * instead of
 *
 *       arg1 * arg2
 *
 * These were left for hand edits and later commits, since few files
 * needed these changes.  (At present, the rmossg.el script takes 1 hour
 * to run on a 2GHz P4, using a ramdisk.  Screening for the 1% that
 * needed change would take too much time.)
 *
 *    C.  License Information
 *    --------------------------------------------------
 *
 * After useful discussion on IRC, the following license changes were
 * made:
 *
 *    1) Absent support for $License::BSD$ in the repository, license
 * and copyright information was added to each file.
 *
 *    2) Each file begins with:
 *
 *    Copyright (c) 2002, The Tendra Project <http://www.tendra.org>
 *    All rights reserved.
 *
 *    Usually, copyright stays with the author of the code; however, I
 * feel very strongly that this is a group effort, and so the tendra
 * project should claim any new (c) interest.
 *
 *    3) The comment field then shows the bsd license and warranty
 *
 *    4) The comment field then shows the Crown Copyright, since our
 * changes are not yet extensive enough to claim any different.
 *
 *    5) The comment field then closes with the $TenDRA$ tag.
 *
 *    D.  Comment Formatting
 *    --------------------------------------------------
 *
 * The TenDRA-4.1.2 code base tended to use comment in this form:
 *
 *     /*
 *        Statement statement
 *        statement
 *      */
 *
 * while style(9) suggests:
 *
 *     /*
 *      * Statement statement
 *      * statement
 *      */
 *
 * Not every comment in -4.1.2 needed changing.  A parser was written to
 * identify non-compliant comments.  Note that a few comments do not
 * follow either the TenDRA-4.1.2 style or style(9), or any style I can
 * recognize.  These need hand fixing.
 *
 *    E.  Indentation
 *    --------------------------------------------------
 *
 *    A elisp tendra-c-mode was created to define how code should be
 * indented.  The structure follows style(9) in the following regards:
 *
 *   (c-set-offset 'substatement-open 0)
 *   (setq c-indent-tabs-mode t
 * 	c-indent-level 4
 * 	c-argdecl-indent t
 * 	c-tab-always-indent t
 * 	backward-delete-function nil
 * 	c-basic-offset 4
 * 	tab-width 4))
 *
 * This means that substatement opening are not indented.  E.g.:
 *
 *    if (condition)
 *    {
 *
 * instead of
 *
 *    if (condition)
 *      {
 *
 * or even
 *
 *    if (condition) {
 *
 * Each statement is indented by a tab instead of a spaces.  Set your tab
 * stop to comply with style(9); see the vim resources in the tendra
 * tree.  I'll add the emacs mode support shortly.
 *
 * No doubt, a function or two escaped change because of unusual
 * circumstances.  These must be hand fixed as well.
 *
 * III.  Things Not Changed
 * =========================
 *
 *     A large number of style(9) deficiencies remain.  These will
 * require a separate effort.  I decided to stop with the changes noted
 * above because:
 *
 *    0)  The script currently takes hours to run to completion even on
 * high-end consumer machines.
 *
 *    1)  We need to move on and fix other substantive problems.
 *
 *    2) The goal of this commit was *just* ossg removal; I took the
 * opportunity to get other major white-space issues out of the way.
 *
 *     I'll also note that despite this commit, a few ossg issues remain.
 * These include:
 *
 *    0) The ossg headers remain.  They contain useful flags needed by
 * other operations.  Additionally, the BUILD_ERRORS perl script still
 * generates ossg-compliant headers.  (This is being removed as we change
 * the build process.)
 *
 *    1) A few patches of code check for ossg flags: "if (ossg) etc."
 * These can be hand removed as well.
 *
 *    2) No doubt, a few ossg headers escaped the elisp script.  We can
 * address these seriatim.
 *
 * IV.  Testing
 * =========================
 *
 *     Without a complete build or test suite, it's difficult to
 * determine if these changes have introduced any bugs.  I've identified
 * several situations where removal of ossg caused bugs in sid and
 * calculus operations.  The elisp script avoids these situations; we
 * will hand edit a few files.
 *
 *     As is, the changes should behave properly; the source base builds
 * the same before and after the rmossg.el script is run.  Nonetheless,
 * please note that this commit changes over 23,000 PROTO declarations,
 * and countless line changes.  I'll work closely with any developers
 * affected by this change.
 *
 * Revision 1.2  1998/02/06  17:05:29  release
 * Last minute pre-release polishing.
 *
 * Revision 1.1.1.1  1998/01/17  15:57:16  release
 * First version to be checked into rolling release.
 *
 * Revision 1.12  1997/11/05  14:39:35  smf
 * main.c:
 * 	- Updated "VERSION" number.
 *
 * Revision 1.11  1996/05/23  16:03:15  smf
 * main.c:
 * 	- updated version number.
 *
 * Revision 1.10  1996/03/27  10:42:35  smf
 * main.c:
 * 	- updated version number.
 *
 * Revision 1.9  1996/03/04  17:01:16  smf
 * main.c:
 * 	- updated version number.
 *
 * Revision 1.8  1995/12/04  11:51:32  smf
 * Updated version.
 *
 * Fixed version message to include architecture name banner.
 *
 * Revision 1.7  1995/09/22  08:35:00  smf
 * Updated version number.
 * Fixed problems with incomplete structure definitions (to shut "tcc" up).
 *
 * Revision 1.6  1995/09/08  16:10:50  smf
 * Updated version number.
 *
 * Revision 1.5  1995/07/07  15:31:46  smf
 * Updated to support TDF specification 4.0.
 *
 * Revision 1.4  1995/07/05  11:56:59  smf
 * Incremented version number.  Added release identification to version string.
 * Removed "build_tld" from CVS control.
 *
 * Revision 1.3  1994/12/12  11:41:40  smf
 * Upgrade VERSION to 3.6#2.
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.2  1994/08/23  09:38:19  smf
 * Fixed bug DR114:ids-too-long.  Updated linker build process.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:21  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
 **/

/****************************************************************************/

#include "os-interface.h"
#include "release.h"
#include "arg-data.h"
#include "arg-parse.h"
#include "builder.h"
#include "contents.h"
#include "debug.h"
#include "error.h"
#include "error-file.h"
#include "exception.h"
#include "extract.h"
#include "gen-errors.h"
#include "linker.h"
#include "rename-file.h"

#include "solve-cycles.h"

/*--------------------------------------------------------------------------*/

#define USAGE "\
\tusage: [mode] [option ...] file ...\n\
\twhere mode is one of: '-mc' (create library), '-ml' (link capsules),\n\
\t'-mt' (library table of contents) or '-mx' (extract from library),\n\
\tand option (for the current mode - default '-ml') is one of:"
#ifndef VERSION
#define VERSION "tld version 4.0#7"
#endif /* !defined (VERSION) */
#ifndef RELEASE
#define RELEASE "LOCAL"
#endif /* !defined (RELEASE) */
#ifndef BANNER
#define BANNER ""
#endif /* !defined (BANNER) */

/*--------------------------------------------------------------------------*/

#ifdef FS_NO_ENUM
typedef int ModeT, *ModeP;
#define MODE_BUILDER		(0)
#define MODE_CONTENTS		(1)
#define MODE_EXTRACT		(2)
#define MODE_LINKER		(3)
#else
typedef enum {
    MODE_BUILDER,
    MODE_CONTENTS,
    MODE_EXTRACT,
    MODE_LINKER
} ModeT, *ModeP;
#endif /* defined (FS_NO_ENUM) */

/*--------------------------------------------------------------------------*/

static BoolT    main_used_one_off = FALSE;
static BoolT    main_used_other   = FALSE;
static ArgDataT main_arg_data;

/*--------------------------------------------------------------------------*/

static void
main_print_version()
{
    write_cstring (ostream_error, VERSION);
    write_cstring (ostream_error, " (");
    write_cstring (ostream_error, RELEASE);
    write_cstring (ostream_error, ")");
    write_cstring (ostream_error, BANNER);
    write_newline (ostream_error);
    ostream_flush (ostream_error);
}

static void
main_handle_all(CStringP option, ArgUsageP usage,
				GenericP gclosure, BoolT enable)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_set_extract_all (&main_arg_data, enable);
}

static void
main_handle_all_hide_defd(CStringP option,
						  ArgUsageP usage,
						  GenericP gclosure,
						  BoolT enable)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_set_all_hide_defd (&main_arg_data, enable);
}

static void
main_handle_basename(CStringP option, ArgUsageP usage,
					 GenericP gclosure, BoolT enable)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_set_extract_basename (&main_arg_data, enable);
}

static void
main_handle_debug_file(CStringP option, ArgUsageP usage,
					   GenericP gclosure,
					   CStringP debug_file)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_set_debug_file (&main_arg_data, debug_file);
}

static void
main_handle_help(CStringP option, ArgUsageP usage,
				 GenericP gclosure)
{
    UNUSED (option);
    UNUSED (gclosure);
    main_used_one_off = TRUE;
    write_arg_usage (ostream_error, usage);
    write_newline (ostream_error);
    ostream_flush (ostream_error);
}

static void
main_handle_hide(CStringP option, ArgUsageP usage,
				 GenericP gclosure, CStringP shape,
				 CStringP name)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_add_hide (&main_arg_data, shape, name);
}

static void
main_handle_hide_defined(CStringP option,
						 ArgUsageP usage,
						 GenericP gclosure,
						 CStringP shape)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_add_hide_defined (&main_arg_data, shape);
}

static void
main_handle_index(CStringP option, ArgUsageP usage,
				  GenericP gclosure, BoolT enable)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_set_content_index (&main_arg_data, enable);
}

static void
main_handle_info(CStringP option, ArgUsageP usage,
				 GenericP gclosure, BoolT enable)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    if (enable) {
		error_set_min_report_severity (ERROR_SEVERITY_INFORMATION);
    } else {
		error_set_min_report_severity (ERROR_SEVERITY_ERROR);
    }
}

static void
main_handle_keep(CStringP option, ArgUsageP usage,
				 GenericP gclosure, CStringP shape,
				 CStringP name)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_add_keep (&main_arg_data, shape, name);
}

static void
main_handle_keep_all(CStringP option, ArgUsageP usage,
					 GenericP gclosure, CStringP shape)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_add_keep_all (&main_arg_data, shape);
}

static void
main_handle_library_file(CStringP option,
						 ArgUsageP usage,
						 GenericP gclosure,
						 CStringP library_file)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_add_library_file (&main_arg_data, library_file);
}

static void
main_handle_match_base(CStringP option, ArgUsageP usage,
					   GenericP gclosure,
					   BoolT enable)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_set_extract_match_base (&main_arg_data, enable);
}

static void
main_handle_output_file(CStringP option, ArgUsageP usage,
						GenericP gclosure,
						CStringP output_file)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_set_output_file (&main_arg_data, output_file);
}

static void
main_handle_library_path(CStringP option,
						 ArgUsageP usage,
						 GenericP gclosure,
						 CStringP directory)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_add_library_path (&main_arg_data, directory);
}

static void
main_handle_rename(CStringP option, ArgUsageP usage,
				   GenericP gclosure, CStringP shape,
				   CStringP from, CStringP to)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_parse_rename (&main_arg_data, shape, from, to);
}

static void
main_handle_rename_file(CStringP option, ArgUsageP usage,
						GenericP gclosure,
						CStringP name)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    rename_file_parse (name, &main_arg_data);
}

static void
main_handle_show_errors(CStringP option, ArgUsageP usage,
						GenericP gclosure)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_one_off = TRUE;
    write_error_file (ostream_output);
    ostream_flush (ostream_output);
}

static void
main_handle_size(CStringP option, ArgUsageP usage,
				 GenericP gclosure, BoolT enable)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_set_content_size (&main_arg_data, enable);
}

static void
main_handle_suppress(CStringP option, ArgUsageP usage,
					 GenericP gclosure, CStringP shape,
					 CStringP name)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_add_suppress (&main_arg_data, shape, name);
}

static void
main_handle_suppress_all(CStringP option,
						 ArgUsageP usage,
						 GenericP gclosure,
						 CStringP shape)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_add_suppress_all (&main_arg_data, shape);
}

static void
main_handle_suppress_mult(CStringP option,
						  ArgUsageP usage,
						  GenericP gclosure,
						  BoolT enable)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_set_suppress_mult (&main_arg_data, enable);
}

static void
main_handle_tdf_version(CStringP option, ArgUsageP usage,
						GenericP gclosure,
						BoolT enable)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_set_content_version (&main_arg_data, enable);
}

static void
main_handle_unit_file(CStringP option, ArgUsageP usage,
					  GenericP gclosure,
					  CStringP unit_file)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_set_unit_file (&main_arg_data, unit_file);
}

static void
main_handle_version(CStringP option, ArgUsageP usage,
					GenericP gclosure)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_one_off = TRUE;
    main_print_version ();
}

static void
main_handle_warning(CStringP option, ArgUsageP usage,
					GenericP gclosure, BoolT enable)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    if (enable) {
		error_set_min_report_severity (ERROR_SEVERITY_WARNING);
    } else {
		error_set_min_report_severity (ERROR_SEVERITY_ERROR);
    }
}

/*--------------------------------------------------------------------------*/

static EStringDataT main_description_strings [] = {
    UB {
		"description of all",
		"\n\tEnable/disable extraction of all capsules."
    } UE, UB {
		"description of all-hide-defined",
		"\n\tEnable/disable hiding of all external names of any shape that have a definition."
    } UE, UB {
		"description of basename",
		"\n\tEnable/disable extraction of capsules to their basename."
    } UE, UB {
		"description of debug-file",
		" FILE\n\tWrite debugging output to FILE."
    } UE, UB {
		"description of help",
		"\n\tDisplay an option summary for the current mode."
    } UE, UB {
		"description of hide",
		" SHAPE NAME\n\tHide the external SHAPE NAME."
    } UE, UB {
		"description of hide-defined",
		" SHAPE\n\tHide all external SHAPE names that have a definition."
    } UE, UB {
		"description of include-library",
		" LIBRARY\n\tInclude the contents of LIBRARY in the output library."
    } UE, UB {
		"description of index",
		"\n\tEnable/disable the display of the library index as well as the capsule names."
    } UE, UB {
		"description of info",
		"\n\tEnable/disable informational messages."
    } UE, UB {
		"description of keep",
		" SHAPE NAME\n\tEnsure that external SHAPE NAME is not hidden."
    } UE, UB {
		"description of keep-all",
		" SHAPE\n\tEnsure that no external SHAPE is hidden."
    } UE, UB {
		"description of library-file",
		" FILE\n\tUse FILE as a TDF library."
    } UE, UB {
		"description of l",
		"FILE\n\tUse FILE as a TDF library."
    } UE, UB {
		"description of match-basename",
		"\n\tEnable/disable matching capsules by their basename"
    } UE, UB {
		"description of output-file",
		" FILE\n\tWrite output to FILE (default 'library.tl')."
    } UE, UB {
		"description of path",
		" DIRECTORY\n\tAppend DIRECTORY to library search path."
    } UE, UB {
		"description of L",
		"DIRECTORY\n\tAppend DIRECTORY to library search path."
    } UE, UB {
		"description of rename",
		" SHAPE FROM TO\n\tRename SHAPE FROM to TO."
    } UE, UB {
		"description of rename-file",
		" FILE\n\tParse FILE as a rename file."
    } UE, UB {
		"description of size",
		"\n\tEnable/disable the display of the size of library capsules as well as their names."
    } UE, UB {
		"description of show-errors",
		"\n\tDisplay the current error table on the standard output."
    } UE, UB {
		"description of suppress",
		" SHAPE NAME\n\tDo not try to find a definition for SHAPE NAME."
    } UE, UB {
		"description of suppress-all",
		" SHAPE\n\tDo not try to find a definition for any SHAPE."
    } UE, UB {
		"description of suppress-mult",
		"\n\tEnable/disable the suppression of multiple definitions as library definitions."
    } UE, UB {
		"description of tdf-version",
		"\n\tEnable/disable the display of the version of a TDF library."
    } UE, UB {
		"description of unit-file",
		" FILE\n\tRead unit set names from FILE."
    } UE, UB {
		"description of version",
		"\n\tDisplay the version number on the standard error."
    } UE, UB {
		"description of warning",
		"\n\tEnable/disable warning messages."
    } UE, ERROR_END_STRING_LIST
};

#ifdef __TenDRA__
/* Some conversions to ArgProcP are slightly suspect */
#pragma TenDRA begin
#pragma TenDRA conversion analysis (pointer-pointer) off
#endif

static ArgListT main_builder_arg_list [] = {
    {
		"debug-file", 'd',			AT_FOLLOWING,
		(ArgProcP) main_handle_debug_file,	NIL (GenericP),
		UB "description of debug-file" UE
    }, {
		"help", '?',				AT_EMPTY,
		(ArgProcP) main_handle_help,		NIL (GenericP),
		UB "description of help" UE
    }, {
		"include-library", 'i',			AT_FOLLOWING,
		(ArgProcP) main_handle_library_file,	NIL (GenericP),
		UB "description of include-library" UE
    }, {
		"output-file", 'o',			AT_FOLLOWING,
		(ArgProcP) main_handle_output_file,	NIL (GenericP),
		UB "description of output-file" UE
    }, {
		"show-errors", 'e',			AT_EMPTY,
		(ArgProcP) main_handle_show_errors,	NIL (GenericP),
		UB "description of show-errors" UE
    }, {
		"suppress", 's',			AT_FOLLOWING2,
		(ArgProcP) main_handle_suppress,	NIL (GenericP),
		UB "description of suppress" UE
    }, {
		"suppress-all", 'S',			AT_FOLLOWING,
		(ArgProcP) main_handle_suppress_all,	NIL (GenericP),
		UB "description of suppress-all" UE
    }, {
		"suppress-mult", 'M',			AT_PROC_SWITCH,
		(ArgProcP) main_handle_suppress_mult,	NIL (GenericP),
		UB "description of suppress-mult" UE
    }, {
		"unit-file", 'u',			AT_FOLLOWING,
		(ArgProcP) main_handle_unit_file,	NIL (GenericP),
		UB "description of unit-file" UE
    }, {
		"version", 'v',				AT_EMPTY,
		(ArgProcP) main_handle_version,		NIL (GenericP),
		UB "description of version" UE
    }, ARG_PARSE_END_LIST
};

static ArgListT main_contents_arg_list [] = {
    {
		"debug-file", 'd',			AT_FOLLOWING,
		(ArgProcP) main_handle_debug_file,	NIL (GenericP),
		UB "description of debug-file" UE
    }, {
		"help", '?',				AT_EMPTY,
		(ArgProcP) main_handle_help,		NIL (GenericP),
		UB "description of help" UE
    }, {
		"index", 'i',				AT_PROC_SWITCH,
		(ArgProcP) main_handle_index,		NIL (GenericP),
		UB "description of index" UE
    }, {
		"show-errors", 'e',			AT_EMPTY,
		(ArgProcP) main_handle_show_errors,	NIL (GenericP),
		UB "description of show-errors" UE
    }, {
		"size", 's',				AT_PROC_SWITCH,
		(ArgProcP) main_handle_size,		NIL (GenericP),
		UB "description of size" UE
    }, {
		"tdf-version", 't',			AT_PROC_SWITCH,
		(ArgProcP) main_handle_tdf_version,	NIL (GenericP),
		UB "description of tdf-version" UE
    }, {
		"version", 'v',				AT_EMPTY,
		(ArgProcP) main_handle_version,		NIL (GenericP),
		UB "description of version" UE
    }, ARG_PARSE_END_LIST
};

static ArgListT main_extract_arg_list [] = {
    {
		"all", 'a',				AT_PROC_SWITCH,
		(ArgProcP) main_handle_all,		NIL (GenericP),
		UB "description of all" UE
    }, {
		"basename", 'b',			AT_PROC_SWITCH,
		(ArgProcP) main_handle_basename,	NIL (GenericP),
		UB "description of basename" UE
    }, {
		"debug-file", 'd',			AT_FOLLOWING,
		(ArgProcP) main_handle_debug_file,	NIL (GenericP),
		UB "description of debug-file" UE
    }, {
		"show-errors", 'e',			AT_EMPTY,
		(ArgProcP) main_handle_show_errors,	NIL (GenericP),
		UB "description of show-errors" UE
    }, {
		"help", '?',				AT_EMPTY,
		(ArgProcP) main_handle_help,		NIL (GenericP),
		UB "description of help" UE
    }, {
		"info", 'i',				AT_PROC_SWITCH,
		(ArgProcP) main_handle_info,		NIL (GenericP),
		UB "description of info" UE
    }, {
		"match-basename", 'm',			AT_PROC_SWITCH,
		(ArgProcP) main_handle_match_base,	NIL (GenericP),
		UB "description of match-basename" UE
    }, {
		"version", 'v',				AT_EMPTY,
		(ArgProcP) main_handle_version,		NIL (GenericP),
		UB "description of version" UE
    }, ARG_PARSE_END_LIST
};

static ArgListT main_linker_arg_list [] = {
    {
		"all-hide-defined", 'a',		AT_PROC_SWITCH,
		(ArgProcP) main_handle_all_hide_defd,	NIL (GenericP),
		UB "description of all-hide-defined" UE
    }, {
		"debug-file", 'd',			AT_FOLLOWING,
		(ArgProcP) main_handle_debug_file,	NIL (GenericP),
		UB "description of debug-file" UE
    }, {
		"help", '?',				AT_EMPTY,
		(ArgProcP) main_handle_help,		NIL (GenericP),
		UB "description of help" UE
    }, {
		"hide", 'h',				AT_FOLLOWING2,
		(ArgProcP) main_handle_hide,		NIL (GenericP),
		UB "description of hide" UE
    }, {
		"hide-defined", 'H',			AT_FOLLOWING,
		(ArgProcP) main_handle_hide_defined,	NIL (GenericP),
		UB "description of hide-defined" UE
    }, {
		"keep", 'k',				AT_FOLLOWING2,
		(ArgProcP) main_handle_keep,		NIL (GenericP),
		UB "description of keep" UE
    }, {
		"keep-all", 'K',			AT_FOLLOWING,
		(ArgProcP) main_handle_keep_all,	NIL (GenericP),
		UB "description of keep-all" UE
    }, {
		"library", '\0',			AT_FOLLOWING,
		(ArgProcP) main_handle_library_file,	NIL (GenericP),
		UB "description of library-file" UE
    }, {
		NIL (CStringP), 'l',			AT_EITHER,
		(ArgProcP) main_handle_library_file,	NIL (GenericP),
		UB "description of l" UE
    }, {
		"output-file", 'o',			AT_FOLLOWING,
		(ArgProcP) main_handle_output_file,	NIL (GenericP),
		UB "description of output-file" UE
    }, {
		"path", '\0',				AT_FOLLOWING,
		(ArgProcP) main_handle_library_path,	NIL (GenericP),
		UB "description of path" UE
    }, {
		NIL (CStringP), 'L',			AT_EITHER,
		(ArgProcP) main_handle_library_path,	NIL (GenericP),
		UB "description of L" UE
    }, {
		"rename", 'r',				AT_FOLLOWING3,
		(ArgProcP) main_handle_rename,		NIL (GenericP),
		UB "description of rename" UE
    }, {
		"rename-file", 'R',			AT_FOLLOWING,
		(ArgProcP) main_handle_rename_file,	NIL (GenericP),
		UB "description of rename-file" UE
    }, {
		"show-errors", 'e',			AT_EMPTY,
		(ArgProcP) main_handle_show_errors,	NIL (GenericP),
		UB "description of show-errors" UE
    }, {
		"suppress", 's',			AT_FOLLOWING2,
		(ArgProcP) main_handle_suppress,	NIL (GenericP),
		UB "description of suppress" UE
    }, {
		"suppress-all", 'S',			AT_FOLLOWING,
		(ArgProcP) main_handle_suppress_all,	NIL (GenericP),
		UB "description of suppress-all" UE
    }, {
		"suppress-mult", 'M',			AT_PROC_SWITCH,
		(ArgProcP) main_handle_suppress_mult,	NIL (GenericP),
		UB "description of suppress-mult" UE
    }, {
		"unit-file", 'u',			AT_FOLLOWING,
		(ArgProcP) main_handle_unit_file,	NIL (GenericP),
		UB "description of unit-file" UE
    }, {
		"version", 'v',				AT_EMPTY,
		(ArgProcP) main_handle_version,		NIL (GenericP),
		UB "description of version" UE
    }, {
		"warnings", 'w',			AT_PROC_SWITCH,
		(ArgProcP) main_handle_warning,		NIL (GenericP),
		UB "description of warning" UE
    }, ARG_PARSE_END_LIST
};

#ifdef __TenDRA__
#pragma TenDRA end
#endif

/*--------------------------------------------------------------------------*/

static ModeT
main_init(int argc, char **argv)
{
    EStringP  usage_estring = error_define_string ("tld usage message", USAGE);
    ModeT     mode          = MODE_LINKER;
    ArgListP  arg_list      = main_linker_arg_list;
    CStringP  error_file;
    int       skip;
	
    error_init (argv [0], gen_errors_init_errors);
    error_intern_strings (main_description_strings);
    if ((error_file = getenv ("TLD_ERROR_FILE")) != NIL (CStringP)) {
		error_file_parse (error_file, FALSE);
    }
    argc --;
    argv ++;
  retry:
    if ((argc > 0) && (argv [0][0] == '-') && (argv [0][1] == 'm')) {
		char c = argv [0][2];
		
		argc --;
		argv ++;
		switch (c) {
		case 'c':
			mode     = MODE_BUILDER;
			arg_list = main_builder_arg_list;
			arg_data_init (&main_arg_data, "library.tl");
			break;
		case 't':
			mode     = MODE_CONTENTS;
			arg_list = main_contents_arg_list;
			arg_data_init (&main_arg_data, NIL (CStringP));
			break;
		case 'x':
			mode     = MODE_EXTRACT;
			arg_list = main_extract_arg_list;
			arg_data_init (&main_arg_data, NIL (CStringP));
			break;
		case 'l':
			goto linker_case;
		case 'v':
			main_used_one_off = TRUE;
			main_used_other   = FALSE;
			main_print_version ();
			goto retry;
		default:
			E_bad_mode (argv [0][2]);
			UNREACHED;
		}
    } else {
      linker_case:
		arg_data_init (&main_arg_data, "capsule.j");
    }
    arg_parse_intern_descriptions (arg_list);
    skip = arg_parse_arguments (arg_list, usage_estring, argc, argv);
    argc -= skip;
    argv += skip;
    if (main_used_one_off && (!main_used_other) && (argc == 0)) {
		exit (EXIT_SUCCESS);
		UNREACHED;
    } else if (argc == 0) {
		E_missing_files ();
		UNREACHED;
    }
    arg_data_set_files (&main_arg_data, argc, argv);
    arg_data_vector_libraries (&main_arg_data);
    debug_set_file (arg_data_get_debug_file (&main_arg_data));
    return (mode);
}

/*--------------------------------------------------------------------------*/

int
main(int argc, char **argv)
{
    HANDLE {
		istream_setup ();
		ostream_setup ();
		switch (main_init (argc, argv)) EXHAUSTIVE {
		case MODE_BUILDER:
			builder_main (&main_arg_data);
			break;
		case MODE_CONTENTS:
			contents_main (&main_arg_data);
			break;
		case MODE_EXTRACT:
			extract_main (&main_arg_data);
			break;
		case MODE_LINKER:
			linker_main (&main_arg_data);
			break;
		}
    } WITH {
		ExceptionP exception = EXCEPTION_EXCEPTION ();
		
		if (exception == XX_dalloc_no_memory) {
			E_no_memory ();
			UNREACHED;
		} else if ((exception == XX_istream_read_error) ||
				   (exception == XX_bistream_read_error)) {
			CStringP file = (CStringP) EXCEPTION_VALUE ();
			
			E_read_error (file);
			UNREACHED;
		} else if ((exception == XX_ostream_write_error) ||
				   (exception == XX_bostream_write_error)) {
			CStringP file = (CStringP) EXCEPTION_VALUE ();
			
			E_write_error (file);
			UNREACHED;
		} else {
			RETHROW ();
			UNREACHED;
		}
    } END_HANDLE
		  exit (EXIT_SUCCESS);
    UNREACHED;
}

/*
 * Local variables(smf):
 * compile-command: "build_tld next-cc"
 * eval: (include::add-path-entry "os-interface" "library" "tdf")
 * eval: (include::add-path-entry "frontends" "generated")
 * End:
 **/
