@ECHO ------------------------------------------
@ECHO      CGDK8 Clean-Up Projects. (c)2014
@ECHO ------------------------------------------
@ECHO @ start Clean up
@ECHO OFF

cd ..

REM --------------------------------------
REM Cleanup temporary files
REM --------------------------------------

ECHO Delete 'ncb' filess
del *.ncb /S /Q >nul

ECHO Delete 'sdf' files
del *.sdf /S /Q >nul

ECHO Delete 'VC.db' files
del *.VC.db /S /Q >nul

ECHO Delete 'aps' files
del *.aps /S /Q >nul

ECHO Delete 'suo' files
del *.suo /S /Q /a:h >nul

ECHO Delete 'suo.old' files
del *.suo.old /S /Q /a:h >nul

ECHO Delete 'opensdf' files
del *.opensdf /S /Q /a:h >nul

ECHO Delete 'ipch' files
del *.ipch /S /Q /a:h >nul

ECHO Delete Dump files
del crash*.dmp /S /Q >nul

ECHO Delete ilk files
del *.ilk /S /Q >nul

ECHO Delete xml files
del *.xml /S /Q >nul

ECHO Delete etc files
del *.lastcodeanalysissucceeded /S /Q >nul
del *.exp /S /Q >nul

ECHO gcc files
del *.o /S /Q >nul
del *.d /S /Q >nul
del *.gcno /S /Q >nul
del *.exe /S /Q >nul
del *.log /S /Q >nul


REM --------------------------------------
REM Cleanup temporary directories
REM --------------------------------------

:DELETE_EXECUTE_DIR
  IF NOT EXIST "execute" GOTO DELETE_OUTPUT_DIR
  ECHO Delete 'execute' directory
  del .\execute\*.*  /Q >nul

:DELETE_OUTPUT_DIR
  IF NOT EXIST "Output" GOTO DELETE_LIB_DIR
  ECHO Delete 'Output' directory
  rd "Output"  /S /Q >nul

:DELETE_LIB_DIR
  IF NOT EXIST "Lib" GOTO DELETE_IPCH_DIR
  ECHO Delete 'Lib' directory
  del .\Lib\CG*.*  /S /Q >nul
  del .\Lib\libCG*.*  /S /Q >nul

:DELETE_IPCH_DIR
  IF NOT EXIST "ipch" GOTO DELETE_DOT_VS_DIR
  ECHO Delete 'ipch' directory
  rd "ipch"  /S /Q >nul

:DELETE_DOT_VS_DIR
  ECHO Delete '.vs' directory
  rd "src/common/.vs"  /S /Q >nul
  rd "src/license/.vs"  /S /Q >nul
  rd "src/net.p2p/.vs"  /S /Q >nul
  rd "src/net.socket/.vs"  /S /Q >nul
  rd "src/net.update/.vs"  /S /Q >nul
  rd "src/server.admin/.vs"  /S /Q >nul
  rd "src/server.oauth/.vs"  /S /Q >nul
  rd "src/server.query/.vs"  /S /Q >nul
  rd "src/server.service/.vs"  /S /Q >nul
  rd "src/server.system/.vs"  /S /Q >nul
  rd "src/server.web/.vs"  /S /Q >nul
  rd "src/system/.vs"  /S /Q >nul

  rd "tutorial/common.1.object/.vs"  /S /Q >nul
  rd "tutorial/common.2.buffer/.vs"  /S /Q >nul
  rd "tutorial/common.3.execute/.vs"  /S /Q >nul
  rd "tutorial/network.1.socket/.vs"  /S /Q >nul
  rd "tutorial/network.2.p2p/.vs"  /S /Q >nul
  rd "tutorial/network.3.update/.vs"  /S /Q >nul
  rd "tutorial/server.1.log/.vs"  /S /Q >nul
  rd "tutorial/server.2.group/.vs"  /S /Q >nul
  rd "tutorial/server.3.service/.vs"  /S /Q >nul
  rd "tutorial/server.4.time_event/.vs"  /S /Q >nul
  rd "tutorial/server.5.query/.vs"  /S /Q >nul
  rd "tutorial/server.6.oauth/.vs"  /S /Q >nul
  rd "tutorial/server.7.doss/.vs"  /S /Q >nul


REM --------------------------------------
REM Cleanup Src ipch directory
REM --------------------------------------
:DELETE_SRC

  IF NOT EXIST "Src" GOTO DELETE_BENCHMARK
  cd Src

