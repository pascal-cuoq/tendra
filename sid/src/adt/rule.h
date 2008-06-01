/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
/*
    		 Crown Copyright (c) 1997

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/

/*
 * rule.h - Rule ADT.
 *
 * This file specifies the interface to the SID rule, alternative and item
 * handling routines.  The actual implementations are spread across a number
 * of files, but are all logically part of the same file.  See the files named
 * in the declarations for more information.
 */

#ifndef H_RULE
#define H_RULE

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/bitvec.h>
#include <exds/dalloc.h>
#include "../adt/entry.h"
#include "../adt/entry-list.h"
#include "../adt/non-local.h"
#include <exds/ostream.h>
#include "../adt/rstack.h"
#include "../adt/table.h"
#include "../adt/types.h"

typedef enum {
    DFS_UNTRACED,
    DFS_TRACING,
    DFS_CYCLING,
    DFS_TRACED
} DFSStateT;

typedef enum {
    CT_LEFT,
    CT_TAIL,
    CT_ALL,
    CT_MUTATE
} CycleTypeT;

/*
 * An ItemT is therefore a rule, an action call, a terminal or TODO
 * (rename, name) already declared in a TableT.
 *
 * Items are held as a list within an AltT.
 */
typedef struct ItemT {
	/*
	 * The next item in the list held by an alternate.
	 */
    struct ItemT	       *next;

	/*
	 * Tuples of types containing the list of input parameters (.param)
	 * and output parameters (.result).
	 */
    TypeTupleT			param;
    TypeTupleT			result;

	/*
	 * The type and definition of the item.
	 *
	 * This may be a terminal, rule, action or identity already declared
	 * and stored in the hash map TableT.
	 *
	 * If the item is just an identity, then EntryT.type is ET_RENAME and
	 * .entry contains no other useful information.
	 * TODO this is not guarenteed, but was deduced from reading the code.
	 */
    EntryTypeT			type;
    EntryT *			entry;

	/* TODO */
    BoolT			inlinable;
    BoolT			tail_call;
} ItemT;

/*
 * One alternative within a rule.
 * For example, the rule:
 *
 *  basic-arithmetic = {
 *      number; plus; number;
 *  ||  number; minus; number;
 *  };
 *
 * contains two alternatives, each with three items.
 */
typedef struct AltT {
	/*
	 * The rule type RuleT contains a list of alternatives; this field
	 * gives the next alternate in the list held by a RuleT.
	 */
    struct AltT		       *next;

	/*
	 * A list of all local variables which appear as a left hand side in in
	 * all items of the alternate.
	 *
	 * TODO probably including non-locals if they appear on the left hand side
	 * of an identify?
	 */
    TypeTupleT			names;

    BitVecT			first_set;

	/*
	 * A list of items within an alternate.
	 * For the first alternative in the example above, the list of items
	 * would be: number; plus; number;
	 *
	 * An ItemT is therefore a rule, an action call, a terminal or TODO
	 * (rename, name) already declared in a TableT.
	 */
    ItemT *			item_head;
    ItemT *		       *item_tail;
} AltT;

