//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                          network socket classes                           *
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
/*!
* @class Ireceivable_stream
*
* @ingroup net::io
*
* @brief stream�� ������ I/O�� ���� �����ͼ��� ó���� �����ϴ� Ŭ����
*
*/
//-----------------------------------------------------------------------------
class net::io::Ireceivable_stream :
	virtual public				Ireferenceable
{
public:
	// @brief reset�Ҷ� ȣ���ϴ� �Լ�.(�⺻�� ���...) @return 0 ���� @return !0 ����
	virtual	void				process_reset_receivable() PURE;
	// @brief receive�� prepare�ϴ� �Լ��̴�.(�� �Լ� ���Ŀ� receive�� ����������.) @return 0 ���� @return !0 ����
	//    (���� ó���� �߸��Ǵ� ��� throw�� �Ҽ��� �ִ�.)
	virtual	bool				prepare_receive() PURE;
	// @brief receive�� �޾��� �� ȣ��ȴ�. @return 0 ���� @return !0 ���� @return 0 ���� @return !0 ����
	virtual	intptr_t			process_complete_receivable(intptr_t _result, std::size_t _transferred) PURE;
};


}