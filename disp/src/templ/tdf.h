/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

@use all
@special external
@special sortname
@special token
@special tokdec
@special tokdef
@special tagdec
@special tagdef
@special al_tagdef
@special diag_tagdef
@special token_defn
@special exp case
@special exp labelled
@special exp make_proc
@special nat make_nat
@special signed_nat make_signed_nat
@special string make_string
@special version make_version
#ifndef TDF_INCLUDED
#define TDF_INCLUDED

/* AUTOMATICALLY GENERATED BY %ZX VERSION %ZV FROM TDF %VA.%VB */

@loop sort
@if sort.basic
extern long de_%SN(void);
@endif
@end

extern void decode(char *);
extern sortid find_sort(sortname);
extern sortname find_sortname(int);
extern void init_foreign_sorts(void);
extern char find_variable(string, long);
typedef void(*equation_func)(void);
extern equation_func find_equation(string, string *, int *);

@loop sort
@if sort.link
extern long var_%SN;
@endif
@end

#define version_magic		%48t"TDFC"
#define version_major		%48t%VA
#define version_minor		%48t%VB

@loop sort
@if sort.unit
#define HAVE_%SN		%48t1
@endif
@end

@loop sort
@if sort.basic
#define sort_%20SN		%48t%SCE
@endif
@end
#define sort_foreign		%48tsortname_foreign_sort
#define sort_unknown		%48t0

@loop sort
@loop sort.cons
@if sort.special
#define %10SN_%20CN		%48t%CE
@else
@if cons.special
#define %10SN_%20CN		%48t%CE
@if cons.eq.make_string
#define %10SN_bits		%48t%SB
#define %10SN_ext		%48t%SE
@endif
@endif
@endif
@end
@end

#endif
