/*
 * Automatically generated from the files:
 *	syntax.sid
 * and
 *	syntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#line 188 "syntax.act"


/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef SYNTAX_INCLUDED
#define SYNTAX_INCLUDED

#line 26 "syntax.h"

/* BEGINNING OF FUNCTION DECLARATIONS */

#ifndef __SID_SPLIT
extern void parse_init(IDENTIFIER, EXP *);
extern void parse_tok_type(TYPE *);
extern void parse_type_param(IDENTIFIER *);
extern void parse_type(TYPE *);
extern void parse_file(TYPE, DECL_SPEC);
extern void parse_offset(OFFSET, TYPE, OFFSET *, TYPE *);
extern void parse_nat(EXP *);
extern void parse_param(TYPE, int, IDENTIFIER *);
extern void parse_func(EXP *);
extern void parse_id(IDENTIFIER *);
extern void parse_exp(EXP *);
extern void parse_stmt(EXP *);
extern void parse_mem_type(TYPE *);
extern void parse_operator(IDENTIFIER *);
extern void parse_decl(TYPE, DECL_SPEC);
#else /* __SID_SPLIT */
extern void ZR1397(NAMESPACE *, IDENTIFIER *);
extern void ZR1270(NAMESPACE *, EXP *);
extern void ZRbase_Htype_Hspecifier(BASE_TYPE *);
extern void ZR1271(EXP *);
extern void ZRmem_Hinitialiser_Hlist(NAMESPACE);
extern void ZRdecl_Hspecifier_Hseq(TYPE, BASE_TYPE *, TYPE *, CV_SPEC *, DECL_SPEC *);
extern void ZR1401(NAMESPACE *, IDENTIFIER *, IDENTIFIER *);
extern void ZRclose_Hsquare_Hx(void);
extern void ZRnested_Hid(NAMESPACE, IDENTIFIER *);
extern void ZRdeclarator_Htail(IDENTIFIER, TYPE *, int *);
extern void ZR1148(EXP, EXP *);
extern void ZRparameter_Hdeclaration(TYPE, int, IDENTIFIER *);
extern void ZRboolean_Hliteral(EXP *);
extern void ZR1405(NAMESPACE *, IDENTIFIER *, IDENTIFIER *);
extern void ZRnonempty_Hnested_Hname(NAMESPACE *);
extern void ZRtarget_Hcondition(EXP *);
extern void ZR1152(TYPE, TYPE *);
extern void ZRfield_Hid_Hexpression(NAMESPACE, IDENTIFIER *);
extern void ZRdecl_Hspecifier(TYPE, BASE_TYPE *, TYPE *, CV_SPEC *, DECL_SPEC *);
extern void parse_init(IDENTIFIER, EXP *);
extern void ZR1408(NAMESPACE *, IDENTIFIER *, IDENTIFIER *);
extern void ZRdeclaration_Hseq_Hopt(TYPE, DECL_SPEC);
extern void ZRabstract_Hdeclarator_Htail(TYPE *);
extern void ZRscoped_Hstatement(EXP, EXP *);
extern void ZRbase_Hspecifier(void);
extern void ZRinit_Hdeclarator(DECL_SPEC, BASE_TYPE, TYPE, ACCESS_LIST);
extern void ZRdeclaration(TYPE, DECL_SPEC, EXP *);
extern void ZRinitialiser_Hexp_Hlist(IDENTIFIER, SID_LIST_EXP *);
extern void ZR1287(EXP *);
extern void ZRcontrol_Hstatement(EXP *);
extern void ZRfull_Hqualified_Htype(IDENTIFIER *);
extern void ZRctor_Hinitialiser_Hopt(EXP, EXP *, EXP *);
extern void ZR1289(EXP *);
extern void ZRunqualified_Htype(IDENTIFIER *);
extern void ZRexception_Hdeclaration(int, IDENTIFIER *);
extern void ZRclass_Hkey(BASE_TYPE *);
extern void ZRinitialiser_Hlist(IDENTIFIER, SID_LIST_EXP *);
extern void ZRmember_Hcond_Hhead(EXP *);
extern void parse_tok_type(TYPE *);
extern void ZR1164(TYPE, IDENTIFIER, TYPE *, IDENTIFIER *);
extern void ZRequality_Hoperator(void);
extern void ZRmaxmin_Hexpression(EXP *);
extern void ZRmem_Hinitialiser(NAMESPACE);
extern void ZR1292(EXP *, EXP *);
extern void ZRinset_Hflow_Hexpression(EXP *);
extern void ZR1293(EXP *, SID_LIST_EXP *);
extern void ZR1294(EXP *);
extern void ZRdelete_Hoperator(int *);
extern void parse_type_param(IDENTIFIER *);
extern void ZRmember_Hspecification_Hopt(TYPE, DECL_SPEC);
extern void ZRclose_Hround_Hx(void);
extern void ZRtypeid_Hexpression(int, EXP *);
extern void ZR1170(EXP, EXP *);
extern void ZRsizeof_Hexpression(int, EXP *);
extern void ZRunqualified_Hid(IDENTIFIER *);
extern void ZRtry_Hblock(EXP *);
extern void ZR920(TYPE *, BASE_TYPE *, TYPE *, CV_SPEC *, DECL_SPEC *, BASE_TYPE *, TYPE *, CV_SPEC *, DECL_SPEC *);
extern void ZRtemplate_Hdeclaration(TYPE, DECL_SPEC, EXP *);
extern void ZRparameter_Hdeclarator_Haux_Hopt(TYPE *, IDENTIFIER *);
extern void ZRparameter_Hdeclarator_Hopt(TYPE, TYPE *, IDENTIFIER *);
extern void ZRasm_Hdefinition(EXP *);
extern void ZR1432(int *, int *, int *, EXP *);
extern void ZRnew_Hinitialiser_Hopt(TYPE, EXP *);
extern void ZRconditional_Hexpression(EXP *);
extern void ZRparameter_Htail(int, TYPE *);
extern void ZR1433(int *, EXP *);
extern void ZR1434(int *);
extern void ZR1180(TYPE, IDENTIFIER, int, TYPE *, IDENTIFIER *, int *);
extern void ZRdeclarator_Hid(IDENTIFIER *);
extern void parse_type(TYPE *);
extern void ZRcondition_Hdeclarator(IDENTIFIER *);
extern void ZRdesignator_Hlist(OFFSET, TYPE, OFFSET *, TYPE *);
extern void ZR1435(int *);
extern void ZRany_Hqualified_Htype(IDENTIFIER *);
extern void ZRnew_Hdeclarator_Hopt(TYPE *);
extern void ZRdeclaration_Hcond_Hhead(EXP *);
extern void ZR1436(IDENTIFIER *, EXP *);
extern void ZRdeclarator_Haux(TYPE *, IDENTIFIER *, int *);
extern void ZRshift_Hexpression(EXP *);
extern void ZRfor_Hcond_Hstatement(EXP *, EXP *);
extern void ZRconversion_Hdeclarator_Hopt(TYPE *);
extern void ZRenumerator_Hdefinition(IDENTIFIER);
extern void ZRdeclarator(TYPE, TYPE *, IDENTIFIER *, int *);
extern void ZRinitialiser_Hopt(int, IDENTIFIER, EXP *);
extern void parse_file(TYPE, DECL_SPEC);
extern void ZR1439(EXP *, EXP *);
extern void ZRfunction_Hdefinition_Hbody(EXP *);
extern void ZRexport_Hopt(int *);
extern void parse_offset(OFFSET, TYPE, OFFSET *, TYPE *);
extern void parse_nat(EXP *);
extern void ZRinitialiser_Hexpression(EXP *);
extern void parse_param(TYPE, int, IDENTIFIER *);
extern void ZR1442(EXP *);
extern void ZR1315(NAMESPACE *, IDENTIFIER *, IDENTIFIER *);
extern void ZRtype_Hspecifier_Hseq(BASE_TYPE *, TYPE *, CV_SPEC *);
extern void ZR1443(EXP *);
extern void ZR1316(NAMESPACE *, IDENTIFIER *);
extern void ZRqualified_Htype(IDENTIFIER *);
extern void ZRtype_Hid_Hlist(SID_LIST_TYPE *);
extern void ZRany_Hqualified_Hid(IDENTIFIER *);
extern void ZRabstract_Hdeclarator_Haux(TYPE *);
extern void parse_func(EXP *);
extern void ZR1318(NAMESPACE *, NAMESPACE *, IDENTIFIER *);
extern void ZR1191(EXP, EXP, int, EXP *, EXP *, int *);
extern void ZRpseudo_Hdestr_Hsuffix(IDENTIFIER *, BASE_TYPE *);
extern void ZRmember_Hcond_Hbody(void);
extern void ZRtop_Hqualified_Htype(IDENTIFIER *);
extern void ZRstorage_Hclass_Hspecifier(DECL_SPEC *);
extern void ZR1320(NAMESPACE *, NAMESPACE *, IDENTIFIER *);
extern void parse_id(IDENTIFIER *);
extern void ZR1322(int *);
extern void ZR1195(EXP, EXP *);
extern void ZRcast_Hexpression(EXP *);
extern void ZRtype_Hspecifier(TYPE, BASE_TYPE *, TYPE *, CV_SPEC *);
extern void ZRparameter_Hdeclaration_Hclause(int *);
extern void ZRabstract_Hdeclarator_Hopt(TYPE, TYPE *);
extern void ZR1323(int *);
extern void ZRopen_Hround_Hx(void);
extern void ZR1324(int *);
extern void ZRenumerator_Hlist(IDENTIFIER);
extern void ZR1199(EXP, EXP *);
extern void ZRfor_Hinit_Hstatement(EXP *);
extern void ZRfunction_Htry_Hblock(EXP *);
extern void ZRdesignator(OFFSET, TYPE, OFFSET *, TYPE *);
extern void ZR1327(TYPE *, BASE_TYPE *, BASE_TYPE *, TYPE *, CV_SPEC *);
extern void ZRrelational_Hexpression(EXP *);
extern void ZRmember_Hdeclaration(TYPE, DECL_SPEC);
extern void ZR1328(TYPE *, BASE_TYPE *, TYPE *, CV_SPEC *);
extern void ZRfor_Hend_Hstatement(EXP *);
extern void ZR1329(int *);
extern void ZRnew_Htype_Hid(TYPE *, int *);
extern void ZRand_Hexpression(EXP *);
extern void ZR1330(int *);
extern void ZR1203(EXP, EXP *);
extern void parse_exp(EXP *);
extern void ZR1331(DECL_SPEC *);
extern void ZRdeclaration_Hnonempty(TYPE, DECL_SPEC, EXP *);
extern void ZR1078(BASE_TYPE *, DECL_SPEC *, TYPE *, ACCESS_LIST *, int *, IDENTIFIER *);
extern void ZRthrow_Hexpression(EXP *);
extern void ZR1079(BASE_TYPE *, DECL_SPEC *, TYPE *, ACCESS_LIST *);
extern void ZR1207(EXP, EXP *);
extern void parse_stmt(EXP *);
extern void ZRmember_Hdeclarator_Hlist(DECL_SPEC, TYPE, BASE_TYPE, ACCESS_LIST, int);
extern void ZRtype_Hid(TYPE *, int *);
extern void ZRflow_Hexpression(EXP *);
extern void ZRdeclaration_Hbasic(TYPE, DECL_SPEC);
extern void ZRdeclaration_Hcond_Hbody(void);
extern void ZR956(EXP *);
extern void ZR1211(EXP, EXP *);
extern void ZRoperator_Hname(int *);
extern void ZRcolon_Hx(void);
extern void ZRexpression_Hlist(SID_LIST_EXP *);
extern void ZRassignment_Hexpression(EXP *);
extern void ZR1342(TYPE *, BASE_TYPE *, TYPE *, CV_SPEC *, DECL_SPEC *);
extern void ZR1215(EXP, EXP *);
extern void ZRexpression_Hlist_Hopt(SID_LIST_EXP *);
extern void ZR1343(void);
extern void ZRlogical_Hand_Hexpression(EXP *);
extern void ZRjump_Hstatement(EXP *);
extern void ZR1471(IDENTIFIER *, EXP *);
extern void ZRcast_Hoperand(TYPE *, EXP *, int *);
extern void ZRtarget_Hcondition_Hhead(EXP *, EXP *, int *);
extern void ZRcv_Hqualifier_Hseq(CV_SPEC *);
extern void ZRfunction_Hbody(EXP, EXP *);
extern void ZR1473(IDENTIFIER *, EXP *);
extern void ZR1219(EXP, EXP *);
extern void ZR1347(NAMESPACE *, IDENTIFIER *);
extern void ZRcv_Hqualifier_Hseq_Hopt(CV_SPEC *);
extern void ZR1602(EXP *, EXP *);
extern void ZR1475(IDENTIFIER *, EXP *);
extern void ZR1348(NAMESPACE *, IDENTIFIER *);
extern void ZRcondition(EXP *);
extern void ZR1476(NAMESPACE *, EXP *);
extern void ZR1349(IDENTIFIER *);
extern void ZR1095(BASE_TYPE *, DECL_SPEC *, TYPE *, ACCESS_LIST *, IDENTIFIER *);
extern void ZR1477(NAMESPACE *, EXP *);
extern void ZR1223(EXP, EXP *);
extern void ZRbase_Hclause_Hopt(int *);
extern void ZRdirect_Hnew_Hdeclarator(TYPE *);
extern void ZR1478(EXP *);
extern void ZRany_Hnested_Hname(NAMESPACE *);
extern void ZRfall_Hcheck(void);
extern void ZRcv_Hqualifier(CV_SPEC *);
extern void ZRmember_Hcond(void);
extern void ZR1606(void);
extern void ZRunary_Hoperator(void);
extern void ZRmember_Hdeclarator(DECL_SPEC, TYPE, BASE_TYPE, ACCESS_LIST, int, IDENTIFIER *);
extern void ZR1227(EXP, EXP *);
extern void ZRany_Hnested_Hname_Hopt(NAMESPACE *);
extern void ZR1609(NAMESPACE *, IDENTIFIER *);
extern void ZRinitialiser_Hclause(IDENTIFIER, EXP *);
extern void ZRtemplate_Hmember_Hdecl(TYPE, DECL_SPEC);
extern void ZR1610(NAMESPACE *, IDENTIFIER *);
extern void ZRadditive_Hexpression(EXP *);
extern void ZRdirect_Hdeclarator(TYPE *, IDENTIFIER *, int *);
extern void ZR1611(IDENTIFIER *);
extern void ZRselection_Hstatement(EXP *);
extern void ZR1231(EXP, EXP *);
extern void ZRexpression(EXP *);
extern void ZRnew_Hplace_Hand_Htype(SID_LIST_EXP *, TYPE *, int *);
extern void ZRstatement_Hseq_Hopt(EXP, EXP *);
extern void ZRfunction_Hspecifier(DECL_SPEC *);
extern void ZR1235(EXP, EXP *);
extern void ZRstatement(EXP *);
extern void ZRdirect_Habstract_Hdeclarator(TYPE *);
extern void ZRhandler_Hseq_Hopt(EXP);
extern void ZR1239(EXP, EXP *);
extern void ZRiteration_Hstatement(EXP *);
extern void ZRassignment_Hoperator(void);
extern void ZR1368(DECL_SPEC *, TYPE *, BASE_TYPE *, ACCESS_LIST *, int *, IDENTIFIER *, IDENTIFIER *);
extern void ZRexpression_Hstatement(EXP *);
extern void ZRdeclaration_Hother(EXP *);
extern void ZRmember_Hdesignator(OFFSET, TYPE, OFFSET *, TYPE *);
extern void ZRany_Hclass_Hname(IDENTIFIER *);
extern void ZRhandler(EXP);
extern void ZRdeclaration_Hcond(void);
extern void ZR1243(EXP, EXP *);
extern void ZRpm_Hexpression(EXP *);
extern void ZR1371(DECL_SPEC *, TYPE *, BASE_TYPE *, ACCESS_LIST *, int *, IDENTIFIER *, IDENTIFIER *);
extern void ZRtemplate_Hopt(NAMESPACE, int *);
extern void ZRaccess_Hspecifier(DECL_SPEC *);
extern void ZRusing_Hdeclaration(void);
extern void ZR1374(TYPE *, IDENTIFIER *);
extern void parse_mem_type(TYPE *);
extern void ZR872(IDENTIFIER *);
extern void parse_operator(IDENTIFIER *);
extern void ZRmember_Hspecifier_Hopt(EXP *);
extern void ZRinclusive_Hor_Hexpression(EXP *);
extern void ZR1255(TYPE *, BASE_TYPE *, TYPE *, CV_SPEC *, DECL_SPEC *);
extern void ZRjump_Hlabel(EXP *);
extern void ZRsimple_Htype_Hspecifier(BASE_TYPE *, TYPE *);
extern void ZRcomma_Hexpression_Htail(SID_LIST_EXP *);
extern void ZRparameter_Hdeclaration_Hlist(int *);
extern void ZR1257(TYPE *, DECL_SPEC *, BASE_TYPE *, TYPE *, CV_SPEC *, EXP *);
extern void ZRliteral(EXP *);
extern void ZRexception_Hspecification_Hopt(SID_LIST_TYPE *);
extern void parse_decl(TYPE, DECL_SPEC);
extern void ZR1385(TYPE *, TYPE *);
extern void ZR1258(void);
extern void ZR1004(IDENTIFIER *, SID_LIST_EXP *);
extern void ZR1386(TYPE *);
extern void ZR1387(SID_LIST_TYPE *);
extern void ZR1260(void);
extern void ZRexclusive_Hor_Hexpression(EXP *);
extern void ZRcompound_Hstatement(EXP *);
extern void ZR1261(EXP *);
extern void ZRsemicolon_Hx(void);
extern void ZRlogical_Hor_Hexpression(EXP *);
extern void ZRconstant_Hexpression(EXP *);
extern void ZRtemplate_Hparam_Hname(IDENTIFIER *);
extern void ZR1262(EXP *);
extern void ZR501(SID_LIST_EXP *);
extern void ZRptr_Hoperator(TYPE *);
extern void ZRbase_Hspecifier_Hlist(void);
extern void ZRlinkage_Hspecification(TYPE, DECL_SPEC, EXP *);
extern void ZR1265(EXP *, EXP *);
extern void ZRequality_Hexpression(EXP *);
extern void ZRinit_Hdeclarator_Hlist(DECL_SPEC, BASE_TYPE, TYPE, ACCESS_LIST);
extern void ZR1267(EXP *, EXP *);
extern void ZRmultiplicative_Hexpression(EXP *);
extern void ZR1269(NAMESPACE *, EXP *);
extern void ZR1142(TYPE, TYPE *);
extern void ZR888(BASE_TYPE *, TYPE *, CV_SPEC *, BASE_TYPE *, TYPE *, CV_SPEC *);
extern int ZI0;
#endif /* __SID_SPLIT */

