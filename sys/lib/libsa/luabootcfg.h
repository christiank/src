/* $NetBSD$ */

#include <lua.h>

struct bootcfg_def {
	lua_State *L;
};

extern struct bootcfg_def bootcfg_info;

void perform_bootcfg(const char *conf);
void bootcfg_do_noop(void);
