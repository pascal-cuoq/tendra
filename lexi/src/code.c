/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include <shared/xalloc.h>

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dalloc.h>
#include <exds/dstring.h>

#include <adt/trans.h>

#include "code.h"

struct code *
code_create(enum code_kind kind)
{
	struct code *c;

	c = xmalloc(sizeof *c);
	c->kind = kind;
	c->next = NULL;

	return c;
}

static NStringT *
code_name(struct code *c)
{
	assert(c != NULL);

	return &c->name;
}

static void
code_append(struct code **p, struct code *new)
{
	assert(p != NULL);

	while (*p != NULL) {
		p = &(*p)->next;
	}

	*p = new;
}

void
code_append_at(struct code **c)
{
	struct code *new;

	new = code_create(CODE_AT);
	code_append(c, new);
}

void
code_append_ident(struct code **c, NStringT *i)
{
	struct code *new;

	new = code_create(CODE_IDENT);
	nstring_assign(code_name(new), i);
	code_append(c, new);
}

void
code_append_ref(struct code **c, NStringT *i)
{
	struct code *new;

	new = code_create(CODE_REF);
	nstring_assign(code_name(new), i);
	code_append(c, new);
}

void
code_append_string(struct code **c, NStringT *s)
{
	struct code *new;

	new = code_create(CODE_STRING);
	nstring_assign(code_name(new), s);
	code_append(c, new);
}

void
code_destroy(struct code *c)
{
	struct code *p, *next;

	for (p = c; p != NULL; p = p->next) {
		next = p->next;

		switch (p->kind) {
		case CODE_IDENT:
		case CODE_STRING:
			nstring_destroy(code_name(p));
			break;

		case CODE_AT:
			/* do nothing */
			break;
		}

		xfree(p);
	}
}

void
code_out(FILE *file, struct code *c, struct trans *t, int d)
{
	struct code *p;

	for (p = c; p != NULL; p = p->next) {
		switch (p->kind) {
		case CODE_STRING: {
			char *s;

			s = nstring_to_cstring(code_name(p));
			fputs(s, file);
			xfree(s);
			break;
		}

		case CODE_IDENT: {
			struct arg *to;

			to = trans_find(t, code_name(p));
			arg_out(to, false, d, file);
			break;
		}

		case CODE_REF: {
			struct arg *to;

			to = trans_find(t, code_name(p));
			arg_out(to, true, d, file);
			break;
		}

		case CODE_AT:
			fputs("@", file);
			break;
		}
	}
}

