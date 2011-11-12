/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "config.h"
#include "exptypes.h"

#include "exp.h"
#include "procrectypes.h"
#include "addrtypes.h"

extern needs specialneeds(int i);
extern int specialfn(exp fn);
extern int specialmake(int n, exp par, space sp, where dest, int exitlab);