:DELETE_SRC_IPCH
  IF NOT EXIST "ipch" GOTO DELETE_SRC_CLIENT3D
  ECHO Delete 'Src/ipch' directory
  rd "ipch" /S /Q >nul
:END_DELETE_SRC_IPCH
  rd ".vs"  /S /Q >nul


:DELETE_SRC_CLIENT3D
  IF NOT EXIST "GameApp" GOTO DELETE_SRC_NETWORK
  cd GameApp
  IF NOT EXIST "ipch" GOTO END_DELETE_SRC_CLIENT3D
  ECHO Delete 'Src/GameApp/ipch' directory
  rd "ipch" /S /Q >nul
:END_DELETE_SRC_CLIENT3D
  cd ..


:DELETE_SRC_NETWORK
  IF NOT EXIST "Network" GOTO DELETE_SRC_SERVER
  cd Network

:DELETE_SRC_SOCKET
  IF NOT EXIST "Socket" GOTO DELETE_SRC_P2P
  cd Socket
  IF NOT EXIST "ipch" GOTO END_DELETE_SRC_SOCKET
  ECHO Delete 'Src/Network/Socket/ipch' directory
  rd "ipch" /S /Q >nul
:END_DELETE_SRC_SOCKET
  cd ..

:DELETE_SRC_P2P
  IF NOT EXIST "P2P" GOTO DELETE_SRC_UPDATE
  cd P2P
  IF NOT EXIST "ipch" GOTO END_DELETE_SRC_P2P
  ECHO Delete 'Src/Network/P2P/ipch' directory
  rd "ipch" /S /Q >nul
:END_DELETE_SRC_P2P
  cd ..

:DELETE_SRC_UPDATE
  IF NOT EXIST "Update" GOTO END_DELETE_SRC_NETWORK
  cd Update
  IF NOT EXIST "ipch" GOTO END_DELETE_SRC_UPDATE
  ECHO Delete 'Src/Network/Update/ipch' directory
  rd "ipch" /S /Q >nul
:END_DELETE_SRC_UPDATE
  cd ..

:END_DELETE_SRC_NETWORK
  cd ..


:DELETE_SRC_SERVER
  IF NOT EXIST "Server" GOTO DELETE_BENCHMARK
  cd Server

:DELETE_SRC_SERVER
  IF NOT EXIST "Server" GOTO DELETE_SRC_QUERY
  cd Server
  IF NOT EXIST "ipch" GOTO END_DELETE_SRC_SERVER
  ECHO Delete 'Src/Server/Server/ipch' directory
  rd "ipch" /S /Q >nul
:END_DELETE_SRC_SERVER
  cd ..

:DELETE_SRC_QUERY
  IF NOT EXIST "ServerQuery" GOTO DELETE_SRC_SERVERADMIN
  cd ServerQuery
  IF NOT EXIST "ipch" GOTO END_DELETE_SRC_QUERY
  ECHO Delete 'Src/Server/ServerQuery/ipch' directory
  rd "ipch" /S /Q >nul
:END_DELETE_SRC_QUERY
  cd ..

:DELETE_SRC_SERVERADMIN
  IF NOT EXIST "ServerAdmin" GOTO END_DELETE_SRC_SERVER
  cd ServerAdmin
  IF NOT EXIST "ipch" GOTO END_DELETE_SRC_SERVERADMIN
  ECHO Delete 'Src/Server/ServerAdmin/ipch' directory
  rd "ipch" /S /Q >nul
:END_DELETE_SRC_SERVERADMIN
  cd ..

:END_DELETE_SRC_SERVER
  cd ..


:DELETE_SRC_WEB
  IF NOT EXIST "Web" GOTO END_:DELETE_SRC_WEB
  cd Web
  IF NOT EXIST "ipch" GOTO :END_:DELETE_SRC_WEB
  ECHO Delete 'Src/Web/ipch' directory
  rd "ipch" /S /Q >nul
:END_:DELETE_SRC_WEB
  cd ..


:END_DELETE_SRC
  cd ..


REM --------------------------------------
REM Cleanup Benchmark ipch directory
REM --------------------------------------
:DELETE_BENCHMARK

  IF NOT EXIST "BenchMark" GOTO DELETE_SAMPLE
  cd BenchMark
  IF NOT EXIST "ipch" GOTO END_DELETE_BENCHMARK
  ECHO Delete 'Benchmark/ipch' directory
  rd "ipch" /S /Q >nul
:END_DELETE_BENCHMARK
  cd ..


