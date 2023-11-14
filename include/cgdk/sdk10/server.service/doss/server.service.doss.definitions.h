//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 9.0 / release 2017.01.03                        *
//*                                                                           *
//*                 Distributed Object Storage System Classes                 *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************
#pragma once
//-----------------------------------------------------------------------------
// 1) eTRANSACTION_OPTION
//-----------------------------------------------------------------------------
enum class eTRANSACTION_OPTION : uint64_t
{
	EXCLUSIVE_CHECKIN		  = 0,	// ������ checkin() - �ϳ��� entity�� ���ϳ��� checkin�� ����Ѵ�. ������ checkin�� �����Ѵ�.
	REJECT_IF_ALEADY_EXIST,			// ���� checkin ���� - ������ checkin�� ������ �ű� checkin�� �ź��Ѵ�.
	ALLOW_DUPLICATED_CHECKIN,		// �ߺ� checkin ��� - �ϳ��� entity�� �������� checkin�� ����Ѵ�.(EXCLUSIVE_CHECKIN�� �ݴ��.)
	TRANSFER_CHECKIN				// checkin�� ���� - �̹� checkin�� checkin�� ��ü�Ѵ�. ���� ������ checkin_id�� �̹� �����ؾ� ���ȴ�.
};


//-----------------------------------------------------------------------------
// 2) eTRANSACTION_TYPE
//
//-----------------------------------------------------------------------------
enum class eTRANSACTION_TYPE : uint32_t
{
	NONE					 = 0,	

	CHECKIN					 = 1,
	COMMAND					 = 2,
	UPDATE					 = 3,
	CHECKOUT				 = 4,
	CREATE					 = 5,
	REMOVE					 = 6
};


// ----------------------------------------------------------------------------
// 3) sREPOSITORY_ID
//    - repository�� id��.
//
//      * sOBJECT_ID	id_object;
//        - ������ �����Ǵ� repository�� id�̴�.
//      
//      * uint64_t		key_certify;
//        - repository�� �ʱ�ȭ�� �� ���� �����ϰ� �ο��ִ� ���̴�.
//        - �� ���� ���� Ȯ�ο븸���� ���ȴ�.
//
//      * uint64_t			key_checkin;
//
// ----------------------------------------------------------------------------
struct sREPOSITORY_ID
{
public:
	constexpr sREPOSITORY_ID() noexcept {}
	constexpr sREPOSITORY_ID(sOBJECT_ID _id_object) noexcept : id_object(_id_object) {}
	constexpr sREPOSITORY_ID(const sREPOSITORY_ID&) noexcept = default;
	constexpr sREPOSITORY_ID(sREPOSITORY_ID&&) noexcept = default;

public:
	constexpr bool				exist() const noexcept								{ return id_object.exist(); }
	constexpr bool				empty() const noexcept								{ return id_object.empty(); }
	constexpr bool				valid() const noexcept								{ return exist(); }
	constexpr void				reset() noexcept									{ id_object.reset(); }

	constexpr const auto&		object_id() const noexcept							{ return id_object; }

	static	sREPOSITORY_ID		generate() noexcept									{ return sREPOSITORY_ID{ sOBJECT_ID::generate()}; }

	constexpr sREPOSITORY_ID&	operator = (const sREPOSITORY_ID& _rhs) noexcept = default;
	constexpr sREPOSITORY_ID&	operator = (sREPOSITORY_ID&& _rhs) noexcept = default;
	constexpr 					operator bool () const noexcept						{ return exist();}
	constexpr 					operator sOBJECT_ID() const noexcept				{ return id_object; }
protected:
			sOBJECT_ID			id_object;
};

