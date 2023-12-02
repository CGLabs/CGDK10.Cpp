//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 9.0 / release 2017.01.03                        *
//*                                                                           *
//*                        Server System MFC Controls                         *
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
namespace CGDK
{

template <class TENTITY, class TCREATE>
doss::repository::remote<TENTITY, TCREATE>::remote() :
	doss::Nrepository<TENTITY>(),
	Nmessage_transmitter(),
	net::io::connect_requestable::Ntcp_reconnect(),
	net::socket::tcp<>()
{
	// 1) object type
	object::Iidentifiable::set_object_type(eOBJECT_TYPE::REPOSITORY_REMOTE);

	// 2) rid를 설정한다.
	this->Irepository::m_id_repository = sREPOSITORY_ID::generate();

	// 3) register repository
	doss::manager_repository::get_instance()->register_repository(this);

	// 4) set send option
	this->maximum_send_buffer_size(32768);
}

template <class TENTITY, class TCREATE>
doss::repository::remote<TENTITY, TCREATE>::remote(const std::string_view _name) :
	doss::Nrepository<TENTITY>(),
	Nmessage_transmitter(),
	net::io::connect_requestable::Ntcp_reconnect(_name),
	net::socket::tcp<>()
{
	// 1) object type
	object::Iidentifiable::set_object_type(eOBJECT_TYPE::REPOSITORY_REMOTE);

	// 2) rid를 설정한다.
	this->Irepository::m_id_repository = sREPOSITORY_ID::generate();

	// 3) register repository
	doss::manager_repository::get_instance()->register_repository(this);

	// 4) set send option
	this->maximum_send_buffer_size(32768);
}

template <class TENTITY, class TCREATE>
doss::repository::remote<TENTITY, TCREATE>::~remote() noexcept
{
	// 1) Unregister Repository
	doss::manager_repository::get_instance()->unregister_repository(this);
}

template <class TENTITY, class TCREATE>
void doss::repository::remote<TENTITY, TCREATE>::on_initializing(context& /*_context*/)
{
	// 1) sREPOSITORY_ID를 새로 할당받는다.
	Irepository::m_id_repository = sREPOSITORY_ID::generate();
}

template <class TENTITY, class TCREATE>
void doss::repository::remote<TENTITY, TCREATE>::on_initialize(context& /*_context*/)
{
}

template <class TENTITY, class TCREATE>
void doss::repository::remote<TENTITY, TCREATE>::on_destroying()
{
	// 1) checkout all entity
	this->checkout_all();
}

template <class TENTITY, class TCREATE>
void doss::repository::remote<TENTITY, TCREATE>::on_destroy()
{
	// 1) sREPOSITORY_ID를 Reset한다.
	this->Irepository::m_id_repository.reset();
}

// 2) Start/Stop
template <class TENTITY, class TCREATE>
void doss::repository::remote<TENTITY, TCREATE>::on_starting(context& /*_context*/)
{
	// log)
	LOG_PROGRESS << "@ <BEGIN> start doss REPOSITYR_REMOTE['" << name() << "']";

	// 1) enable reconnect
	this->enable_reconnect();

	// 2) set reconnect retrying invterval (5scoends)
	this->set_reconnect_interval(chrono::seconds(5));

	// 3) set execute interval (10seconds)
	this->execute_interval(chrono::seconds(10));

	// 4) register schedulable
	system_executor::register_schedulable(this);
}

template <class TENTITY, class TCREATE>
void doss::repository::remote<TENTITY, TCREATE>::on_start(context& /*_context*/)
{
	// 1) unregister schedulable
	system_executor::unregister_schedulable(this);

	// log) 
	LOG_PROGRESS << "@ <END> start doss REPOSITORY_REMOTE['" << name() << "']";
}

template <class TENTITY, class TCREATE>
void doss::repository::remote<TENTITY, TCREATE>::on_stop_request()
{
	// - set eOBJECT_STATE::RUNNING if state is 'eOBJECT_STATE::ESTABLISHED'
	set_object_state_if(eOBJECT_STATE::ESTABLISHED, eOBJECT_STATE::RUNNING);
}

template <class TENTITY, class TCREATE>
void doss::repository::remote<TENTITY, TCREATE>::on_stopping()
{
	// log)
	LOG_PROGRESS << "@ <BEGIN> stop doss REPOSITORY_REMOTE['" << name() << "']";

	// 1) disable reconnect
	this->disable_reconnect();
}

template <class TENTITY, class TCREATE>
void doss::repository::remote<TENTITY, TCREATE>::on_stop()
{
	// log)
	LOG_PROGRESS << "@ <END> stop doss REPOSITORY_REMOTE['" << name() << "']";
}

template <class TENTITY, class TCREATE>
void doss::repository::remote<TENTITY, TCREATE>::on_request_connect(const net::sockaddr& _address)
{
	// log)
	LOG_INFO << " > doss REPOSITORY_REMOTE['" << name() << "']: retry connecting to '" << to_string<char>(_address) << "' ";
}

template <class TENTITY, class TCREATE>
void doss::repository::remote<TENTITY, TCREATE>::on_connect()
{
	// log)
	LOG_INFO << " > doss REPOSITORY_REMOTE['" << name() << "']: socket connected (" << remote_endpoint().address().to_string<char>() << ")";
	LOG_INFO << "     rid : " << this->m_id_repository.object_id().value;
	LOG_INFO << "     remote rid : " << this->m_id_repository.object_id().value;

	// 1) Certify를 요청하는 메시지를 전송한다.
	this->send(message_SERVER_DOSS_REQUEST_CERTIFY(this->m_id_repository, this->m_id_repository_remote_alloc, this->m_receive_sequence));
}

template <class TENTITY, class TCREATE>
void doss::repository::remote<TENTITY, TCREATE>::on_fail_connect(uint64_t /*_reason*/)
{
	// log)
	LOG_INFO << " < doss REPOSITORY_REMOTE['" << name() << "']: fail to connect";
}

template <class TENTITY, class TCREATE>
void doss::repository::remote<TENTITY, TCREATE>::on_disconnect(uint64_t /*_reason*/)
{
	// log)
	LOG_INFO << " < doss REPOSITORY_REMOTE['" << name() << "']: socket disconnected (" << remote_endpoint().address().to_string<char>() << ")";
}

template <class TENTITY, class TCREATE>
void doss::repository::remote<TENTITY, TCREATE>::on_execute()
{
}

template <class TENTITY, class TCREATE>
BEGIN_CGMESSAGE_MAP_TEMPLATE(doss::repository::remote, TENTITY, TCREATE)
	CGMESSAGE_TYPE_SUB_BUFFER_NETWORK
		ON_CGMESSAGE(eMESSAGE::SERVER::DOSS::RESPONSE_CERTIFY,	on_message_SERVER_DOSS_RESPONSE_CERTIFY, sMESSAGE_NETWORK)
		ON_CGMESSAGE(eMESSAGE::SERVER::DOSS::COMMAND_RESPONSE,	on_message_SERVER_DOSS_COMMAND_RESPONSE, sMESSAGE_NETWORK)
		ON_CGMESSAGE(eMESSAGE::SERVER::DOSS::CONTROL_REQUEST,	on_message_SERVER_DOSS_CONTROL_REQUEST, sMESSAGE_NETWORK)
		ON_CGMESSAGE(eMESSAGE::SERVER::DOSS::SEND_ACK,			on_message_SERVER_DOSS_SEND_ACK,		sMESSAGE_NETWORK)
	END_SUB_CGMESSAGE_MAP
END_CGMESSAGE_MAP

template <class TENTITY, class TCREATE>
result_code doss::repository::remote<TENTITY, TCREATE>::on_message(sMESSAGE_NETWORK& _msg)
{
	// 1) Message Map
	EXECUTE_CGMESSAGE_MAP(_msg);

	// return) 
	return eRESULT::BYPASS;
}

template <class TENTITY, class TCREATE>
result_code doss::repository::remote<TENTITY, TCREATE>::on_message_SERVER_DOSS_RESPONSE_CERTIFY(sMESSAGE_NETWORK& _msg)
{
	// declare) 
	const uint32_t MESSAGE_SIZE = 8 + sizeof(sREPOSITORY_ID);

	// check) 메시지 길이를 확인한다.
	CGASSERT_ERROR(_msg.buf_message.size() > MESSAGE_SIZE);

	// check) 메시지 길이를 확인한다.
	THROW_IF(_msg.buf_message.size() <= MESSAGE_SIZE, throwable::failure(eRESULT::INVALID_MESSAGE_LENGTH, 0, std::string_view("received Message size is invalid")), LOG_ERROR << "(err ) invalid message size [value:" << _msg.buf_message.size() << ", Requried:" << MESSAGE_SIZE << "]");

	// 1) 
	auto buf_recv = _msg.buf_message + offset(8);

	// 2) remote repository id를 얻는다.
	auto& rid_remote_alloc = buf_recv.extract<sREPOSITORY_ID>();
	auto vec_rid_remote = buf_recv.extract<std::vector<sREPOSITORY_ID>>();
	/*auto receive_sequence_ack =*/ buf_recv.extract<uint64_t>();

	// log)
	LOG_INFO << " > doss REPOSITORY_REMOTE['" << name() << "']: remote repository CERTIFIED!! (" << remote_endpoint().address().to_string<char>() << ")";

	// 3) reset repository
	process_reset_repository(rid_remote_alloc, std::move(vec_rid_remote));

	// 4-1) 새로 RID를 전송했을 경우 Reset처리한다.
	if (rid_remote_alloc.exist())
	{
		// log) 
		LOG_INFO << "     initialize doss ACCOUNT_INFO[remote rid : " << rid_remote_alloc.object_id().value << "]' ";

		// - state ...
		this->set_object_state(eOBJECT_STATE::ESTABLISHED);

		// - notify one 
		this->m_cv_complete.notify_one();
	}
	// 4-2) RID를 empty를 전송해 왔을 경우 기존 복구한다.
	else
	{
		// log) 
		LOG_INFO << "     recover doss ACCOUNT_INFO : " << Irepository::m_id_repository.object_id().value;
	}

	// return) 
	return	1;
}

template <class TENTITY, class TCREATE>
result_code doss::repository::remote<TENTITY, TCREATE>::on_message_SERVER_DOSS_COMMAND_RESPONSE(sMESSAGE_NETWORK& _msg)
{
	// 1) Buffer를 얻는다. 
	auto buf_temp = _msg.buf_message + offset(8);

	// 2) 값들을 읽어온다.
	auto recv_seq = buf_temp.extract<uint64_t>();
	[[maybe_unused]] auto type = buf_temp.extract<eTRANSACTION_TYPE>();
	auto cid = buf_temp.extract<sCHECKIN_ID>();
	[[maybe_unused]] auto rid = buf_temp.extract<sREQUEST_ID>();
	auto result = buf_temp.extract<eRESULT>();
	auto buf_result = buf_temp.extract<shared_buffer>();

	// 3) 
	auto pentity = this->find_entity(cid.id_entity);

	// check) 
	RETURN_IF(pentity.empty(), eRESULT::DONE);

	// declare)
	object_ptr<Itransactable> ptransactable;

	try
	{
		// 4) queue transactioin
		scoped_lock(pentity->m_lockable_queue_transaction)
		{
			// check) 
			CGASSERT_ERROR(pentity->m_queue_command.empty() == false);

			// check)
			THROW_IF(pentity->m_queue_command.empty(), throwable::failure(eRESULT::NOT_EXIST));

			// - get transaction object
			ptransactable = pentity->m_queue_command.front();

			// check) 
			CGASSERT_ERROR(ptransactable->m_rid == rid);
		}

		// check) 
		CGASSERT_ERROR(ptransactable->m_type == type);

		// check) 
		CGASSERT_ERROR(ptransactable->m_cid.id_entity == ptransactable->m_pentity->m_eid);

		// 5) set cid
		ptransactable->m_cid = cid;

		// 6) completion
		ptransactable->complete_transaction(result, buf_result);
	}
	catch (...)
	{
	}

	// 7) process recv ack
	process_receive_ack(recv_seq);

	// return) 
	return eRESULT::DONE;
}

template <class TENTITY, class TCREATE>
result_code doss::repository::remote<TENTITY, TCREATE>::on_message_SERVER_DOSS_CONTROL_REQUEST(sMESSAGE_NETWORK& _msg)
{
	// 1) Buffer를 얻는다. 
	auto buf_temp = _msg.buf_message + offset(8);

	// 2) 값들을 읽어온다.
	auto recv_seq = buf_temp.extract<uint64_t>();
	auto command = buf_temp.extract<eTRANSACTION_TYPE>();
	auto cid = buf_temp.extract<sCHECKIN_ID>();
	/*auto rid =*/ buf_temp.extract<sREQUEST_ID>();
	/*auto result =*/ buf_temp.extract<eRESULT>();

	// 3) get entity
	auto pentity = this->find_entity(cid.id_entity);

	// check) 
	RETURN_IF(pentity.empty(), eRESULT::DONE);

	switch (command)
	{
	case	eTRANSACTION_TYPE::CHECKIN:
			break;

	case	eTRANSACTION_TYPE::COMMAND:
			break;

	case	eTRANSACTION_TYPE::UPDATE:
			break;

	case	eTRANSACTION_TYPE::CHECKOUT:
			scoped_lock(this->m_lockable_map_entity)
			{
				//  - remove cid
				pentity->process_remove_cid(cid);

				// statistics) 
				++this->m_statistics.m_statistics_checkout_forcible;
			}
			break;

	case	eTRANSACTION_TYPE::CREATE:
			break;

	case	eTRANSACTION_TYPE::REMOVE:
			break;

	default:
			break;
	}

	// 4) process recv ack
	this->process_receive_ack(recv_seq);

	// return) 
	return eRESULT::DONE;
}

template <class TENTITY, class TCREATE>
result_code doss::repository::remote<TENTITY, TCREATE>::on_message_SERVER_DOSS_SEND_ACK(sMESSAGE_NETWORK& _msg)
{
	// 1) ...
	auto buf_temp = _msg.buf_message + offset(8);

	// 2) ...
	auto send_seq = buf_temp.extract<uint64_t>();

	// 3) set...
	this->process_send_ack(send_seq);

	// return) 
	return eRESULT::DONE;
}

template <class TENTITY, class TCREATE>
object_ptr<TENTITY> doss::repository::remote<TENTITY, TCREATE>::process_alloc_entity(sENTITY_ID _entity_id)
{
	// check)
	THROW_IF(this->m_id_repository.empty(), throwable::failure(eRESULT::NOT_READY));

	// 1) alloc entity object
	auto pentity = make_object<TCREATE>();

	// 2) set entity_id 
	pentity->m_eid = _entity_id;

	// return)
	return pentity;
}

template <class TENTITY, class TCREATE>
void doss::repository::remote<TENTITY, TCREATE>::process_reset_repository(const sREPOSITORY_ID& _id_repository_remote, std::vector<sREPOSITORY_ID>&& _vec_repository)
{
	// 1) sREPOSITORY_ID를 설정한다
	this->m_id_repository_remote_alloc = _id_repository_remote;
	this->m_vector_id_repository_remote = std::move(_vec_repository);

	// 2) 모든 Checkin정보 Reset!
	scoped_lock(this->m_lockable_map_entity)
	{
		// - Clear한다.
		this->m_map_entity_by_eid.clear();
	}
}


template <class TENTITY, class TCREATE>
result_code doss::repository::remote<TENTITY, TCREATE>::process_request_transaction(Itransactable* _ptransactable)
{
	// check) 
	CGASSERT_ERROR(_ptransactable->m_prepository.exist());
	CGASSERT_ERROR(_ptransactable->m_pentity.exist());
	CGASSERT_ERROR(_ptransactable->m_psession.exist());

	// declare)
	result_code	result = eRESULT::NOT_DEFINED;

	// 1) 상태를 eRESULT::REQUEST로 변경한다.
	_ptransactable->m_result = eRESULT::REQUEST;

	// 2) call process_entity_transaction_request of session object
	if (_ptransactable->m_psession.exist())
	{
		_ptransactable->m_psession->process_entity_transaction_request(_ptransactable);
	}

	// 3) call m_f_request fuction if m_f_request is not nullptr
	if (_ptransactable->m_f_request != nullptr)
	{
		// m_f_request를 호출한다. (여기서 실패시 바로 실패)
		result = _ptransactable->m_f_request(_ptransactable);

		// check) 여기서 Pending이어서는 안됀다.
		CGASSERT_ERROR(result != eRESULT::PENDED);

		// check) SUCCESS가 아닐 경우는 Exception을 던진다.(여기서는 PENDING도 해서는 안됀다.
		RETURN_IF(result != eRESULT::SUCCESS, eRESULT::INVALID_STATE);
	}

	try
	{
		// check) 
		THROW_IF(this->get_object_state() != eOBJECT_STATE::ESTABLISHED, throwable::failure(eRESULT::NOT_READY));

		// check) 
		THROW_IF(this->m_id_repository.empty(), throwable::failure(eRESULT::NOT_READY));

		// declare) 
		result = eRESULT::PENDED;

		// 1) command별 처리
		switch (_ptransactable->m_type)
		{
		// process_complete_transaction_checkin
		case	eTRANSACTION_TYPE::CHECKIN:
				{
					// statistics) 
					++this->Irepository::m_statistics.m_statistics_checkin_request;

					// !주의) 만약 cid가 동일하다면 m_psession->process_entity_transaction_request에서 cid가 empty가 되어 온다.

					// check) 이미 동일한 cid로 checkin이 이미 되어 있다면 이것은 취소
					THROW_IF(_ptransactable->m_cid.id_entity.empty(), throwable::failure(eRESULT::ALEADY_DONE));

					// - send request message remote repository
					auto is_sended = this->process_send_restoreable(_ptransactable);

					// check) throw exception if failed
					THROW_IF(is_sended == false, throwable::failure(eRESULT::FAIL));
				}
				break;

		// process_complete_transaction_command
		case	eTRANSACTION_TYPE::COMMAND:
				{
					// statistics)
					++this->Irepository::m_statistics.m_statistics_command_request;

					// check) 이미 동일한 cid로 checkin이 이미 되어 있다면 이것은 취소
					THROW_IF(_ptransactable->m_cid.empty(), throwable::failure(eRESULT::NOT_READY));

					// - send request message remote repository
					auto is_sended = this->process_send_restoreable(_ptransactable);

					// check) throw exception if failed
					THROW_IF(is_sended == false, throwable::failure(eRESULT::FAIL));
				}
				break;

		// process_complete_transaction_update
		case	eTRANSACTION_TYPE::UPDATE:
				{
					// statistics)
					++this->Irepository::m_statistics.m_statistics_update_request;

					// check) 이미 동일한 cid로 checkin이 이미 되어 있다면 이것은 취소
					THROW_IF(_ptransactable->m_cid.empty(), throwable::failure(eRESULT::NOT_READY));

					// - send request message remote repository
					auto is_sended = this->process_send_restoreable(_ptransactable);

					// check) throw exception if failed
					THROW_IF(is_sended == false, throwable::failure(eRESULT::FAIL));
				}
				break;

		// process_complete_transaction_checkout
		case	eTRANSACTION_TYPE::CHECKOUT:
				{
					// statistics)
					++this->Irepository::m_statistics.m_statistics_checkout_request;

					// - copy pentity value temporary
					auto* pentity = _ptransactable->m_pentity.get();

					// check)
					CGASSERT_ERROR(pentity != nullptr);

					// check) return if pentity is nullptr
					THROW_IF(pentity == nullptr, throwable::failure(eRESULT::NOT_EXIST));

					scoped_lock(this->m_lockable_map_entity)
					{
						// - remove cid 
						auto is_success = pentity->process_remove_cid(_ptransactable->m_psession);

						// check) ...
						THROW_IF(is_success == false, throwable::failure(eRESULT::NOT_EXIST));
					}

					// - set result
					THROW_IF(_ptransactable->m_cid.empty(), throwable::failure(eRESULT::NOT_READY));

					// check) 
					CGASSERT_ERROR(_ptransactable->m_cid.id_entity == _ptransactable->m_pentity->m_eid);

					// - set result  as success
					result = eRESULT::SUCCESS;
					_ptransactable->set_result(result);

					// - request checkout
					this->process_send_restoreable(_ptransactable);
				}
				break;

		// process_complete_transaction_create
		case	eTRANSACTION_TYPE::CREATE:
				{
					// statistics)
					++this->Irepository::m_statistics.m_statistics_create_request;

					// - send request message remote repository
					auto is_sended = this->process_send_restoreable(_ptransactable);

					// check) throw exception if failed
					THROW_IF(is_sended == false, throwable::failure(eRESULT::FAIL));
				}
				break;

		// process_complete_transaction_remove
		case	eTRANSACTION_TYPE::REMOVE:
				{
					// statistics)
					++this->Irepository::m_statistics.m_statistics_remove_request;

					// - send request message remote repository
					auto is_sended = this->process_send_restoreable(_ptransactable);

					// check) throw exception if failed
					THROW_IF(is_sended == false, throwable::failure(eRESULT::FAIL));
				}
				break;

		// default) 
		default:
				CGASSERT_ERROR(false);
				throw throwable::failure(eRESULT::INVALID_ARGUMENT);
				break;
		}
	}
	catch (throwable::failure & _e)
	{
		// - set result
		result = _e.reason();
		_ptransactable->set_result(result);
	}
	catch (...)
	{
		// - set result
		result = eRESULT::EXCEPTION;
		_ptransactable->set_result(result);
	}

	// return)
	return	result;
}

template <class TENTITY, class TCREATE>
void doss::repository::remote<TENTITY, TCREATE>::process_fail_transaction(Itransactable* _ptransactable) noexcept
{
	// 1) process command
	switch (_ptransactable->m_type)
	{
	// process_complete_transaction_checkin
	case	eTRANSACTION_TYPE::CHECKIN:
			{
				this->process_send_restoreable_COMMAND_FAIL(_ptransactable);
			}
			break;

	// process_complete_transaction_command
	case	eTRANSACTION_TYPE::COMMAND:
			break;

	// process_complete_transaction_update
	case	eTRANSACTION_TYPE::UPDATE:
			break;

	// process_complete_transaction_checkout
	case	eTRANSACTION_TYPE::CHECKOUT:
			break;

	// process_complete_transaction_create
	case	eTRANSACTION_TYPE::CREATE:
			break;

	default:
			CGASSERT_ERROR(false);
	}
}

template <class TENTITY, class TCREATE>
bool doss::repository::remote<TENTITY, TCREATE>::process_send_restoreable(Itransactable* _ptransactable)
{
	// locked) 
	{
		// scoped_lock) 
		std::lock_guard<lockable<>> cs(this->m_lockable_send_sequence);

		// 1) generate send_sequence
		uint64_t send_sequence = ++this->m_send_sequence;

		// 2) send
		return this->send(message_SERVER_DOSS_COMMAND_REQUEST(send_sequence, _ptransactable));
	}
}

template <class TENTITY, class TCREATE>
bool doss::repository::remote<TENTITY, TCREATE>::process_send_restoreable_COMMAND_FAIL(Itransactable* _ptransactable)
{
	// locked) 
	{
		// scoped_lock) 
		std::lock_guard<lockable<>> cs(this->m_lockable_send_sequence);

		// 1) generate send_sequence
		uint64_t send_sequence = ++this->m_send_sequence;

		// 2) send
		return this->send(message_SERVER_DOSS_COMMAND_FAIL(send_sequence, _ptransactable));
	}
}

template <class TENTITY, class TCREATE>
void doss::repository::remote<TENTITY, TCREATE>::process_send_ack(uint64_t _send_sequence) noexcept
{
	// locked)
	{
		// scoped_lock) 
		std::lock_guard<lockable<>> cs(this->m_lockable_send_sequence);

		// check)
		CGASSERT_ERROR(this->m_send_sequence >= _send_sequence);

		// check)
		CGASSERT_ERROR(this->m_send_sequence_ack < _send_sequence);

		// 1) update send_sequence
		this->m_send_sequence_ack = _send_sequence;

		// 2) popup ack
		//this->m_send_sequence_buffer.pop_front();
	}
}

template <class TENTITY, class TCREATE>
void doss::repository::remote<TENTITY, TCREATE>::process_receive_ack(uint64_t _receive_sequence) noexcept
{
	// check)
	CGASSERT_ERROR(this->m_receive_sequence < _receive_sequence);

	// 1) update send_sequence
	this->m_receive_sequence = _receive_sequence;

	// 2) send ack
	this->send(message_SERVER_DOSS_SEND_ACK(_receive_sequence));
}


}