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
// 1. CG3D::CMatrix란!
//    1) 가장 기본적인 TransformMatrix정보를 가진 객체
//    2) 자체적으로 Reference Count를 가지고 있다.
//
//-----------------------------------------------------------------------------
namespace CG3D
{

class CMatrix :
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	public						CG3D::MATRIX,
	virtual public				ICGReferenceable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CMatrix()													{}
			CMatrix(const CMatrix& p_rMatrix) : CG3D::MATRIX((const CG3D::MATRIX&)p_rMatrix)	{}
			CMatrix(const CG3D::MATRIX& p_rMatrix) : CG3D::MATRIX(p_rMatrix)	{}
	virtual ~CMatrix()													{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Operator - assignment
			CMatrix&			operator=(const CMatrix& rhs)			{	*(CG3D::MATRIX*)this=(const CG3D::MATRIX&)rhs; return *this;}
			CMatrix&			operator=(const CG3D::MATRIX& rhs)		{	*(CG3D::MATRIX*)this=rhs; return *this;}

	// 2) Operator - type casting
								operator	CG3D::MATRIX&()				{	return *(CG3D::MATRIX*)this;}
};


}