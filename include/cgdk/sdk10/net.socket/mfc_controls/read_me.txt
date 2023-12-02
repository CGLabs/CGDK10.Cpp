==============================================================================
                                                                            
                      Cho sanghyun's Game Classes II                       
                       Ver 9.0 / Release 2017.01.03                         
                                                                           
                        Network Socket MFC Controls
                                                                            
                                                                            
                                                                            
   This Program is programmed by Cho SangHyun. sangducks@gamil.com           
   Best for Game Developement and Optimized for Game Developement.          
                                                                            
                 (c) 2016 Cho Sanghyun All right reserved                    
                            http://www.CGCII.co.kr                          
                                                                            
==============================================================================

1. CGCII Network Socket MFC Classes
	 실질적으로 프로그램을 수행하는 부위인 Thread와 그 관련 관리 및 동작에 
	관련된 class들을 제공한다.
	
	 기본적인 Thread의 사용 및 관리를 위한 class와 다중 Thread의 관리와 효율적인
	사용을 위한 class들을 제공한다.
	
	 또 이 Thread에 작업을 효율적으로 분리하여 처리하기 위한 class들이 제공되며
	Excetion처리를 위한 구조 역시 제공된다.

	
2. CGObject Classes의 주요 구성 요소들

	1) Pools
	   - Memoory Block Pool			메모리를 블럭단위로 할당하는 풀이다.
	   - Memory Pool				고정된 크기의 메모리를 할당하는 풀이다.
	   - Object Pool				객체단위의 풀

	2) Factory
	   - Indexed Factory			생성된 객체에 고유번호를 부여하는 Factory
	   - Indexed Factory(Pool)		객체 생산에 Pool을 사용하는 Factory

	3) Releaser
	   Reference count가 0이 되었을 때 호출되는 on_final_release/process_dispose
	   함수를 정의한 class이다.
	   
	   - NCGPoolable				Pool로 되돌린다.
	   - NCGProductable				Factory로 되돌린다.


	보다 자세한 내용은 Source와 그에 붙어 있는 세부적인 주석을 참조하기 바란다.


3. Contact us
	@Mail: sangduck@cgcii.co.kr

	@Web: www.CGCII.co.kr
	
	본 소프트웨어의 모든 저작권은 '조상현(Cho Sanghyun)'에 있습니다.
