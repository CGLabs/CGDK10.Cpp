//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                               Pool Classes                                *
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

 @class		Ipoolable
 
*/
//-----------------------------------------------------------------------------
template <class TTYPE> struct SCGLIST_ENTRY { TTYPE* Next = nullptr; };

template <class TOBJECT>
class CGDK::Ipoolable : public SCGLIST_ENTRY<TOBJECT>, virtual public Ireferenceable
{
};

#define	DEFAULT_FACTORY_NAME(name)	static std::string_view	_get_static_factory_name() { return #name;}
