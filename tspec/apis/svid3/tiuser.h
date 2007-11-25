#   		 Crown Copyright (c) 1997
#   
#   This TenDRA(r) Computer Program is subject to Copyright
#   owned by the United Kingdom Secretary of State for Defence
#   acting through the Defence Evaluation and Research Agency
#   (DERA).  It is made available to Recipients with a
#   royalty-free licence for its use, reproduction, transfer
#   to other parties and amendment for any purpose not excluding
#   product development provided that any such use et cetera
#   shall be deemed to be acceptance of the following conditions:-
#   
#       (1) Its Recipients shall ensure that this Notice is
#       reproduced upon any copies or amended versions of it;
#   
#       (2) Any amended version of it shall be clearly marked to
#       show both the nature of and the organisation responsible
#       for the relevant amendment or amendments;
#   
#       (3) Its onward transfer from a recipient to another
#       party shall be deemed to be that party's acceptance of
#       these conditions;
#   
#       (4) DERA gives no warranty or assurance as to its
#       quality or suitability for any purpose and DERA accepts
#       no liability whatsoever in relation to any use to which
#       it may be put.
#
+USE "svid3", "fcntl.h" ;

+CONST int T_BIND, T_CALL, T_OPTMGMT, T_DIS, T_UNITDATA, T_UDERROR, T_INFO ;
+CONST int T_ADDR, T_OPT, T_UDATA, T_ALL ;
+CONST int T_UNBND, T_IDLE, T_OUTCON, T_INCON, T_DATAXFER, T_OUTREL ;
+CONST int T_INREL, T_UNINIT ;
+CONST int T_LISTEN, T_CONNECT, T_DATA, T_EXDATA, T_DISCONNECT, T_ERROR ;
+CONST int T_UDERR, T_ORDREL ;
+CONST int T_COTS, T_COTS_ORD, T_CLTS ;
+CONST int T_NEGOTIATE, T_CHECK, T_DEFAULT ;
+CONST int T_MORE, T_EXPEDITED ;

+FIELD struct netbuf {
    unsigned int maxlen ;
    unsigned int len ;
    char *buf ;
} ;

+FIELD struct t_bind | t_bind_struct {
    struct netbuf addr ;
    unsigned qlen ;
} ;

+FIELD struct t_call {
    struct netbuf addr ;
    struct netbuf opt ;
    struct netbuf udata ;
    int sequence ;
} ;

+FIELD struct t_info {
    long addr ;
    long options ;
    long tsdu ;
    long etsdu ;
    long connect ;
    long discon ;
    long servtype ;
} ;

+FIELD struct t_optmgmt | t_optmgmt_struct {
    struct netbuf opt ;
    long flags ;
} ;

+FIELD struct t_discon {
    struct netbuf udata ;
    int reason ;
    int sequence ;
} ;

+FIELD struct t_unitdata {
    struct netbuf addr ;
    struct netbuf opt ;
    struct netbuf udata ;
} ;

+FIELD struct t_uderr {
    struct netbuf addr ;
    struct netbuf opt ;
    long error ;
} ;

+CONST int TACCES, TBADADDR, TBADDATA, TBADF, TBADFLAG, TBADOPT, TBADSEQ ;
+CONST int TBUFOVFLW, TFLOW, TLOOK, TNOADDR, TNODATA, TNODIS, TNOREL ;
+CONST int TNOTSUPPORT, TNOUDERR, TOUTSTATE, TSTATECHNG, TSYSERR ;

+EXP (extern) int t_errno ;
+EXP (extern) char *t_errlist [] ;
+EXP (extern) int t_nerr ;

+FUNC int t_accept ( int, int, struct t_call * ) ;
+FUNC char *t_alloc ( int, int, int ) ;
+FUNC int t_bind ( int, struct t_bind *, struct t_bind * ) ;
+FUNC int t_close ( int ) ;
+FUNC int t_connect ( int, struct t_call *, struct t_call * ) ;
+FUNC void t_error ( const char * ) ;
+FUNC int t_free ( char *, int ) ;
+FUNC int t_getinfo ( int, struct t_info * ) ;
+FUNC int t_getstate ( int ) ;
+FUNC int t_listen ( int, struct t_call * ) ;
+FUNC int t_look ( int ) ;
+FUNC int t_open ( const char *, int, struct t_info * ) ;
+FUNC int t_optmgmt ( int, struct t_optmgmt *, struct t_optmgmt * ) ;
+FUNC int t_rcv ( int, char *, unsigned, int * ) ;
+FUNC int t_rcvconnect ( int, struct t_call * ) ;
+FUNC int t_rcvdis ( int, struct t_discon * ) ;
+FUNC int t_rcvrel ( int ) ;
+FUNC int t_rcvudata ( int, struct t_unitdata *, int * ) ;
+FUNC int t_rcvuderr ( int, struct t_uderr * ) ;
+FUNC int t_snd ( int, const void *, unsigned, int ) ;
+FUNC int t_snddis ( int, struct t_call * ) ;
+FUNC int t_sndrel ( int ) ;
+FUNC int t_sndudata ( int, struct t_unitdata * ) ;
+FUNC int t_sync ( int ) ;
+FUNC int t_unbind ( int ) ;