constexpr bool operator == (const sREPOSITORY_ID& _lhs, const sREPOSITORY_ID& _rhs) noexcept { return  (_lhs.object_id() == _rhs.object_id()); }
constexpr bool operator >  (const sREPOSITORY_ID& _lhs, const sREPOSITORY_ID& _rhs) noexcept { return  (_lhs.object_id() >  _rhs.object_id()); }
constexpr bool operator != (const sREPOSITORY_ID& _lhs, const sREPOSITORY_ID& _rhs) noexcept { return !(_lhs == _rhs); }
constexpr bool operator <  (const sREPOSITORY_ID& _lhs, const sREPOSITORY_ID& _rhs) noexcept { return  (_rhs >  _lhs); }
constexpr bool operator >= (const sREPOSITORY_ID& _lhs, const sREPOSITORY_ID& _rhs) noexcept { return !(_lhs <  _rhs); }
constexpr bool operator <= (const sREPOSITORY_ID& _lhs, const sREPOSITORY_ID& _rhs) noexcept { return !(_lhs >  _rhs); }

constexpr bool operator == (const sREPOSITORY_ID& _lhs, const sOBJECT_ID& _rhs) noexcept { return  (_lhs.object_id() == _rhs); }
constexpr bool operator >  (const sREPOSITORY_ID& _lhs, const sOBJECT_ID& _rhs) noexcept { return  (_lhs.object_id() >  _rhs); }
constexpr bool operator != (const sREPOSITORY_ID& _lhs, const sOBJECT_ID& _rhs) noexcept { return !(_lhs == _rhs); }
constexpr bool operator <  (const sREPOSITORY_ID& _lhs, const sOBJECT_ID& _rhs) noexcept { return  (_rhs > _lhs.object_id()); }
constexpr bool operator >= (const sREPOSITORY_ID& _lhs, const sOBJECT_ID& _rhs) noexcept { return !(_lhs < _rhs); }
constexpr bool operator <= (const sREPOSITORY_ID& _lhs, const sOBJECT_ID& _rhs) noexcept { return !(_lhs > _rhs); }


// ----------------------------------------------------------------------------
// 4) sENTITY_ID
//	  - ��ü�� �ο��Ǵ� ���� ID�� ���� �Һ��� ���� ID�̴�.
//
// ----------------------------------------------------------------------------
struct sENTITY_ID
{
public:
	constexpr sENTITY_ID() noexcept {}
	constexpr sENTITY_ID(sREPOSITORY_ID _id_repository, sOBJECT_ID _id_object) noexcept : id_repository(_id_repository), id_object(_id_object) {}
	constexpr sENTITY_ID(sOBJECT_ID _id_object) noexcept : id_repository(), id_object(_id_object) {}
	constexpr sENTITY_ID(const sENTITY_ID&) noexcept = default;
	constexpr sENTITY_ID(sENTITY_ID&&) noexcept = default;

public:
	constexpr bool				exist() const noexcept { return id_repository.exist() && id_object.exist(); }
	constexpr bool				empty() const noexcept { return !exist();}
	constexpr bool				valid() const noexcept { return exist();}
	constexpr void				reset() noexcept { id_repository.reset(); id_object.reset();}

	constexpr const auto&		repository_id() const noexcept { return id_repository; }
	constexpr const auto&		object_id() const noexcept { return id_object; }

	constexpr sENTITY_ID&		operator = (const sENTITY_ID& _rhs) noexcept { id_repository = _rhs.repository_id(); id_object = _rhs.object_id(); return *this; }
	constexpr sENTITY_ID&		operator = (sENTITY_ID&& _rhs) noexcept { id_repository = _rhs.repository_id(); id_object = _rhs.object_id(); _rhs.reset(); return *this; }
	constexpr sENTITY_ID&		operator = (const sREPOSITORY_ID& _rhs) noexcept { id_repository = _rhs; return *this; }
	constexpr sENTITY_ID&		operator = (sREPOSITORY_ID&& _rhs) noexcept { id_repository = std::move(_rhs); return *this; }
	constexpr sENTITY_ID&		operator = (const sOBJECT_ID& _rhs) noexcept { id_object = _rhs; return *this; }
	constexpr sENTITY_ID&		operator = (sOBJECT_ID&& _rhs) noexcept { id_object = std::move(_rhs); return *this; }
	constexpr sENTITY_ID&		operator = (uint64_t _rhs) noexcept { id_object = _rhs; return *this; }
	constexpr 					operator bool () const noexcept { return exist();}
	constexpr 					operator sOBJECT_ID() const noexcept { return id_object;}

protected:
			sREPOSITORY_ID		id_repository;
			sOBJECT_ID			id_object;
};

