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

namespace CGDK
{
 //-----------------------------------------------------------------------------
/**

 @class		Nreferenceable
 

*/
//-----------------------------------------------------------------------------
template <class TOBJECT>
class Nreferenceable : virtual public Ireferenceable, public Idisposable::Ndelete
{
public:
			Nreferenceable(CGNEW_DEBUG_INFO_PARAMETERS);
	virtual ~Nreferenceable() noexcept;

private:
	object_ptr<factory::object<TOBJECT>>	m_pfactory_object;
};

#if defined(_USE_CREATE_FACTORY_FOR_ALL_OBJECT)
	#define		REFERENCEABLE_RELEASER				CGDK::Nreferenceable<TOBJECT>
	#define		REFERENCEABLE_RELEASER_INIT(param)	,CGDK::Nreferenceable<TOBJECT>(param)
#else
	#define		REFERENCEABLE_RELEASER				CGDK::Idisposable::Ndelete
	#define		REFERENCEABLE_RELEASER_INIT(param)
#endif


}