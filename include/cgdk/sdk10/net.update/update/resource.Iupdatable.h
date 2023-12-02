//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                          network update classes                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                (c) 2003. Cho Sanghyun. All right reserved.                *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
// ----------------------------------------------------------------------------
//
// resource::updatable::folder
//
//
// ----------------------------------------------------------------------------
class CGDK::resource::Iupdatable :
	virtual public				CGDK::Iresource,
	virtual public				object::Iinitializable
{
public:
			using INITIALIZE_PARAMETER = sINITIALIZE_INFO_UPDATABLE_RESOURCE;
public:

	virtual shared_buffer		get_block(uint64_t _pos) PURE;
	virtual const sUPDATABLE_FILE_COMPLETION_INFO& get_meta_completion() { return this->m_meta_completion; }
	const auto&					_get_meta_info() const noexcept { return this->m_meta_info; }

protected: 
			lockable<>			m_cs_info;
			sUPDATABLE_FILE_META_INFO m_meta_info;
			sUPDATABLE_FILE_COMPLETION_INFO m_meta_completion;
};