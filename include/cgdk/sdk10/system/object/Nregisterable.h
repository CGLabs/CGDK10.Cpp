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
//-----------------------------------------------------------------------------
/**

 @class		Nregisterable

*/
//-----------------------------------------------------------------------------
template <typename TTYPE, typename TCON=std::vector<object_ptr<TTYPE>>>
class Nregisterable : virtual public Iregisterable<TTYPE>
{
public:
	virtual	~Nregisterable() noexcept {}

public:
	[[nodiscard]] bool			empty() const noexcept { return this->m_container.empty();}
	[[nodiscard]] bool			exist() const noexcept { return !this->m_container.empty();}

	[[nodiscard]] object_ptr<TTYPE> find(TTYPE* _psource) noexcept;
	void						for_each(const std::function<void(TTYPE* _psource)>& _function);
	int							clear() noexcept;

	[[nodiscard]] auto			begin() noexcept { return this->m_container.begin();}
	[[nodiscard]] auto			end() noexcept { return this->m_container.end();}
	[[nodiscard]] auto			rbegin() noexcept { return this->m_container.rbegin();}
	[[nodiscard]] auto			rend() noexcept { return this->m_container.rend();}
	[[nodiscard]] size_t		size() const noexcept { return this->m_container.size();}

public:
	virtual	bool				process_register(TTYPE* _psource);
	virtual	bool				process_unregister(TTYPE* _psource) noexcept;

protected:
			TCON				m_container;

public:
			using TCONTAINER = TCON;
};


template <typename TTYPE, typename TCON>
bool Nregisterable<TTYPE, TCON>::process_register(TTYPE* _psource)
{
	// check) nullptr이면 안됀다.
	CGASSERT_ERROR(_psource != nullptr);

	// check) 
	RETURN_IF(_psource == nullptr, false);

	// check) 자기 자신이면 안됀다!
	CGASSERT_ERROR(_psource != static_cast<TTYPE*>(this));

	// check) 자기 자신이면 안됀다!
	RETURN_IF(_psource == static_cast<TTYPE*>(this), false);

	// 1) 이미 존재하는지 찾는다.
	auto iter_find = std::find(this->m_container.begin(), this->m_container.end(), _psource);

	// check) 이미 존재하면 그냥 ASSERT 발생!
	CGASSERT_ERROR(iter_find == this->m_container.end());

	// check) 이미 존재하면 그냥 false를 리턴한다.
	RETURN_IF(iter_find != this->m_container.end(), false);

	// 2) 추가하기
	this->m_container.emplace_back(_psource);

	// return) 성공!!
	return true;
}

template <typename TTYPE, typename TCON>
bool Nregisterable<TTYPE, TCON>::process_unregister(TTYPE* _psource) noexcept
{
	// check) nullptr이면 안됀다.
	CGASSERT_ERROR(_psource != nullptr);

	// check) 
	RETURN_IF(_psource == nullptr, false);

	// check) 자기 자신이면 안됀다!
	CGASSERT_ERROR(_psource != static_cast<TTYPE*>(this));

	// check) 자기 자신이면 안됀다!
	RETURN_IF(_psource == static_cast<TTYPE*>(this), false);

	// 1) 이미 존재하는지 확인한다.
	auto iter_find = std::find(this->m_container.begin(), this->m_container.end(), _psource);

	// check) 찾지 못했다!
	RETURN_IF(iter_find == this->m_container.end(), false);

	// 2) 찾은 객체를 지운다.
	this->m_container.erase(iter_find);

	// return) 실패!!
	return true;
}

template <typename TTYPE, typename TCON>
object_ptr<TTYPE> Nregisterable<TTYPE, TCON>::find(TTYPE* _psource) noexcept
{
	// 1) 먼저 찾는다.
	auto iter_find = std::find(this->m_container.begin(), this->m_container.end(), _psource);

	// check) 
	RETURN_IF(iter_find == this->m_container.end(), object_ptr<TTYPE>());

	// return)
	return	(*iter_find);
}

template <typename TTYPE, typename TCON>
void Nregisterable<TTYPE, TCON>::for_each(const std::function<void(TTYPE* _psource)>& _function)
{
	for(auto& iter:this->m_container)
	{
		// - Renderer를 추가한다.
		_function(iter);
	}
}

template <typename TTYPE, typename TCON>
int Nregisterable<TTYPE, TCON>::clear() noexcept
{
	// declare) 
	std::vector<object_ptr<TTYPE>> vec_temp;

	// 1) m_container에 복사
	vec_temp.assign(this->m_container.begin(), this->m_container.end());

	// 2) 갯수를 구한다.
	int	count = vec_temp.size();

	// 3) 모두 detach
	for(auto& iter:vec_temp)
	{
		this->process_detach(iter);
	}

	// return)
	return count;
}


}