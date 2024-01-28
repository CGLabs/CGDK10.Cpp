# CGDK10.Cpp
게임 서버의 개발을 위해 개발된 서버엔진입니다.
게임 서버에 요구되는 강력한 성능과 높은 부하 상태에서 안정성 그리고 생산성을 제공합니다.

효율적인 다중 쓰레드 처리, 각종 i/o 최적화를 통해 최고 수준의 성능을 제공하며
공고한 설계와, 철저한 예외 안전 처리, 쓰레드 안전, 고부하 대응 처리 등 강력한 안정성을 제공합니다.
또 수십여 개의 상용 프로젝트에 적용되며 검증을 했습니다.

## 요구사항
- OS Windows or Linux 
- Language C++20이상

# 설치 및 적용 방법
1. CGDK.10을 Clone 혹은 다운로드 받아 원하는 곳에 설치합니다.
2. CGDK.10/Include 디렉토리를 'Include' 디렉토리에 포함시켜줍니다.
3. CGDK.10/Lib 디렉토리를 'Lib' 디렉토리에 포함시켜줍니다.
4. Compile 합니다.

# 디렉토리 설명
- __/include__
- __/lib__
- __/dll__
- __/build__
- __/tutorials__
- __/examples__
- __/benchmark__

# 튜터리얼 및 예제 프로젝트
  CGDK.10/tutorials 디렉토리 밑에 튜터리얼이 있습니다.

  ### /tutorials<br>

   - __common.1.object__ <br/>
     기본적인 객체 시스템에 대한 설명입니다. 스마트포인터와 풀시스템 그리고 그에 관련된 인터페이스 시스템에 대한 설명입니다.<br/>
   - __common.2.buffer__<br/>
     CGDK.buffer에 대한 설명입니다. CGDK.buffer에 대한 따로 해당 프로젝트에 자세히 설명되어 있으므로 간략한 설계만 있습니다. 또 CGDK.10에서 어떻게 적용되었는 지에 대한 설명입니다.<br/>
   - __common.3.execute__<br/>
     쓰레드와 실행 처리에 대한 설명입니다. CGCII executor는 proactor 패턴의 쓰레드풀 시스템입니다. 이를 사용해 비동기 처리나 반복 실행 또는 특정 시간 등의 처리 방법에 대한 설명입니다.<br/>
   - __network.1.socket__ <br/>
     tcp/udp 소켓에 대한 설명입니다. CGCII socket 시스템은 강력한 성능과 안정성을 제공하며 Interface의 조합을 통해 다양한 구현이 가능합니다. 이에 대한 설명입니다.<br/>
   - __network.2.p2p__<br/>
     CGCII p2p system에 대한 설명입니다. unrelaible, sequenced, reliable, reliable oreded 등의 delibery 시스템과 CGCII p2p framework 그리고 NAT 상에서의 동작을 위한 CGCII TURN에 대한 설명입니다.<br/>
   - __network.3.update__<br/>
     Update Patch 시스템에 대한 설명입니다. 다양한 파일을 패치하거나 <br/>
   - __server.1.log__<br/>
     log system에 대한 설명입니다. CGCII log system은 계층 로깅에 대한 설명과 다양한 로깅 방법 등에 대하 설명합니다.<br/>
   - __server.2.group__<br/>
     서버의 소켓 혹은 접속자 관리를 위한 CGCII group system에 대한 설명입니다.<br/>
   - __server.3.service__<br/>
     CGCII server는 서버 프레임워크에 대한 설명입니다.<br/>
   - __server.4.time_event__<br/>
     CGCII time_event는 서비스 중 서버의 운영 중 실행되어야 하는 각종 이벤트를 처리하는 시스템입니다. 이에 대한 설명입니다.<br/>
   - __server.5.query__<br/>
     odbc(rdb), redis, http query까지 다양한 외부 쿼리 처리 시스템에 대한 설명입니다. <br/>
   - __server.6.http_api__<br/>
     google, naver, 은행 공통 전상망 등 각종 open api를 편리하게 쓸 수 있도록 미리 구현한 시스템에 대한 설명입니다.<br/>
   - __server.7.doss__<br/>
     대규모 분산 서버 시스템의 구현을 위해 높은 정합성을 제공하는 시스템에 대한 설명입니다. 
   - __x.etc__<br/>
     기타<br/>

  CGDK.10/examples 디렉토리 밑에 예제파일들이 있습니다.
  실제 서비스 가능할 수준의 품질로 작성된 것들 입니다. 

   ### /examples<br/>
   - __1.1 tcp_echo__<br/>
   - __1.2 tcp_relay_echo__<br/>
   - __1.3 tcp_multicat_echo__<br/>
   - __2.1 chatting_simple__<br/>
   - __2.2 chatting_scaleout__<br/>
   - __2.3 chatting__<br/>
   - __3.1 channel_system_1__<br/>
   - __3.2 channel_system_2__<br/>
   - __4.1 game_simple_server_1__<br/>
   - __4.2 game_simple_server_2__<br/>
   - __4.3 game_login_system__<br/>
   - __4.4 game_scalable_server_system__<br/>
   - __5.1 game_match_making_server_system__<br/>
   - __5.2 game_friend_system__<br/>
   - __5.3 game_mail_system_1__<br/>
   - __5.6 game_shop_system__<br/>
   - __6.1 game_mmo_field_1__<br/>
   - __6.2 game_mmo_field_2__<br/>
   - __6.3 game_quest_system__<br/>
   - __6.4 game_instance_dungeon__<br/>
   - __6.5 game_tade_server_system__<br/>
   - __7.1 update_service__<br/>

