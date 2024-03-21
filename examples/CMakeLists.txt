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
PROJECT ( "CGDK10.example" )

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
# 1) tcp_echo
ADD_SUBDIRECTORY (1.1.tcp_echo)
ADD_SUBDIRECTORY (1.2.tcp_relay_echo)
ADD_SUBDIRECTORY (1.3.tcp_multicast_echo)
#ADD_SUBDIRECTORY (1.4.tcp_echo_ex)
#ADD_SUBDIRECTORY (1.5.udp_echo)

# 2) 1.chatting_simple
ADD_SUBDIRECTORY (2.1.chatting_simple)
#ADD_SUBDIRECTORY (2.2.chatting_scaleout)
#ADD_SUBDIRECTORY (2.3.chatting)

# 3) channel_system
#ADD_SUBDIRECTORY (3.1.channel_system_1)
#ADD_SUBDIRECTORY (3.2.channel_system_2)

# 4) game_simple_server
#ADD_SUBDIRECTORY (4.1.game_simple_server_1)
#ADD_SUBDIRECTORY (4.2.game_simple_server_2)
#ADD_SUBDIRECTORY (4.3.game_login_system)
#ADD_SUBDIRECTORY (4.4.game_scalable_server_system)

# 5) game_server_system
#ADD_SUBDIRECTORY (5.1.game_match_making_server_system)
#ADD_SUBDIRECTORY (5.2.game_friend_system)
#ADD_SUBDIRECTORY (5.3.game_mail_system_1)
#ADD_SUBDIRECTORY (5.6.game_shop_system)

# 6) game_mmo_field_system
#ADD_SUBDIRECTORY (6.1.game_mmo_field_1)
#ADD_SUBDIRECTORY (6.2.game_mmo_field_2)
#ADD_SUBDIRECTORY (6.3.game_quest_system)
#ADD_SUBDIRECTORY (6.4.game_instance_dungeon)
#ADD_SUBDIRECTORY (6.5.game_trade_server_system)

# 7) update_service
#ADD_SUBDIRECTORY (7.1.update_service)

