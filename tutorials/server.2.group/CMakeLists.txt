#*****************************************************************************
#*                                                                           *
#*                      Cho sanghyun's Game Classes II                       *
#*                      Ver 10.0 / release 2019.12.11                        *
#*                                                                           *
#*                          CMake - tutorial.group                           *
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
PROJECT ( "CGDK10.tutorial.group" )

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
# 1) simple
ADD_SUBDIRECTORY (group.01.simple)

# 2) message_mediator
ADD_SUBDIRECTORY (group.02.message_mediator)

# 3) schedulable
ADD_SUBDIRECTORY (group.03.schedulable)

# 4) chatting
ADD_SUBDIRECTORY (group.04.chatting)

# 5) observer.1
ADD_SUBDIRECTORY (group.05.observer.1)

# 5) observer.2
ADD_SUBDIRECTORY (group.06.observer.2)

# 5) ex.group_type
ADD_SUBDIRECTORY (group.ex01.group_type)

# 5) ex.startable
ADD_SUBDIRECTORY (group.ex02.startable)
