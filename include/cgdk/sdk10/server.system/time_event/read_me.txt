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

  ���� � �� Ư���� �ð� Ȥ�� �����ð� ���� �����ؾ��ϴ� Event�� ���� ��� �̸�
 ���� Ŭ�������� �ǹ��Ѵ�.
  �Ϲ� ������ ���񽺸� ��� �� Ư�� �ð��� ������ ������Ű�ų� ����� �ϰų� 
 �����ڸ� �����ؼ� ����������Ű�ų� ��� Ư���� �ð� Ȥ�� ���� �ð����� ����Ǿ��
 �ϴ� ���� �ʿ��� ������ ���� ���ȴ�.

   Event Classes���� ũ�� �ѹ��� ����Ǵ� ��ü, �ݺ������� ����Ǵ� ��ü, ���۰�
  ���� ������ ���� ����Ǵ� ��ü, ������ ������ �ð����� ����Ǿ�� �ϴ� ��ü ����
  �����Ѵ�.
   �ʿ信 ���� �ش� ��ü�� ���ӹ޾� ������ �ϰų� �����Ͽ� Event manager�� ���
  �����ν� ����ǰ� �ȴ�.
  
2. CGEvnet::manager�� time_event::Ientity Ŭ����
    time_event::entity_manager�� EventObject�� �����Ű�� ���հ����ڷμ� ������ Event Object��
   �ݵ�� Event Manger�� ��ϵǾ�� ����ȴ�.
    Event manager�� �̱��� ��ü�� ���� ������ �ʿ� ���� ���������� �����ϰ� �ϳ���
   �����Ǿ� �ִ�.

3. time_event::object Ŭ������

   1) ���ѹ� ����
      - time_event::object::once
      - time_event::object::onceFunction<TFUNCTION>
   2) �ݺ������� ����
      - time_event::object::iteration
      - time_event::object::iterationFunction<TFUNCTION>

   3) ���۰� ������ ������ ����
      - time_event::object::start_end
      - time_event::object::start_endFunction<TFUNCTION>

   4) ���۽����� �������� ����Ǹ� �� ���� �ð����� �����ð����� ����
      - time_event::object::start_iteration_end
      - time_event::object::start_iteration_endFunction<TFUNCTION>

4. time_event Schedule ���� Ŭ������ ���
   Schedule�� ���� ���� ������ �ϳ��� ��ü���� ������ �� �ֵ��� ����Ǿ���.
   �� ���� Event ��ü�� �޸� ���� CSchedule ��ü�� �����Ͽ� �̸� Event ��ü��
   ����Ͽ� ����ϵ��� �Ǿ� �ִ�.

   1) time_event::object::schedule Ŭ����

   2) time_event::object::schedule_function Ŭ����

   3) time_event::Schedule Ŭ����
      time_event Schedule��ü�� ��ϵǾ� ���Ǵ� ��ü�̴�.
	  ������ �ʿ��� ���� �����ϰ� �̸� Event Schedule ��ü�� ����Ѵ�.
      - time_event::Schedule::CFunction
      - time_event::Schedule::CLambda
      - time_event::Schedule::CMemberFunction<TCLASS>

5. Contact us
	@Mail: sangduck@cgcii.co.kr

	@Web: www.CGCII.co.kr
	
	�� ����Ʈ������ ��� ���۱��� '������(Cho Sanghyun)'�� �ֽ��ϴ�.

