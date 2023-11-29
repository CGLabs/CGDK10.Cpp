//*****************************************************************************
//*                                                                           *
//*                     CGCII simple chatting system (1)                      *
//*                                                                           *
//*                             chatting Server                               *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                 ¨Ï 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// user::manager
//
//-----------------------------------------------------------------------------
class user::manager :
	public						object::Ninitializable_startable,
	public						object::Nnameable
{
public:
			void				register_user (socket* _psocket);
			void				unregister_user	(socket* _psocket) noexcept;

protected:
			lockable<std::unordered_map<ACCOUNT_ID, object_ptr<socket>>> m_container_user;
};
