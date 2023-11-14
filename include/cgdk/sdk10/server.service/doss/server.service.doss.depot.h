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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
// doss::CAccount
//-----------------------------------------------------------------------------
namespace CGDK
{

class doss::depot : 
// inherited classes)
	public						Ndepot
{
// constructor/destructor) 
public:
			depot() {}
			depot(const std::string_view _name) : Ndepot(_name) {}
	virtual	~depot() noexcept {}

// public)
public:
	//! @brief 모든 [Account]를 [체크_아웃]한다.
	void						checkout_all();

	[[nodiscard]] virtual object_ptr<Irepository> get_repository(const shared_buffer& /*_buffer*/) const noexcept override { return m_prepository; }
			void				set_repository(Irepository* _prepository) { m_prepository = _prepository; }

// frameworks) 
private:
	virtual	void				on_destroying() override { m_prepository.reset(); Ndepot::on_destroying(); }

// frameworks) 
private:
			object_ptr<Irepository> m_prepository;
};


}