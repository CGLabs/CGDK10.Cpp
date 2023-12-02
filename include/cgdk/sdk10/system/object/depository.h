//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                              object classes                               *
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
// ----------------------------------------------------------------------------
// 	   
// TOKEN_INDEX for depository
// 
// ----------------------------------------------------------------------------
class TOKEN_INDEX
{
public:
			TOKEN_INDEX() noexcept : sid(), tid() {}
			TOKEN_INDEX(bool) noexcept : sid(), tid(1) {}
			TOKEN_INDEX(const TOKEN_INDEX& _copy) noexcept : sid(_copy.sid), tid(_copy.tid) {}
			TOKEN_INDEX(TOKEN_INDEX&& _move) noexcept : sid(_move.sid), tid(_move.tid) { _move = TOKEN_INDEX(); }
			TOKEN_INDEX(sOBJECT_ID _sid) noexcept : sid(_sid), tid(1) {}
			TOKEN_INDEX(sOBJECT_ID _sid, uint64_t _tid) noexcept : sid(_sid), tid(_tid) {}
			TOKEN_INDEX(uint64_t _id) noexcept : sid(), tid(_id) {}
public:
			sOBJECT_ID			sid;
			uint64_t			tid = 0;
public:
			void				reset() noexcept { this->sid.reset(); this->tid = 0; }
	[[nodiscard]] static TOKEN_INDEX generate() noexcept { return TOKEN_INDEX(sOBJECT_ID(), generate_tid()); }
	[[nodiscard]] static TOKEN_INDEX generate(sOBJECT_ID _sid) noexcept { return TOKEN_INDEX(_sid, generate_tid()); }

	[[nodiscard]] bool			empty() const noexcept { return this->tid == 0; }
	[[nodiscard]] bool			exist() const noexcept { return this->tid != 0; }
public:
			TOKEN_INDEX&		operator= (const TOKEN_INDEX& _rhs) noexcept { this->sid=_rhs.sid; this->tid=_rhs.tid; return (*this); }
			bool				operator==(const TOKEN_INDEX& _rhs) const noexcept { return this->tid==_rhs.tid && this->sid==_rhs.sid; }
			bool				operator!=(const TOKEN_INDEX& _rhs) const noexcept { return !this->operator==(_rhs); }
			bool				operator< (const TOKEN_INDEX& _rhs) const noexcept { return (this->tid<_rhs.tid) ? true : ((this->tid>_rhs.tid) ? false : (this->sid< _rhs.sid)); }
			bool				operator<=(const TOKEN_INDEX& _rhs) const noexcept { return !this->operator> (_rhs); }
			bool				operator> (const TOKEN_INDEX& _rhs) const noexcept { return (this->tid>_rhs.tid) ? true : ((this->tid<_rhs.tid) ? false : (this->sid> _rhs.sid)); }
			bool				operator>=(const TOKEN_INDEX& _rhs) const noexcept { return !this->operator< (_rhs); }
			TOKEN_INDEX			operator++(int) noexcept { auto tid_old = this->tid; this->tid = generate_tid(); return TOKEN_INDEX{sid, tid_old }; }
			TOKEN_INDEX			operator++() noexcept { this->tid = generate_tid(); return *this; }
	[[nodiscard]]				operator bool () const noexcept { return this->exist();}

protected:
	[[nodiscard]] static uint64_t generate_tid() noexcept { static std::atomic<uint64_t> tid(0); uint64_t temp = ++tid; if (temp == 0) temp = ++tid; return temp; }
};


