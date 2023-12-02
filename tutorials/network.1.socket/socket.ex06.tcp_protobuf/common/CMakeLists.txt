#*****************************************************************************
#*                                                                           *
#*                      Cho sanghyun's Game Classes II                       *
#*                      Ver 10.0 / release 2019.12.11                        *
#*                                                                           *
#*                  CMake - tutorial.socket.tcp_send_receive                 *
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
# protubuf
#-----------------------------------------------------------------------------
# 1) compile protobuf
#EXECUTE_PROCESS(COMMAND protoc messages.proto --cpp_out=./
#            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/common
#            RESULT_VARIABLE PROTOBUF_RESULT
#            OUTPUT_VARIABLE PROTOBUF_OUTPUT_VARIABLE)

# 1) find protobuf
INCLUDE(FindProtobuf)
FIND_PACKAGE(Protobuf REQUIRED)

# 2) include
INCLUDE_DIRECTORIES(${PROTOBUF_INCLUDE_DIR})

# 3) generate
PROTOBUF_GENERATE_CPP(PROTO_SRC PROTO_HEADER messages.proto)

# 4) library
ADD_LIBRARY(proto ${PROTO_HEADER} ${PROTO_SRC})