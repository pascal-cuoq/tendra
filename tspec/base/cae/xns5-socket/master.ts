# Copyright 2014, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.

# This is Chapter 9, "Sockets Headers"
# of the CAE Networking Services (XNS) Issue 5,
# Specified by The Open Group. Document number C523,
# ISBN: 1-85912-165-9 published Feburary 1997.

$UNIQUE = 1;
$VERSION = "2.8";

$INFO = "X/Open CAE XNS Issue 5 - Sockets Headers";

+IMPLEMENT "cae/xns5-socket", "sys/socket.h.ts";
+IMPLEMENT "cae/xns5-socket", "sys/stat.h.ts";
+IMPLEMENT "cae/xns5-socket", "sys/uio.h.ts";
+IMPLEMENT "cae/xns5-socket", "sys/un.h.ts";

+IMPLEMENT "cae/xns5-socket", "fcntl.h.ts";

