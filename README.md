# lua-time
Small C module for *some* extended time functions for Lua.
Developed for and tested on Lua 5.4.4.

# Building
This project uses a very simple build script to build into the `build` directory.
It is completely optional - you can build this module however you like.
## Windows
Set the LUA_DIR environment variable to the path (without ending slash) where you have a Lua distribution installed and built.
The folder should have an `include` directory for include files and a `build` directory for the `lua54` library.
Afterwards, run `build.bat`.
## Linux
Simply run the `build.sh` script.

# Usage
If `require` is used, make sure the built library is in the same place as the Lua working directory.
If `package.loadlib` is used, provide the string `luaopen_time` as the exported symbol name.
## Note on `clock` and `uclock`
The `clock` and `uclock` functions should not be used for getting absolute time.
These functions are intended for measuring relative time with high precision.
It is not guaranteed that they will ever return absolute time.
## Example
Below is a simple example for Lua 5.4.4.
```lua
local time = require "time"

-- Localize time functions.
local time_uclock<const> = time.uclock
local time_usleep<const> = time.usleep

-- Some action to be executed repeatedly.
local callback<const> = function (dt)
    print(("Timer executed after %.15Gs"):format(dt / 1000000))
end

-- Start main loop that continues until interrupted.
local interval<const> = 1000000     -- 1000000us = 1s
local lastTick = time_uclock()
local nextClock = time_uclock()
while true do
    local currentClock = time_uclock()
    if currentClock >= nextClock then
        -- Execute some action here.
        callback(currentClock - lastTick)

        lastTick = currentClock
        nextClock = currentClock + interval
    end

    -- Wait until next tick.
    time_usleep((nextClock - currentClock) // 4)
end
```

# API
## time.uclock
```lua
time.uclock() -> integer
```
Return a high-precision clock as an integer in microseconds.
## time.usleep
```lua
time.usleep(duration: integer)
```
Make the running thread sleep for a duration of time in microseconds.
## time.clock
```lua
time.clock() -> number
```
Return a high-precision clock value as a number in seconds.
## time.sclock
```lua
time.sleep(duration: number)
```
Make the running thread sleep for a duration of time in seconds.
