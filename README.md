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

# 튜터리얼 및 예제 프로젝트
  CGDK.10/tutorials 디렉토리 밑에 튜터리얼이 있습니다.

  /tutorials
   - common.1.object        기본적인 객체 시스템에 대한 설명입니다. 스마트포인터와 풀시스템 그리고 그에 관련된 인터페이스 시스템에 대한 설명입니다.
   - common.2.buffer        CGDK.buffer에 대한 설명입니다. CGDK.buffer에 대한 따로 해당 프로젝트에 자세히 설명되어 있으므로 간략한 설계만 있습니다. 또 CGDK.10에서 어떻게 적용되었는 지에 대한 설명입니다.
   - common.3.execute       쓰레드와 실행 처리에 대한 설명입니다. CGCII executor는 proactor 패턴의 쓰레드풀 시스템입니다. 이를 사용해 비동기 처리나 반복 실행 또는 특정 시간 등의 처리 방법에 대한 설명입니다.
   - network.1.socket       tcp/udp 소켓에 대한 설명입니다. CGCII socket 시스템은 강력한 성능과 안정성을 제공하며 Interface의 조합을 통해 다양한 구현이 가능합니다. 이에 대한 설명입니다.
   - network.2.p2p          CGCII p2p system에 대한 설명입니다. unrelaible, sequenced, reliable, reliable oreded 등의 delibery 시스템과 CGCII p2p framework 그리고 NAT 상에서의 동작을 위한 CGCII TURN에 대한 설명입니다.
   - network.3.update       Update Patch 시스템에 대한 설명입니다. 다양한 파일을 패치하거나 
   - server.1.log           log system에 대한 설명입니다. CGCII log system은 계층 로깅에 대한 설명과 다양한 로깅 방법 등에 대하 설명합니다.
   - server.2.group         서버의 소켓 혹은 접속자 관리를 위한 CGCII group system에 대한 설명입니다.
   - server.3.service       CGCII server는 서버 프레임워크에 대한 설명입니다.
   - server.4.time_event    CGCII time_event는 서비스 중 서버의 운영 중 실행되어야 하는 각종 이벤트를 처리하는 시스템입니다. 이에 대한 설명입니다.
   - server.5.query         odbc(rdb), redis, http query까지 다양한 외부 쿼리 처리 시스템에 대한 설명입니다. 
   - server.6.http_api      google, naver, 은행 공통 전상망 등 각종 open api를 편리하게 쓸 수 있도록 미리 구현한 시스템에 대한 설명입니다.
   - server.7.doss          대규모 분산 서버 시스템의 구현을 위해 높은 정합성을 제공하는 시스템에 대한 설명입니다. 
   - x.etc                  기타

   /example
    1.1 tcp_echo
    1.2 tcp_relay_echo
    1.3 tcp_multicat_echo
    2.1 chatting_simple
    2.2 chatting_scaleout
    2.3 chatting
    3.1 channel_system_1
    3.2 channel_system_2
    4.1 game_simple_server_1
    4.2 game_simple_server_2
    4.3 game_login_system
    4.4 game_scalable_server_system
    5.1 game_match_making_server_system
    5.2 game_friend_system
    5.3 game_mail_system_1
    5.6 game_shop_system
    6.1 game_mmo_field_1
    6.2 game_mmo_field_2
    6.3 game_quest_system
    6.4 game_instance_dungeon
    6.5 game_tade_server_system
    7.1 update_service
