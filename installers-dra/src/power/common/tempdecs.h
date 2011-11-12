/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef TEMPDECSDECS_H
#define TEMPDECSDECS_H

#include "config.h"

#include "installtypes.h"
#include "exptypes.h"

extern bool tempdecopt;
extern int tempdec(exp, bool);
extern bool APPLYLIKE(exp);
extern bool RETURNS_R_RESULT(exp);
extern bool RETURNS_FR_RESULT(exp);
extern int end_param;

#endif /* tempdecdecs.h */
