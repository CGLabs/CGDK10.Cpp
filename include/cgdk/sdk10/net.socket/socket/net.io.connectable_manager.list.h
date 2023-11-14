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

//-----------------------------------------------------------------------------
//
// net::io::connectable_manager
//
// 1. net::io::connectable_manager
//    1) socket�� List�� �����Ͽ� ��� ���ӵ� socket�� �����ϰų� ��ü���� �޽�����
//       �����ϵ��� �� �� �ִ�.
//    2) �� connectable manager�� �Ϲ������� connective::IAccptor�� Iconnective��
//       ������������ �ʿ�� �Ѵ�.
//       acceptor�� �Բ� ���� ��ӹ޾� acceptor�� ���� socket�� connectable manager��
//       ����� �����ϴ� ���� �Ϲ����̴�.
//
// 2. connectable�� �����ϱ� ���� Iterator
//    1) �� connectable manager���� �����ϴ� Iterator�� Iterator�� ��� ����
//       ��ü�� Lock�� �ɸ��� �Ǹ� Iterator�� �Ҹ�ɶ����� Lock�� �����Ѵ�.
//       ���� Iterator�� ��� �۾��� ó���� �� �ִ��� ���� Iterator�� �Ҹ���Ѿ�
//       �Ѵ�.
//
//
//-----------------------------------------------------------------------------
template <class TCONNECTABLE=CGDK::net::io::Iconnectable>
class CGDK::net::io::connectable_manager::list :
// inherited classes)
	virtual	public				Iconnectable_manager
{
// definitions)
public:
		using ITERATOR = typename circular_list<object_ptr<TCONNECTABLE>>::iterator;

// constructor/destructor)
protected:
			list() noexcept	{}
	virtual	~list() noexcept;

// publics) 
public:
	// 1) Connected socket
	virtual	bool				add_connectable(Iconnectable* _pconnectable) noexcept override;
	virtual	bool				remove_connectable(Iconnectable* _pconnectable) noexcept override;
			void				remove_all_connectable() noexcept;
	[[nodiscard]] virtual bool	is_exist_connectable(Iconnectable* _pconnectable) const noexcept override;

	// 2) disconnect All Accepted socket
	virtual	void				disconnect_connectable_all() noexcept override;
	virtual	void				close_connectable_all(uint64_t _flag = 0) noexcept override;

	// 3) send (send�Լ��� ���� ��츸...)
	virtual bool				process_send(shared_buffer&& _buffer, std::size_t _count_message, uint64_t _option) override;

	// 4) connectable ��
	[[nodiscard]] virtual size_t count() const noexcept override;

	// 5) Iterator���
	[[nodiscard]] virtual object_ptr<CONNECTABLE_ITERATOR> alloc_iterator() override { return make_object<CONNECTABLE_ITERATORList>(m_list_connectable.begin(), m_list_connectable.end(), &m_lockable_list_connectable); }

	// 6) Iterator���.
	[[nodiscard]] ITERATOR		begin() { return m_list_connectable.begin();}
	[[nodiscard]] ITERATOR		end() { return m_list_connectable.end();}

	// 7) Lock�� �ɱ� ����...											  
	[[nodiscard]] std::recursive_mutex& get_lockable() noexcept { return this->m_lockable_list_connectable;}
	[[nodiscard]] const std::recursive_mutex& get_lockable() const noexcept { return this->m_lockable_list_connectable;}
	[[nodiscard]] 				operator std::recursive_mutex&() noexcept { return this->m_lockable_list_connectable;}
	[[nodiscard]] 				operator const std::recursive_mutex& () const noexcept { return this->m_lockable_list_connectable; }

	// 8) Lambda executor
	[[nodiscard]] object_ptr<TCONNECTABLE> find_connectable(const std::function<bool (TCONNECTABLE*)>& _pred) noexcept;
			bool				for_each_connectable(const std::function<bool (TCONNECTABLE*)>& _function);

// implementation)
protected:
	// 1) ���� Accept���� socket ����.
			std::recursive_mutex m_lockable_list_connectable;
			circular_list<object_ptr<TCONNECTABLE>>	m_list_connectable;

			void				clear_connectable_list() noexcept;

	// definitions) connectable Iterator
	class CONNECTABLE_ITERATORList : public CONNECTABLE_ITERATOR
	{
	public:
				CONNECTABLE_ITERATORList(ITERATOR _iter_begin, ITERATOR _iter_end, std::recursive_mutex* _cs_lock) : m_lockable_lock(_cs_lock), m_iter_now(_iter_begin), m_iter_begin(_iter_begin), m_iter_end(_iter_end) { m_lockable_lock->lock(); }
				~CONNECTABLE_ITERATORList() noexcept { m_lockable_lock->unlock();}

		virtual	void			reset() override { this->m_iter_now=m_iter_begin;}
		[[nodiscard]] virtual TCONNECTABLE* get_pre() override { return	(this->m_iter_now != m_iter_begin) ? (*this->m_iter_now--).get() : nullptr;}
		[[nodiscard]] virtual TCONNECTABLE* get_next() override { return (this->m_iter_now != m_iter_end) ? (*this->m_iter_now++).get() : nullptr;}

	public:
				std::recursive_mutex* m_lockable_lock;
				ITERATOR		m_iter_now;
				ITERATOR		m_iter_begin;
				ITERATOR		m_iter_end;
	};

	friend	CONNECTABLE_ITERATORList;
};

