//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              CG3D D3D Classes                             *
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
//
// CGMSG
//
// 1. CGMSG는...
//    1) 렌더링을 위한 상황정보를 담고 있는 Class
//
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 1. CGMSG- Query
//-----------------------------------------------------------------------------
//const int	CGFUNCTION_SET_WORLDTRANSFORMATRIX	 = 16;
//const int	CGFUNCTION_GET_WORLDTRANSFORMATRIX	 = 17;
//const int	CGFUNCTION_SET_LOCALTRANSFORMATRIX	 = 18;
//const int	CGFUNCTION_GET_LOCALTRANSFORMATRIX	 = 19;
//const int	CGFUNCTION_SET_PARENT_TRANSFORMATRIX = 20;
//const int	CGFUNCTION_GET_PARENT_TRANSFORMATRIX = 21;
//const int	CGFUNCTION_SET_SOURCETRANSFORMATRIX	 = 22;
//const int	CGFUNCTION_GET_SOURCETRANSFORMATRIX	 = 23;
//const int	CGFUNCTION_SET_TARGETTRANSFORMATRIX	 = 24;
//const int	CGFUNCTION_GET_TARGETTRANSFORMATRIX	 = 25;

const int	CGFUNCTION_ATTACH_BOUND				 = 28;
const int	CGFUNCTION_DETACH_BOUND				 = 29;


enum _CGAUTOMATIONTYPE
{
	// 1) Transform Matrix
	CG3DNOTIFY_ON_WORLDTRANSFORMATRIX_CHANGE,
	CG3DNOTIFY_ON_LOCALTRANSFORMATRIX_CHANGE,

	// 2) Attach/Detach
	CG3DNOTIFY_ON_ATTACH,
	CG3DNOTIFY_ON_DETACH,

	// 3) Scene node
	CG3DNOTIFY_ON_PARENT_CHANGE,
	CG3DNOTIFY_ON_SIBLING_ATTACH,
	CG3DNOTIFY_ON_SIBLING_DETACH,

	// Max)
	CGAUTOMATIONTYPE_MAX
};


