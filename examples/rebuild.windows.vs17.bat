@ECHO OFF
call  _build.windows.vs17 Debug x64 rebuild
call  _build.windows.vs17 Release x64 rebuild
pause