template <class TCONNECTABLE>
CGDK::net::io::connectable_manager::list<TCONNECTABLE>::~list() noexcept
{
	// check) 
	scoped_lock(this->m_lockable_list_connectable)
	{
		if (this->m_list_connectable.empty() == false)
		{
			LOG_WARNING << "(warn) some sockets are not released. ("sv << this->m_list_connectable.size() << "sockets are remained)"sv;
		}
	}

	// 1) remove all connectable
	remove_all_connectable();
}

template <class TCONNECTABLE>
bool CGDK::net::io::connectable_manager::list<TCONNECTABLE>::add_connectable(Iconnectable* _pconnectable) noexcept
{
	// 1) get connectable pointer
	auto pconnectable = dynamic_cast<TCONNECTABLE*>(_pconnectable);

	// check)
	CGASSERT_ERROR(pconnectable != nullptr);

	// check) 
	RETURN_IF(pconnectable == nullptr, false);

	try
	{
		scoped_lock(this->m_lockable_list_connectable)
		{
			// 1) add connectable to list
			this->m_list_connectable.push_front(pconnectable);

			// check) 
			CGASSERT_ERROR(_pconnectable->m_flexible.get<Iconnectable_manager*>() == nullptr);

			// 2) store pconnectable_manager pointer to flexible storage
			_pconnectable->m_flexible.get<Iconnectable_manager*>() = this;

			// 3) store iterator to flexible storage
		#pragma push_macro("new")
		#undef new
			new (&pconnectable->m_flexible.flexible<32>::get<ITERATOR>(sizeof(Iconnectable_manager*))) typename circular_list<object_ptr<TCONNECTABLE>>::iterator(this->m_list_connectable.begin());
		#pragma pop_macro("new")
		}

		// return)
		return true;
	}
	catch (...)
	{
		// return) 
		return false;
	}
}

template <class TCONNECTABLE>
bool CGDK::net::io::connectable_manager::list<TCONNECTABLE>::remove_connectable(Iconnectable* _pconnectable) noexcept
{
	scoped_lock(this->m_lockable_list_connectable)
	{
		// 1) get connectable manager pointer from flexible storage
		auto pconnectable_manager = _pconnectable->m_flexible.get<Iconnectable_manager*>();

		// check)
		RETURN_IF(pconnectable_manager == nullptr, false);

		// check)
		CGASSERT_ERROR(pconnectable_manager == this);

		// 2) clear flexible storage
		_pconnectable->m_flexible.get<Iconnectable_manager*>() = nullptr;

		// 3) erase connectable from connectable list
		this->m_list_connectable.erase(_pconnectable->m_flexible.get<ITERATOR>(sizeof(Iconnectable_manager*)));
	}

	// return) 
	return true;
}

template <class TCONNECTABLE>
void CGDK::net::io::connectable_manager::list<TCONNECTABLE>::remove_all_connectable() noexcept
{
	clear_connectable_list();
}

template <class TCONNECTABLE>
bool CGDK::net::io::connectable_manager::list<TCONNECTABLE>::is_exist_connectable(Iconnectable* _pconnectable) const noexcept
{
	scoped_lock(this->m_lockable_list_connectable)
	{
		for (auto& iter : this->m_list_connectable)
		{
			if (iter == _pconnectable)
			{
				return true;
			}
		}
	}

	// return)
	return false;
}

template <class TCONNECTABLE>
void CGDK::net::io::connectable_manager::list<TCONNECTABLE>::clear_connectable_list() noexcept
{
	// locked) 
	{
		// scoped_lock)
		std::lock_guard<std::recursive_mutex> cs(this->m_lockable_list_connectable);

		// check)
		RETURN_IF(this->m_list_connectable.empty());

		// 1) clear connectable list
		this->m_list_connectable.clear();
	}
}

template <class TCONNECTABLE>
void CGDK::net::io::connectable_manager::list<TCONNECTABLE>::disconnect_connectable_all() noexcept
{
	// declare)
	std::vector<object_ptr<TCONNECTABLE>> vector_connectable;

	scoped_lock(this->m_lockable_list_connectable)
	{
		// 1) reserve vector
		vector_connectable.reserve(this->m_list_connectable.size());

		// 2) copy connectable
		for (auto& iter : this->m_list_connectable)
		{
			// check)
			CONTINUE_IF(iter.empty());

			// - push_back
			vector_connectable.push_back(iter);
		}
	}

	// 3) disconnect all
	for (auto& iter : vector_connectable)
	{
		iter->disconnect();
	}
}

