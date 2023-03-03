
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
    // Clamp to minimum 0.
    if (usec < 0) usec = 0;
#ifdef LUA_LTIMER_WINDOWS
    HANDLE timer;
    LARGE_INTEGER ft;
    // Convert to 100 nanosecond interval.
    ft.QuadPart = -(10 * usec);
    timer = CreateWaitableTimer(NULL, TRUE, NULL);
    SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
    WaitForSingleObject(timer, INFINITE);
    CloseHandle(timer);
#else
    usleep(usec);
#endif
}
