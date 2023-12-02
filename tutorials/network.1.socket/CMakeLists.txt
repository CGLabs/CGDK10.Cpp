#*****************************************************************************
#*                                                                           *
#*                      Cho sanghyun's Game Classes II                       *
#*                      Ver 10.0 / release 2019.12.11                        *
#*                                                                           *
#*                          CMake - tutorial.socket                          *
#*                                                                           *
#*                                                                           *
#*                                                                           *
#*                                                                           *
#*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
#*  Best for Game Developement and Optimized for Game Developement.          *
#*                                                                           *
#*                (c) 2016 Cho Sanghyun All right reserved.                  *
#*                          http://www.CGCII.co.kr                           *
#*                                                                           *
#*****************************************************************************

#-----------------------------------------------------------------------------
# setting
#-----------------------------------------------------------------------------
# 1) project name
PROJECT ( "CGDK10.tutorial.socket" )

# 2) project version
SET ( PROJECT_VERSION_MAJOR 10 )
SET ( PROJECT_VERSION_MINOR 0 )
SET ( PROJECT_VERSION_PATCH 100 )
SET ( PROJECT_VERSION_TWEAK 1 )
SET ( DEFAULT_BUILD_TYPE Debug )

# 3) build version
CMAKE_MINIMUM_REQUIRED ( VERSION 3.20 )
CMAKE_POLICY( VERSION 3.20 )


#-----------------------------------------------------------------------------
# compile
#-----------------------------------------------------------------------------
# 1) tcp_simple
ADD_SUBDIRECTORY (socket.01.tcp_simple)

# 2) tcp_send_receive
ADD_SUBDIRECTORY (socket.02.tcp_send_receive)

# 3) tcp_configure
ADD_SUBDIRECTORY (socket.03.tcp_configure)

# 4) udp_simple
ADD_SUBDIRECTORY (socket.04.udp_simple)

# 5) http
ADD_SUBDIRECTORY (socket.05.http)

# 6) websocket
ADD_SUBDIRECTORY (socket.06.websocket)

# ex1) tcp graceful close
ADD_SUBDIRECTORY (socket.ex01.tcp_graceful_close)

# ex2) tcp neet ip
ADD_SUBDIRECTORY (socket.ex02.net.ip)

# ex3) tcp reconneect
ADD_SUBDIRECTORY (socket.ex03.reconnect)

# ex4) unity 3D
# ex5) unrael 3D

# ex6) tcp protobuf
ADD_SUBDIRECTORY (socket.ex06.tcp_protobuf)

# ex7) tcp connector
ADD_SUBDIRECTORY (socket.ex07.tcp_connector)

# ex8) socket logger
ADD_SUBDIRECTORY (socket.ex08.socket_logger)