typedef struct RuleT {
	/*
	 * The EntryT in the hash table that holds this rule.
	 * XXX I don't know why entry is necessary
	 */
    EntryT *			entry;

	/*
	 * The type specification of the input and output parameters of a rule
	 * respectively.
	 */
    TypeTupleT			param;
    TypeTupleT			result;

	/*
	 * A type tuple  of all the non-locals declared in the rule. It does not
	 * include the non-locals declared in an enclosing rules.
	 * TODO This should be checked once again.
	 */
    NonLocalListT		non_locals;

    NStringT			maximum_scope;

	/*
	 * True if the rule has been defined, false if it hasn't been defined yet.
	 * This is necessary to verify that all declared rules have been defined.
	 * TODO what is a definition? During output?
	 */
    BoolT			defined;

	/*
	 * Set to true if the rule has an empty alternate.
	 * See .alt_head below.
	 */
    BoolT			has_empty_alt;

	/*
	 * True for all rules in the %entry% section of the .sid file. It is used
	 * only by rule-simp.c.
	 * XXX Surprisingly, this is not used to check that all rules are
	 * accessible: should we do that?
	 */
    BoolT			required;

    EntryListT			reverse_list;
    DFSStateT			dfs_state;
    struct RuleT	       *next_in_root_list;
    struct RuleT	       *next_in_dfs;
    struct RuleT	       *next_in_reverse_dfs;
    BoolT			no_cycles;
    unsigned			cycle_index;

	/*
	 * Indicates if the first set has already been computed.
	 */
    BoolT			computed_first_set;

	/*
	 * Indicates that we are currently computing the first set.
	 * It is currently not set back to false once the computation has
	 * terminated.
	 */
    BoolT			computing_first_set;

	/*
	 * This is a bitfield designed to contain what terminals are part of the
	 * first set of the rule. For a description of what the first set is, you
	 * may want to read a book on LL(1) parsing. Please note that after
	 * parsing, the first set has not been computed yet. In the program, the
	 * computation is done at the top level by grammar_compute_first_set().
	 */
    BitVecT			first_set;

    EntryListT			predicate_first;
    BoolT			see_through;
    unsigned			priority;
    BoolT			factored;
    struct RuleT	       *tail_group;
    BoolT			being_inlined;
    BoolT			checked_for_inlining;
    EntryListT			call_list;
    struct RuleT	       *next_in_table;
    BitVecT			follow_set;
    EntryListT			predicate_follow;
    BoolT			started_follows;
    AltT *			see_through_alt;
    BoolT			needs_function;
    BoolT			all_basics;
    SaveRStackT			rstack_state;
    SaveRStackT			non_local_state;
    BoolT			being_output;
    unsigned			start_label;
    unsigned			call_count;
    unsigned			end_label;
    BoolT			used_end_label;
    unsigned			next_label;
    unsigned			handler_label;
    BoolT			used_handler_label;


	/*
	 * The exception handler alternate. There can only be one for each rule.
	 * This is specified after ## in the .sid file.
	 */
    AltT *			handler;

	/*
	 * The list of the alternatives except the empty alternate (epsilon rule)
	 * marked as $; in the .sid file. For that, see .has_empty_alt instead.
	 */
    AltT *			alt_head;
    AltT *		       *alt_tail;
} RuleT;

typedef struct RuleListT {
    RuleT *			head;
    RuleT *		       *tail;
} RuleListT;

typedef struct FactorClosureT {
    BitVecT			bitvec1;
    BitVecT			bitvec2;
    TableT *			table;
    EntryT *			predicate_id;
} FactorClosureT;

typedef struct SimpClosureT {
    BoolT			did_inline;
    TableT *			table;
} SimpClosureT;

typedef struct ClashListT {
    struct ClashListT	       *next;
    RuleT *			rule;
    AltT *			alt;
    ItemT *			item;
} ClashListT;


/*
 * Defined in "rule.c":
 */

