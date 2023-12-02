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
    CGNetUpdateClasses는 파일의 전송이나 Update Server나 Client를 만들기 위한
   Classes들로 구성되어 있다.
    게임에서 사용되는 Update Server나 P2P게임 도중 Map과 같은 정보를 상대에게
   전송하는 기능을 손쉽게 구현할수 있도록 되어 있다.

2. CGCII update classes의 특징
     
   1) 다양한 활용성을 고려한 설계.
      - 일반적인 대규모 Update Server를 위한 대규모 전송시스템을 구비하고 있어
        대규모 Update Server의 제작에 매우 효율적인 Server를 손쉽게 제작이
        가능하다.
      - 손쉽게 Patch를 외부가 아니라 프로그램 실행 도중에도 전송이 가능하며
        이로 인해 다양한 응용성이 생긴다.
        * Guild War와 같이 필요할 때 파일들을 Download받을 수 있는 기능.
        * StartCarft처럼 Map이 없을 때 해당 맵을 다른 User로 부터 Download받을
          수 있는 기능.
        * 게임도중에 원하는 파일을 안정적으로 전송할 수 있다..
      - CGNetClientP2P와 연동하여 P2P상에서도 손쉽게 연동이 가능하며 TCP뿐만 
        아니라 UDP로도 안정적인 전송이 가능하다.
      
   2) 강력한 기능
      - File을 일정 Block단위로 나누어 압축한 후 전송하는 압축전송을 지원한다. 
        따라서 따로 File을 Zip과 같은 형식으로 묶지 않아도 효율적인 전송이
        가능하다.
      - 만약에 압축효율이 좋지 못하다면 자동적으로 압축하지 않은 형태로 전송
        하여 쓸데없이 압축을 해제하는 성능의 낭비를 막아준다.
      - 대규모 파일을 위해 이어받기 기능을 제공한다.
      - 다중 접속 Update를 지원합니다. Patch를 받는 입장에서는 하나의 Server
        에서만 Patch를 받지 않고 여러 Server에서 동시에 Update를 받을 수 있는
        다중 Patch기능을 제공합니다. 따라서 Client입장에서는 최고의 성능으로
        Update를 받을 수 있습니다.
      
   3) 최고의 Performance.
      - File의 Send와 Receive는 모두 Overlapped I/O를 통해 Multi-Threaded로
        수행이 된다.
      - Network상의 Send/Receive와 같은 I/O뿐만이 아니라 전송받은 File의  
        Write도 모두 Overlapped I/O를 통해 Multi-Thread 분산처리를 함으로써
        뛰어난 속도와 효율성을 자랑한다.
        이런 이유로 게임의 실행 중 Patch를 하여도 될 정도로 강력하다.
      - 모든 처리는 UnReliable Transfer를 가정하여 제작되었으므로 TCP뿐만
        아니라 UDP에서도 정확히 동작을 한다.
      - 대량의 File전송은 Sliding WIndow기법을 통해 구현되어 대량의 데이터라
        할지라도 순차적으로 안정적인 전송을 수행한다.
      - 대규모 전송을 수행하는 Server를 위해 File을 전송 할 때마다 Hard Disk상에서
        읽어서 처리하는 것이 아니라 미리 File을 하드디스크에서 읽어들여 압축하여
        메모리상에 올려놓고 Update를 요구시 메모리 상에서 전송함으로써 대규모 
        전소을 위한 Server에서는 엄청난 성능을 제공한다.
        (CGNetUpdate::Sendable::CFileStatic)
      - 만약 대규모 Update Server가 아닌 P2P에서 Peer끼리 파일을 전송시 File을
        모두 읽어들인 이후에 전송하면 Delay가 길어질 수가 있으므로 파일을
        전송하는 분량만큼만 즉시즉시 읽어들여 파일을 전송하는 기능도 제공해
        준다. 또 파일의 전송의 효율을 위해 압축기능을 해제할수도 있다.
        (CGNetUpdate::Sendable::CFileInstant)

   4) 강력한 보안 기능.
      - MD5를 통해 파일의 변조 등을 확인하여 Patch함으로써 정확한 파일의 전송
        뿐만이 아니라 파일의 변조로 인한 문제를 해결할수 있다.
      - 또 전송된 File은 File이 제대로 전송되었는지 Confirm을 수행하며 제대로
        전송되지 않았다고 판단되면 재전송을 수행한다.

   5) Update Server와 Update Client제공
      - CCGNetUpdateClasses로 제작된 UpdateServer와 Update Client를 제공한다.
      - 제공되는 CGNetUpdateServer는 대규모 Update를 수행하는 Server로 제작된
        것이다. 
      - 따라서 원하는 추가기능이 있으면 이 Server를 수정함으로써 손쉽게 제작이
        가능하며 특별히 추가를 하지 않더라도 CGNetUpdate만으로 충분히 강력한 
        기능을 가지고 있다.
      - Update를 하고자하는 Folder와 Update시 저장할 Folder 등을 설정하는 기능을
        가지고 있다.
      - 하나의 Update만 있는 것이 아니라 여러 개의 Folder로 나뉘어서 Update를
        관리하므로 한꺼번에 다양한 Update를 제공 할수 있다. 또 이를 통해 Guild War
        에서 선보였던 것처럼 Instant Download기능의 구현이 가능하다.        
      - Exe나 DLL같은 중요한 File의 경우 보다 강력한 보안 검사를 하는 기능을 가지고
        있으며 이를 직접  설정할 수 있다.(Exe나 DLL은 Default로 Security File로 설정된다.)
      - 해당하는 Folder에 지워야하는 File이 있을 경우 설정을 통해 Update시 특정파일을
        지울수 있도록 하는 기능이 있다.
      - Client상에서는 효율적인 처리를 위해 한번 Scan한 Folder는 cgfile.dat파일을 
        만들어 Folder 파일의 정보를 보관하고 있으며 만약 Folder의 파일 내용을 
        변경했을 경우 다음 Update시 자동으로 판단하여 Update하는 기능을 가지고 있다.
      - Update용 Client는 Update완료 후 실행해야하는 File을 설정하는 기능이 있다.
        따라서 Update가 완료 후 Application을 실행하는 형태로 설정이 가능하다.
      - Config기능을 가지고 있어 Update를 위해 설정한 기능들을 Config 파일로 저장하는
        기능이 있으며 이것을 실행시 자동으로 읽어들여 적용처리한다.
      - Update Client는 MFC로 제작이 되었으며 자체 Skin을 가지고 있어 미려한 디자인
        을 가지고 있으며 추후 변경을 원할 경우 쉽게 변경이 가능하다.


2. Class의 구성

   1) CGNetIO Compoment
       File Send와 Receive를 구현하기 위한 I/O Component Class들의 모음이다.
      크게 File의 Send를 위한 File Sender와 그 부속 class 그리고 전송되어온  
      FIle을 받기위한File Receiver와 그 부속 Class들로 구성되어 있다.
      
      - File Sender와 부속 Classes
        파일의 전송을 담당하는 Class들이다.
       크기 NUpdateSender와 CFileSendable로 나눌수 있으며 FileSe...
      
      - File Receiver와 부속 Classes
      
      
   2) Classes
   
      - AddOn으로 제작된 Classes
      - Socket으로 제작된 Classes
