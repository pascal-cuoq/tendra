/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "dw2_config.h"
#include "flags.h"
#include "machine.h"
#include "basicread.h"
#include "target_v.h"

long dwarf_lab_num = 0;

void
out_string(char *s)
{
  outs(".string \"");
  outs(s);
  outs("\"");
  d_outnl();
  return;
}

void
start_string(char *s)
{
  outs(".string \"");
  outs(s);
  return;
}

void
end_string(void)
{
  outs("\"");
  d_outnl();
  return;
}

void
enter_section(char *s)
{
  outs(".section .");
  outs(s);
  d_outnl();
  return;
}

void
exit_section(void)
{
  outs(".previous");
  d_outnl();
  return;
}

void
outnl_comment(char *s)
{
  outs("\t/");
  outs(s);
  d_outnl();
  return;
}

void
outnl_comment_i(char *s, long i)
{
  outs("\t/");
  outs(s);
  outs(" ");
  outn(i);
  d_outnl();
  return;
}

void
out_dwf_label(long l, int set)
{
  if (!l) {
    failer("unknown label");
  }
  outs(".Ldw");
  outn(l);
  if (set) {
    outs(":");
    d_outnl();
  }
  return;
}

void
out_code_label(long l)
{
  outs(local_prefix);
  outn(l);
  return;
}

void
out_dwf_dist_to_label(long l)
{
  out_dwf_label(l, 0);
  outs(" - . - 4");
  return;
}

void
out_dwf_labdiff(long lo, long hi)
{
  if (hi == lo) {
    outn((long)0);
  } else {
    out_dwf_label(hi, 0);
    outs(" - ");
    out_dwf_label(lo, 0);
  }
  return;
}

void
out_ext_label(char *s)
{
  outs(".globl ");
  outs(s);
  d_outnl();
  outs(s);
  outs(":");
  d_outnl();
  return;
}

void
out_producer(char *s)
{
  outs(".string \"");
  outs(s);
  outs("   with TenDRA 80x86/Solaris installer ");
  outn((long)target_version);
  outs(".");
  outn((long)target_revision);
  outs("\"");
  d_outnl();
  return;
}


static char *first_data = NULL;
static char *first_ro = NULL;

void
note_data(char *s)
{
  if (!first_data) {
    first_data = s;
  }
  return;
}

void
note_ro(char *s)
{
  if (!first_ro) {
    first_ro = s;
  }
  return;
}

void
dw2_data_aranges(void)
{
  long lab_data = 0, lab_ro = 0;
  if (first_data) {
    lab_data = next_dwarf_label();
    if (do_prom) {
      outs(".bss ");
      out_dwf_label(lab_data, 0);
      outs(", 0");
      d_outnl();
    } else {
      outs(".data");
      d_outnl();
      out_dwf_label(lab_data, 1);
    }
  }
  if (first_ro) {
    lab_ro = next_dwarf_label();
    out_readonly_section();
    d_outnl();
    out_dwf_label(lab_ro, 1);
  }
  outs(".text");
  d_outnl();
  enter_section("debug_aranges");
  if (first_data) {
    out32(); outs(first_data); d_outnl();
    out32(); out_dwf_label(lab_data, 0); outs(" - ");
    outs(first_data); d_outnl();
  }
  if (first_ro) {
    out32(); outs(first_ro); d_outnl();
    out32(); out_dwf_label(lab_ro, 0); outs(" - ");
    outs(first_ro); d_outnl();
  }
  exit_section();
  return;
}