constexpr sENTITY_ID make_entity_id(sREPOSITORY_ID _id_repository, sOBJECT_ID _id_object) noexcept { return sENTITY_ID{ _id_repository, _id_object }; }
constexpr sENTITY_ID make_entity_id(sOBJECT_ID _id_repository, sOBJECT_ID _id_object) noexcept { return sENTITY_ID{ sREPOSITORY_ID{ _id_repository }, _id_object }; }


constexpr bool operator == (const sENTITY_ID& _lhs, const sENTITY_ID& _rhs) noexcept { return (_lhs.repository_id() == _rhs.repository_id()) && (_lhs.object_id() == _rhs.object_id()); }
constexpr bool operator >  (const sENTITY_ID& _lhs, const sENTITY_ID& _rhs) noexcept
{
	if (_lhs.repository_id() > _rhs.repository_id())
		return true;
	else if (_lhs.repository_id() < _rhs.repository_id())
		return false;
	else
		return _lhs.object_id() > _rhs.object_id();
}
constexpr bool operator != (const sENTITY_ID& _lhs, const sENTITY_ID& _rhs) noexcept { return !(_lhs == _rhs); }
constexpr bool operator <  (const sENTITY_ID& _lhs, const sENTITY_ID& _rhs) noexcept { return  (_rhs >  _lhs); }
constexpr bool operator >= (const sENTITY_ID& _lhs, const sENTITY_ID& _rhs) noexcept { return !(_lhs <  _rhs); }
constexpr bool operator <= (const sENTITY_ID& _lhs, const sENTITY_ID& _rhs) noexcept { return !(_lhs >  _rhs); }


// ----------------------------------------------------------------------------
// 5) sSESSION_ID
//    - session�� id�� session�� ������ �� �����ȴ�.
//
//      * sOBJECT_ID		id_host;
//        - host_id�� id�̴�. ������ �� �Ҵ�ȴ�.
//      
//      * sOBJECT_ID		id_object;
//        - ������ �� �Ҵ�Ǵ� id�̴�.
//
// ----------------------------------------------------------------------------
struct sSESSION_ID
{
public:
	constexpr sSESSION_ID() noexcept = default;
	constexpr sSESSION_ID(sOBJECT_ID _id_host) noexcept : id_host(_id_host) {}
	constexpr sSESSION_ID(sOBJECT_ID _id_host, sOBJECT_ID _id_object) noexcept : id_host(_id_host), id_object(_id_object) {}
	constexpr sSESSION_ID(const sSESSION_ID&) noexcept = default;
	constexpr sSESSION_ID(sSESSION_ID&&) noexcept = default;

public:
			sOBJECT_ID			id_host {1llu};
			sOBJECT_ID			id_object;
public:
	constexpr bool				exist() const noexcept { return id_host.exist() && id_object.exist(); }
	constexpr bool				empty() const noexcept { return !exist(); }
	constexpr bool				valid() const noexcept { return exist();}
	constexpr void				reset() noexcept { id_host.reset(); id_object.reset(); }

	constexpr const auto&		host_id() const noexcept { return id_host; }
	constexpr const auto&		object_id() const noexcept { return id_object; }
	constexpr					operator bool () const noexcept { return exist();}

public:
	constexpr sSESSION_ID&		operator = (const sSESSION_ID& _rhs) noexcept = default;
	constexpr sSESSION_ID&		operator = (sSESSION_ID&& _rhs) noexcept = default;

public:
	static	sSESSION_ID			generate() noexcept { return sSESSION_ID{ sOBJECT_ID{1llu}, sOBJECT_ID::generate() }; }

};

