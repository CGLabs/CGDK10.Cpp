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
// channel::Igroup
//
//-----------------------------------------------------------------------------
class channel::Igroup : public group::preset<user::socket>
{
public:
	virtual ~Igroup() noexcept {}

public:
			eCHANNEL_TYPE		m_type_channel { eCHANNEL_TYPE::NONE };
			eCHANNEL_OPTION		m_option_channel { eCHANNEL_OPTION::NONE };
			CHANNEL_ID			get_channel_id() const noexcept { return this->m_id_channel; }
protected:
			CHANNEL_ID			m_id_channel{ 0 };
			object_ptr<manager> m_pmanager;
			friend class manager;
};
