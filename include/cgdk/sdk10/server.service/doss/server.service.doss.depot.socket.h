//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 9.0 / release 2017.01.03                        *
//*                                                                           *
//*                              Account Classes                              *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
// doss::CAccount
//-----------------------------------------------------------------------------
namespace CGDK
{

class doss::Idepot::socket :
// inherited classes)
	public						net::socket::tcp<>,
	public						Nmessage_transmitter,
	public						Igroupable<socket>
{
// constructor/destructor) 
public:
			socket() noexcept;
	virtual	~socket() noexcept;

// Public) 
public:
	//! @brief [데폿] 정보를 리셋한다.
			void				reset_depot_info() noexcept;
	[[nodiscard]] sSESSION_ID	get_session_id() const noexcept { return m_id_session; }
			bool				send_restoreable(Itransactable* _ptransactable);
			bool				send_restoreable(eTRANSACTION_TYPE _command, const sCHECKIN_ID& _cid, sREQUEST_ID _rid, eRESULT _result, const shared_buffer& _buf_response);
			bool				send_restoreable_control_resquest(eTRANSACTION_TYPE _command, const sCHECKIN_ID& _cid, sREQUEST_ID _rid, eRESULT _result);
			void				process_send_ack(uint64_t _send_sequence) noexcept;
			void				process_receive_ack(uint64_t _receive_sequence) noexcept;

// frameworks) 
private:
	// 1) Socket
	virtual void				on_connect() override;
	virtual void				on_disconnect(uint64_t _Reason) override;

	// 2) Message 처리 함수
	virtual	result_code			on_message(sMESSAGE_NETWORK& _msg) override;

// implementation) 
public:
	// 3) Checkined Account from this socket
			lockable<circular_list<sCHECKIN_ID>> m_list_entity_checkined;

			sREPOSITORY_ID		m_rid_remote;
			sSESSION_ID			m_id_session;
			object_ptr<restore>	m_prestore;

	// 4) send sequence
			lockable<>			m_lockable_send_sequence;
			uint64_t			m_send_sequence = 0;
			uint64_t			m_send_sequence_ack = 0;
			circular_list<shared_buffer> m_send_sequence_buffer;
			std::atomic<uint64_t> m_receive_sequence = 0;
};


}