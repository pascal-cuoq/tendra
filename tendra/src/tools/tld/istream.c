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


/**** istream.c --- Input stream handling.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file implements the input stream facility specified in the file
 * "istream.h".  See that file for more details.
 *
 **** Change Log:
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
 * Revision 1.1.1.1  1998/01/17  15:57:18  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/12  11:45:41  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:06:10  smf
 * Initial import of os-interface shared files.
 *
 **/

/****************************************************************************/

#include "istream.h"
#include "cstring.h"
#include "syntax.h"

/*--------------------------------------------------------------------------*/

#define ISTREAM_BUFSIZE 8193

/*--------------------------------------------------------------------------*/

ExceptionP XX_istream_read_error = EXCEPTION ("error reading from stream");

/*--------------------------------------------------------------------------*/

static char istream_input_buffer [ISTREAM_BUFSIZE];

static IStreamT		istream_input_1 = {
    NIL (FILE *),
    &(istream_input_buffer [0]),
    &(istream_input_buffer [ISTREAM_BUFSIZE - 1]),
    &(istream_input_buffer [ISTREAM_BUFSIZE]),
    &(istream_input_buffer [ISTREAM_BUFSIZE]),
    1,
    "<stdin>",
    FALSE
};

IStreamT	 *const istream_input = &istream_input_1;

/*--------------------------------------------------------------------------*/

static IStreamStatusT
istream_read_hex_char(IStreamP istream, char *c_ref)
{
    int value;
    int tmp;
    char c;
	
  redo1:
    switch (c = ISTREAM_READ_CHAR (istream)) {
	case '\0':
		ISTREAM_HANDLE_NULL (istream, redo1, eof);
		return (ISTREAM_STAT_SYNTAX_ERROR);
	case '\n':
		istream_inc_line (istream);
		return (ISTREAM_STAT_SYNTAX_ERROR);
	default:
		if (((value = syntax_value (c)) == SYNTAX_NO_VALUE) || (value >= 16)) {
			return (ISTREAM_STAT_SYNTAX_ERROR);
		}
		tmp = value;
		break;
    }
  redo2:
    switch (c = ISTREAM_READ_CHAR (istream)) {
	case '\0':
		ISTREAM_HANDLE_NULL (istream, redo2, eof);
		return (ISTREAM_STAT_SYNTAX_ERROR);
	case '\n':
		istream_inc_line (istream);
		return (ISTREAM_STAT_SYNTAX_ERROR);
	default:
		if (((value = syntax_value (c)) == SYNTAX_NO_VALUE) || (value >= 16)) {
			return (ISTREAM_STAT_SYNTAX_ERROR);
		}
		break;
    }
    *c_ref = (char) ((tmp * 16) + value);
    return (ISTREAM_STAT_READ_CHAR);
  eof:
    return (ISTREAM_STAT_SYNTAX_ERROR);
}

/*--------------------------------------------------------------------------*/

void
istream_setup()
{
    istream_input_1.file = stdin;
}

#ifdef FS_FAST
#undef istream_init
#endif /* defined (FS_FAST) */
void
istream_init(IStreamP istream)
{
    istream->name = NIL (CStringP);
}
#ifdef FS_FAST
#define istream_init(is) ((is)->name = NIL (CStringP))
#endif /* defined (FS_FAST) */

BoolT
istream_open(IStreamP istream, CStringP name)
{
    if ((istream->file = fopen (name, "r")) == NIL (FILE *)) {
		return (FALSE);
    }
    istream->buffer  = ALLOCATE_VECTOR (char, ISTREAM_BUFSIZE);
    istream->limit   = &(istream->buffer [ISTREAM_BUFSIZE]);
    istream->line    = 1;
    istream->name    = name;
    X__istream_fill_buffer (istream);
    return (TRUE);
}

void
istream_assign(IStreamP to, IStreamP from)
{
    to->file      = from->file;
    to->buffer    = from->buffer;
    to->current   = from->current;
    to->end       = from->end;
    to->limit     = from->limit;
    to->line      = from->line;
    to->name      = from->name;
    to->read_last = from->read_last;
}