REM --------------------------------------
REM Cleanup Sample ipch directory
REM --------------------------------------
:DELETE_SAMPLE

  IF NOT EXIST "Samples" GOTO DELETE_TUTORIAL
  cd Samples

:DELETE_SAMPLE_ADMINSERVERCLASSES
  IF NOT EXIST "AdminServerClasses" GOTO DELETE_SAMPLE_P2PCLASSES
  cd AdminServerClasses
  IF NOT EXIST "ipch" GOTO END_DELETE_SAMPLE_ADMINSERVERCLASSES
  ECHO Delete 'Sample: AdminServerClasses/ipch' directory
  rd "ipch" /S /Q >nul
:END_DELETE_SAMPLE_ADMINSERVERCLASSES
  cd ..

:DELETE_SAMPLE_P2PCLASSES
  IF NOT EXIST "P2PClasses" GOTO DELETE_SAMPLE_ROOMCLASSES
  cd P2PClasses
  IF NOT EXIST "ipch" GOTO END_DELETE_SAMPLE_P2PCLASSES
  ECHO Delete 'Sample: P2PClasses/ipch' directory
  rd "ipch" /S /Q >nul
:END_DELETE_SAMPLE_P2PCLASSES
  cd ..

:DELETE_SAMPLE_ROOMCLASSES
  IF NOT EXIST "RoomClasses" GOTO DELETE_SAMPLE_SOCKETCLASSES
  cd RoomClasses
  IF NOT EXIST "ipch" GOTO END_DELETE_SAMPLE_ROOMCLASSES
  ECHO Delete 'Sample: RoomClasses/ipch' directory
  rd "ipch" /S /Q >nul
:END_DELETE_SAMPLE_ROOMCLASSES
  cd ..

:DELETE_SAMPLE_SOCKETCLASSES
  IF NOT EXIST "SocketClasses" GOTO DELETE_SAMPLE_TURNCLASSES
  cd SocketClasses
  IF NOT EXIST "ipch" GOTO END_DELETE_SAMPLE_SOCKETCLASSES
  ECHO Delete 'Sample: SocketClasses/ipch' directory
  rd "ipch" /S /Q >nul
:END_DELETE_SAMPLE_SOCKETCLASSES
  cd ..

:DELETE_SAMPLE_TURNCLASSES
  IF NOT EXIST "TURNClasses" GOTO DELETE_SAMPLE_SOCKETCLASSES
  cd TURNClasses
  IF NOT EXIST "ipch" GOTO END_DELETE_SAMPLE_TURNCLASSES
  ECHO Delete 'Sample: TURNClasses/ipch' directory
  rd "ipch" /S /Q >nul
:END_DELETE_SAMPLE_TURNCLASSES
  cd ..

:DELETE_SAMPLE_UPDATECLASSES
  IF NOT EXIST "UpdateClasses" GOTO DELETE_SAMPLE_WEBCLASSES
  cd UpdateClasses
  IF NOT EXIST "ipch" GOTO END_DELETE_SAMPLE_UPDATECLASSES
  ECHO Delete 'Sample: UpdateClasses/ipch' directory
  rd "ipch" /S /Q >nul
:END_DELETE_SAMPLE_UPDATECLASSES
  cd ..

:DELETE_SAMPLE_WEBCLASSES
  IF NOT EXIST "WebClasses" GOTO END_DELETE_SAMPLE
  cd WebClasses
  IF NOT EXIST "ipch" GOTO END_DELETE_SAMPLE_WEBCLASSES
  ECHO Delete 'Sample: WebClasses/ipch' directory
  rd "ipch" /S /Q >nul
:END_DELETE_SAMPLE_WEBCLASSES
  cd ..

:END_DELETE_SAMPLE

  cd ..



REM --------------------------------------
REM Cleanup Tutorial ipch directory
REM --------------------------------------
:DELETE_TUTORIAL

  IF NOT EXIST "Tutorials" GOTO DELETE_END
  cd Tutorials

:DELETE_TUTORIAL_OBJECTCLASSES
  IF NOT EXIST "[Common] 1. Object System" GOTO DELETE_TUTORIAL_EXECUTECLASSES
  cd "[Common] 1. Object System"
  IF NOT EXIST "ipch" GOTO END_DELETE_TUTORIAL_OBJECTCLASSES
  ECHO Delete 'Tutorials: ObjectClasses/ipch' directory
  rd "ipch" /S /Q >nul
:END_DELETE_TUTORIAL_OBJECTCLASSES
  cd ..

