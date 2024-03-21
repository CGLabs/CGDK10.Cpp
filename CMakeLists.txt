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
# Setting
#-----------------------------------------------------------------------------
# 1) Project name
PROJECT ( "CGDK10" )

# 2) Project version
SET ( PROJECT_VERSION_MAJOR 0 )
SET ( PROJECT_VERSION_MINOR 0 )
SET ( PROJECT_VERSION_PATCH 100 )
SET ( PROJECT_VERSION_TWEAK 1 )
set ( DEFAULT_BULD_TYPE debug )

# 3) build version
CMAKE_MINIMUM_REQUIRED ( VERSION 3.20 )


#-----------------------------------------------------------------------------
# Compile
#-----------------------------------------------------------------------------
# 1) tutorial
ADD_SUBDIRECTORY (tutorials)

# 2) example
ADD_SUBDIRECTORY (examples)
