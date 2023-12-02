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
 @brief		�׷��� ����� �Ǳ� ���� �������̽� Ŭ�����̴�.
 @todo		
 @ref		
 @details	\n
       
*///-----------------------------------------------------------------------------
template <class _TMEMBERBASE>
class Imember_containerable : virtual public Ireferenceable
{
// public)
public:
	//! @brief Ư�� ����� ã�´�. @param _pred ã�� ���� �Լ� @return ã�� ��� ������
	[[nodiscard]] virtual object_ptr<_TMEMBERBASE> find_member(const std::function<bool(_TMEMBERBASE*)>& _pred) PURE;

	//! @brief ��� ����� Ư�� �Լ��� �����Ѵ�. @param _function �����ϴ� �Լ� @return true ���� @return false ����
	virtual	bool				for_each_member(const std::function<bool(_TMEMBERBASE*)>& _function) PURE;

};


}