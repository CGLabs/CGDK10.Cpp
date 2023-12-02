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
*/
//-----------------------------------------------------------------------------
template <class TTYPE> class Iattachable;
template <class TOBJECT> bool OBJECT_ATTACH(object::Iattachable<TOBJECT>*	_ptarget, TOBJECT* _object);
template <class TOBJECT> bool OBJECT_ATTACH(Ireferenceable* _ptarget, TOBJECT* _object);
template <class TOBJECT> bool OBJECT_ATTACH(object::Iattachable<TOBJECT>*	_ptarget, Ireferenceable* _object);
template <class TOBJECT> bool OBJECT_ATTACH(Ireferenceable* _ptarget, Ireferenceable* _object);
		 
template <class TOBJECT> bool OBJECT_DETACH(object::Iattachable<TOBJECT>*	_ptarget, TOBJECT* _object) noexcept;
template <class TOBJECT> bool OBJECT_DETACH(Ireferenceable* _ptarget, TOBJECT* _object) noexcept;
template <class TOBJECT> bool OBJECT_DETACH(object::Iattachable<TOBJECT>*	_ptarget, Ireferenceable* _object) noexcept;
template <class TOBJECT> bool OBJECT_DETACH(Ireferenceable* _ptarget, Ireferenceable* _object) noexcept;


//-----------------------------------------------------------------------------
/**

 @class		Iattachable
 

*/
//-----------------------------------------------------------------------------
template <class TTYPE>
class object::Iattachable : virtual public Ireferenceable
{
public:
	virtual ~Iattachable() noexcept {}

public:
	//! @ ...
			bool				attach(object_ptr<TTYPE>&& _pchild) { return this->process_attach(std::move(_pchild));}
			bool				detach(TTYPE* _pchild) noexcept	{ return this->process_detach(_pchild);}

	#if defined(_WIN32)
			template <class T>
			std::enable_if_t<std::is_base_of_v<Iattachable<TTYPE>, T>, bool>
								attach(object_ptr<TTYPE>&& _pchild) { return this->process_attach(std::move(_pchild));}
			template <class T>
			std::enable_if_t<std::is_base_of_v<Iattachable<TTYPE>, T>, bool>
								detach(TTYPE* _pchild) noexcept { return this->process_detach(_pchild);}
	#endif

protected:
	virtual bool				process_attach(object_ptr<TTYPE>&& _pchild) PURE;
	virtual bool				process_detach(TTYPE* _pchild) noexcept PURE;
};

////! @brief _pparent객체에 _pchild를 붙인다. @param _pattach 피 붙임 객체 @param _pchild 붙일 객체 @return true 성공 @return false 실패(일반적으로 이미 붙어 있을 경우)
//template <class TOBJECT>
//bool OBJECT_ATTACH(Iattachable<TOBJECT>* _pparent, TOBJECT* _pchild)
//{
//	// check)
//	RETURN_IF(_pparent == nullptr, false);
//
//	return _pparent->attach(_pchild);
//}
//
//template <class TOBJECT>
//bool OBJECT_ATTACH(Iattachable<TOBJECT>* _pparent, object_ptr<Ireferenceable>&& _pchild)
//{
//	// check)
//	RETURN_IF(_pparent == nullptr, false);
//
//	auto pchild = dynamic_pointer_cast<TOBJECT>(_pchild);
//
//	return _pparent->attach(std::move(pchild));
//}
//
//template <class TOBJECT>
//bool OBJECT_ATTACH(Ireferenceable* _pparent, object_ptr<TOBJECT>&& _pchild)
//{
//	auto pnode_parent = dynamic_cast<Iattachable<TOBJECT>*>(_pparent);
//
//	// check)
//	RETURN_IF(pnode_parent == nullptr, false);
//
//	return pnode_parent->attach(std::move(_pchild));
//}
//
//template <class TOBJECT>
//bool OBJECT_ATTACH(Ireferenceable* _pparent, Ireferenceable* _pchild)
//{
//	auto pnode_parent = dynamic_cast<Iattachable<TOBJECT>*>(_pparent);
//
//	// check)
//	RETURN_IF(pnode_parent == nullptr, false);
//
//	auto pchild = dynamic_cast<TOBJECT*>(_pchild);
//
//	return pnode_parent->attach(pchild);
//}
//
//template <class TOBJECT>
//bool OBJECT_DETACH(Iattachable<TOBJECT>* _pparent, TOBJECT* _pchild) noexcept
//{
//	// check)
//	RETURN_IF(_pparent == nullptr, false);
//
//	return _pparent->detach(_pchild)!=0;
//}
//
//template <class TOBJECT>
//bool OBJECT_DETACH(Ireferenceable* _pparent, Ireferenceable* _pchild) noexcept
//{
//	auto pnode_parent = dynamic_cast<Iattachable<TOBJECT>*>(_pparent);
//
//	// check)
//	RETURN_IF(pnode_parent == nullptr, false);
//
//	auto pchild = dynamic_cast<TOBJECT*>(_pchild);
//
//	return pnode_parent->detach(pchild);
//}
//
//template <class TOBJECT>
//bool OBJECT_DETACH(Ireferenceable* _pparent, TOBJECT* _pchild) noexcept
//{
//	auto pnode_parent = dynamic_cast<Iattachable<TOBJECT>*>(_pparent);
//
//	// check)
//	RETURN_IF(pnode_parent == nullptr, false);
//
//	return pnode_parent->detach(_pchild);
//}
//
//template <class TOBJECT>
//bool OBJECT_DETACH(Iattachable<TOBJECT>* _pparent, Ireferenceable* _pchild) noexcept
//{
//	// check)
//	RETURN_IF(_pparent == nullptr, false);
//
//	auto pchild = dynamic_cast<TOBJECT*>(_pchild);
//
//	return _pparent->detach(pchild) != 0;
//}


}