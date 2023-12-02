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
	 ��ü�� �Ϲ����̰� �⺻���� �Ӽ�(Property)�� ���õ� �������̽� Ŭ������ ����
	���� Ŭ�������̴�.

	
2. CGCII object classes�� �ֿ� ���� ��ҵ�
   (1) ��ü�� �⺻���� �Ӽ��� ���ۿ� ���õ� ��ҵ��̴�.

3. CGCII object classes
   (I) Ireferenceable
       - ��������� ������ �Ӽ� (������ �Ҹ꿡 ������ �ִ�.)
	   - ����: object_ptr<T>, own_ptr<T>, CGOBJ<T>

   (I) Imessageable
       - Message�� ���� �� �ִ� �Ӽ�

   (I) ICGDispatchable
       - Imessageable�� �޽����� �����ϴ� �Ӽ�

   (I) Inameable
       - ��ü�� �̸��� ������ �Ӽ�

   (I) ICGObjectState : (v)Ireferenceable
	   - Object�� ���¸� �����ϰ� ������ �� �ִ� �Ӽ��� ������ Ŭ�����̴�.

   (I) ICGResource : (v)ICGObject
	   - �ڿ� ��ü�� ��� Ŭ�����̴�.
	   - �� Ŭ������ ��ӹ����� ResourceManager�� �߰��Ǿ� ������ �� �ִ�.

   (I) Object Status ���� �Ӽ���
	   - (I) Iinitializable
	   - (I) ICGOpenable
	   - (I) Istartable
	   - (I) ICGUpdatable

   (T) object_ptr<T> (object_ptr<T>)

   (T) own_ptr<T>

   (T) CGOGJ<T> (own_ptr<T>)


3. CGCII Pool Classes�� �ֿ� ���� ��ҵ�
   ��ü�� �޸��� ����� �Ҵ�� ������ ���� ������ �ս��� ���̱� ���� ������
   ���ݱ��� �����Ǿ��� ��� Ǯ�ý��ۺ��� �پ ������ �������ش�.

   CGCII Pool Classes���� �������ִ� Ǯ�ý����� ũ�� �ΰ����� ������ �ִ�.
   ù°, "�޸� �� Ǯ �ý���"���� ���� �޸� �Ҵ��� ���� Ǯ�̴�.
   ��°, "��ü Ǯ �ý���"���� �Ϲ����� Ŭ������ ���ǵ� ��ü�� ���� Ǯ�̴�.

	1) �޸� �� Ǯ �ý���(MBPS, memory Block Pool System)
	   - �޸��� �Ҵ��� ������ ũ���� ������ �Ҵ��� �ϰų� �����ϴ� Ǯ �ý����̴�.
	   - �������� �޸𸮸� �Ҵ� ��û�ϸ� ��û�� ũ��� ���ų� ū ���� �Ҵ��� �ش�.
	   - �Ҵ�� ��ü�� object_ptr<ICGBuffer>�� �Ҵ����ش�.
	   - �� ��ü�� ���� ����� 0�� �Ǹ� �ڵ������� Ǯ�� ���ư���.

	2) ��ü Ǯ (OPS, Object Pool System)
	   - Ŭ������ ���ǵ� ��ü�� ���� Ǯ �ý������� Ǯ�� �ǰ����ϴ� ��ü�� �ݵ��
	     ICGPoolable�� ��ӹ޾� �����Ǿ�� �Ѵ�.
	   - ��, ��ü�� �����ڴ� ���� ������ �� �ѹ��� ȣ��Ǹ� �Ҹ��� ���� ����������.
	     �Ҵ�� ���� OnPoolAlloc()�Լ��� ȣ��Ǹ� ������ ���� OnPoolFree()�Լ��� 
		 ȣ��ȴ�.

	���� �ڼ��� ������ Source�� �׿� �پ� �ִ� �������� �ּ��� �����ϱ� �ٶ���.


4. Contact us
	@Mail: sangduck@cgcii.co.kr

	@Web: www.CGCII.co.kr
	
	�� �ҽ��� ����Ʈ������ ��� ���۱��� CGCIII�� �ֽ��ϴ�.
