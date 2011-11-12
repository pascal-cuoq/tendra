/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*********************************************************************
                     main.c

   This is the main routine.
    It constructs .G (binasm) and .T (symbol table) files from the input .t
    files. If -S is given it will also construct a .s (assembler) file in as_file.

 *********************************************************************/

#include "config.h"

#include "version.h"
#include "basicread.h"
#include "flags.h"
#include "main_reads.h"
#include "flpt.h"
#include "externs.h"
#include "installglob.h"
#include "machine.h"
#include "exp.h"
#include "dump_distr.h"
#include "construct_v.h"
#include "reader_v.h"

extern void output_symtab(char*);


/* extern int bytes_allocated; */

void out_rename
(char * oldid, char * newid)
{
	/* ??? this may be wrong with diagnostics */
	return;
}

extern int good_trans;
bool do_extern_adds;
FILE * as_file;

FILE * ba_file;

int   majorno = 3;
int   minorno = 18;

long  currentfile = -1;		/* our source fileno 0.. */
long  mainfile = 0;		/* would be best if it  actually contained
				   main ! */
bool BIGEND = (little_end == 0);

bool do_tlrecursion = 0;

bool opt
(char c)
{ if (c == '0' || c == 0) return 0;
  else return 1;
}

int   main
(int argc, char **argv)
{
  long  i;
  char *nm;
  char *aname;
  char *dname;
  bool withs = 0;
  bool no_opts = 0;
  bool override_diags = 0;
  PIC_code = 0;

  as_file = (FILE *)0;
  do_inlining = 1;
  redo_structfns = 1;
  do_unroll = 1;
  do_extern_adds = 0;


  flpt_const_overflow_fail = 0; /* HUGEVAL requires 0 for Ysystem */

  do_foralls = 1;
  do_alloca = 0;
  for (i = 1; argv[i][0] == '-'; ++i) {/* read flags */
    char *s = argv[i];
    switch (s[1]) {
      case 'A':
	do_alloca = opt(s[2]);
	break;
      case 'B':
	flpt_const_overflow_fail = opt(s[2]);
	break;
      case 'C':
	do_loopconsts = opt(s[2]);
	break;
      case 'D':
	PIC_code = opt(s[2]);
	break;
      case 'E':
        extra_checks = 0;
        break;
      case 'e':
	do_extern_adds = opt(s[2]);
	break;
      case 'F':
        do_foralls = opt(s[2]);
        break;
      case '-':
      	override_diags = 1;
      	break;
      case 'H':
	diagnose = 1;
	do_alloca = 0; /* dbx does not understand variable frame sizes */
	break;
      case 'I':
	do_inlining = opt(s[2]);
        break;
      case 'K':
	/* only MIPS */
	break;
      case 'M':
	strict_fl_div = (opt(s[2]) == 0);
	break;
      case 'P':
	do_profile = 1;
	break;
      case 'Q':
	exit(EXIT_FAILURE);
      case 'R':
	round_after_flop = opt(s[2]);
	break;
      case 'S':
	withs =1;
	break;
      case 'U':
        do_unroll = opt(s[2]);
        break;
      case 'V': {
		int   ind = 2;
		int maj = 0;
		minorno = 0;
		for (;; ind++) {
		  char  si = s[ind];
		  if (si != ' ') {
		    if (si >= '0' && si <= '9') {
		      maj = maj * 10 + si - '0';
		    }
		    else
		      break;
		  }
		}

		if (s[ind]!= '.') {
		  fprintf(stderr,
                "DRA TDF Mips (as:3.x) translator %d.%d: (TDF version %d.%d); 30th June 1994\n",
                 mipstrans_version,mipstrans_revision, MAJOR_VERSION, MINOR_VERSION);
                 fprintf(stderr, "reader %d.%d: \n", reader_version,
		 reader_revision);
	         fprintf(stderr, "construct %d.%d: \n", construct_version,
		 construct_revision);
        	 break;
		}
		majorno = maj;
		minorno = 0;

		for (ind++;; ind++) {
		  char  si = s[ind];
		  if (si >= '0' && si <= '9') {
		    minorno = minorno * 10 + si - '0';
		  }
		  else
		    break;
		}

	      }
      case 'W':
        writable_strings = opt(s[2]);
        break;
      case 'X':
        no_opts = 1;
        break;
      case 'd':
        do_dump_opt = 0;
        break;
      case 'l':
        do_tlrecursion = opt(s[2]);
        break;
      case 'Z': /* prints on stderr the versions of all the capsules
                   from which this capsule was made */
        report_versions = 1;
        break;
      default:
	failer("Illegal flag");
	break;
    };
  };

	if (do_alloca && PIC_code) {
		failer("Can't do inline alloca with PIC code at the moment");
		exit(EXIT_FAILURE);
	}

  if (override_diags)diagnose = 0;
  if (diagnose || no_opts) {		/* line numbering goes to hell with
				   optimisations */

        do_inlining = 0;
        do_loopconsts = 0;
        do_foralls = 0;
        do_dump_opt = 0;
        do_unroll = 0;
	do_tlrecursion = 0;
  };


  if (withs) {			/* requires assembler text */
    aname = argv[argc - 1];
    as_file = fopen(aname, "w");
    if (as_file == (FILE *)0) {
      failer("can't find .s file");
      return 1;
    }
    argc--;
  }


  dname = argv[argc - 1];	/* the .T file */
  nm = argv[argc - 2];		/* the .G file */
  ba_file = fopen(nm, "w");
  if (ba_file == (FILE *)0) {
    printf("install: can't open output file %s\n", nm);
    return 1;
  }


  if (!initreader(argv[argc - 3])) {
    failer("cant read .t file");
    return 1;
  };

  init_flpt();
#include "inits.h"
  top_def = (dec*)0;





  local_prefix = "$$";
  name_prefix = "";


  d_capsule();



  if (as_file)
    fclose (as_file);		/* close the .s file */
  fclose (ba_file);		/* close the .G file */
  output_symtab (dname);	/* construct the .T file */
  return good_trans;		/* return 1 for error, 0 for good */
}
