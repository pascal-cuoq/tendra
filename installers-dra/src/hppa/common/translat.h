/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef TRANSLAT_INCLUDED
#define TRANSLAT_INCLUDED

extern int optim_level;
extern int maxfix_tregs;
extern dec **main_globals;
extern dec *diag_def;

extern int translate(char *, char *, char *);
extern void exit_translator(void);

enum section {
    no_section = 0,
    data_section,
    shortdata_section,
    text_section,
    bss_section,
    shortbss_section,
    rodata_section
};
extern void insection(enum section);
extern int OPTIM;
extern int for_gcc;

#endif /* TRANSLAT_INCLUDED */
