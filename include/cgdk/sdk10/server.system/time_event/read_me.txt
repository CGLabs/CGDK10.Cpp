==============================================================================
                                                                             
                        Cho sanghyun's Game Classes II                       
                         Ver 9.0 / Release 2017.01.03                         
                                                                             
                             Server System Classes                             
                                                                             
                                                                             
                                                                             
                                                                             
    This Program is programmed by Cho SangHyun. sangducks@gamil.com           
    Best for Game Developement and Optimized for Game Developement.          
                                                                             
                  (c) 2016 Cho Sanghyun All right reserved                     
                             http://www.CGCII.co.kr
                                                                             
==============================================================================

1. CGCII Server System Classes

  서버 운영 시 특정한 시간 혹은 일정시간 마다 수행해야하는 Event가 있을 경우 이를
 위한 클래스들을 의미한다.
  일반 적으로 서비스를 운영할 때 특정 시간에 서버를 중지시키거나 백업을 하거나 
 접속자를 조사해서 접속해제시키거나 등등 특정한 시간 혹은 일정 시간마다 실행되어야
 하는 운용상 필요한 실행을 위해 사용된다.

   Event Classes들은 크게 한번만 실행되는 객체, 반복적으로 실행되는 객체, 시작과
  종료 시점에 각각 실행되는 객체, 임의의 정해진 시간마다 실행되어야 하는 객체 등이
  존재한다.
   필요에 따라 해당 객체를 생속받앙 재정의 하거나 생성하여 Event manager에 등록
  함으로써 실행되게 된다.
  
2. CGEvnet::manager와 time_event::Ientity 클래스
    time_event::entity_manager는 EventObject를 실행시키는 통합관리자로서 생성된 Event Object는
   반드시 Event Manger에 등록되어야 실행된다.
    Event manager는 싱글톤 객체로 따로 생성할 필요 없이 내부적으로 유일하게 하나만
   생성되어 있다.

3. time_event::object 클래스들

   1) 단한번 실행
      - time_event::object::once
      - time_event::object::onceFunction<TFUNCTION>
   2) 반복적으로 실행
      - time_event::object::iteration
      - time_event::object::iterationFunction<TFUNCTION>

   3) 시작과 끝나는 시점에 실행
      - time_event::object::start_end
      - time_event::object::start_endFunction<TFUNCTION>

   4) 시작시점과 끝시점에 실행되며 그 사이 시간에는 일정시간마다 실행
      - time_event::object::start_iteration_end
      - time_event::object::start_iteration_endFunction<TFUNCTION>

4. time_event Schedule 관련 클래스와 기능
   Schedule은 여러 개의 실행을 하나의 객체에서 실행할 수 있도록 설계되었다.
   또 앞의 Event 객체와 달리 따로 CSchedule 객체를 생성하여 이를 Event 객체에
   등록하여 사용하도록 되어 있다.

   1) time_event::object::schedule 클래스

   2) time_event::object::schedule_function 클래스

   3) time_event::Schedule 클래스
      time_event Schedule객체에 등록되어 사용되는 객체이다.
	  생성후 필요한 값을 설정하고 이를 Event Schedule 객체에 등록한다.
      - time_event::Schedule::CFunction
      - time_event::Schedule::CLambda
      - time_event::Schedule::CMemberFunction<TCLASS>

5. Contact us
	@Mail: sangduck@cgcii.co.kr

	@Web: www.CGCII.co.kr
	
	본 소프트웨어의 모든 저작권은 '조상현(Cho Sanghyun)'에 있습니다.

