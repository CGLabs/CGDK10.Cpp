*****************************************************************************
*                                                                           *
*                      Cho sanghyun's Game Classes II                       *
*                       Ver 10.0 / Release 2019.12.11                       *
*                                                                           *
*                              CGDK10.C++.asio                              *
*                                                                           *
*                                                                           *
*                                                                           *
*                                                                           *
*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
*  Best for Game Developement and Optimized for Game Developement.          *
*                                                                           *
*                (c) 2003. Cho Sanghyun. All right reserved.                *
*                          http://www.CGCII.co.kr                           *
*                                                                           *
*****************************************************************************

1. CGDK10.C++.asio
boost.asio를 CGDK10.net.socket과 비슷한 형태의 인터페이스로 랩핑한 클래스들입니다.
서버,클라이언트의 네트워크 처리에 사용할 수 CGDK10.net.socket과 사용법이 유하사게
acceptor와 socket 그리고 connector를 boost.asio를 사용한 구현한 것입니다.

2. 특징 및 구성
   1) boost.asio의 모듈들과 클래스를 사용하여 제작되었습니다.
   2) 따라서 windows에서는 iocp로 동작하며 linux에서는 epoll로 동작합니다.
   3) 다중 쓰레드 하에 동작하도록 제작이 되었습니다.
   4) 직렬화 기능은 포함되지 않았으며 asio::mutable_buffer 등의 버퍼로 송수신을 수행합니다.
   5) 상용 서비스에 사용될 수 있을 만큼의 충분한 안정성 확보를 고려해 제작이 되었습니다.

3. 간단한 server 제작법
   1) 먼저 접속을 받을 socket을 asio::Nsocket_tcp를 상속 받아 정의합니다.
          on_connect, on_disconnect, on_message 함수를 재정의 합니다.
   2) 플릿 인자로 정의한 socket 클래스를 넣어 aceeptor를 선언합니다.
   3) acceptor에 접속을 받을 ip주소를 설정해 start함수를 호출합니다.
   4) 접속이 들어오면 템플릿 인자로 넘긴 사용자 정의한 socket 객체를 생성해 on_connect()함수룰 호출해줍니다.
         메시지가 전송되어 오면 on_message()함수가 호출됩니다.
      on_message()함수의 _msg 변수의 버퍼에 전송받은 메지시가 전달되어 옵니다.
      접속이 종료되면 on_disconnect()함수가 호출됩니다.
   5) socket객체의 send()함수를 호출해 메시지를 전송합니다.
   6) 메시지의 포맷은 메시지의 첫 4byte가 메시지의 길이란 것 뿐입니다. 
   7) 접속을 종료하려면 closesocket() 혹은 disconnect()를 호출하면 됩니다.
         closesocket()은 Abortive close를 수행하며 disconnect()는 Graceful close를 수행합니다.

4. 라이센스
     MIT license를 따르고 있습니다. 자세한 것은 license 파일을 참조하시기 바랍니다.

CGCII.
sangduck@cgcii.co.rk


