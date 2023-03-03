
IF NOT EXIST "build/" MKDIR build
gcc -m64 -O3 -Wall "-L%LUA_DIR%\build" -llua54 "-I%LUA_DIR%\include" -Isrc src/ltime/*.c -fPIC -shared -o build/time.dll %*