constexpr bool operator == (const sSESSION_ID& _lhs, const sSESSION_ID& _rhs) noexcept
{
	return _lhs.host_id() == _rhs.host_id()
		&& _lhs.object_id() == _rhs.object_id();
}
constexpr bool operator >  (const sSESSION_ID& _lhs, const sSESSION_ID& _rhs) noexcept
{
	if (_lhs.host_id() > _rhs.host_id())
		return true;
	else if (_lhs.host_id() < _rhs.host_id())
		return false;
	else
		return _lhs.object_id() > _rhs.object_id();
}
constexpr bool operator != (const sSESSION_ID& _lhs, const sSESSION_ID& _rhs) noexcept { return !(_lhs == _rhs); }
constexpr bool operator <  (const sSESSION_ID& _lhs, const sSESSION_ID& _rhs) noexcept { return  (_rhs >  _lhs); }
constexpr bool operator >= (const sSESSION_ID& _lhs, const sSESSION_ID& _rhs) noexcept { return !(_lhs <  _rhs); }
constexpr bool operator <= (const sSESSION_ID& _lhs, const sSESSION_ID& _rhs) noexcept { return !(_lhs >  _rhs); }


// ----------------------------------------------------------------------------
// 6) sCHECKIN_ID
//    - checkin�� ������ �־����� ID�� �ǹ��Ѵ�.
//
//      * sENTITY_ID		id_entity;
//        - entity�� ���� ID�̴�. �� ���� ������ ������ ���� ������.
//		  - repository_id�� object_id�� �����ȴ�.
//      
//      * sOBJECT_ID		id_session;
//        - checkin�� ��û�� session�� id�̴�.
//		  - host�� ���� id
//
//      * uint64_t			key_checkin;
//        - checkin�� ������ �ο��Ǵ� randon�� Ű�̴�.
//        - �̰��� Check-in�� ������ �������� ����ȴ�.
//
// ----------------------------------------------------------------------------
struct sCHECKIN_ID
{
public:
			sENTITY_ID			id_entity;
			sSESSION_ID			id_session;
			sOBJECT_ID			id_object;
			uint64_t			key_certify = 0;
public:
	constexpr bool				exist() const noexcept { return id_entity.exist() && id_session.exist() && id_object.exist() && (key_certify != 0); }
	constexpr bool				empty() const noexcept { return !exist(); }
	constexpr bool				valid() const noexcept { return exist();}
	constexpr void				reset() noexcept { id_entity.reset(); id_session.reset(); id_object.reset(); key_certify = 0;}

	constexpr const auto&		entity_id() const noexcept { return id_entity; }
	constexpr const auto&		session_id() const noexcept { return id_session; }
	constexpr const auto&		object_id() const noexcept { return id_object; }
	constexpr const auto&		certify_id() const noexcept { return key_certify; }

	constexpr sCHECKIN_ID&		operator = (const sENTITY_ID& _rhs) noexcept { id_entity = _rhs; return *this; }
	constexpr sCHECKIN_ID&		operator = (sENTITY_ID&& _rhs) noexcept { id_entity = std::move(_rhs); return *this; }
	constexpr sCHECKIN_ID&		operator = (const sSESSION_ID& _rhs) noexcept { id_session = _rhs; return *this; }
	constexpr sCHECKIN_ID&		operator = (sSESSION_ID&& _rhs) noexcept { id_session = std::move(_rhs); return *this; }
	constexpr sCHECKIN_ID&		operator = (const sOBJECT_ID& _rhs) noexcept { id_object = _rhs; return *this; }
	constexpr sCHECKIN_ID&		operator = (sOBJECT_ID&& _rhs) noexcept { id_object = std::move(_rhs); return *this; }
	constexpr sCHECKIN_ID&		operator = (uint64_t _rhs) noexcept { key_certify = _rhs; return *this; }
	constexpr 					operator bool () const noexcept { return exist();}
};

