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


#include "config.h"
#include "filename.h"
#include "list.h"
#include "environ.h"
#include "flags.h"
#include "options.h"
#include "suffix.h"
#include "utility.h"


/*
 *    THE CURRENT ENVIRONMENTS PATH
 *
 *    The environment path is a colon-separated list of directories which
 *    are searched for tcc environments.
 */

static char *envpath = ".";


/*
 *    UPDATE THE ENVIRONMENTS PATH
 *
 *    This routine initialises and updates the environments path.  This is
 *    given by the contents of the system variable TCCENV, plus the default
 *    directory (environ_dir), plus the current directory.
 */

void
find_envpath()
{
    char *p = buffer;
    char *tcc_env = getenv (TCCENV_VAR);
    if (tcc_env) {
		IGNORE sprintf (p, "%s:", tcc_env);
		p += strlen (p);
    }
    IGNORE sprintf (p, "%s:.", environ_dir);
    if (!streq (buffer, envpath)) envpath = string_copy (buffer);
    return;
}


/*
 *    PRINT THE ENVIRONMENTS PATH
 *
 *    This routine prints the environment path.
 */

void
show_envpath()
{
    find_envpath ();
    error (INFO, "Environment path is '%s'", envpath);
    return;
}


/*
 *    CHARACTER TYPES
 *
 *    These macros identify various character types.
 */

#define is_alphanum(X)	(((X) >= 'A' && (X) <= 'Z') ||\
				  ((X) >= '0' && (X) <= '9') ||\
				  ((X) == '_'))
#define is_whitespace(X)	((X) == ' ' || (X) == '\t')
#define is_quote(X)		((X) == '"')
#define is_newline(X)		((X) == '\n')


/*
 *    READ AN ENVIRONMENT - AUXILIARY ROUTINE
 *
 *    This routine reads the environment named nm, returning zero if it
 *    is successful.  A return value of 1 indicates that the environment
 *    could not be found, otherwise 2 is returned.
 */

int
read_env_aux(char *nm)
{
    /* Find the environment */
    FILE *f;
    char *p, *q;
    if (*nm == 0) {
		return (1);
    } else if (*nm == '/') {
		f = fopen (nm, "r");
    } else {
		p = envpath;
		do {
			q = buffer;
			while (*p && *p != ':') *(q++) = *(p++);
			*(q++) = '/';
			IGNORE strcpy (q, nm);
			f = fopen (buffer, "r");
		} while (f == null && *(p++));
    }
    if (f == null) return (1);
	
    /* Read the environment one line at a time */
    while (fgets (buffer, buffer_size, f) != null) {
		char c = *buffer;
		if (c == '<' || c == '>' || c == '+' || c == '?') {
			/* Only process lines beginning with these characters */
			char *sp;
			list dummy;
			char line [1000];
			line [0] = c;
			p = buffer + 1;
			q = line + 1;
			while (c = *(p++), is_alphanum (c)) *(q++) = c;
			sp = q;
			*(q++) = 0;
			if (!is_whitespace (c)) {
				error (WARNING, "Illegal environmental variable, '%s'",
					   line);
			}
			while (c = *(p++), is_whitespace (c)) /* empty */;
			if (!is_quote (c)) {
				error (WARNING, "Illegal environmental value for '%s'",
					   line);
			}
			while (c = *(p++), !is_quote (c)) {
				if (c == '\\') c = *(p++);
				if (c == 0 || is_newline (c)) {
					error (WARNING, "Illegal environmental value for '%s'",
						   line);
					break;
				}
				*(q++) = c;
			}
			while (c = *(p++), is_whitespace (c)) /* empty */;
			if (!is_newline (c)) {
				error (WARNING, "Illegal environmental value for '%s'",
					   line);
			}
			*sp = ' ';
			*q = 0;
			dummy.item = string_copy (line);
			dummy.next = null;
			process_options (&dummy, environ_optmap);
		}
    }
    IGNORE fclose (f);
    return (0);
}


/*
 *    READ AN ENVIRONMENT
 *
 *    This routine reads the environment named nm, reporting an error if
 *    it is unsuccessful.
 */

void
read_env(char *nm)
{
    int e = read_env_aux (nm);
    if (e == 1) error (WARNING, "Can't find environment, '%s'", nm);
    return;
}
