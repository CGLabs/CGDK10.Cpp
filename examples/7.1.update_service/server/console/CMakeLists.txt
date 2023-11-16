#*****************************************************************************
#*                                                                           *
#*                               project GRUMA                               *
#*                                                                           *
#*                           update_service.server                           *
#*                                                                           *
#*                                                                           *
#*                                                                           *
#*                                                                           *
#*                  ¨Ï2017. Cho SangHyun. All rights reserved                *
#*                          http://www.CGCIII.co.kr                          *
#*                                                                           *
#*****************************************************************************

#-----------------------------------------------------------------------------
# setting
#-----------------------------------------------------------------------------
# 1) project name
PROJECT ( "CGDK10.example.update_service.server.console" )

# 2) project version
SET ( PROJECT_VERSION_MAJOR 10 )
SET ( PROJECT_VERSION_MINOR 0 )
SET ( PROJECT_VERSION_PATCH 100 )
SET ( PROJECT_VERSION_TWEAK 1 )
set ( DEFAULT_BUILD_TYPE Debug )

# 3) build version
CMAKE_MINIMUM_REQUIRED ( VERSION 3.10 )

# 4) default BUILD_TYPE
IF (NOT DEFINED CMAKE_BULD_TYPE)
	SET (CMAKE_BULD_TYPE "Debug")
ENDIF()

# 5) directories
SET ( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../../lib/cgdk/sdk10 )
SET ( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../../lib/cgdk/sdk10 )
SET ( CMAKE_RUNTIME_OTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../execute )
SET ( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../execute/account_server )

# 6) compile options
set ( CMAKE_CXX_STANDARD 20)
set ( CMAKE_CXX_STANDARD_REQUIRED ON)
SET ( CMAKE_CXX_FLAGS "-DC_FLAGS -fexceptions -std=c++20" )
SET ( CMAKE_CXX_FLAGS_DEBUG "-D_DEBUG -g -Wall -Wextra" )
SET ( CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O3 -Wall -Wextra" )

# 7) include directories
INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}/../../../../include
	./
	${CMAKE_CURRENT_SOURCE_DIR}/../shared
)

# 8) library directories
LINK_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}/../../../../lib/cgdk/sdk10
)


#-----------------------------------------------------------------------------
# source files
#-----------------------------------------------------------------------------
SET (SRC_FILES
# ...
pch.cpp

# include
../shared/include.cpp

# main
CGDK10.update.update_service.server.cpp

# account
../shared/socket_peer.cpp
../shared/group_peer_immigration.cpp
../shared/group_peer.cpp

#service
../shared/service.cpp
)


#-----------------------------------------------------------------------------
# compile
#-----------------------------------------------------------------------------
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
TARGET_PRECOMPILE_HEADERS(${PROJECT_NAME}.${BUILD_TYPE} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:pch.h>")

# 4) link
TARGET_LINK_LIBRARIES( ${PROJECT_NAME}.${BUILD_TYPE}
	CGDK10.server.system.service_linux.${BUILD_TYPE}
	CGDK10.server.system.time_event_linux.${BUILD_TYPE}
	CGDK10.server.system.log_linux.${BUILD_TYPE}
	CGDK10.net.update_linux.${BUILD_TYPE}
	CGDK10.net.socket_linux.${BUILD_TYPE}
	CGDK10.system.util.crypt_linux.${BUILD_TYPE}
	CGDK10.system.object_linux.${BUILD_TYPE}
	rt
	pthread
)
