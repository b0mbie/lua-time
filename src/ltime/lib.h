
#pragma once

#include <lauxlib.h>
#include <lua.h>

#if defined(_WIN32) || defined(_WIN64)
#define LUA_LTIME_WINDOWS
#endif

lua_Integer ltime_uclock(void);
void ltime_usleep(lua_Integer usec);
