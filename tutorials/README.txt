주의) linux버전을 컴파일 할 경우.

- tutorial/network1.socket/socket.ex06.tcp_protobuf 를 컴파일 하려면 probuf의 설치가 필요합니다.
   ubuntu일 경우 'sudo apt install libprotobuf-dev'같은 걸로 설치해 주시면 될 것입니다.
   플랫폼별 설치법은 protobuf 사이트를 참고해 주세요.
- protobuf의 설치를 제외하고 싶다면 tutorials/network.1.socket/CMakeFile.txt파일을 열어 

   ADD_SUBDIRECTORY (socket.ex06.tcp_protobuf)

  문장 앞에 #을 붙혀서 주석처리해주세요.

   #ADD_SUBDIRECTORY (socket.ex06.tcp_protobuf)

