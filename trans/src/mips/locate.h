/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/* locatedecs.h
    externs from locate.c
*/

#include <reader/exp.h>

#include <construct/installtypes.h>

#include "addr.h"
#include "procrec.h"

extern long locals_offset;
extern long frame_size;

extern  baseoff boff(exp x);
extern  where locate(exp e, space sp, shape s, int dreg);
extern  bool simplepars;
