# $NetBSD: Makefile,v 1.1 2015/04/23 23:22:27 pgoyette Exp $

.include "../Makefile.inc"

.PATH:	${S}/dev/sysmon

KMOD=	sysmon_envsys

SRCS=	sysmon_envsys.c
SRCS+=	sysmon_envsys_events.c
SRCS+=	sysmon_envsys_tables.c
SRCS+=	sysmon_envsys_util.c

.include <bsd.kmodule.mk>
