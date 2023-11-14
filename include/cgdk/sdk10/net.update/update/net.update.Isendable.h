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
// CGDK::update::Isendable
//
//
// ----------------------------------------------------------------------------
class CGDK::update::Isendable :
	virtual public				object::Idestroyable
{
public:
//	// 1) Sending Object를 할당하는 함수.
//	virtual	CGPTR<ICGNetUpdateSending>	AllocUpdateSending(const _CHAR* _strPath) PURE;
//
//	// 2) Attribue
//	virtual	uint32_t			GetAttribute(uint32_t _Mask) const PURE;
//	virtual	const edc::md5&		GetMD5() const PURE;
//
//	// 3) 전송해야할 Bytes수
//			uint32_t			GetSendingBytes() const { return m_bytesSending;}
//			void				SetSendingBytes(uint32_t _bytesSending)	{ m_bytesSending=_bytesSending;}
//
//	// 4) ItemData
//			uintptr_t			GetItemData() const { return m_pItemData;}
//			void				SetItemData(uintptr_t _ItemData) { m_pItemData=_ItemData;}
//
//public:
//			uint32_t			m_bytesSending;
//			uintptr_t			m_pItemData;
};
