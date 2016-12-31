/*
 * $NetBSD$
 */

#include <stdio.h>
#include <stdlib.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

static int luakq_hello(lua_State *);
int luaopen_kqueue(lua_State *);

const luaL_Reg luakq_functions[] = {
	{"hello", luakq_hello},
	{NULL, NULL}
};

static int
luakq_hello(lua_State *L)
{
	return 0;
}


int
luaopen_kqueue(lua_State *L)
{
	luaL_newlib(L, luakq_functions);
	return 1;
}
