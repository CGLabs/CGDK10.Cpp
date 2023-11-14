==============================================================================
                                                                             
                        Cho sanghyun's Game Classes II                       
                          Ver 9.0 / Release 2017.01.03                         
                                                                             
                                 MFC Controls                            
                                                                             
                                                                             
                                                                             
                                                                             
    This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr           
    Best for Game Developement and Optimized for Game Developement.          
                                                                             
                     (C) 2008 CGCIII All right reserved.                     
                             http://www.CGCII.co.kr                          
                                                                             
==============================================================================

1. CGCII MFC Controls
	 실질적으로 프로그램을 수행하는 부위인 Thread와 그 관련 관리 및 동작에 
	관련된 class들을 제공한다.
	
	
2. CGCII MFC Controls의 주요 구성 요소들

	1) Pools
	   - Memoory Block Pool			memory를 Block단위로 할당하는 Pool이다.
	   - memory Pool				고정된 크기의 memory를 할당하는 Pool이다.
	   - Object Pool				지역변수를 사용한 고정크기의 vector

	2) Factory
	   - Indexed Factory			생성된 객체에 고유번호를 부여하는 Factory
	   - Indexed Factory(Pool)		객체 생산에 Pool을 사용하는 Factory

	3) Releaser
	   Reference count가 0이 되었을 때 호출되는 process_dispose함수를 정의한 
	   class이다.
	   
	   - ICGDisposable::NoAct		아무 일도 하지 않는다.
	   - ICGDisposable::NDelete		delete로 스스로 지운다.
	   - NCGPoolable				Pool로 되돌린다.
	   - NCGProductable				Factory로 되돌린다.


	보다 자세한 내용은 Source와 그에 붙어 있는 세부적인 주석을 참조하기 바란다.


3. Contact us
	@Mail: sangduck@cgcii.co.kr

	@Web: www.CGCII.co.kr
	
	본 소프트웨어의 모든 저작권은 CGCIII에 있습니다.
