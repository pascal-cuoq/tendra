/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>
#include <stdlib.h>

#include <shared/check.h>
#include <shared/getopt.h>
#include <shared/error.h>

#include <reader/basicread.h>
#include <reader/main_reads.h>
#include <reader/externs.h>
#include <reader/readglob.h>

#include <construct/flags.h>
#include <construct/flpt.h>
#include <construct/installglob.h>
#include <construct/machine.h>
#include <construct/exp.h>

#include <main/driver.h>

#include "dump_distr.h"
#include "fail.h"
#include "bool.h"

FILE *ba_file;
char *dname;	/* name of file to hold symbol table */

#define VERSION_STR "2.4.11"

#define SUCCESS 0
#define FAILURE 1

int use_umulh_for_div;
bool fail_with_denormal_constant = TRUE;
bool treat_denorm_specially = FALSE;
bool trap_all_fops = FALSE;
bool do_extern_adds = FALSE;

static bool produce_binasm = FALSE;

void
out_rename(char *oldid, char *newid)
{
  UNUSED(oldid);
  UNUSED(newid);
  return;
}

long currentfile = -1;
long mainfile=0;
int majorno = 3;
int minorno = 11;

static void
init(void)
{
	endian    = ENDIAN_LITTLE;
	assembler = ASM_GAS;
	format    = FORMAT_ELF;
	diag      = DIAG_NONE;
	cconv     = CCONV_ALPHA;
	abi       = ABI_OSF1;

	target_dbl_maxexp = 308;
	redo_structfns    = 1;
	promote_pars      = 0;
	do_alloca         = 0;
#if DO_NEW_DIVISION
	use_umulh_for_div = 1;
#else
	use_umulh_for_div = 0;
#endif
}

static int
option(char c, const char *optarg)
{
	switch (c) {
	case 'u': use_umulh_for_div = 1; break;
	case 's': produce_binasm = TRUE; break;
	case 'd':
		/* handle IEEE denormals */
		treat_denorm_specially = TRUE;

		switch (atoi(optarg)) {
		case 0:
			/* replace denormal const with 0.0 (don't do this) */
			alphawarn("Unsupported denormal switch");
			fail_with_denormal_constant = FALSE;
			break;

		case 1:
			/* error if denormal const is encountered */
			fail_with_denormal_constant = TRUE;
			break;

		case 2:
			/*
			 * Handle denormals properly (and slowly), by stopping the
			 * interleaving of floating point operations and using the
			 * OS exception handler
			 */
			treat_denorm_specially = FALSE;
			trap_all_fops = TRUE;
			break;

		default:
			return -1;
		}
	}

	return 0;
}

static void
unhas(void)
{
	/* Things trans.alpha does not "has" */
	has &= ~HAS_BYTEOPS;
	has &= ~HAS_BYTEREGS;
	has &= ~HAS_NEGSHIFT;
	has &= ~HAS_ROTATE;
	has &= ~HAS_MAXMIN;
	has &= ~HAS_CONDASSIGN;
	has &= ~HAS_DIV0;
	has &= ~HAS_SETCC;
	has &= ~HAS_COMPLEX;

	/* This does not work on the alpha */
	optim &= ~OPTIM_CASE;

	if (PIC_code) {
		failer("no PIC code available");
		exit(EXIT_FAILURE);
	}
}

static void
main(void)
{
	int i;
	char *aname;	/* name of file for assembly output */
	char *baname;
	char *tname;

	/* the files are passed in the order { .G .T | .s } */
	if (produce_binasm) {
		/* TODO: these can become separate driver-specific flags,
		 * and a .s file is always generated */
		baname  = "TODO"; /* argv[1]; */
		dname   = "TODO"; /* argv[0]; */
	}

	if (produce_binasm) {
		ba_file = fopen(baname, "w");
		if (ba_file == NULL) {
			alphafail(CANNOT_OPEN_FILE, baname);
		}
	} else {
		ba_file = NULL;
	}

	init_flpt();

#include <reader/inits.h>

	top_def = NULL;
	local_prefix = "$$";
	name_prefix  = "";

	(void) d_capsule();
	if (good_trans) {
		exit(EXIT_FAILURE);
	}
}

static void
cleanup(void)
{
	if (produce_binasm) {
		output_symtab(dname);
	}

	if (produce_binasm) {
		fclose(ba_file);
	}
}

struct driver driver = {
	VERSION_STR,

	init,
	unhas,
	main,
	cleanup,

	"sud:",
	option,
	NULL,

	ABI_OSF1,
	CCONV_ALPHA,
	ENDIAN_BIG | ENDIAN_LITTLE,
	FORMAT_ELF,
	DIAG_NONE | DIAG_STABS,
	ASM_OSF1 | ASM_GAS
};
