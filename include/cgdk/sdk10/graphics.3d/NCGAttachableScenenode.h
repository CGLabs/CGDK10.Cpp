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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGAttachable::NRenderer
//
// 1. ICGScene��...
//    1) Scene�� ����� �����ϴ� �⺻���� ������ ������ �ִ� Interface Class�̴�.
//    2) Scene�� �⺻������ Message Trigging�� Scene�� Chained working�� �⺻����
//       �����ǰ� �Ǿ� �ִ�.
//
// 2. ICGScene�� �ٽ�! Function�� ��� ����
//    1) CloseScene()	�ݴ� �Լ�. Open()�� �پ��Ҽ� �ֱ� ������ virtual�� �������� �ʴ´�.
//
//
//-----------------------------------------------------------------------------
namespace CGAttachable
{

template <typename TTYPE=ICG3DSceneNode, typename TCONTAINER=vector<CGPTR<ICG3DSceneComponent>>>
class NSceneNode : 
	virtual public NCGAttachable<TTYPE, TCONTAINER>
{
public:
			NSceneNode()		{}	
	virtual ~NSceneNode()		{}
};


}