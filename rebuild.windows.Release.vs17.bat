@ECHO OFF

cd build
call _build.windows.vs17 Release x64 rebuild
cd ..

cd tutorials
call _build.windows.vs17 Release x64 rebuild
cd ..

cd examples
call _build.windows.vs17 Release x64 rebuild
cd ..

pause