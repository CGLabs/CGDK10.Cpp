==============================================================================
                                                                             
                        Cho sanghyun's Game Classes II                       
                         Ver 9.0 / Release 2017.01.03                         
                                                                             
                             Server Log Classes                             
                                                                             
                                                                             
                                                                             
                                                                             
    This Program is programmed by Cho SangHyun. sangducks@gamil.com           
    Best for Game Developement and Optimized for Game Developement.          
                                                                             
                  (c) 2016 Cho Sanghyun All right reserved                     
                             http://www.CGCII.co.kr                          
                                                                             
==============================================================================

1. CGCII Server Log Classes

 Log와 관련된 클래스 구현한 것이다.
  Server는 일반적으로 대량의 Log를 남기고 이를 처리하기 때문에 이를 파일로 저장할 
 경우 잦은 파일의 억세스로 성능이 많이 저하되게 된다.
  또 Log는 실시간으로 화면에 표시되기도 해야하며 파일로도 저장되어야 하는 등 다중
표시 혹은 저장이 필요하다.

 이를 해결하고자 대량의 로그를 파일로 저장할 시에도 디스크의 억세스를 최소화하면서도
 안전하게 데이터를 처리하도록 설계되었고 또 파일을 사용한 로그나 MFCControl과 
연동하여 화면에 출력하기 위한 로그를 동시에 처리할 수 있다.
 그리고 로그의 필터 등을 활용한 선택적 로그 기능을 제공한다.
 
2. CGCII Server Log Classes의 주요 클래스 및 구성 요소들

   1) file_log 
   - 로그 파일용의 파일 클래스라고 할수 있다.
   - 로그 파일을 남기는 중 파일을 열어볼수 있도록 Shared open 속성으로 파일을 연다.
   - 만에 하나 시스템이 다운되어도 로그를 남기기 위해 파일을 저장하는 순간에만
     파일을 열었다 다 쓰면 바로 닫도록 처리한다.
   - 고성능 파일 저장을 지원하기 위해 Overlapped I/O를 지원하며 Gathering을
     이용한 저장을 수행한다.
   - 파일의 저장으로 인해 처리가 지연되는 것을 최소화되도록 구현되어 있다.
     (대부분 파일 저장을 완료하지 않아도 바로 리턴되며 내부적으로 파일을 저장
	 하게 된다.)

   2) _logFilter
   - C_logEvent에 세팅되어 사용되는 클래스로 특정한 로그만을 선택적으로 
     처리하기 위한 필터 클래스이다.
   - 기본적으로 로그의 종류, 레벨의 범위를 설정하면 그 범위에 해당하는
     로그만 필터링 되도록 한다.

   3) _logEvent 
   - 이 클래스로 생성된 객체의 trace()함수를 호출하면 필터로 필터링 후 등록된
     모든 타겟에 로그를 전달하는 클래스이다.
   
   4) _logFile
   - 이 클래스로 생성된 객체의 trace()함수를 호출하면 필터가 있을 경우 필터를
     수행한 후 타겟 파일에 해당 로그를 저장하게 된다.
   - 이 클래스는 open()을 사용하여 반드시 파일을 먼저 열어야 된다.


3. Contact us
	@Mail: sangduck@cgcii.co.kr

	@Web: www.CGCII.co.kr
	
	본 소프트웨어의 모든 저작권은 '조상현(Cho Sanghyun)'에 있습니다.

