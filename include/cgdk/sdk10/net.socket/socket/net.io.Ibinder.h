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
// net::io::IBindable
//
// 1. IBindable은~
//    bind를 위한 bind Interface를 가진 Interface Class임.
//
// 2. 주요사용처.
//    1) UDP socket을 위한 binder이다.
//    2) 만약 UDP socket을 특정한 주소와 Port에 bind해야 한다면 이 binder 클래스를
//       상속받아 bind()함수를 사용하여 특정 주소와 포트에 bind할 수 있다.
//    3) binder가 된다면 내부적으로 binder manager에 등록된다. 또 closesocket()
//       되면 binder manager에서 등록해제된다.
//    4) 등록된 binder들은 싱글턴인 net::io::binder::manager 객체를 통해 정보를
//       얻을 수 있다.
//
//-----------------------------------------------------------------------------
class net::io::Ibinder : 
	virtual	public				net::io::Isocket,
	virtual public				Imessageable,
	virtual	public				object::Inameable
{
public:
			Ibinder() noexcept {}
	virtual	~Ibinder() noexcept {}

// public)
public:
	// 1) 추가 bind함수
			bool				bind( const net::sockaddr& _address);
			bool				bind( u_short p_dwPort = 0);

public:
	// 2) bind함수
	virtual	bool				process_request_bind( const net::sockaddr& _address) PURE;

	// 3) reset할때 호출하는 함수.(기본은 빈것...)
	virtual	void				process_reset_binder() PURE;

protected:
			void				register_binder(net::io::statistics::Nsocket* _pstatistics_socket);
			void				unregister_binder() noexcept;

public:
			lockable<>			m_lockable_manager_binder;
			binder::manager*	m_pmanager_binder = nullptr;
};


}
