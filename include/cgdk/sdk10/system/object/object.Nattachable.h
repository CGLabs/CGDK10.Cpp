//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                                  Common                                   *
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
/**

 @class		object::Nattachable


*/
//-----------------------------------------------------------------------------
template <typename TTYPE, typename TCON>
class CGDK::object::Nattachable : virtual public Iattachable<TTYPE>
{
public:
	[[nodiscard]] bool			is_attached_empty() const noexcept { return this->m_container.empty();}
	[[nodiscard]] bool			is_attached_exist() const noexcept { return !this->m_container.empty();}
	[[nodiscard]] size_t		attached_size() const noexcept { return this->m_container.size();}

	[[nodiscard]] object_ptr<TTYPE>	find_attachable(TTYPE* _child) noexcept;

			int					clear() noexcept;

public:
	virtual	bool				process_attach(object_ptr<TTYPE>&& _child) override;
	virtual	bool				process_detach(TTYPE* _child) noexcept override;

public:
			TCON				m_container;

public:
			using TCONTAINER = TCON;
};

template <typename TTYPE, typename TCON>
bool CGDK::object::Nattachable<TTYPE, TCON>::process_attach(object_ptr<TTYPE>&& _child)
{
	// check) nullptr이면 안됀다.
	CGASSERT_ERROR(_child.exist());

	// check) _child가 nullptr이면 안됀다.
	RETURN_IF(_child.empty(), false);

	// 1) 이미 존재하는지 찾는다.
	auto iter_find = std::find(this->m_container.begin(), this->m_container.end(), _child);

	// check) 이미 존재하면 그냥 ASSERT 발생!
	CGASSERT_ERROR(iter_find == this->m_container.end());

	// check) 이미 존재하면 그냥 false를 리턴한다.
	RETURN_IF(iter_find != this->m_container.end(), false);

	// 2) 추가하기
	this->m_container.emplace_back(std::move(_child));

	// return) 
	return true;
}

template <typename TTYPE, typename TCON>
bool CGDK::object::Nattachable<TTYPE, TCON>::process_detach(TTYPE* _child) noexcept
{
	// check) No nullptr!
	if(_child == nullptr)
	{
		return this->clear() != 0;
	}

	// check) No Self!
	CGASSERT_ERROR(_child != dynamic_cast<TTYPE*>(this));

	// 1) Check aleady exists
	auto iter_find = std::find(this->m_container.begin(), this->m_container.end(), _child);

	// check) find?
	RETURN_IF(iter_find == this->m_container.end(), false);

	// 2) Delete found item
	this->m_container.erase(iter_find);

	// return) 
	return true;
}

template <typename TTYPE, typename TCON>
CGDK::object_ptr<TTYPE> CGDK::object::Nattachable<TTYPE, TCON>::find_attachable(TTYPE* _child) noexcept
{
	// 1) 먼저 찾는다.
	auto iter_find = std::find(this->m_container.begin(), this->m_container.end(), _child);

	// check) 
	RETURN_IF(iter_find == this->m_container.end(), object_ptr<TTYPE>());

	// return) 
	return (*iter_find);
}

template <typename TTYPE, typename TCON>
int CGDK::object::Nattachable<TTYPE, TCON>::clear() noexcept
{
	// declare) 
	std::vector<object_ptr<TTYPE>> vec_temp;

	// 1) m_container에 복사
	vec_temp.assign(this->m_container.begin(), this->m_container.end());

	// declare)
	const int count = static_cast<int>(vec_temp.size());

	// 2) 모두 detach
	for(auto& iter:vec_temp)
	{
		this->process_detach(iter);
	}

	// return) 
	return count;
}