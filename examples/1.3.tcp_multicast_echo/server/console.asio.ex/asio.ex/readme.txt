*****************************************************************************
*                                                                           *
*                      Cho sanghyun's Game Classes II                       *
*                       Ver 10.0 / Release 2019.12.11                       *
*                                                                           *
*                            CGDK10.C++.asio.ex                             *
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

1. CGDK10.C++.asio.ex
boost.asio를 CGDK10.net.socket과 비슷한 형태의 인터페이스로 랩핑한 클래스들로
'CGDK10.C++.asio' 버전의 클래스들을 좀더 업그레이드한 버전입니다.
서버,클라이언트의 네트워크 처리에 사용할 수 CGDK10.net.socket과 사용법이 유하사게
acceptor와 socket 그리고 connector를 boost.asio를 사용한 구현한 것입니다.


2. 특징 및 구성
   1) 'CGDK10.C++.asio'과 동일하게 boost.asio의 모듈들과 클래스를 사용하여 제작되었습니다.
   2) 'CGDK10.C++.asio'에 직렬화 라이브러리인 CGDK.buffer를 통합하였습니다.
   3) CGDK.buffer의 통합으로 무복사 전송(Zero-copy transfer)가 구현되었습니다.
   4) socket의 send gathering 등 성능을 향상시키기 위한 알고리즘들이 적용되었습니다.
          (Nsocket_tcp_gather과 Nsocket_tcp_gather_buffer 클래스가 추가되었습니다.)
   5) 다중 쓰레드 acceptor를 지원합니다.
          'CGDK10.C++.asio'는 하나의 acceptor는 하나의 thread로 접속을 받을 수 있었으마 
         ex버전은 다중 쓰레드에서 접속을 받을 수 있습니다.
   6) on_discoonect()함수에 접속 종료 원일을 알수 있게 에러 코드를 전달합니다.
   7) 기타 소소한 기능 및 안정화를 위한 알고리즘이 적용되었습니다.

3. 간단한 server 제작법
   1) 'CGDK10.C++.asio'와 동일합니다.
   2) 먼저 접속을 받을 socket을 asio::Nsocket_tcp를 상속 받아 정의합니다.
      이때 asio::Nsocket_tcp_gather이나 asio::Nsocket_tcp_gahter_buffer를 상속받을 수도 있습니다.
          이 클래스들은 send시 gathering 알고리즘이 적용되어 전송 능력(throught-put)성능을 상당히 높혔습니다.
          또 polling 등을 알고리즘을 사용한 것이 아니라 응답속도 역시 동일하게 빠릅니다.

   3) 상속받은 socket 클래스에 on_connect, on_disconnect, on_message 함수를 재정의 합니다.
   4) 플릿 인자로 정의한 socket 클래스를 넣어 aceeptor를 선언합니다.
   5) acceptor에 접속을 받을 ip주소를 설정해 start함수를 호출합니다.
   6) 접속이 들어오면 템플릿 인자로 넘긴 사용자 정의한 socket 객체를 생성해 on_connect()함수룰 호출해줍니다.
         메시지가 전송되어 오면 on_message()함수가 호출됩니다.
      on_message()함수의 _msg 변수의 버퍼에 전송받은 메지시가 전달되어 옵니다.
      접속이 종료되면 on_disconnect()함수가 호출됩니다.
   7) socket객체의 send()함수를 호출해 메시지를 전송합니다.
   8) 메시지의 포맷은 메시지의 첫 4byte가 메시지의 길이란 것 뿐입니다. 
   9) 접속을 종료하려면 closesocket() 혹은 disconnect()를 호출하면 됩니다.
         closesocket()은 Abortive close를 수행하며 disconnect()는 Graceful close를 수행합니다.

4. 라이센스
     MIT license를 따르고 있습니다. 자세한 것은 license 파일을 참조하시기 바랍니다.

CGCII.
sangduck@cgcii.co.rk
