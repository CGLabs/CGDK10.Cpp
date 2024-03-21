#*****************************************************************************
#*                                                                           *
#*                      Cho sanghyun's Game Classes II                       *
#*                      Ver 10.0 / release 2019.12.11                        *
#*                                                                           *
#*                          CMake - tutorial.object                          *
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
PROJECT ( "CGDK10.tutorial.object" )

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
# 1) pointer
ADD_SUBDIRECTORY (object.01.pointer)

# 2) contexts
ADD_SUBDIRECTORY (object.02.contexts)

# 3) object_interfaces 1
ADD_SUBDIRECTORY (object.03.object_interfaces.1)

# 4) object_interfaces 2
ADD_SUBDIRECTORY (object.04.object_interfaces.2)

# 5) object_interfaces 3
ADD_SUBDIRECTORY (object.05.object_interfaces.3)

# 6) file_io
ADD_SUBDIRECTORY (object.ex01.file_io)

# 7) endcoding_decoding
ADD_SUBDIRECTORY (object.ex02.endcoding_decoding)
