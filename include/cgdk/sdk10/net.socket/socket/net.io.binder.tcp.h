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
//
// net::io::binder::Ntcp
// 
// 1. binder은~
//    1) TCP를 위한 bind() 기능이 있는 함수로 TCP를 위해 제작된 클래스이다.
//    2) TCP의 경우 Accept를 위해 bind를 수행하는데 이를 위한 클래스이다.
//    3) Accept를 하지 않더라도 클라이언트 TCP 소켓의 경우 BInd를 하고자 할 때가
//       있다 이때 사용할 수 있다.
//    4) TCP용 connector 객체는 기본적으로 BInder를 상속받아 제작된다.
//    5) bind시 주소에 0으로  설정하면 하드웨어의 모든 주소에 bind되며 포트를 0으로
//       하면 임의의 빈 포트를 자동적으로 선택하여 bind된다.
//    6) 특정한 주소와 포트에 바인드를 할 때는 되도록 1000이상의 포트를 사용하는
//       것이 좋다. 왜냐하면 그 이하의 포트는 예약된 포트가 많기 때문이다.
//
//-----------------------------------------------------------------------------
class net::io::binder::Ntcp :
// inherited classes)
	virtual public				net::io::Isocket,
	virtual public				net::io::Ibinder,
	virtual public				net::io::statistics::Nsocket
{
// publics)
public:
	virtual	bool				process_request_bind(const net::sockaddr& _address) override;
	virtual	void				process_reset_binder() override {}
};


}