#ifdef FS_FAST
#undef istream_is_open
#endif /* defined (FS_FAST) */
BoolT
istream_is_open(IStreamP istream)
{
    return (istream->name != NIL (CStringP));
}
#ifdef FS_FAST
#define istream_is_open(is) ((is)->name != NIL (CStringP))
#endif /* defined (FS_FAST) */

BoolT
istream_read_char(IStreamP istream, char *c_ref)
{
    char c;
	
  redo:
    switch (c = ISTREAM_READ_CHAR (istream)) {
	case '\n':
		istream_inc_line (istream);
		break;
	case '\0':
		ISTREAM_HANDLE_NULL (istream, redo, eof);
		break;
	default:
		break;
    }
    *c_ref = c;
    return (TRUE);
  eof:
    return (FALSE);
}

BoolT
istream_peek_char(IStreamP istream, char *c_ref)
{
    char c;
	
  redo:
    switch (c = ISTREAM_PEEK_CHAR (istream)) {
	case '\0':
		ISTREAM_HANDLE_NULL (istream, redo, eof);
		break;
	default:
		break;
    }
    *c_ref = c;
    return (TRUE);
  eof:
    return (FALSE);
}

IStreamStatusT
istream_read_escaped_char(IStreamP istream,
						  char *c_ref)
{
    char c;
	
  redo:
    switch (c = ISTREAM_READ_CHAR (istream)) {
	case '\0':
		ISTREAM_HANDLE_NULL (istream, redo, eof);
		*c_ref = c;
		return (ISTREAM_STAT_READ_CHAR);
	case '\n':
		istream_inc_line (istream);
		return (ISTREAM_STAT_NO_CHAR);
	case '0':
		*c_ref = '\0';
		return (ISTREAM_STAT_READ_CHAR);
	case 'f': case 'F':
		*c_ref = '\f';
		return (ISTREAM_STAT_READ_CHAR);
	case 'n': case 'N':
		*c_ref = '\n';
		return (ISTREAM_STAT_READ_CHAR);
	case 'r': case 'R':
		*c_ref = '\r';
		return (ISTREAM_STAT_READ_CHAR);
	case 't': case 'T':
		*c_ref = '\t';
		return (ISTREAM_STAT_READ_CHAR);
	case 'x': case 'X':
		return (istream_read_hex_char (istream, c_ref));
	default:
		*c_ref = c;
		return (ISTREAM_STAT_READ_CHAR);
    }
  eof:
    return (ISTREAM_STAT_SYNTAX_ERROR);
}

#ifdef FS_FAST
#undef istream_inc_line
#endif /* defined (FS_FAST) */
void
istream_inc_line(IStreamP istream)
{
    istream->line ++;
}
#ifdef FS_FAST
#define istream_inc_line(is) ((is)->line ++)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef istream_line
#endif /* defined (FS_FAST) */
unsigned
istream_line(IStreamP istream)
{
    return (istream->line);
}
#ifdef FS_FAST
#define istream_line(is) ((is)->line)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef istream_name
#endif /* defined (FS_FAST) */
CStringP
istream_name(IStreamP istream)
{
    return (istream->name);
}
#ifdef FS_FAST
#define istream_name(is) ((is)->name)
#endif /* defined (FS_FAST) */

void
istream_close(IStreamP istream)
{
    (void) fclose (istream->file);
    if (istream != istream_input) {
		DEALLOCATE (istream->buffer);
    }
    istream_init (istream);
}

/*--------------------------------------------------------------------------*/

void
X__istream_fill_buffer(IStreamP istream)
{
    SizeT bytes = fread ((GenericP) (istream->buffer), sizeof (char),
						 (SizeT) (ISTREAM_BUFSIZE - 1), istream->file);
	
    if ((bytes == (SizeT) 0) && (ferror (istream->file))) {
		CStringP name = cstring_duplicate (istream->name);
		
		THROW_VALUE (XX_istream_read_error, name);
		UNREACHED;
    }
    istream->current   = istream->buffer;
    istream->end       = (istream->current + bytes);
    istream->read_last = FALSE;
    *(istream->end) ++ = '\0';
}
