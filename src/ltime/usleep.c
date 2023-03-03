
#include <lua.h>

#include "ltime/lib.h"

#ifdef LUA_LTIMER_WINDOWS
#include <inttypes.h>
#include <Windows.h>
#else
#include <unistd.h>
#endif

void ltime_usleep(lua_Integer usec)
{
#ifdef LUA_LTIMER_WINDOWS
    HANDLE timer;
    LARGE_INTEGER ft;
    // Convert to 100 nanosecond interval, negative value
    // indicates relative time.
    ft.QuadPart = -(10 * usec);
    timer = CreateWaitableTimer(NULL, TRUE, NULL);
    SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
    WaitForSingleObject(timer, INFINITE);
    CloseHandle(timer);
#else
    usleep(usec);
#endif
}
