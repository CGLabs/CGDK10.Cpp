#*****************************************************************************
#*                                                                           *
#*                               project GRUMA                               *
#*                                                                           *
#*                               server.field                                *
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
PROJECT ( "CGDK10.example.update_service.service" )

# 2) project version
SET ( PROJECT_VERSION_MAJOR 10 )
SET ( PROJECT_VERSION_MINOR 0 )
SET ( PROJECT_VERSION_PATCH 100 )
SET ( PROJECT_VERSION_TWEAK 1 )
set ( DEFAULT_BUILD_TYPE release )

# 3) build version
CMAKE_MINIMUM_REQUIRED ( VERSION 3.10 )


#-----------------------------------------------------------------------------
# compile
#-----------------------------------------------------------------------------
# 1) session server.console
ADD_SUBDIRECTORY (./console)