RuleT *		rule_create(EntryT *);
void		rule_reinit(RuleT *);
EntryT *		rule_entry(RuleT *);
TypeTupleT *	rule_param(RuleT *);
TypeTupleT *	rule_result(RuleT *);
NonLocalListT *	rule_non_locals(RuleT *);
NStringT *		rule_maximum_scope(RuleT *);
BoolT		rule_is_defined(RuleT *);
void		rule_defined(RuleT *);
void		rule_add_alt(RuleT *, AltT *);
BoolT		rule_has_empty_alt(RuleT *);
void		rule_add_empty_alt(RuleT *);
BoolT		rule_has_one_alt(RuleT *);
void		rule_compute_result_intersect(RuleT *);
void		rule_compute_minimal_dataflow(RuleT *, TypeTupleT *);
BoolT		rule_is_required(RuleT *);
void		rule_required(RuleT *);
void		rule_compute_reverse_list(RuleT *, CycleTypeT);
void		rule_reinit_reverse_list(RuleT *);
EntryListT *	rule_reverse_list(RuleT *);
void		rule_set_dfs_state(RuleT *, DFSStateT);
RuleT *		rule_next_in_root_list(RuleT *);
void		rule_build_root_list(EntryT *, void *);
RuleT *		rule_get_next_in_dfs(RuleT *);
void		rule_compute_dfs(RuleT *, CycleTypeT, RuleT * *);
RuleT *		rule_get_next_in_reverse_dfs(RuleT *);
RuleT *	       *rule_next_in_reverse_dfs_ref(RuleT *);
void		rule_compute_reverse_dfs(RuleT *, RuleT *, RuleT * *);
BoolT		rule_has_no_cycles(RuleT *);
void		rule_no_cycles(RuleT *);
unsigned		rule_get_cycle_index(RuleT *);
void		rule_set_cycle_index(RuleT *, unsigned);
void		rule_reset_cycle_index(RuleT *);
BoolT		rule_has_computed_first_set(RuleT *);
void		rule_computed_first_set(RuleT *);
BoolT		rule_is_computing_first_set(RuleT *);
void		rule_computing_first_set(RuleT *);
BitVecT *		rule_first_set(RuleT *);
EntryListT *	rule_predicate_first(RuleT *);
BoolT		rule_is_see_through(RuleT *);
void		rule_see_through(RuleT *);
unsigned		rule_get_priority(RuleT *);
void		rule_set_priority(RuleT *, unsigned);
BoolT		rule_is_factored(RuleT *);
void		rule_factored(RuleT *);
RuleT *		rule_get_tail_group(RuleT *);
void		rule_set_tail_group(RuleT *, RuleT *);
BoolT		rule_is_being_inlined(RuleT *);
void		rule_being_inlined(RuleT *);
BoolT		rule_is_checked_for_inlining(RuleT *);
void		rule_checked_for_inlining(RuleT *);
EntryListT *	rule_call_list(RuleT *);
RuleT *		rule_get_next_in_table(RuleT *);
RuleT *	       *rule_get_next_in_table_ref(RuleT *);
void		rule_set_next_in_table(RuleT *, RuleT *);
BitVecT *		rule_follow_set(RuleT *);
EntryListT *	rule_predicate_follow(RuleT *);
BoolT		rule_has_started_follows(RuleT *);
void		rule_started_follows(RuleT *);
void		rule_set_see_through_alt(RuleT *, AltT *);
AltT *		rule_see_through_alt(RuleT *);
BoolT		rule_needs_function(RuleT *);
void		rule_will_need_function(RuleT *);
BoolT		rule_is_all_basics(RuleT *);
void		rule_all_basics(RuleT *);
SaveRStackT *	rule_rstack_state(RuleT *);
SaveRStackT *	rule_non_local_state(RuleT *);
BoolT		rule_is_being_output(RuleT *);
void		rule_being_output(RuleT *);
void		rule_not_being_output(RuleT *);
unsigned		rule_get_start_label(RuleT *);
void		rule_set_start_label(RuleT *, unsigned);
unsigned		rule_get_call_count(RuleT *);
void		rule_inc_call_count(RuleT *);
unsigned		rule_get_end_label(RuleT *);
void		rule_set_end_label(RuleT *, unsigned);
BoolT		rule_used_end_label(RuleT *);
unsigned		rule_get_next_label(RuleT *);
void		rule_set_next_label(RuleT *, unsigned);
unsigned		rule_get_handler_label(RuleT *);
void		rule_set_handler_label(RuleT *, unsigned);
BoolT		rule_used_handler_label(RuleT *);
AltT *		rule_get_handler(RuleT *);
void		rule_set_handler(RuleT *, AltT *);
AltT *		rule_alt_head(RuleT *);
void		rule_renumber(RuleT *, BoolT, EntryT *);
void		rule_iter_for_table(RuleT *, BoolT,
					    void(*)(EntryT *, void *),
					    void *);
void		rule_deallocate(RuleT *);

void		write_rule_lhs(OStreamT *, RuleT *);
void		write_rule(OStreamT *, RuleT *);

void		rule_list_init(RuleListT *);
void		rule_list_append (RuleListT *, RuleT *, RuleT * *);
void		rule_list_terminate(RuleListT *);
RuleT *		rule_list_head(RuleListT *);


/*
 * Defined in "rule-check.c":
 */

