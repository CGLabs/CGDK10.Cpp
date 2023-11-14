//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 9.0 / release 2017.01.03                        *
//*                                                                           *
//*                              Account Classes                              *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                 ¨Ï 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// doss::Ndepot<TENTITY>
//
//
//-----------------------------------------------------------------------------
namespace CGDK
{

class doss::Idepot :
// inherited classes)
	public						Isession,
	public						object::Nnameable,
	public                      object::Ninitializable_startable,
	public						net::io::messageable::Nbase
{
// defintions)
public:
		class socket;
		class group_immigration;
		class restore;

// constructor/destructor) 
public:
			Idepot() {}
			Idepot(const std::string_view _name) : Nnameable(_name) {}
	virtual	~Idepot() noexcept {}
};


}
