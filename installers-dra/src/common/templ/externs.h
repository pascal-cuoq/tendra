/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/* AUTOMATICALLY GENERATED BY %ZX VERSION %ZV FROM TDF %VA.%VB */

#ifndef EXTERNS_INCLUDED
#define EXTERNS_INCLUDED

@use all
@special exp
@loop sort
@if !sort.builtin

/* CONSTRUCTS FOR %ST */
@if sort.simple
@loop sort.cons
@if cons.params
@loop cons.param
@if param.break
@if param.first
extern void start_%CN(void);
@else
extern void start_%CN(%
@loop param.prev
 %PSN,%
@end
%b);
@endif
@endif
@end
extern %SN f_%CN(%
@loop cons.param
 %PSN,%
@end
%b);
@else
@if sort.special
extern %SN f_%CN(void);
@else
extern %SN f_%CN;
@endif
@endif
@end
extern %SN f_dummy_%SN;
@else
@if sort.option
extern %SN yes_%SN(%SSN);
extern %SN no_%SN;
@else
extern %SN new_%SN(int);
extern %SN add_%SN(%SN, %SSN, int);
@endif
@endif
extern void init_%SN(void);
@endif
@end


#endif
