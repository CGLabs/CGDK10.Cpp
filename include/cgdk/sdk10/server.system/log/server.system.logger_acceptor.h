//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                            Server Log Classes                             *
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
// C_logAcceptor
//
// 1. C_logAcceptor은~
//    소켓으로 원격 연결을 하여 로그 메시지를 원격 전달하기 위한 체계로
//    접속을 받는 서버쪽 소켓 Log 객체다.
//    접속이 연결되면 전달되어온 메시지를 연결된 Log 객체에 전달한다.
//
//-----------------------------------------------------------------------------
class logger_acceptor : 
	virtual public				Ilogger,
	public						net::io::connective::acceptor::Ntcp
{
public:
			struct INITIALIZE_PARAMETER
			{
				std::string_view address;
			};

			logger_acceptor();
			logger_acceptor(const std::string_view _name);
	virtual ~logger_acceptor() noexcept;

			result_code			initialize(const INITIALIZE_PARAMETER& _initialize_param);
			result_code			initialize(const std::string_view _address);
	virtual	result_code			initialize(context& _context) override { return this->object::Ninitializable::initialize(_context); }

	virtual	void				disconnect_connectable_all() noexcept override;
	virtual	void				close_connectable_all(uint64_t _flag = 0) noexcept override;

	[[nodiscard]] virtual size_t count() const noexcept override;
	
protected:
	virtual	void				process_log(const std::vector<object_ptr<LOG_RECORD>>& _vector_log_record) override;

	virtual	result_code			_process_initializing(context& _context) override;
	virtual	result_code			_process_destroying() noexcept;

	virtual	object_ptr<net::io::Iconnectable> process_alloc_connectable() override;

	virtual	bool				add_connectable(net::io::Iconnectable* _pconnectable) noexcept override;
	virtual	bool				remove_connectable(net::io::Iconnectable* _pconnectable) noexcept override;

	virtual	object_ptr<net::io::Iconnectable_manager::CONNECTABLE_ITERATOR>	alloc_iterator() override;

public:
			class socket;

protected:
			own_ptr<net::socket::tcp_client_reconnect<>> m_psocket_log;
};


}