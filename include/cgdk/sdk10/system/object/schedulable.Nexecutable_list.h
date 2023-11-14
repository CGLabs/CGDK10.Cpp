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

 @class		schedulable::Nexecutable_list


*///-----------------------------------------------------------------------------
template <class TEXECUTABLE = Iexecutable>
class schedulable::Nexecutable_list :
	public						schedulable::Iexecutable
{
protected:
			Nexecutable_list();
	virtual ~Nexecutable_list() noexcept;

public:
			using CONTAINER = circular_list<object_ptr<TEXECUTABLE>>;
			class ITERATOR;

			bool				register_executable(TEXECUTABLE* _pexecutable);
			bool				unregister_executable(TEXECUTABLE* _pexecutable) noexcept;
			void				unregister_executable_all() noexcept;

	[[nodiscard]] ITERATOR		get_iterator() const;

	[[nodiscard]] size_t		executable_count() const noexcept;
	[[nodiscard]] bool			empty() const noexcept;
	[[nodiscard]] bool			exist() const noexcept;

protected:
	virtual intptr_t			process_execute(intptr_t _return, size_t _param) override;

private:
			std::shared_mutex	m_lockable_list_executable;
			CONTAINER			m_list_executable;
			typename CONTAINER::iterator m_iter_now;
};


}

#include "cgdk/sdk10/system/object/schedulable.Nexecutable_list.inl"
