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
* @brief stream용 저수준 I/O를 통해 데이터수신 처리를 정의하는 클래스
*
*/
//-----------------------------------------------------------------------------
class net::io::Ireceivable_stream :
	virtual public				Ireferenceable
{
public:
	// @brief reset할때 호출하는 함수.(기본은 빈것...) @return 0 성공 @return !0 실패
	virtual	void				process_reset_receivable() PURE;
	// @brief receive를 prepare하는 함수이다.(이 함수 이후에 receive가 가능해진다.) @return 0 성공 @return !0 실패
	//    (만약 처리중 잘못되는 경우 throw를 할수도 있다.)
	virtual	bool				prepare_receive() PURE;
	// @brief receive를 받았을 때 호출된다. @return 0 성공 @return !0 실패 @return 0 성공 @return !0 실패
	virtual	intptr_t			process_complete_receivable(intptr_t _result, std::size_t _transferred) PURE;
};


}