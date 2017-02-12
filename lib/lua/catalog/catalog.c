/* $NetBSD$ */

/*
 * catalog.c
 * Charlotte Koch <cfkoch@edgebsd.org>
 */

#include <stdio.h>
#include <stdlib.h>

#include <lua.h>
#include <lauxlib.h>

#include <nl_types.h>

int luaopen_catalog(lua_State *);
static int lua_catopen(lua_State *);
static int lua_catgets(lua_State *);
static int lua_catclose(lua_State *);

static const luaL_Reg catalog[] = {
	{"open", lua_catopen},
	{"gets", lua_catgets},
	{"close", lua_catclose},
	{NULL, NULL}
};

/*
 * cat = catalog.open(name)
 */
static int
lua_catopen(lua_State *L)
{
	const char *name = luaL_checkstring(L, 1); 
	nl_catd *catp = lua_newuserdata(L, sizeof(nl_catd));
	*catp = catopen(name, 0);
	luaL_setmetatable(L, "catalog");
	return 1;
}

/*
 * string = catalog.gets(cat, set_id, msg_iud, default)
 */
static int
lua_catgets(lua_State *L)
{
	nl_catd *catp = luaL_checkudata(L, 1, "catalog");
	int set_id = luaL_checkinteger(L, 2);
	int msg_id = luaL_checkinteger(L, 3);
	const char *default_s = luaL_checkstring(L, 4);
	const char *result = (const char *)catgets(*catp, set_id, msg_id, default_s);
	lua_pushstring(L, result);
	return 1;
}

/*
 * catalog.close(cat)
 */
static int
lua_catclose(lua_State *L)
{
	nl_catd *catp = luaL_checkudata(L, 1, "catalog");
	catclose(*catp);
	return 0;
}

int
luaopen_catalog(lua_State *L)
{
	luaL_newmetatable(L, "catalog");
	lua_pop(L, 1);
	luaL_newlib(L, catalog);
	lua_setglobal(L, "catalog");
	return 1;
}
