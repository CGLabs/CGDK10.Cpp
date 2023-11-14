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
	// check) nullptr�̸� �ȉ´�.
	CGASSERT_ERROR(_psource != nullptr);

	// check) 
	RETURN_IF(_psource == nullptr, false);

	// check) �ڱ� �ڽ��̸� �ȉ´�!
	CGASSERT_ERROR(_psource != static_cast<TTYPE*>(this));

	// check) �ڱ� �ڽ��̸� �ȉ´�!
	RETURN_IF(_psource == static_cast<TTYPE*>(this), false);

	// 1) �̹� �����ϴ��� ã�´�.
	auto iter_find = std::find(this->m_container.begin(), this->m_container.end(), _psource);

	// check) �̹� �����ϸ� �׳� ASSERT �߻�!
	CGASSERT_ERROR(iter_find == this->m_container.end());

	// check) �̹� �����ϸ� �׳� false�� �����Ѵ�.
	RETURN_IF(iter_find != this->m_container.end(), false);

	// 2) �߰��ϱ�
	this->m_container.emplace_back(_psource);

	// return) ����!!
	return true;
}

template <typename TTYPE, typename TCON>
bool Nregisterable<TTYPE, TCON>::process_unregister(TTYPE* _psource) noexcept
{
	// check) nullptr�̸� �ȉ´�.
	CGASSERT_ERROR(_psource != nullptr);

	// check) 
	RETURN_IF(_psource == nullptr, false);

	// check) �ڱ� �ڽ��̸� �ȉ´�!
	CGASSERT_ERROR(_psource != static_cast<TTYPE*>(this));

	// check) �ڱ� �ڽ��̸� �ȉ´�!
	RETURN_IF(_psource == static_cast<TTYPE*>(this), false);

	// 1) �̹� �����ϴ��� Ȯ���Ѵ�.
	auto iter_find = std::find(this->m_container.begin(), this->m_container.end(), _psource);

	// check) ã�� ���ߴ�!
	RETURN_IF(iter_find == this->m_container.end(), false);

	// 2) ã�� ��ü�� �����.
	this->m_container.erase(iter_find);

	// return) ����!!
	return true;
}

template <typename TTYPE, typename TCON>
object_ptr<TTYPE> Nregisterable<TTYPE, TCON>::find(TTYPE* _psource) noexcept
{
	// 1) ���� ã�´�.
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
		// - Renderer�� �߰��Ѵ�.
		_function(iter);
	}
}

template <typename TTYPE, typename TCON>
int Nregisterable<TTYPE, TCON>::clear() noexcept
{
	// declare) 
	std::vector<object_ptr<TTYPE>> vec_temp;

	// 1) m_container�� ����
	vec_temp.assign(this->m_container.begin(), this->m_container.end());

	// 2) ������ ���Ѵ�.
	int	count = vec_temp.size();

	// 3) ��� detach
	for(auto& iter:vec_temp)
	{
		this->process_detach(iter);
	}

	// return)
	return count;
}


}