
#pragma once

#include <lauxlib.h>
#include <lua.h>

#if defined(_WIN32) || defined(_WIN64)
#define LUA_LTIMER_WINDOWS
#endif

#if defined(_WIN32)
#define LUA_LTIMER_SYSTEM "win32"
#elif defined(_WIN64)
#define LUA_LTIMER_SYSTEM "win64"
#else
#define LUA_LTIMER_SYSTEM "other"
#endif

lua_Integer ltime_uclock(void);
void ltime_usleep(lua_Integer usec);
