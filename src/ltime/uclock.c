
#include <lua.h>

#include "ltime/lib.h"

#define USECONDS_PER_SECOND 1000000LL

#ifdef LUA_LTIMER_WINDOWS
#include <inttypes.h>
#include <Windows.h>
#else
#include <time.h>
const lua_Integer NANOSECONDS_PER_MICROSECOND = 1000LL;
#endif

#define UNIX_TIME_START 0x019DB1DED53E8000LL
#define TICKS_PER_SECOND 10000000LL

lua_Integer ltime_uclock(void)
{
#ifdef LUA_LTIMER_WINDOWS
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);

    const DWORD64 fullTime =
        ( ((DWORD64)ft.dwHighDateTime << 32) |
        ft.dwLowDateTime) - UNIX_TIME_START;
    return (lua_Integer)((fullTime * USECONDS_PER_SECOND) /
        TICKS_PER_SECOND);
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return USECONDS_PER_SECOND * ts.tv_sec + ts.tv_nsec /
        NANOSECONDS_PER_MICROSECOND;
#endif
}