constexpr bool operator == (const sCHECKIN_ID& _lhs, const sCHECKIN_ID& _rhs) noexcept
{
	return _lhs.id_object == _rhs.id_object
		&& _lhs.id_session == _rhs.id_session
		&& _lhs.id_entity == _rhs.id_entity
		&& _lhs.key_certify == _rhs.key_certify;
}
constexpr bool operator >  (const sCHECKIN_ID& _lhs, const sCHECKIN_ID& _rhs) noexcept
{
	if (_lhs.entity_id() > _rhs.entity_id())
		return true;
	else if (_lhs.entity_id() < _rhs.entity_id())
		return false;
	else if (_lhs.session_id() > _rhs.session_id())
		return true;
	else if (_lhs.session_id() < _rhs.session_id())
		return false;
	else if (_lhs.object_id() > _rhs.object_id())
		return true;
	else if (_lhs.object_id() < _rhs.object_id())
		return false;
	else
		return _lhs.certify_id() > _rhs.certify_id();
}
constexpr bool operator != (const sCHECKIN_ID& _lhs, const sCHECKIN_ID& _rhs) noexcept { return !(_lhs == _rhs); }
constexpr bool operator <  (const sCHECKIN_ID& _lhs, const sCHECKIN_ID& _rhs) noexcept { return  (_rhs >  _lhs); }
constexpr bool operator >= (const sCHECKIN_ID& _lhs, const sCHECKIN_ID& _rhs) noexcept { return !(_lhs <  _rhs); }
constexpr bool operator <= (const sCHECKIN_ID& _lhs, const sCHECKIN_ID& _rhs) noexcept { return !(_lhs >  _rhs); }



// ----------------------------------------------------------------------------
// 7) sREQUEST_ID
//
//    ��û�� ������ �� ���Ǵ� ID
//    ��û ID��
//    
//    1. ��û�� �� ���� ��Ÿ���� sSESSION_ID
//    2. ��û �Ϸ� ��ȣ�� �ǹ��ϴ� index_request (REQUEST_UNIQUE_SERIAL)
//
//    �� �����Ͽ� �����Ѵ�.
//
//   index_request��  1���� ���������� ������Ű�� �߱��� ID�̹Ƿ�
//    �ٸ� ������ ������ sREQUEST_ID��  ���� �޾��� ��� index_request�����δ� �ߺ��� �� �ִ�.
//   
//   ���� ���� ���� index_request�� ���� ���� ���� �ǹ��ϴ� sSESSION_ID�� �����Ͽ� ���� ID�̴�.
//   �Ϲ������� ���� Remote���� ���� ���� index_request�� �����Ͽ� ����� �� ���δ�.
// ----------------------------------------------------------------------------
class sREQUEST_ID
{
public:
	constexpr sREQUEST_ID() noexcept : id_session(), index_request() {}
	constexpr sREQUEST_ID(bool) noexcept : id_session(), index_request(1) {}
	constexpr sREQUEST_ID(sSESSION_ID _id_session) noexcept : id_session(_id_session), index_request(1) {}
	constexpr sREQUEST_ID(sSESSION_ID _id_session, uint64_t _index_request) noexcept : id_session(_id_session), index_request(_index_request) {}
	constexpr sREQUEST_ID(uint64_t _id) noexcept : id_session(), index_request(_id) {}
	constexpr sREQUEST_ID(const sREQUEST_ID&) noexcept = default;
	constexpr sREQUEST_ID(sREQUEST_ID&&) noexcept = default;

public:
	[[nodiscard]]constexpr bool	exist() const noexcept { return id_session.exist() && (index_request != 0); }
	[[nodiscard]]constexpr bool	empty() const noexcept { return !exist(); }
	[[nodiscard]]constexpr bool	valid() const noexcept { return exist();}
	constexpr void				reset() noexcept { id_session.reset(); index_request = 0; }

	[[nodiscard]] constexpr const auto& session_id() const noexcept { return id_session; }
	[[nodiscard]] constexpr const auto&	request_index() const noexcept { return index_request; }

	constexpr sREQUEST_ID&		operator= (const sREQUEST_ID& _rhs) noexcept { id_session = _rhs.id_session; index_request = _rhs.index_request; return *this; }
	constexpr sREQUEST_ID&		operator= (sREQUEST_ID&& _rhs) noexcept { id_session = std::move(_rhs.id_session); index_request = _rhs.index_request; _rhs.index_request = 0; return *this; }
	constexpr sREQUEST_ID&		operator= (const sSESSION_ID& _rhs) noexcept { id_session = _rhs; return *this; }
	constexpr sREQUEST_ID&		operator= (sSESSION_ID&& _rhs) noexcept { id_session = std::move(_rhs); return *this; }
	constexpr sREQUEST_ID&		operator= (uint64_t _rhs) noexcept { index_request = _rhs; return *this; }
			sREQUEST_ID			operator++(int) noexcept { sREQUEST_ID temp = *this; index_request = generate_tid(); return temp; }
			sREQUEST_ID&		operator++() noexcept { index_request = generate_tid(); return *this; }
	[[nodiscard]]				operator bool () const noexcept { return exist();}

