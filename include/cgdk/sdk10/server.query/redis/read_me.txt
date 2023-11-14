==============================================================================
                                                                             
                        Cho sanghyun's Game Classes II                       
                         Ver 9.0 / Release 2017.01.03                         
                                                                             
                             server.query.redis
                                                                             
                                                                             
                                                                             
                                                                             
    This Program is programmed by Cho SangHyun. sangducks@gamil.com           
    Best for Game Developement and Optimized for Game Developement.          
                                                                             
                  (c) 2016 Cho Sanghyun All right reserved                     
                             http://www.CGCII.co.kr
                                                                             
==============================================================================

1. CGCII redis query classes

 Database와 연동하여 데이터를 처리하기 위해서 OLE DB나 odbc를 활용하여 DB와 접속을
하고 이를 통해 Query를 수행한다.
 CGCII Server DB Query Classes는 OLE DB를 사용하여 Database의 Query를 효율적으로
수행하도록 설계되었다.

 최적의 Query 성능을 위해 DB Query session 풀을 사용하며 다중 쓰레드 상에서 원활히
Query가 동작하도록 설계되었다.
 
2. CGCII Server oledb Query Classes의 주요 클래스 및 구성 요소들
   
   CGCII DB Query Class는 크게 Querier와 Query로 나눌 수 있다.
   하나의 Query 객체는 하나의 Query를 의미하며 Query를 위한 각종 정보와 Query의
   결과를 저장하고 있다.
   
   Query를 수행하기 위해서는 Query 객체를 생성한 후 필요한 정보를 설정하고 이를
   Querier에 요청하는 방법으로 수행된다.
   
   물론 Querier는 Query의 쿼리 요청을 받아들이기 전에 Database와의 연결과 인증
   과정이 완료된 상태여야만 하며 이는 open()을 통해 수행할 수 있다.

   1) Querier/Query
      - Iserver_query
      - Iserver_query_executable
      - CGServerQuerier
      - CGServerQueryStatistics
   
   3) Querier Manager
	  - query::manager_querier

3. Contact us
	@Mail: sangduck@cgcii.co.kr

	@Web: www.CGCII.co.kr
	
	본 소프트웨어의 모든 저작권은 '조상현(Cho Sanghyun)'에 있습니다.

