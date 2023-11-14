@ECHO OFF

cd build
call _build.windows.vs17 Debug x64 build
call _build.windows.vs17 Release x64 build
cd ..

cd tutorials
call _build.windows.vs17 Debug x64 build
call _build.windows.vs17 Release x64 build
cd ..

cd examples
call _build.windows.vs17 Debug x64 build
call _build.windows.vs17 Release x64 build
cd ..

pause