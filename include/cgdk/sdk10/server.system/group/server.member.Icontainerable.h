//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                          Group Template Classes                           *
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

namespace CGDK
{
//-----------------------------------------------------------------------------
/**

 @class		Imember_containerable
 @brief		그룹의 멤버가 되기 위한 인터페이스 클래스이다.
 @todo		
 @ref		
 @details	\n
       
*///-----------------------------------------------------------------------------
template <class _TMEMBERBASE>
class Imember_containerable : virtual public Ireferenceable
{
// public)
public:
	//! @brief 특정 멤버를 찾는다. @param _pred 찾는 조건 함수 @return 찾은 멤버 데이터
	[[nodiscard]] virtual object_ptr<_TMEMBERBASE> find_member(const std::function<bool(_TMEMBERBASE*)>& _pred) PURE;

	//! @brief 모든 멤버에 특정 함수를 실행한다. @param _function 실행하는 함수 @return true 성공 @return false 실패
	virtual	bool				for_each_member(const std::function<bool(_TMEMBERBASE*)>& _function) PURE;

};


}