//-----------------------------------------------------------------------------
//
// depository 
//
//-----------------------------------------------------------------------------
template <class TOBJECT, class TKEY = TOKEN_INDEX>
class depository
{
public:
			depository() noexcept : m_key_last(1llu) {}
	virtual	~depository() noexcept {}

// publics)
public:
			TKEY				put(const TOBJECT& _object) { scoped_lock(this->m_map_registery) { return _put_object(_object);}}
			TKEY				put(TOBJECT&& _object) { scoped_lock(this->m_map_registery) { return _put_object(std::forward<TOBJECT>(_object));}}
			void				put(const TOBJECT& _object, const TKEY& _key) { scoped_lock(this->m_map_registery) { _put_object(_object, _key);}}
			void				put(const TOBJECT& _object, TKEY&& _key) { scoped_lock(this->m_map_registery) { _put_object(_object, _key);}}
	[[nodiscard]] TOBJECT		get(const TKEY& _key) noexcept { scoped_lock(this->m_map_registery) { TOBJECT temp; _get_object(_key, temp); return temp;}}
	[[nodiscard]] TOBJECT		get(TKEY&& _key) noexcept { scoped_lock(this->m_map_registery) { TOBJECT temp; _get_object(_key, temp); return temp;}}
	[[nodiscard]] bool			get(const TKEY& _key, TOBJECT& _object) noexcept { scoped_lock(this->m_map_registery) { return _get_object(_key, _object);}}
	[[nodiscard]] bool			get(TKEY&& _key, TOBJECT& _object) noexcept { scoped_lock(this->m_map_registery) { return _get_object(_key, _object);}}
	[[nodiscard]] std::unordered_map<TKEY, TOBJECT> get_all() noexcept
			{
				// declare) 
				std::unordered_map<TKEY, TOBJECT> map_registery;

				scoped_lock(this->m_map_registery)
				{
					// 1) 모든 Request의 on_get를 호출한다.
					for(auto& iter: this->m_map_registery)
					{
						// - get한다.
						on_get(iter.second, iter.first);
					}

					// 2) 클리어한다.
					this->m_map_registery.clear();

					// 3) 이동
					map_registery = std::move(this->m_map_registery);
				}

				// return)
				return	map_registery;
			}
	[[nodiscard]] TOBJECT		peek(const TKEY& _key) const { scoped_lock(this->m_map_registery) { return _peek(_key);}}
	[[nodiscard]] TOBJECT		peek(TKEY&& _key) const { scoped_lock(this->m_map_registery) { return _peek(_key);}}

	[[nodiscard]] size_t		count() const noexcept { scoped_lock(this->m_map_registery) { return static_cast<int>(this->m_map_registery.size()); }}

