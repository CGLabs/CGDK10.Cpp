//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                                  Common                                   *
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

//-----------------------------------------------------------------------------
/**

 @class		object::Iupdatable
 @brief		업데이트 속성의 인터페이스 클래스
 @todo		
 @ref		
 @details	\n

*/
//-----------------------------------------------------------------------------
class CGDK::object::Iupdatable :
// Inherited Classes) 
	virtual public				Ireferenceable
{
// destructor)
public:
	virtual ~Iupdatable() noexcept {}

// public)
public:
			result_code			update() { context _context; return this->process_update(_context); }
			result_code			update(context& _context) { return this->process_update(_context); }

// framework)
public:
	//! @brief 업데이트 과정을 정의한다. @param _pMSG 전달할 인자 @return true 성공 @return false 실패
	virtual	result_code			process_update(context& _context) PURE;
};
