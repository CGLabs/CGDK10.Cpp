@ECHO OFF

cd build
call _build.windows.vs17 Debug.NDI x64 build
call _build.windows.vs17 Release.NDI x64 build
cd ..

pause