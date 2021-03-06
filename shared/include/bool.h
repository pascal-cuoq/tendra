/*
 * Copyright 2014, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef SHARED_BOOL_H
#define SHARED_BOOL_H

#if __STDC_VERSION__ >= 199901L
#include <stdbool.h>
#else
typedef unsigned int bool; /* unsigned to allow for use in bitfields */
#define true  1
#define false 0
#endif

#endif

