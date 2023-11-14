*****************************************************************************
*                                                                           *
*                      Cho sanghyun's Game Classes II                       *
*                       Ver 10.0 / Release 2019.12.11                       *
*                                                                           *
*                          network update classes                           *
*                                                                           *
*                                                                           *
*                                                                           *
*                                                                           *
*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
*  Best for Game Developement and Optimized for Game Developement.          *
*                                                                           *
*                (c) 2003. Cho Sanghyun. All right reserved.                *
*                          http://www.CGCII.co.kr                           *
*                                                                           *
*****************************************************************************


1. CGCII update classes
    CGNetUpdateClasses�� ������ �����̳� Update Server�� Client�� ����� ����
   Classes��� �����Ǿ� �ִ�.
    ���ӿ��� ���Ǵ� Update Server�� P2P���� ���� Map�� ���� ������ ��뿡��
   �����ϴ� ����� �ս��� �����Ҽ� �ֵ��� �Ǿ� �ִ�.

2. CGCII update classes�� Ư¡
     
   1) �پ��� Ȱ�뼺�� ����� ����.
      - �Ϲ����� ��Ը� Update Server�� ���� ��Ը� ���۽ý����� �����ϰ� �־�
        ��Ը� Update Server�� ���ۿ� �ſ� ȿ������ Server�� �ս��� ������
        �����ϴ�.
      - �ս��� Patch�� �ܺΰ� �ƴ϶� ���α׷� ���� ���߿��� ������ �����ϸ�
        �̷� ���� �پ��� ���뼺�� �����.
        * Guild War�� ���� �ʿ��� �� ���ϵ��� Download���� �� �ִ� ���.
        * StartCarftó�� Map�� ���� �� �ش� ���� �ٸ� User�� ���� Download����
          �� �ִ� ���.
        * ���ӵ��߿� ���ϴ� ������ ���������� ������ �� �ִ�..
      - CGNetClientP2P�� �����Ͽ� P2P�󿡼��� �ս��� ������ �����ϸ� TCP�Ӹ� 
        �ƴ϶� UDP�ε� �������� ������ �����ϴ�.
      
   2) ������ ���
      - File�� ���� Block������ ������ ������ �� �����ϴ� ���������� �����Ѵ�. 
        ���� ���� File�� Zip�� ���� �������� ���� �ʾƵ� ȿ������ ������
        �����ϴ�.
      - ���࿡ ����ȿ���� ���� ���ϴٸ� �ڵ������� �������� ���� ���·� ����
        �Ͽ� �������� ������ �����ϴ� ������ ���� �����ش�.
      - ��Ը� ������ ���� �̾�ޱ� ����� �����Ѵ�.
      - ���� ���� Update�� �����մϴ�. Patch�� �޴� ���忡���� �ϳ��� Server
        ������ Patch�� ���� �ʰ� ���� Server���� ���ÿ� Update�� ���� �� �ִ�
        ���� Patch����� �����մϴ�. ���� Client���忡���� �ְ��� ��������
        Update�� ���� �� �ֽ��ϴ�.
      
   3) �ְ��� Performance.
      - File�� Send�� Receive�� ��� Overlapped I/O�� ���� Multi-Threaded��
        ������ �ȴ�.
      - Network���� Send/Receive�� ���� I/O�Ӹ��� �ƴ϶� ���۹��� File��  
        Write�� ��� Overlapped I/O�� ���� Multi-Thread �л�ó���� �����ν�
        �پ �ӵ��� ȿ������ �ڶ��Ѵ�.
        �̷� ������ ������ ���� �� Patch�� �Ͽ��� �� ������ �����ϴ�.
      - ��� ó���� UnReliable Transfer�� �����Ͽ� ���۵Ǿ����Ƿ� TCP�Ӹ�
        �ƴ϶� UDP������ ��Ȯ�� ������ �Ѵ�.
      - �뷮�� File������ Sliding WIndow����� ���� �����Ǿ� �뷮�� �����Ͷ�
        ������ ���������� �������� ������ �����Ѵ�.
      - ��Ը� ������ �����ϴ� Server�� ���� File�� ���� �� ������ Hard Disk�󿡼�
        �о ó���ϴ� ���� �ƴ϶� �̸� File�� �ϵ��ũ���� �о�鿩 �����Ͽ�
        �޸𸮻� �÷����� Update�� �䱸�� �޸� �󿡼� ���������ν� ��Ը� 
        ������ ���� Server������ ��û�� ������ �����Ѵ�.
        (CGNetUpdate::Sendable::CFileStatic)
      - ���� ��Ը� Update Server�� �ƴ� P2P���� Peer���� ������ ���۽� File��
        ��� �о���� ���Ŀ� �����ϸ� Delay�� ����� ���� �����Ƿ� ������
        �����ϴ� �з���ŭ�� ������ �о�鿩 ������ �����ϴ� ��ɵ� ������
        �ش�. �� ������ ������ ȿ���� ���� �������� �����Ҽ��� �ִ�.
        (CGNetUpdate::Sendable::CFileInstant)

   4) ������ ���� ���.
      - MD5�� ���� ������ ���� ���� Ȯ���Ͽ� Patch�����ν� ��Ȯ�� ������ ����
        �Ӹ��� �ƴ϶� ������ ������ ���� ������ �ذ��Ҽ� �ִ�.
      - �� ���۵� File�� File�� ����� ���۵Ǿ����� Confirm�� �����ϸ� �����
        ���۵��� �ʾҴٰ� �ǴܵǸ� �������� �����Ѵ�.

   5) Update Server�� Update Client����
      - CCGNetUpdateClasses�� ���۵� UpdateServer�� Update Client�� �����Ѵ�.
      - �����Ǵ� CGNetUpdateServer�� ��Ը� Update�� �����ϴ� Server�� ���۵�
        ���̴�. 
      - ���� ���ϴ� �߰������ ������ �� Server�� ���������ν� �ս��� ������
        �����ϸ� Ư���� �߰��� ���� �ʴ��� CGNetUpdate������ ����� ������ 
        ����� ������ �ִ�.
      - Update�� �ϰ����ϴ� Folder�� Update�� ������ Folder ���� �����ϴ� �����
        ������ �ִ�.
      - �ϳ��� Update�� �ִ� ���� �ƴ϶� ���� ���� Folder�� ����� Update��
        �����ϹǷ� �Ѳ����� �پ��� Update�� ���� �Ҽ� �ִ�. �� �̸� ���� Guild War
        ���� �������� ��ó�� Instant Download����� ������ �����ϴ�.        
      - Exe�� DLL���� �߿��� File�� ��� ���� ������ ���� �˻縦 �ϴ� ����� ������
        ������ �̸� ����  ������ �� �ִ�.(Exe�� DLL�� Default�� Security File�� �����ȴ�.)
      - �ش��ϴ� Folder�� �������ϴ� File�� ���� ��� ������ ���� Update�� Ư��������
        ����� �ֵ��� �ϴ� ����� �ִ�.
      - Client�󿡼��� ȿ������ ó���� ���� �ѹ� Scan�� Folder�� cgfile.dat������ 
        ����� Folder ������ ������ �����ϰ� ������ ���� Folder�� ���� ������ 
        �������� ��� ���� Update�� �ڵ����� �Ǵ��Ͽ� Update�ϴ� ����� ������ �ִ�.
      - Update�� Client�� Update�Ϸ� �� �����ؾ��ϴ� File�� �����ϴ� ����� �ִ�.
        ���� Update�� �Ϸ� �� Application�� �����ϴ� ���·� ������ �����ϴ�.
      - Config����� ������ �־� Update�� ���� ������ ��ɵ��� Config ���Ϸ� �����ϴ�
        ����� ������ �̰��� ����� �ڵ����� �о�鿩 ����ó���Ѵ�.
      - Update Client�� MFC�� ������ �Ǿ����� ��ü Skin�� ������ �־� �̷��� ������
        �� ������ ������ ���� ������ ���� ��� ���� ������ �����ϴ�.


2. Class�� ����

   1) CGNetIO Compoment
       File Send�� Receive�� �����ϱ� ���� I/O Component Class���� �����̴�.
      ũ�� File�� Send�� ���� File Sender�� �� �μ� class �׸��� ���۵Ǿ��  
      FIle�� �ޱ�����File Receiver�� �� �μ� Class��� �����Ǿ� �ִ�.
      
      - File Sender�� �μ� Classes
        ������ ������ ����ϴ� Class���̴�.
       ũ�� NUpdateSender�� CFileSendable�� ������ ������ FileSe...
      
      - File Receiver�� �μ� Classes
      
      
   2) Classes
   
      - AddOn���� ���۵� Classes
      - Socket���� ���۵� Classes