:DELETE_TUTORIAL_EXECUTECLASSES
  IF NOT EXIST "[Common] 2. execute system" GOTO DELETE_TUTORIAL_EXCEPTION
  cd "[Common] 2. execute system"
  IF NOT EXIST "ipch" GOTO END_DELETE_TUTORIAL_EXECUTECLASSES
  ECHO Delete 'Tutorials: ExecuteClasses/ipch' directory
  rd "ipch" /S /Q >nul
:END_DELETE_TUTORIAL_EXECUTECLASSES
  cd ..

:DELETE_TUTORIAL_EXCEPTION
  IF NOT EXIST "[Common] 3. Exeception system" GOTO DELETE_TUTORIAL_MESSAGE
  cd "[Common] 3. Exeception system"
  IF NOT EXIST "ipch" GOTO END_DELETE_TUTORIAL_EXCEPTION
  ECHO Delete 'Tutorials: Exception/ipch' directory
  rd "ipch" /S /Q >nul
:END_DELETE_TUTORIAL_EXCEPTION
  cd ..

:DELETE_TUTORIAL_MESSAGE
  IF NOT EXIST "[Common] 4. Message system" GOTO DELETE_TUTORIAL_DYNAMIC
  cd "[Common] 4. Message system"
  IF NOT EXIST "ipch" GOTO END_DELETE_TUTORIAL_MESSAGE
  ECHO Delete 'Tutorials: Message/ipch' directory
  rd "ipch" /S /Q >nul
:END_DELETE_TUTORIAL_MESSAGE
  cd ..

:DELETE_TUTORIAL_DYNAMIC
  IF NOT EXIST "[Common] 5. Dynamic system" GOTO DELETE_TUTORIAL_SCRIPT
  cd "[Common] 5. Dynamic system"
  IF NOT EXIST "ipch" GOTO END_DELETE_TUTORIAL_DYNAMIC
  ECHO Delete 'Tutorials: Dynamic directory
  rd "ipch" /S /Q >nul
:END_DELETE_TUTORIAL_DYNAMIC
  cd ..

:DELETE_TUTORIAL_SCRIPT
  IF NOT EXIST "[Common] 6. Script system" GOTO DELETE_TUTORIAL_FSM
  cd "[Common] 6. Script system"
  IF NOT EXIST "ipch" GOTO END_DELETE_TUTORIAL_SCRIPT
  ECHO Delete 'Tutorials: Script directory
  rd "ipch" /S /Q >nul
:END_DELETE_TUTORIAL_SCRIPT
  cd ..

:DELETE_TUTORIAL_FSM
  IF NOT EXIST "[Common] 7. State system" GOTO DELETE_TUTORIAL_SOCKETCLASSES
  cd "[Common] 7. State system"
  IF NOT EXIST "ipch" GOTO END_DELETE_TUTORIAL_FSM
  ECHO Delete 'Tutorials: FSM directory
  rd "ipch" /S /Q >nul
:END_DELETE_TUTORIAL_FSM
  cd ..

:DELETE_TUTORIAL_SOCKETCLASSES
  IF NOT EXIST "[Network] 1. Socket classes" GOTO DELETE_TUTORIAL_UPDATECLASSES
  cd "[Network] 1. Socket classes"
  IF NOT EXIST "ipch" GOTO END_DELETE_TUTORIAL_SOCKETCLASSES
  ECHO Delete 'Tutorials: SocketClasses/ipch' directory
  rd "ipch" /S /Q >nul
:END_DELETE_TUTORIAL_SOCKETCLASSES
  cd ..

:DELETE_TUTORIAL_UPDATECLASSES
  IF NOT EXIST "[Network] 2. Update system" GOTO DELETE_TUTORIAL_P2PCLASSES
  cd "[Network] 2. Update system"
  IF NOT EXIST "ipch" GOTO END_DELETE_TUTORIAL_UPDATECLASSES
  ECHO Delete 'Tutorials: SocketClasses/ipch' directory
  rd "ipch" /S /Q >nul
:END_DELETE_TUTORIAL_UPDATECLASSES
  cd ..

:DELETE_TUTORIAL_P2PCLASSES
  IF NOT EXIST "[Network] 3. P2P classes" GOTO DELETE_TUTORIAL_TURNCLASSES
  cd "[Network] 3. P2P classes"
  IF NOT EXIST "ipch" GOTO END_DELETE_TUTORIAL_P2PCLASSES
  ECHO Delete 'Tutorials: P2P Classes/ipch' directory
  rd "ipch" /S /Q >nul
