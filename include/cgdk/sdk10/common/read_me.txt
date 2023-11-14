==============================================================================
                                                                             
                        Cho sanghyun's Game Classes II                       
                          Ver 9.0 / Release 2017.01.03                         
                                                                             
                                   Common                                   
                                                                             
                                                                             
                                                                             
                                                                             
    This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr           
    Best for Game Developement and Optimized for Game Developement.          
                                                                             
                     (C) 2008 CGCIII All right reserved.                     
                             http://www.CGCII.co.kr                          
                                                                             
==============================================================================

1. CGCII Common Classes
	 실질적으로 프로그램을 수행하는 부위인 Thread와 그 관련 관리 및 동작에 
	관련된 class들을 제공한다.
	
	 기본적인 Thread의 사용 및 관리를 위한 class와 다중 Thread의 관리와 효율적인
	사용을 위한 class들을 제공한다.
	
	 또 이 Thread에 작업을 효율적으로 분리하여 처리하기 위한 class들이 제공되며
	Excetion처리를 위한 구조 역시 제공된다.

	
2. CGCII Common Classes의 주요 구성 요소들

	1) APIs (Low level classes)
	    Thread의에 관련된 것과 IOCP에 관련된 API차원의 class를 제공해 준다.
	   
	   - Thread					지역변수를 사용한 고정크기의 vector
	   - ThreadPool				일반적인 vector
	   - IOCompletionPort		일반적인 list (circulare linked list)
	
	2) Concurrency-Division Load balancing Support.
	    
	   - Executor				Executor를 실행하는 실행자.(일반적으로 Thread)
	   - Excutor with IOCP		IOCP를 이용하여 구현한 Executor
	   - Completr				Executor서 실행되는 실행의 단위.


	3) Exception classes
	   - ICGReferenceable		count가 0이 되면 on_final_release/process_dispose
	                            함수를 호출해주는 Class
	   - ReferenceCountWaiter	동기화를 위한 class
	   - Exception classes		Throw를 위한 class들...


	보다 자세한 내용은 Source와 그에 붙어 있는 세부적인 주석을 참조하기 바란다.


3. Contact us
	@Mail: sangduck@cgcii.co.kr

	@Web: www.CGCII.co.kr
	
	본 소프트웨어의 모든 저작권은 CGCIII에 있습니다.

