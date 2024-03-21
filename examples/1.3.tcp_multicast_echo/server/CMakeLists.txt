#*****************************************************************************
#*                                                                           *
#*                      Cho sanghyun's Game Classes II                       *
#*                      Ver 10.0 / release 2019.12.11                        *
#*                                                                           *
#*                                   CMake                                   *
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
PROJECT ( "CGDK10.tcp_echo_multi.server" )

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
FIND_PACKAGE(Boost 1.71.0)
IF(Boost_FOUND)

# 1) tcp multi echo server - boost.asio
ADD_SUBDIRECTORY (console.asio)

# 2) tcp multi echo server - boost.asio.ex
ADD_SUBDIRECTORY (console.asio.ex)

ENDIF(Boost_FOUND)

# 3) tcp multi echo server - CGDK10
ADD_SUBDIRECTORY (console)

# 4) tcp multi echo server with gather - CGDK10
ADD_SUBDIRECTORY (console.gather)