/* BEGINNING OF TERMINAL DEFINITIONS */

#define lex_double (102)
#define lex_arith_Hcap (177)
#define lex_macro_Harg (349)
#define lex_hash_Helse (28)
#define lex_private (142)
#define lex_incompatible (242)
#define lex_new_Harray_Hfull (352)
#define lex_ifdef (233)
#define lex_reject (291)
#define lex_compute (193)
#define lex_dollar (207)
#define lex_tendra (309)
#define lex_unreachable (323)
#define lex_vtable (331)
#define lex_inline (137)
#define lex_public (144)
#define lex_namespace_Hname (3)
#define lex_hash_H1 (51)
#define lex_either (208)
#define lex_hash_H2 (90)
#define lex_catch (128)
#define lex_const_Hcast (130)
#define lex_pointer (276)
#define lex_inset_Hstart (347)
#define lex_full_Hname (9)
#define lex_nested (264)
#define lex_suspend (306)
#define lex_break (95)
#define lex_begin (182)
#define lex_ignore (235)
#define lex_volatile_Ht (330)
#define lex_assign (36)
#define lex_endif (212)
#define lex_hash_Hhash_Hop (346)
#define lex_keyword (251)
#define lex_promote (283)
#define lex_wstring_Hlit (15)
#define lex_static (117)
#define lex_virtual (155)
#define lex_extend (220)
#define lex_this_Hname (311)
#define lex_minus_Hminus (61)
#define lex_lvalue (257)
#define lex_struct_Hcap (305)
#define lex_inset_Hend (348)
#define lex_lshift (57)
#define lex_open_Hround (65)
#define lex_false (135)
#define lex_block (184)
#define lex_scanf (297)
#define lex_wstring_Hexp (20)
#define lex_comma (42)
#define lex_union_Hcap (320)
#define lex_wchar_Hlit (13)
#define lex_func_Hcap (227)
#define lex_and_H1 (33)
#define lex_lshift_Heq (58)
#define lex_typeid (152)
#define lex_rvalue (295)
#define lex_string_Hlit (14)
#define lex_rshift (75)
#define lex_sizeof (116)
#define lex_and_H2 (157)
#define lex_unknown (0)
#define lex_wchar_Hexp (18)
#define lex_after (169)
#define lex_macro (258)
#define lex_precedence (279)
#define lex_undef (318)
#define lex_type_Hname (2)
#define lex_switch (119)
#define lex_assert (180)
#define lex_octal (269)
#define lex_ptrdiff_Ht (286)
#define lex_ident (231)
#define lex_printf (281)
#define lex_string_Hexp (19)
#define lex_and_Heq_H1 (34)
#define lex_reinterpret_Hcast (145)
#define lex_depth (202)
#define lex_unused (324)
#define lex_char_Hlit (12)
#define lex_rshift_Heq (76)
#define lex_arrow_Hstar (82)
#define lex_float (106)
#define lex_class (129)
#define lex_and_Heq_H2 (158)
#define lex_bottom (185)
#define lex_nline (265)
#define lex_open_Hinit (353)
#define lex_extern (105)
#define lex_decl (197)
#define lex_proc_Hcap (282)
#define lex_string (304)
#define lex_typeof (315)
#define lex_while (125)
#define lex_conditional (194)
#define lex_new_Harray (351)
#define lex_char_Hexp (17)
#define lex_code (189)
#define lex_option (273)
#define lex_reachable (289)
#define lex_colon (41)
#define lex_case (96)
#define lex_import (238)
#define lex_char (97)
#define lex_value (326)
#define lex_logical_Hand_H1 (55)
#define lex_fall (223)
#define lex_tag_Hcap (308)
#define lex_logical_Hand_H2 (160)
#define lex_allow (172)
#define lex_array (178)
#define lex_elif (209)
#define lex_file (224)
#define lex_limit (252)
#define lex_name (262)
#define lex_hash_Hif (26)
#define lex_return (113)
#define lex_token (312)
#define lex_close_Hbrace_H1 (38)
#define lex_export (134)
#define lex_reset (293)
#define lex_close_Hbrace_H2 (88)
#define lex_compatible (191)
#define lex_extra (222)
#define lex_main (259)
#define lex_destructor_Hname (5)
#define lex_nat_Hcap (263)
#define lex_type_Hcap (314)
#define lex_struct (118)
#define lex_using (154)
#define lex_close_Htemplate (339)
#define lex_identifier (1)
#define lex_const (98)
#define lex_line (253)
#define lex_weak (333)
#define lex_else (103)
#define lex_delete_Harray_Hfull (343)
#define lex_union (121)
#define lex_statement_Hname (4)
#define lex_cast (186)
#define lex_error (215)
#define lex_arrow (35)
#define lex_bool (127)
#define lex_stmt_Hcap (303)
#define lex_unify (319)
#define lex_minus (59)
#define lex_new_Hfull (350)
#define lex_definition (201)
#define lex_int_Hcap (250)
#define lex_array_Hop (336)
#define lex_not_H1 (62)
#define lex_quote (288)
#define lex_backslash (37)
#define lex_long (111)
#define lex_not_H2 (162)
#define lex_exp_Hcap (218)
#define lex_dot_Hstar (84)
#define lex_short (114)
#define lex_namespace (139)
#define lex_character (187)
#define lex_minus_Heq (60)
#define lex_void (123)
#define lex_cond_Hop (340)
#define lex_hash_Hop (345)
#define lex_reference (290)
#define lex_va_Hargs (329)
#define lex_not_Heq_H1 (63)
#define lex_abs (85)
#define lex_enum (104)
#define lex_throw (149)
#define lex_not_Heq_H2 (163)
#define lex_incomplete (243)
#define lex_interface (247)
#define lex_end (211)
#define lex_less (53)
#define lex_xor_H1 (80)
#define lex_this (148)
#define lex_wchar_Ht (156)
#define lex_xor_H2 (166)
#define lex_all (171)
#define lex_eof (32)
#define lex_close_Hsquare_H1 (40)
#define lex_plus_Hplus (71)
#define lex_auto (94)
#define lex_goto (108)
#define lex_star (78)
#define lex_close_Hsquare_H2 (89)
#define lex_into (249)
#define lex_no_Hdef (267)
#define lex_off (271)
#define lex_func_Hop (344)
#define lex_environment (213)
#define lex_tag (307)
#define lex_less_Heq (54)
#define lex_xor_Heq_H1 (81)
#define lex_xor_Heq_H2 (167)
#define lex_size_Ht_H2 (300)
#define lex_unmatched (321)
#define lex_or_H1 (67)
#define lex_assignment (181)
#define lex_open_Hbrace_H1 (64)
#define lex_star_Heq (79)
#define lex_or_H2 (164)
#define lex_open_Hbrace_H2 (92)
#define lex_asm (126)
#define lex_true (150)
#define lex_un_Hknown (316)
#define lex_nested_Hname_Hstar (10)
#define lex_div (44)
#define lex_type (313)
#define lex_open_Htemplate (354)
#define lex_or_Heq_H1 (68)
#define lex_rem (73)
#define lex_min (87)
#define lex_dynamic_Hcast (132)
#define lex_directive (203)
#define lex_writeable (334)
#define lex_plus (69)
#define lex_or_Heq_H2 (165)
#define lex_max (86)
#define lex_text (310)
#define lex_delete_Harray (342)
#define lex_dot (46)
#define lex_for (107)
#define lex_bitfield (183)
#define lex_qualifier (287)
#define lex_div_Heq (45)
#define lex_rem_Heq (74)
#define lex_lit (255)
#define lex_sort (301)
#define lex_plus_Heq (70)
#define lex_new (140)
#define lex_variable (327)
#define lex_int (110)
#define lex_std (302)
#define lex_builtin_Hfile (337)
#define lex_conversion (195)
#define lex_exhaustive (217)
#define lex_set (298)
#define lex_logical_Hor_H1 (56)
#define lex_use (325)
#define lex_semicolon (77)
#define lex_if (109)
#define lex_logical_Hor_H2 (161)
#define lex_hash_Hpragma (30)
#define lex_protected (143)
#define lex_indented (244)
#define lex_implement (236)
#define lex_ambiguous (173)
#define lex_define_Hcap (199)
#define lex_do (101)
#define lex_decimal (196)
#define lex_defined (200)
#define lex_template_Htype (7)
#define lex_as (179)
#define lex_builtin_Hline (338)
#define lex_of (270)
#define lex_floating_Hexp (22)
#define lex_eq (48)
#define lex_open_Hsquare_H1 (66)
#define lex_open_Hsquare_H2 (93)
#define lex_nested_Hname (8)
#define lex_include_Hnext (241)
#define lex_hash_Hhash_H1 (52)
#define lex_hash_Hhash_H2 (91)
#define lex_delete_Hfull (341)
#define lex_directory (204)
#define lex_resolution (294)
#define lex_includes (240)
#define lex_template_Hid (6)
#define lex_hash_Hendif (29)
#define lex_no (266)
#define lex_on (272)
#define lex_scalar_Hcap (296)
#define lex_complete (192)
#define lex_discard (206)
#define lex_linkage (254)
#define lex_member_Hcap (261)
#define lex_size_Ht (299)
#define lex_try (151)
#define lex_implicit (237)
#define lex_zzzzzz (355)
#define lex_template (147)
#define lex_overload (275)
#define lex_unsigned (122)
#define lex_internal (248)
#define lex_unpostpone (322)
#define lex_alignof (170)
#define lex_disallow (205)
#define lex_volatile (124)
#define lex_longlong (256)
#define lex_explicit (133)
#define lex_static_Hcast (146)
#define lex_ellipsis_Hexp (210)
#define lex_identif (232)
#define lex_typename (153)
#define lex_argument (176)
#define lex_external (221)
#define lex_include (239)
#define lex_default (100)
#define lex_analysis (174)
#define lex_ellipsis (47)
#define lex_colon_Hcolon (83)
#define lex_continue (99)
#define lex_register (112)
#define lex_zzzz (335)
#define lex_integer_Hlit (16)
#define lex_function (228)
#define lex_variety_Hcap (328)
#define lex_greater (49)
#define lex_mutable (138)
#define lex_define (198)
#define lex_integer_Hexp (21)
#define lex_complex_Htype (25)
#define lex_anonymous (175)
#define lex_ifndef (234)
#define lex_promoted (284)
#define lex_full_Hname_Hstar (11)
#define lex_operator (141)
#define lex_preserve (280)
#define lex_close_Hround (39)
#define lex_initialization (245)
#define lex_integer (246)
#define lex_greater_Heq (50)
#define lex_accept (168)
#define lex_equality (214)
#define lex_escape (216)
#define lex_complex_Hstmt (24)
#define lex_typedef (120)
#define lex_explain (219)
#define lex_hash_Helif (27)
#define lex_newline (31)
#define lex_delete (131)
#define lex_hiding (230)
#define lex_comment (190)
#define lex_complex_Hexp (23)
#define lex_forward (226)
#define lex_overflow (274)
#define lex_object (268)
#define lex_unassert (317)
#define lex_warning (332)
#define lex_friend (136)
#define lex_member (260)
#define lex_pragma (278)
#define lex_compl_H1 (43)
#define lex_class_Hcap (188)
#define lex_float_Hcap (225)
#define lex_hexadecimal (229)
#define lex_prototype (285)
#define lex_question (72)
#define lex_signed (115)
#define lex_compl_H2 (159)
#define lex_postpone (277)
#define lex_representation (292)

/* BEGINNING OF TRAILER */

#line 2179 "syntax.act"



/*
    DUMMY LEXICAL TOKEN VALUES

    These values are used as lexical token values in certain circumstances
    but do not represent actual tokens.  Note that they are all negative.
*/

#define lex_ignore_token	-1
#define lex_end_condition	-2
#define lex_included		-3


#endif
#line 691 "syntax.h"

/* END OF FILE */
