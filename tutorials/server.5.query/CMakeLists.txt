#*****************************************************************************
#*                                                                           *
#*                      Cho sanghyun's Game Classes II                       *
#*                      Ver 10.0 / release 2019.12.11                        *
#*                                                                           *
#*                         CMake - tutorial.query                            *
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
PROJECT ( "CGDK10.tutorial.query" )

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
# 1) rdb_simple
ADD_SUBDIRECTORY (query.01.rdb_simple)

# 2) rdb_parameter
ADD_SUBDIRECTORY (query.02.rdb_parameter)

# 3) rdb_multiple_result
ADD_SUBDIRECTORY (query.03.rdb_multiple_result)

# 4) rdb_alloc_query
ADD_SUBDIRECTORY (query.04.rdb_alloc_query)

# 5) redis
ADD_SUBDIRECTORY (query.05.redis)

# 6) http
ADD_SUBDIRECTORY (query.06.http)

# 7) ex.rdb_blob
ADD_SUBDIRECTORY (query.ex01.rdb_blob)

# 8) ex.rdb_varchar_max
ADD_SUBDIRECTORY (query.ex02.rdb_varchar_max)

# 9) ex.rdb_transaction
ADD_SUBDIRECTORY (query.ex03.rdb_transaction)

# 10) ex.initializing_querier
ADD_SUBDIRECTORY( query.ex05.initializing_querier)

# 11) ex.struct_get_value
ADD_SUBDIRECTORY( query.ex06.query.struct_get_value)