template <class TCONNECTABLE>
void CGDK::net::io::connectable_manager::list<TCONNECTABLE>::close_connectable_all(uint64_t _flag) noexcept
{
	// declare)
	std::vector<object_ptr<TCONNECTABLE>> vector_connectable;

	auto tick_now = chrono::tick::now();

	scoped_lock(this->m_lockable_list_connectable)
	{
		// 1) reserve vector
		vector_connectable.reserve(this->m_list_connectable.size());

		// 2) copy connectable
		for (auto& iter : this->m_list_connectable)
		{
			// check)
			CGASSERT_ERROR(iter.exist());

			// check)
			CONTINUE_IF(iter.empty());

			// check) 
			if (_flag)
			{
				if (iter->socket_state() == eSOCKET_STATE::CLOSED)
				{
					auto tick_differ = tick_now - iter->statistics_get_tick_disconnect();

					// check) 
					CONTINUE_IF(tick_differ < chrono::seconds(10));
				}
			}

			// - push_back
			vector_connectable.push_back(iter);
		}
	}

	for (auto& iter : vector_connectable)
	{
		// - closesocket
		iter->closesocket();
	}
}

template <class TCONNECTABLE>
bool CGDK::net::io::connectable_manager::list<TCONNECTABLE>::process_send(shared_buffer&& _buffer, std::size_t _count_message, uint64_t _option)
{
#if defined(_MSC_VER)
	// Case) send�Լ��� ���� ���...
	__if_exists(TCONNECTABLE::send)
	{
		scoped_lock(this->m_lockable_list_connectable)
		{
			for(auto& iter: this->m_list_connectable)
			{
				// check)
				CGASSERT_ERROR(iter.exist());

				// check)
				CONTINUE_IF(iter.empty());

				// check)
				CONTINUE_IF(iter->socket_state() < eSOCKET_STATE::ESTABLISHED);

				// - send buffer
				iter->send({ _buffer, _count_message }, _option);
			}
		}
	}

	// Case) send�Լ��� ���� ��츸...
	__if_not_exists(TCONNECTABLE::send)
	{
#endif
		scoped_lock(this->m_lockable_list_connectable)
		{
			for(auto& iter: this->m_list_connectable)
			{
				// check)
				CGASSERT_ERROR(iter.exist());

				// check)
				CONTINUE_IF(iter.empty());

				// check)
				CONTINUE_IF(iter->socket_state() < eSOCKET_STATE::ESTABLISHED);

				// - get sender
				auto psender = dynamic_cast<net::io::Isender*>(iter.get());

				// check) 
				CONTINUE_IF(psender == nullptr);

				// - send buffer
				psender->send({ _buffer, _count_message }, _option);
			}
		}
#if defined(_MSC_VER)
	}
#endif

	// return) 
	return true;
}

template <class TCONNECTABLE>
size_t CGDK::net::io::connectable_manager::list<TCONNECTABLE>::count() const noexcept
{
	// locked) 
	{
		// scoped_lock)
		std::lock_guard<std::recursive_mutex> cs(const_cast<std::recursive_mutex&>(this->m_lockable_list_connectable));

		// return) 
		return this->m_list_connectable.size();
	}
}

template <class TCONNECTABLE>
CGDK::object_ptr<TCONNECTABLE> CGDK::net::io::connectable_manager::list<TCONNECTABLE>::find_connectable(const std::function<bool(TCONNECTABLE*)>& _pred) noexcept
{
	scoped_lock(this->m_lockable_list_connectable)
	{
		for(auto& iter: this->m_list_connectable)
		{
			// 1) Ȯ���Ѵ�.
			bool result = _pred(iter);

			// check) result�� true�� ������ �� ���� �����Ѵ�.
			RETURN_IF(result == true, *iter); 
		}
	}

	// return) ã�� ������ ���� nullptr�� ���ϵȴ�.
	return object_ptr<TCONNECTABLE>();
}

template <class TCONNECTABLE>
bool CGDK::net::io::connectable_manager::list<TCONNECTABLE>::for_each_connectable(const std::function<bool(TCONNECTABLE*)>& _function)
{
	// declare)
	std::vector<object_ptr<TCONNECTABLE>> vector_connectable;

	scoped_lock(this->m_lockable_list_connectable)
	{
		// 1) reserve vector
		vector_connectable.reserve(this->m_list_connectable.size());

		// 2) copy connectable
		for (auto& iter : this->m_list_connectable)
		{
			// check)
			CGASSERT_ERROR(iter.exist());

			// check)
			CONTINUE_IF(iter.empty());

			// - push_back
			vector_connectable.push_back(iter);
		}
	}

	// 3) execute all
	for (auto& iter : vector_connectable)
	{
		// - _function�Լ��� �����Ѵ�.
		bool result = _function(iter);

		// check) 
		RETURN_IF(result == false, false);
	}

	// return) 
	return true;
}
