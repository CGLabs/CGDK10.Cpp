==============================================================================
                                                                             
                        Cho sanghyun's Game Classes II                       
                          Ver 9.0 / Release 2017.01.03                         
                                                                             
                                object classes
                                                                             
                                                                             
                                                                             
                                                                             
    This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr           
    Best for Game Developement and Optimized for Game Developement.          
                                                                             
                     (C) 2008 CGCIII All right reserved.                     
                             http://www.CGCII.co.kr                          
                                                                             
==============================================================================

1. CGCII object classes
	 객체의 일반적이고 기본적인 속성(Property)에 관련된 인터페이스 클래스와 관련
	구현 클래스들이다.

	
2. CGCII object classes의 주요 구성 요소들
   (1) 객체의 기본적인 속성과 조작에 관련된 요소들이다.

3. CGCII object classes
   (I) Ireferenceable
       - 참조계수를 가지는 속성 (생성과 소멸에 관련이 있다.)
	   - 관련: object_ptr<T>, own_ptr<T>, CGOBJ<T>

   (I) Imessageable
       - Message를 받을 수 있는 속성

   (I) ICGDispatchable
       - Imessageable에 메시지를 전달하는 속성

   (I) Inameable
       - 객체의 이름을 가지는 속성

   (I) ICGObjectState : (v)Ireferenceable
	   - Object의 상태를 저장하고 설정할 수 있는 속성을 가지는 클래스이다.

   (I) ICGResource : (v)ICGObject
	   - 자원 객체의 기반 클래스이다.
	   - 이 클래스를 상속받으면 ResourceManager에 추가되어 관리될 수 있다.

   (I) Object Status 관련 속성들
	   - (I) Iinitializable
	   - (I) ICGOpenable
	   - (I) Istartable
	   - (I) ICGUpdatable

   (T) object_ptr<T> (object_ptr<T>)

   (T) own_ptr<T>

   (T) CGOGJ<T> (own_ptr<T>)


3. CGCII Pool Classes의 주요 구성 요소들
   객체나 메모리의 빈번한 할당과 해제로 인한 부하의 손실을 줄이기 위한 것으로
   지금까지 제공되어진 어떠한 풀시스템보다 뛰어난 성능을 제공해준다.

   CGCII Pool Classes에서 제공해주는 풀시스템은 크게 두가지로 나눌수 있다.
   첫째, "메모리 블럭 풀 시스템"으로 동적 메모리 할당을 위한 풀이다.
   둘째, "객체 풀 시스템"으로 일반적인 클래스로 정의된 객체를 위한 풀이다.

	1) 메모리 블럭 풀 시스템(MBPS, memory Block Pool System)
	   - 메모리의 할당을 일정한 크기의 블럭으로 할당을 하거나 해제하는 풀 시스템이다.
	   - 동적으로 메모리를 할당 요청하면 요청한 크기와 같거나 큰 블럭을 할당해 준다.
	   - 할당된 객체는 object_ptr<ICGBuffer>로 할당해준다.
	   - 이 객체는 참조 계수가 0이 되면 자동적으로 풀로 돌아간다.

	2) 객체 풀 (OPS, Object Pool System)
	   - 클래스로 정의된 객체를 위한 풀 시스템으로 풀이 되고자하는 객체는 반드시
	     ICGPoolable을 상속받아 생성되어야 한다.
	   - 단, 객체의 생성자는 최초 생성될 때 한번만 호출되며 소멸자 역시 마찬가지다.
	     할당될 때는 OnPoolAlloc()함수가 호출되며 해제될 때는 OnPoolFree()함수가 
		 호출된다.

	보다 자세한 내용은 Source와 그에 붙어 있는 세부적인 주석을 참조하기 바란다.


4. Contact us
	@Mail: sangduck@cgcii.co.kr

	@Web: www.CGCII.co.kr
	
	본 소스와 소프트웨어의 모든 저작권은 CGCIII에 있습니다.