	[[nodiscard]] static sREQUEST_ID generate() noexcept { return sREQUEST_ID(sSESSION_ID(), generate_tid()); }
	[[nodiscard]] static sREQUEST_ID generate(const sSESSION_ID& _id_session) noexcept { return sREQUEST_ID(_id_session, generate_tid()); }

protected:
			sSESSION_ID			id_session;
			uint64_t			index_request = 0;

	[[nodiscard]] static uint64_t generate_tid() noexcept { static std::atomic<uint64_t> index_request(0); uint64_t temp = ++index_request; if (temp == 0) temp = ++index_request; return temp; }
};
[[nodiscard]] constexpr bool operator == (const sREQUEST_ID& _lhs, const sREQUEST_ID& _rhs) noexcept { return _lhs.request_index() == _rhs.request_index() && _lhs.session_id() == _rhs.session_id(); }
[[nodiscard]] constexpr bool operator >  (const sREQUEST_ID& _lhs, const sREQUEST_ID& _rhs) noexcept
{
	if (_lhs.session_id() > _rhs.session_id())
		return true;
	else if (_lhs.session_id() < _rhs.session_id())
		return false;
	else
		return _lhs.request_index() > _rhs.request_index();
}
[[nodiscard]] constexpr bool operator != (const sREQUEST_ID& _lhs, const sREQUEST_ID& _rhs) noexcept { return !(_lhs == _rhs); }
[[nodiscard]] constexpr bool operator <  (const sREQUEST_ID& _lhs, const sREQUEST_ID& _rhs) noexcept { return  (_rhs >  _lhs); }
[[nodiscard]] constexpr bool operator >= (const sREQUEST_ID& _lhs, const sREQUEST_ID& _rhs) noexcept { return !(_lhs <  _rhs); }
[[nodiscard]] constexpr bool operator <= (const sREQUEST_ID& _lhs, const sREQUEST_ID& _rhs) noexcept { return !(_lhs >  _rhs); }

// ----------------------------------------------------------------------------
// 8) sREQUEST_ID
// ----------------------------------------------------------------------------
namespace CGDK
{
	[[nodiscard]] inline bool DOSS_SUCCESS(result_code _result)
	{
		return _result < result_code(eRESULT::FAIL);
	}

	[[nodiscard]] inline bool DOSS_FAILED(result_code _result)
	{
		return !DOSS_SUCCESS(_result);
	}
}

#if !defined(__ANDROID__)
//namespace std 
//{
//
//template <>
//struct hash<sREPOSITORY_ID>
//{
//	std::size_t operator()(const sREPOSITORY_ID& _Key) const noexcept
//	{
//		return	static_cast<size_t>(static_cast<uint64_t>(_Key.id_object));
//	}
//};
//
//template <>
//struct hash<sENTITY_ID>
//{
//	std::size_t operator()(const sENTITY_ID& _Key) const noexcept
//	{
//		return	static_cast<size_t>(static_cast<uint64_t>(_Key.id_object));
//	}
//};
//
//template <>
//struct hash<sCHECKIN_ID>
//{
//	std::size_t operator()(const sCHECKIN_ID& _Key) const noexcept
//	{
//		return	static_cast<size_t>(static_cast<uint64_t>(_Key.key_checkin));
//	}
//};
//
//template <>
//struct hash<sDEVICE_ID>
//{
//	std::size_t operator()(const sDEVICE_ID& _Key) const noexcept
//	{
//		size_t	value	 = 0;
//
//		const _CHAR_DID* iter	 = static_cast<const _CHAR_DID*>(_Key.id);
//		const _CHAR_DID* iterEnd = _Key.id+256;
//		for(; iter<iterEnd && *iter!=_CHAR_DID('\0'); ++iter)
//		{
//			value	+= *iter;
//		}
//
//		return	value;
//	}
//};

//}
#endif
