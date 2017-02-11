# $NetBSD$
#
#	Configuration variables (default values are below):
#
#	S	must be set to the top of the 'sys' tree.
#	LUADST	may be set to the location of the directory where library
#		objects are to be built.  Defaults to ${.OBJDIR}/lib/lua.
#	LUA_AS	may be set to 'obj' to build a object from the library's
#		object files.  (Otherwise, a library will be built.)
#		Defaults to 'library'.
#	LUAMISCCPPFLAGS
#		Miscellaneous cpp flags to be passed to the library's Makefile
#		when building.
#	LUAMISCMAKEFLAGS
#		Miscellaneous flags to be passed to the library's Makefile when
#		building.  See library's Makefile for more details about
#		supported flags and their default values.

# Default values:
LUADST?=		${.OBJDIR}/lib/lua
LUA_AS?=		library
LUADOTDIR?= ../../.

LUADIR=		${S:S@^.@${LUADOTDIR}@:Q}/lib/liblua
.if (${LUA_AS} == "obj")
LUA=		${LUADST}/liblua.o
LUA_PROF=	${LUADST}/liblua.po
.else
LUA=		${LUADST}/liblua.a
LUA=	${LUADST}/liblua_p.a
.endif

LUAMAKE= \
	cd ${LUADST} && ${MAKE} -f ${LUADIR:Q}/Makefile \
	    LUADIR=${LUADIR:Q} \
	    CC=${CC:Q} CFLAGS=${CFLAGS:Q} CPUFLAGS= \
	    AS=${AS:Q} AFLAGS=${AFLAGS:Q} \
	    LORDER=${LORDER:Q} \
	    TSORT=${TSORT:Q} \
	    LD=${LD:Q} STRIP=${STRIP:Q} \
	    AR=${AR:Q} NM=${NM:Q} \
	    RANLIB=${RANLIB:Q} SIZE=${SIZE:Q} \
	    MACHINE=${MACHINE} MACHINE_ARCH=${MACHINE_ARCH:Q} \
	    LUACPPFLAGS=${CPPFLAGS:S@^-I.@-I${LUADOTDIR}@g:Q} \
	    LUAMISCCPPFLAGS=${LUAMISCCPPFLAGS:Q} \
	    ${LUAMISCMAKEFLAGS}

${LUA}:		.NOTMAIN .MAKE __always_make_lua
	@echo making sure the lua library is up to date...
.if (${LUA_AS} == "library")
	@${LUAMAKE} liblua.a
.else
	@${LUAMAKE} liblua.o
.endif

${LUALIB_PROF}:		.NOTMAIN .MAKE __always_make_lua
	@echo making sure the profiled lua library is up to date...
.if (${LUA_AS} == "library")
	@${LUAMAKE} liblua_p.a
.else
	@${LUAMAKE} liblua.po
.endif

clean: .NOTMAIN cleanlua
cleanlua: .NOTMAIN
	@echo cleaning the lua library objects
	@if [ -d "${LUADST}" ]; then ${LUAMAKE} clean; fi

cleandir distclean: .NOTMAIN cleandirlua
cleandirlua: .NOTMAIN
	@echo cleandiring the lua library objects
	@if [ -d "${LUADST}" ]; then ${LUAMAKE} cleandir; fi

dependall depend: .NOTMAIN dependlua
dependlua: .NOTMAIN .MAKE __always_make_lua
	@echo depending the lua library objects
	@${LUAMAKE} depend

.PHONY: __always_make_lua
__always_make_lua: .NOTMAIN
	@mkdir -p ${LUADST}

.PHONY: cleanlua cleandirlua dependlua
