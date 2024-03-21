#*****************************************************************************
#*                                                                           *
#*                      Cho sanghyun's Game Classes II                       *
#*                      Ver 10.0 / release 2019.12.11                        *
#*                                                                           *
#*           CMake - CGDK10.example.chatting_simple.server.console           *
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

# ----------------------------------------------------------------------------
# setting
# ----------------------------------------------------------------------------
# 1) project name
PROJECT ( "CGDK10.chatting_simple.client" )

# 2) project version
SET ( PROJECT_VERSION_MAJOR 10 )
SET ( PROJECT_VERSION_MINOR 0 )
SET ( PROJECT_VERSION_PATCH 100 )
SET ( PROJECT_VERSION_TWEAK 1 )
SET ( DEFAULT_BUILD_TYPE Debug )

# 3) build version
CMAKE_MINIMUM_REQUIRED ( VERSION 3.20 )
CMAKE_POLICY( VERSION 3.20 )

# 4) default BUILD_TYPE
IF (NOT DEFINED CMAKE_BULD_TYPE)
	SET (CMAKE_BULD_TYPE "Debug")
ENDIF()

# 5) directories
SET ( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../../../lib/cgdk/sdk10 )
SET ( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../../../lib/cgdk/sdk10 )
SET ( CMAKE_RUNTIME_OTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../../../execute )
SET ( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../execute )

# 6) compile options
SET ( CMAKE_CXX_FLAGS "-DC_FLAGS -fexceptions -std=c++17" )
SET ( CMAKE_CXX_FLAGS_DEBUG "-D_DEBUG -g3 -Wall -Wextra" )
SET ( CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O3 -Wall -Wextra" )

# 7) include directories
INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}/../../../../include
	./
)

# 8) library directories
LINK_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}/../../../../lib/cgdk/sdk10/${DIST}
)


# ----------------------------------------------------------------------------
# source files
# ----------------------------------------------------------------------------
SET (SRC_FILES

include.cpp

channel_manager.cpp
channel_group_chatting.cpp
channel_group_waiting.cpp

user_manager.cpp
user_group_immigration.cpp
user_socket.cpp

service.cpp
)


# ----------------------------------------------------------------------------
# compile
# ----------------------------------------------------------------------------
IF (${CMAKE_BUILD_TYPE} MATCHES "Debug")
	SET (BUILD_MESSAGE "Debug")
	SET (BUILD_TYPE "Debug")
ELSEIF (${CMAKE_BUILD_TYPE} MATCHES "Release")
	SET (BUILD_MESSAGE "Release")
	SET (BUILD_TYPE "Release")
ELSE ()
	message (SEND_ERROR "'CMAKE_BUILD_TYPE' is not mathed")
ENDIF ()

# 2) messages
MESSAGE (STATUS "compile ${PROJECT_NAME}")
MESSAGE (STATUS "  - configure['${BUILD_MESSAGE}']")

# 3) executable
ADD_EXECUTABLE(${PROJECT_NAME}.${BUILD_TYPE} ${SRC_FILES})
TARGET_PRECOMPILE_HEADERS(${PROJECT_NAME}_linux.${BUILD_TYPE} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:pch.h>")

# 4) link
TARGET_LINK_LIBRARIES( ${PROJECT_NAME}.${BUILD_TYPE}
	CGDK10.net.socket_linux.${BUILD_TYPE}
	CGDK10.system.object_linux.${BUILD_TYPE}
	rt
	pthread
)
