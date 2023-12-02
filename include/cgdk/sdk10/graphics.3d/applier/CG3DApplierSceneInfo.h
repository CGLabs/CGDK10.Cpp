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
// 1. ICGResource��!
//    1) Client�� ���ǰ� �ϱ� ���� Performance���ٴ� Client���� ���⸦ �߿� 
//       ���� �ξ� �ٸ� Program�� �����ϴ� �߰��� Run�� ���������ν� ���� ó��
//       �� �� �� �ֵ��� �� ���̴�.
//    2) �⺻������ �̰��� Connect�� ������ �� Listen�� �������� �ʴ´�.
//    3) �ҷ��� ����ó���� ������ �Ͽ����Ƿ� Socket Manager�� Socket Pool ����
//       �������� �ʴ´�.
//    4) �׷��� ���ſ� ���� �����ӵ��� ũ�� �����Ͽ��� ���� Pending�������� ����
//       Failure�� ���� ���ݴ�.
//
//
// 2. CGNetRoot�� �ٽ�! Function�� ��� ����
//    1) Run   ������ �ô��ؿ� Socket�� ó���ϰ� I/O�� ó���ϴ� ���̴�.
//             �̰��� Loop�� �־ ���� �ð��������� ó���� �� �־�� �Ѵ�.
//             ���� �ҷ��ָ� �׸�ŭ �����ӵ��� ��������.
//
// 3. ���� ����
//  Run�� �׻� ���� �ð����� ������ ���� I/O�� ���� ó���� �ݵ��� ���־�� �Ѵ�.
//
//-----------------------------------------------------------------------------
namespace CG3DApplier
{

class CSceneInfo :
// ****************************************************************************
// 1. ����� Super Class��
// ----------------------------------------------------------------------------
	virtual public				ICG3DApplier,							// (I) Applier
	public						ICGDeviceGraphic						// (@) Device Setting Info (Singleton)
{
// ****************************************************************************
// 4. ������/�ڻ���
// ----------------------------------------------------------------------------
public:
			CSceneInfo(COLOR p_BackColor=0xff000000, COLOR4 p_GlobalAmbient=COLOR4(0.0f, 0.0f, 0.0f, 0.0f));
	virtual	~CSceneInfo();


// ****************************************************************************
// 3. �Ӽ� 
// ----------------------------------------------------------------------------
protected:
			COLOR				m_ColorBack;
			COLOR4				m_GlobalAmbient;

public:
			COLOR				GetBackColor() const					{	return m_ColorBack;}
			void				SetBackColor(COLOR p_BackColor)			{	m_ColorBack=p_BackColor;}

			COLOR4&				GlobalAmbient()							{	return m_GlobalAmbient;}
			void				SetGlobalAmbient(float p_r, float p_g, float p_b)	{	m_GlobalAmbient.r=p_r; m_GlobalAmbient.g=p_g; m_GlobalAmbient.b=p_b;}
			void				SetGlobalAmbient(COLOR4 p_GlobalAmbient){	m_GlobalAmbient=p_GlobalAmbient;}


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	// 1) Process Render
	virtual	int					ProcessRender(CGMSG_PROCESS_RENDER& /*_MSGRender*/) override	{ return 0; }


// ****************************************************************************
// 2. �ٽ� virtual �Լ�
// ----------------------------------------------------------------------------
public:
	virtual	void				Apply(DWORD p_ClearOption);
};


}