	[[nodiscard]] lock_object&	get_lockable() noexcept { return this->m_map_registery;}
	[[nodiscard]] const lock_object& get_lockable() const noexcept { return this->m_map_registery;}
	[[nodiscard]] 				operator lock_object&() noexcept { return this->m_map_registery;}
	[[nodiscard]] 				operator const lock_object&() const noexcept { return this->m_map_registery;}

// framework)
protected:
	virtual void				on_register(const TOBJECT& /*_object*/, const TKEY& /*_key*/) {}
	virtual	void				on_get(const TOBJECT& /*_object*/, const TKEY& /*_key*/) {}

public:
			TKEY				_put_object(const TOBJECT& _object)
			{
				// declare) RequestID을 얻는다.
				TKEY key = (this->m_key_last != 0) ? this->m_key_last++ : (++this->m_key_last)++;

				// check)
				CGASSERT_ERROR(key);

				// 1) Insert한다.
				auto result = this->m_map_registery.emplace(key, _object);

				// check) 삽입하지 못했다면 Exception을 던진다.
				THROW_IF(result.second == false, throwable::failure(eRESULT::ALEADY_EXIST));

				// 2) Hook함수 호출
				this->on_register(_object, key);

				// return) 
				return key;
			}
			TKEY				_put_object(TOBJECT&& _object)
			{
				// declare) RequestID을 얻는다.
				TKEY key = (this->m_key_last) ? this->m_key_last++ : (++this->m_key_last)++;

				// 1) Insert한다.
				auto result = this->m_map_registery.emplace(key, std::forward<TOBJECT>(_object));

				// check) 삽입하지 못했다면 Exception을 던진다.
				THROW_IF(result.second == false, throwable::failure(eRESULT::ALEADY_EXIST));

				// 2) Hook함수 호출
				this->on_register(_object, key);

				// return) 
				return key;
			}
			void				_put_object(const TOBJECT& _object, const TKEY& _key)
			{
				// check)
				CGASSERT_ERROR(_key);

				// check) 삽입하지 못했다면 Exception을 던진다.
				THROW_IF(!_key, throwable::failure(eRESULT::INVALID_ARGUMENT));

				// 1) Insert한다.
				auto result = this->m_map_registery.emplace(_key, _object);

				// check) 삽입하지 못했다면 Exception을 던진다.
				THROW_IF(result.second == false, throwable::failure(eRESULT::ALEADY_EXIST));

				// 2) Hook함수 호출
				this->on_register(_object, _key);
			}
			void				_put_object(TOBJECT&& _object, const TKEY& _key)
			{
				// check)
				CGASSERT_ERROR(_key);

				// check) 삽입하지 못했다면 Exception을 던진다.
				THROW_IF(!_key, throwable::failure(eRESULT::INVALID_ARGUMENT));

				// 1) Insert한다.
				auto result = this->m_map_registery.emplace(_key, std::forward<TOBJECT>(_object));

				// check) 삽입하지 못했다면 Exception을 던진다.
				THROW_IF(result.second == false, throwable::failure(eRESULT::ALEADY_EXIST));

				// 2) Hook함수 호출
				this->on_register(_object, _key);
			}
			TOBJECT				_get_object(TKEY _key) noexcept
			{
				// declare) 
				TOBJECT pobject;

				// check)
				RETURN_IF(!_key, pobject);

				// 1) Account ID에 해당하는 Request정보를 얻는다.
				auto iter_find = this->m_map_registery.find(_key);

				// check) 찾지 못했다면 끝낸다.
				RETURN_IF(iter_find == this->m_map_registery.end(), pobject);

				// 2) 찾은 Request의 SocketUser를 저장해 놓는다.
				pobject = std::move(iter_find->second);

				// 3) Hook함수 호출
				this->on_get(pobject, _key);

				// 4) 지운다.
				this->m_map_registery.erase(iter_find);

				// return) 
				return pobject;
			}
			bool				_get_object(const TKEY& _key, TOBJECT& _object) noexcept
			{
				// check)
				RETURN_IF(!_key, false);

				// 1) Object ID에 해당하는 Request정보를 얻는다.
				auto iter_find = this->m_map_registery.find(_key);

				// check) 찾지 못했다면 끝낸다.
				RETURN_IF(iter_find == this->m_map_registery.end(), false);

				// 2) 찾은 Request의 SocketUser를 저장해 놓는다.
				_object = std::move(iter_find->second);

				// 2) Hook함수 호출
				this->on_get(_object, _key);

				// 3) 지운다.
				this->m_map_registery.erase(iter_find);

				// return) 
				return true;
			}
			bool				_get_object_if(const TKEY& _key, const TOBJECT& _compare) noexcept
			{
				// check) 
				RETURN_IF(!_key, false);

				// declare) 
				TOBJECT	pobject;

				// 1) Object ID에 해당하는 Request정보를 얻는다.
				auto iter_find = this->m_map_registery.find(_key);

				// check) 찾지 못했다면 끝낸다.
				RETURN_IF(iter_find == this->m_map_registery.end(), false);

				// check) _compare가 다르면 끝낸다.
				RETURN_IF(_compare != iter_find->second, false);

				// 2) Hook함수 호출
				this->on_get(iter_find->second, _key);

				// 3) 지운다.
				this->m_map_registery.erase(iter_find);

				// return) 
				return true;
			}
	[[nodiscard]] const TOBJECT& _peek(const TKEY& _key) const
			{
				// check) 찾지 못했다면 exception을 던진다.
				THROW_IF(!_key, throwable::failure(eRESULT::INVALID_ARGUMENT));

				// 1) Object ID에 해당하는 Request정보를 얻는다.
				auto iter_find = this->m_map_registery.find(_key);

				// check) 찾지 못했다면 exception을 던진다.
				THROW_IF(iter_find == this->m_map_registery.end(), throwable::failure(eRESULT::NOT_EXIST));

				// return) 
				return iter_find->second;
			}
	[[nodiscard]] bool			_is_exist(const TKEY& _key) const noexcept
			{
				return	this->m_map_registery.find(_key) != this->m_map_registery.end();
			}
	[[nodiscard]] bool			_find_object(const TKEY& _key, TOBJECT& _result) const noexcept
			{
				// check) 
				RETURN_IF(!_key, false);

				// 1) find key
				auto iter_find = this->m_map_registery.find(_key);
				
				// check) not exist -> return false
				RETURN_IF(iter_find == this->m_map_registery.end(), false);

				// 2) set
				_result = iter_find->second;
				
				// return) 
				return true;
			}

public:
			lockable<std::unordered_map<TKEY, TOBJECT>>	m_map_registery;
			TKEY				m_key_last;
};


}

namespace std
{
	template <>
	struct hash<CGDK::TOKEN_INDEX>
	{
		[[nodiscard]] std::size_t operator() (const CGDK::TOKEN_INDEX& _key) const noexcept
		{
			return static_cast<size_t>(_key.tid);
		}
	};
}
