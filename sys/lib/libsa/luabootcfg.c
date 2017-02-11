/* $NetBSD$ */

#include <sys/types.h>
#include <sys/reboot.h>

#include <lib/libsa/stand.h>
#include <lib/libsa/luabootcfg.h>
#include <lib/libkern/libkern.h>

#include <lua.h>
#include <lauxlib.h>

static int lua_banner(lua_State *); 

void
bootcfg_do_noop()
{
	/* nothing */
}

void
perform_bootcfg(const char *conf)
{
	bootcfg_info.L = luaL_newstate();
}


/*
 * The banner() command.
 */
static int
lua_banner(lua_State *L)
{
	return 0;
}
