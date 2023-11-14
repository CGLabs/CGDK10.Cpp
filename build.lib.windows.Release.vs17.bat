@ECHO OFF

cd build
call _build.windows.vs17 Release x64 build
cd ..

pause