:END_DELETE_TUTORIAL_P2PCLASSES
  cd ..

:DELETE_TUTORIAL_TURNCLASSES
  IF NOT EXIST "[Network] 4. P2P  TURN" GOTO DELETE_TUTORIAL_GROUPCLASSES
  cd "[Network] 4. P2P  TURN"
  IF NOT EXIST "ipch" GOTO END_DELETE_TUTORIAL_TURNCLASSES
  ECHO Delete 'Tutorials: TURN Classes/ipch' directory
  rd "ipch" /S /Q >nul
:END_DELETE_TUTORIAL_TURNCLASSES
  cd ..

:DELETE_TUTORIAL_GROUPCLASSES
  IF NOT EXIST "[Server] 1. Group classes" GOTO DELETE_TUTORIAL_EVENT
  cd "[Server] 1. Group classes"
  IF NOT EXIST "ipch" GOTO END_DELETE_TUTORIAL_GROUPCLASSES
  ECHO Delete 'Tutorials: Group Classes/ipch' directory
  rd "ipch" /S /Q >nul
:END_DELETE_TUTORIAL_GROUPCLASSES
  cd ..

:DELETE_TUTORIAL_EVENT
  IF NOT EXIST "[Server] 2. Event system" GOTO DELETE_TUTORIAL_LOGCLASSES
  cd "[Server] 2. Event system"
  IF NOT EXIST "ipch" GOTO END_DELETE_TUTORIAL_EVENT
  ECHO Delete 'Tutorials: Event Classes/ipch' directory
  rd "ipch" /S /Q >nul
:END_DELETE_TUTORIAL_EVENT
  cd ..

:DELETE_TUTORIAL_LOGCLASSES
  IF NOT EXIST "[Server] 3. Log classes" GOTO DELETE_TUTORIAL_QUERYCLASSES
  cd "[Server] 3. Log classes"
  IF NOT EXIST "ipch" GOTO END_DELETE_TUTORIAL_LOGCLASSES
  ECHO Delete 'Tutorials: Log Classes/ipch' directory
  rd "ipch" /S /Q >nul
:END_DELETE_TUTORIAL_LOGCLASSES
  cd ..

:DELETE_TUTORIAL_QUERYCLASSES
  IF NOT EXIST "[Server] 4. Query classes" GOTO DELETE_TUTORIAL_ROOMCLASSES
  cd "[Server] 4. Query classes"
  IF NOT EXIST "ipch" GOTO END_DELETE_TUTORIAL_QUERYCLASSES
  ECHO Delete 'Tutorials: DB Classes/ipch' directory
  rd "ipch" /S /Q >nul
:END_DELETE_TUTORIAL_QUERYCLASSES
  cd ..

:DELETE_TUTORIAL_ROOMCLASSES
  IF NOT EXIST "[Server] 5. Room classes" GOTO DELETE_TUTORIAL_ADMINCLASSES
  cd "[Server] 5. Room classes"
  IF NOT EXIST "ipch" GOTO END_DELETE_TUTORIAL_ROOMCLASSES
  ECHO Delete 'Tutorials: RoomClasses/ipch' directory
  rd "ipch" /S /Q >nul
:END_DELETE_TUTORIAL_ROOMCLASSES
  cd ..

:DELETE_TUTORIAL_ADMINCLASSES
  IF NOT EXIST "[Server] 6. Admin classes" GOTO DELETE_TUTORIAL_WEBCLASSES
  cd "[Server] 6. Admin classes"
  IF NOT EXIST "ipch" GOTO END_DELETE_TUTORIAL_ADMINCLASSES
  ECHO Delete 'Tutorials: TURN Classes/ipch' directory
  rd "ipch" /S /Q >nul
:END_DELETE_TUTORIAL_ADMINCLASSES
  cd ..

:DELETE_TUTORIAL_WEBCLASSES
  IF NOT EXIST "[Web] 1. WebSocket Classes" GOTO END_DELETE_TUTORIALS
  cd "[Web] 1. WebSocket Classes"
  IF NOT EXIST "ipch" GOTO END_DELETE_TUTORIAL_WEBCLASSES
  ECHO Delete 'Tutorials: Web Classes/ipch' directory
  rd "ipch" /S /Q >nul
:END_DELETE_TUTORIAL_WEBCLASSES
  cd ..

:END_DELETE_TUTORIALS

cd ..


:DELETE_END

@ECHO ------------------------------------------
@ECHO @ Complete Cleanup!!!
@ECHO ------------------------------------------

pause
