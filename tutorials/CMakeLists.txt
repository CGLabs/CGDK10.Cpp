#*****************************************************************************
#*                                                                           *
#*                      Cho sanghyun's Game Classes II                       *
#*                      Ver 10.0 / release 2019.12.11                        *
#*                                                                           *
#*                             CMake - tutorial                              *
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
PROJECT ( "CGDK10.tutorial" )

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
# 1) object
ADD_SUBDIRECTORY (common.1.object)

# 2) buffer
ADD_SUBDIRECTORY (common.2.buffer)

# 3) execute
ADD_SUBDIRECTORY (common.3.execute)

# 4) socket
ADD_SUBDIRECTORY (network.1.socket)

# 5) p2p
ADD_SUBDIRECTORY (network.2.p2p)

# 6) update
ADD_SUBDIRECTORY (network.3.update)

# 7) log
ADD_SUBDIRECTORY (server.1.log)

# 8) group
ADD_SUBDIRECTORY (server.2.group)

# 9) service
ADD_SUBDIRECTORY (server.3.service)

# 10) time_event
ADD_SUBDIRECTORY (server.4.time_event)

# 11) query
ADD_SUBDIRECTORY (server.5.query)

# 12) oauth
ADD_SUBDIRECTORY (server.6.http_api)

# 13) doss
ADD_SUBDIRECTORY (server.7.doss)

# 14) web server
ADD_SUBDIRECTORY (server.8.web_server)

