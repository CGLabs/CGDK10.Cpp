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
	 ���������� ���α׷��� �����ϴ� ������ Thread�� �� ���� ���� �� ���ۿ� 
	���õ� class���� �����Ѵ�.
	
	
2. CGCII MFC Controls�� �ֿ� ���� ��ҵ�

	1) Pools
	   - Memoory Block Pool			memory�� Block������ �Ҵ��ϴ� Pool�̴�.
	   - memory Pool				������ ũ���� memory�� �Ҵ��ϴ� Pool�̴�.
	   - Object Pool				���������� ����� ����ũ���� vector

	2) Factory
	   - Indexed Factory			������ ��ü�� ������ȣ�� �ο��ϴ� Factory
	   - Indexed Factory(Pool)		��ü ���꿡 Pool�� ����ϴ� Factory

	3) Releaser
	   Reference count�� 0�� �Ǿ��� �� ȣ��Ǵ� process_dispose�Լ��� ������ 
	   class�̴�.
	   
	   - ICGDisposable::NoAct		�ƹ� �ϵ� ���� �ʴ´�.
	   - ICGDisposable::NDelete		delete�� ������ �����.
	   - NCGPoolable				Pool�� �ǵ�����.
	   - NCGProductable				Factory�� �ǵ�����.


	���� �ڼ��� ������ Source�� �׿� �پ� �ִ� �������� �ּ��� �����ϱ� �ٶ���.


3. Contact us
	@Mail: sangduck@cgcii.co.kr

	@Web: www.CGCII.co.kr
	
	�� ����Ʈ������ ��� ���۱��� CGCIII�� �ֽ��ϴ�.
