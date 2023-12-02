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
// 1. CEffect��!
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

class CEffect : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICG3DApplier							// (I) Applier
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CEffect();
	virtual ~CEffect();

public:
			CEffect(int p_nPass);


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Create/Destroy
			void				Create(int p_nPass);
	virtual	void				Destroy();

	// 2) Clear
			void				ClearApplierEffect();

	// 2) Get/Set
			void				SetPassVertexShader(int p_iPass, CGResource::CVertexshader* p_rVertexbuffer)	{	m_vectorVertexShader[p_iPass]=p_rVertexbuffer;}
			CGPTR<VERTEXSHADER>	GetPassVertexShader(int p_iPass) const	{	return m_vectorVertexShader[p_iPass];}

			void				SetPassPixelShader(int p_iPass, CGResource::CPixelshader* p_rPixelbuffer)		{	m_vectorPixelShader[p_iPass]=p_rPixelbuffer;}
			CGPTR<PIXELSHADER>	GetPassPixelShader(int p_iPass) const	{	return m_vectorPixelShader[p_iPass];}

			int					GetPassCount() const					{	return (int)m_vectorVertexShader.size();}

	// 3) Apply
			void				ApplyPass(int p_iPass) const;
	virtual void				Apply();


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	// 1) Process Render
	virtual	int					ProcessRender(CGMSG_PROCESS_RENDER& /*_MSGRender*/) override	{	return 0;}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
			vector<CGPTR<CGResource::CVertexshader>>	m_vectorVertexShader;
			vector<CGPTR<CGResource::CPixelshader>>		m_vectorPixelShader;

#if _MSC_VER>=_MSC_VER_2008
#if defined(_DEBUG)
public:
			std::shared_ptr<char>	m_strName;
#endif
#endif
};


}