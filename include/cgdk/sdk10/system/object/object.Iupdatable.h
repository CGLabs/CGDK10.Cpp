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
 @brief		������Ʈ �Ӽ��� �������̽� Ŭ����
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
	//! @brief ������Ʈ ������ �����Ѵ�. @param _pMSG ������ ���� @return true ���� @return false ����
	virtual	result_code			process_update(context& _context) PURE;
};
