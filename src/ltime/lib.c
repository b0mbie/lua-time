
#include <lua.h>
#include <lauxlib.h>

#include "ltime/lib.h"

#ifdef _MSC_VER
    #define EXPORT __declspec(dllexport)
#elif defined(__GNUC__)
    #define EXPORT __attribute__((visibility("default")))
#else
    #define EXPORT
    #warning Unknown dynamic link export semantics.
#endif

static int l_uclock(lua_State *L)
{
    lua_Integer ut = ltime_uclock();
    lua_pushinteger(L, ut);
    return 1;
}
static int l_usleep(lua_State *L)
{
    lua_Integer duration = luaL_checkinteger(L, 1);
    ltime_usleep(duration);
    return 0;
}
static int l_clock(lua_State *L)
{
    lua_pushnumber(L, ( (lua_Number)ltime_uclock() / 1000000 ));
    return 1;
}
static int l_sleep(lua_State *L)
{
    lua_Number duration = luaL_checknumber(L, 1);
    ltime_usleep(duration * 1000000);
    return 0;
}

EXPORT int luaopen_time(lua_State* L)
{
    static const struct luaL_Reg timerlib[] = {
        { "clock", l_clock },
        { "sleep", l_sleep },
        { "uclock", l_uclock },
        { "usleep", l_usleep },
        { NULL, NULL }
    };

    // Check Lua version.
    luaL_checkversion(L);

    // Fill library table with functions.
    luaL_newlibtable(L, timerlib);
    luaL_setfuncs(L, timerlib, 0);

    return 1;
}
