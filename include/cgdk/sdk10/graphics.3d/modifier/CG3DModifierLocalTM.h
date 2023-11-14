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
// 1. CG3DRendererMesh��...
//    1) �������� Render�� Loop���� Render�� ���ÿ� �����ϴ� ����� ���ߴ�.
//    2) Render�� �ʿ��� ���� ������ ���������� ��� ������ �ְ� �Ѵ�. Render��
//       �� ������ �����ؼ� ��������� �ߺ� ���� �� �ٽ� �������� �ʾƵ� �ǰ�
//       ������ �Ѵ�.
//    3) Linked List����� Ȥ�� Array�� ������ ü������ �ʴ´�! ������ Modify��
//       Ʋ���� Arrange���� �ʿ��ϸ� ������ ������ ������ �� �ǹ̰� ���� ������
//       ��. 2D�� ��쳪 Ȥ�� Sprite���� ���� ������ �ʿ��ϳ� �̷� ���� ��
//       �� ������� ������ �ϸ� Default�� �����ϴ� ������ ���� �ʴ´�.
//       ������ �پ��� ����� ������ ������ �� �ֱ� �����̴�. ���� ��� Arrange
//       �� Z Ordering�� �ؾ��ϴ� ��� Y Ordering�� �ؾ��ϴ� ��쳪 �ʿ� ����
//       ��� �� ���� Ʋ�� �ʿ信 ���� �ٸ� ������ ü���ؾ� �ϱ� �����̴�.
//
//
// 2. CGNetRoot�� �ٽ�! Function�� ��� ����
//    1) Render      Render�� �����ϴ� �ٽ� �����̴�.  
//    2) ��...
//
// 3. ���� ����
//    ��... -_-;;
//
//-----------------------------------------------------------------------------
namespace CG3DModifier
{

class CLocalTM : 
// ****************************************************************************
// 1. ����� Super Class��
// ----------------------------------------------------------------------------
	virtual public				ICG3DModifier							// (I) Modifier
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CLocalTM();
			CLocalTM(const MATRIX& p_ptmLocal);
	virtual ~CLocalTM();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Clear
			void				ClearModifierLocalTM();

	// 2) Target Transform matrix
			void				SetTargetTransformMatrix(CMatrix* p_pTransformMatrix)		{	m_ptmTarget=p_pTransformMatrix;}
			void				ResetTargetTransformMatrix()								{	m_ptmTarget.reset();}
			CGPTR<CMatrix>		GetTargetTransformMatrix() const							{	return m_ptmTarget;}

	// 3) Parent Transform matrix
			void				SetParentTransformMatrix(CMatrix* p_pTransformMatrix)		{	m_ptmParent=p_pTransformMatrix;}
			void				ResetParentTransformMatrix()								{	m_ptmParent.reset();}
			CGPTR<CMatrix>		GetParentTransformMatrix() const							{	return m_ptmParent;}

	// 4) Local Transform matrix
			void				SetLocalTransformMatrix(const MATRIX& p_rTransformMatrix)	{	RETURN_IF(m_ptmLocal.empty(), ); *m_ptmLocal=p_rTransformMatrix;}
			void				SetLocalTransformMatrix(CMatrix* p_pTransformMatrix)		{	m_ptmLocal=p_pTransformMatrix;}
			CGPTR<CMatrix>		GetLocalTransformMatrix() const								{	return m_ptmLocal;}


// ****************************************************************************
// Message)
// ----------------------------------------------------------------------------
public:
	// Declare) 
	DECLARE_CGMESSAGE_MAP

	// 1) Functions
	virtual	uint32_t			OnFunction_SetTargetTransformMatrix		(CGMSG_SET<CMatrix>& _Msg);
	virtual	uint32_t			OnFunction_GetTargetTransformMatrix		(CGMSG_GET<CMatrix>& _Msg);

	virtual	uint32_t			OnFunction_SetParentTransformMatrix		(CGMSG_SET<CMatrix>& _Msg);
	virtual	uint32_t			OnFunction_GetParentTransformMatrix		(CGMSG_GET<CMatrix>& _Msg);

	virtual	uint32_t			OnFunction_SetLocalTransformMatrix		(CGMSG_SET<CMatrix>& _Msg);
	virtual	uint32_t			OnFunction_GetLocalTransformMatrix		(CGMSG_GET<CMatrix>& _Msg);


	// 2) Notifications for Automation
	virtual	uint32_t			OnNotify_OnWorldTransformMatrixChange	(CGMSG_COMMAND_PARAM_PTR<CMatrix>& _Msg);
	virtual	uint32_t			OnNotify_OnAttach						(CGMSG_COMMAND_PARAM_PTR<ICGObject>& _Msg);
	virtual	uint32_t			OnNotify_OnDetach						(CGMSG_COMMAND_PARAM_PTR<ICGObject>& _Msg);
	virtual	uint32_t			OnNotify_OnParentChange					(CGMSG_COMMAND_PARAM_PTR<ICGObject>& _Msg);


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
public:
	// 1) Process Message
	virtual	int					ProcessMessage(CGMSG& _Msg) override;
private:
	// 2) Process Render
	virtual	int					ProcessRender(CGMSG_PROCESS_RENDER& _MSGRender) override;


protected:
	// 1) Target Transform matrix
			CGPTR<CMatrix>		m_ptmTarget;

	// 2) Parent Transform matrix & Local Transform matrix
			CGPTR<CMatrix>		m_ptmParent;
			CGPTR<CMatrix>		m_ptmLocal;
};


}
