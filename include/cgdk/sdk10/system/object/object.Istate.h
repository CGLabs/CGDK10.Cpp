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

//-----------------------------------------------------------------------------
/**

 @class		object::Istate
 @brief		상태 속성을 가지고 설정하는 속성을 가진 인터페이스 클래드
 @todo		
 @ref		
 @details	\n
 객체의 상태값을 가지는 인터페이스 클래스이다.
 상태값은 eOBJECT_STATE 형이다.
 SetStatue()함수로 현재의 상태를 설정할 수 있으며 get_status()함수로 현재 상태를 얻을 수도 있다.
 기본적인 상태는 초기화(initialize)-시작(start)-중지(stop)-소멸(destroy)의 4가지를 기본으로 가지고 있으며 이들간의 전이 상태들도 존재한다.

  1) initialize		eOBJECT_STATE::NONE    ->eOBJECT_STATE::INITIALIZING_PENDING ->eOBJECT_STATE::STOPPED
  2) start			eOBJECT_STATE::STOPPED ->eOBJECT_STATE::START_PENDING        ->eOBJECT_STATE::RUNNING
  3) stop			eOBJECT_STATE::RUNNING ->eOBJECT_STATE::STOP_PENDING		 ->eOBJECT_STATE::STOPPED
  4) Destory		eOBJECT_STATE::STOPPED ->eOBJECT_STATE::DESTROYING_PENDING   ->eOBJECT_STATE::NONE
  5) pause			eOBJECT_STATE::RUNNING ->eOBJECT_STATE::PAUSE_PENDING		 ->eOBJECT_STATE::PAUSED
  6) continue		eOBJECT_STATE::PAUSED  ->eOBJECT_STATE::CONTINUE_PENDING	 ->eOBJECT_STATE::RUNNING

*/
//-----------------------------------------------------------------------------
class CGDK::object::Istate : public object::Nattachable<object::Istate>
{
public:
	virtual ~Istate() noexcept {}

// public) 
public:
	virtual	bool				attach_child_object(object_ptr<object::Istate>&& _pchild) { return this->object::Nattachable<object::Istate>::process_attach(std::move(_pchild));}
	virtual	bool				detach_child_object(object::Istate* _pchild) noexcept { return this->object::Nattachable<object::Istate>::process_detach(_pchild);}

	[[nodiscard]] virtual eOBJECT_STATE get_object_state() const noexcept PURE;
	virtual	eOBJECT_STATE		set_object_state(eOBJECT_STATE _state) noexcept PURE;
	virtual	bool				set_object_state_if(eOBJECT_STATE _state_compare, eOBJECT_STATE _state) noexcept PURE;

public:
			struct WAIT_INFO
			{
				object_ptr<object::Istate> pobject;
				result_code		result;
			};
			std::vector<WAIT_INFO> m_queue_pended;
};

namespace CGDK::object
{
	result_code initialize	(object::Istate* _object, context& _context);
	result_code start		(object::Istate* _object, context& _context);
	result_code stop		(object::Istate* _object) noexcept;
	result_code destroy		(object::Istate* _object) noexcept;
	result_code pause		(object::Istate* _object);
	result_code resume		(object::Istate* _object);
}
