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
//*  Best for Game Developement and Optimized for Game Developement.��         *
//*                                                                           *
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CG3DScenenode::CTM
//
// 1. CG3DScenenode::CTM��...
//    1) �⺻���� Scenenode ���������� Modifier�� �߰��� ������ �Ϲ������� Bone��
//       ���ȴ�.
//
//-----------------------------------------------------------------------------
namespace 
{

template <typename TSCENECOMPONENT=ICG3DSceneComponent>
class CCG3DScenenode :
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICG3DSceneNode<TSCENECOMPONENT>,
	public						CGNameable::NString
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CCG3DScenenode()	{	SetObjectType(CGOBJECTTYPE_SCENENODE);}
	virtual ~CCG3DScenenode()	{}
};


}