void		rule_check_first_set(EntryT *, void *);
void		rule_compute_follow_set(EntryT *, void *);
void		rule_compute_see_through_alt(EntryT *, void *);
void		rule_compute_alt_first_sets(EntryT *, void *);

void		write_clashes(OStreamT *, ClashListT *);


/*
 * Defined in "rule-factor.c":
 */

void		rule_factor(EntryT *, void *);
void		rule_set_factor_limit(unsigned);


/*
 * Defined in "rule-firsts.c":
 */

void		rule_compute_first_set_1(RuleT *);
void		rule_compute_first_set(EntryT *, void *);


/*
 * Defined in "rule-lre.c":
 */

void		rule_remove_left_cycle(RuleT *, EntryT *, TableT *);


/*
 * Defined in "rule-mutate.c":
 */

void		rule_compute_mutations(EntryT *, void *);


/*
 * Defined in "rule-names.c":
 */

void		rule_recompute_alt_names(EntryT *, void *);


/*
 * Defined in "rule-simp.c":
 */

void		rule_remove_duplicates(TableT *, EntryT *);


/*
 * Defined in "rule-tail.c":
 */

void		rule_handle_tails(RuleT *);
void		rule_compute_all_basics(EntryT *, void *);
void		rule_compute_inlining(EntryT *, void *);
void		rule_compute_needed_functions(EntryT *, void *);
void		rule_handle_need_functions(RuleT *);
BoolT		rule_get_inline_tail_calls(void);
void		rule_set_inline_tail_calls(BoolT);
void		rule_set_inline_all_basics(BoolT);
void		rule_set_inline_singles(BoolT);
void		rule_set_inline_non_tail_calls(BoolT);
void		rule_set_multiple_inlining(BoolT);


/*
 * Defined in "alt.c":
 */

AltT *		alt_create(void);
AltT *		alt_create_merge(ItemT *, ItemT *, TypeTransT *, TableT *);
AltT *		alt_duplicate(AltT *);
BoolT		alt_less_than(AltT *, AltT *);
BoolT		alt_equal(AltT *, AltT *);
AltT *		alt_next(AltT *);
AltT *	       *alt_next_ref(AltT *);
void		alt_set_next(AltT *, AltT *);
TypeTupleT *	alt_names(AltT *);
BitVecT *		alt_first_set(AltT *);
ItemT *		alt_item_head(AltT *);
ItemT *		alt_unlink_item_head(AltT *);
void		alt_add_item(AltT *, ItemT *);
AltT *		alt_deallocate(AltT *);

void		write_alt(OStreamT *, AltT *);
void		write_alt_highlighting(OStreamT *, AltT *, ItemT *);


/*
 * Defined in "item.c":
 */

ItemT *		item_create(EntryT *);
ItemT *		item_duplicate(ItemT *);
ItemT *		item_duplicate_and_translate(ItemT *, TypeTransT *, TableT *);
void		item_translate_list(ItemT *, TypeBTransT *);
void		item_to_predicate(ItemT *);
ItemT *		item_next (ItemT *);
ItemT *	       *item_next_ref(ItemT *);
void		item_set_next(ItemT *, ItemT *);
EntryT *		item_entry(ItemT *);
void		item_set_entry(ItemT *, EntryT *);
EntryTypeT	item_type(ItemT *);
BoolT		item_is_rule(ItemT *);
BoolT		item_is_action(ItemT *);
BoolT		item_is_predicate(ItemT *);
BoolT		item_is_basic(ItemT *);
BoolT		item_is_rename(ItemT *);
TypeTupleT *	item_param(ItemT *);
void		item_add_param(ItemT *, TypeTupleT *);
TypeTupleT *	item_result(ItemT *);
void		item_add_result(ItemT *, TypeTupleT *);
BoolT		item_is_inlinable(ItemT *);
void		item_inlinable(ItemT *);
BoolT		item_is_tail_call(ItemT *);
void		item_tail_call(ItemT *);
BoolT		item_names_used_in_list(ItemT *, TypeTupleT *);
void		item_compute_minimal_dataflow(ItemT *, TypeTupleT *);
ItemT *		item_deallocate(ItemT *);

void		write_item(OStreamT *, ItemT *);

#endif /* !defined (H_RULE) */
