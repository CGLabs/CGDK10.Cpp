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
// 1. CGNetRootClient��!
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
namespace CGResource
{

class CPixelshader : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICGResource,							// (I) Texture Base
	public						CGNameable::NString,					// (@) Nameable	
	public						ICGDeviceGraphic						// (@) Device Setting Info (Singleton)
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CPixelshader();
			CPixelshader(_In_z_ const _CHAR* p_strName);
			CPixelshader(_In_z_ const _CHAR_SUB* p_strName);
			CPixelshader(const CPixelshader& p_rCopy);
	virtual	~CPixelshader();


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	// 1) Create/Duplicate/Destroy
			void				CreateFromAssembly(_In_z_ const _CHAR* p_strName);
			void				CreateFromAssembly(_In_z_ const _CHAR_SUB* p_strName);
			void				CreateFromHLSL(_In_z_ const _CHAR* p_strFileName, _In_z_ const char*  p_strFunctionName, LPD3DXCONSTANTTABLE* p_ppConstantTable=nullptr, const D3DXMACRO* p_pDefines=nullptr, LPD3DXINCLUDE p_pInclude=nullptr, const char* p_pProfile=nullptr);
			void				CreateFromHLSL(_In_z_ const _CHAR_SUB* p_strFileName, _In_z_ const char*  p_strFunctionName, LPD3DXCONSTANTTABLE* p_ppConstantTable=nullptr, const D3DXMACRO* p_pDefines=nullptr, LPD3DXINCLUDE p_pInclude=nullptr, const char* p_pProfile=nullptr);
			void				Create(const DWORD* p_pdwCode);
			void				Duplicate(const CPixelshader& p_rCopy);
	virtual	void				Destroy();

	// 2) Apply
			HRESULT				Apply() const							{	return m_lpDirect3DDevice->SetPixelShader(m_pD3DShader.get());}

	// 3) �Ӽ� �� ����
			bool				IsCreated() const						{	return m_pD3DShader.exist();}
			bool				IsDestroyed() const						{	return m_pD3DShader.empty();}

			CGPTR<D3DPIXELSHADER9> GetD3DPixelShader() const			{	return m_pD3DShader;}

	// 4) Pixel Shader Manager
			class				Manager;

	// 5) operation
			CPixelshader&		operator=(const CPixelshader& p_rhs)	{	Duplicate(p_rhs); return *this;}


// ****************************************************************************
// Protected) 
// ----------------------------------------------------------------------------
public:
	// 1) Process Render
	virtual	int					ProcessMessage(CGMSG& /*_Msg*/) override	{	return 0;}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
			CGPTR<D3DPIXELSHADER9> m_pD3DShader;

			_STRING			m_strFileName;
};


}