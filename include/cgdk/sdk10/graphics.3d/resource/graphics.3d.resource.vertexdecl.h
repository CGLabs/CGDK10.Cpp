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

class CVertexdecl : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICGResource,							// (I) Resource Interface
	public						CGNameable::NString,					// (@) Nameable	
	public						ICGDeviceGraphic						// (@) Device Setting Info (Singleton)
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CVertexdecl();
			CVertexdecl(DWORD p_dwFVF);
			CVertexdecl(const CVertexdecl& p_rCopy);
			CVertexdecl(const D3DVERTEXELEMENT9* p_pVertexExelment);
	virtual	~CVertexdecl();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) ���� & �ı� 
			void				Create(DWORD p_dwFVF);
			void				Create(const D3DVERTEXELEMENT9* p_pVertexExelment);
			void				Duplicate(const CVertexdecl& p_rCopy);
	virtual	void				Destroy();

	// 2) ����
			HRESULT				ApplyVertexDeclaration()				{	return m_lpDirect3DDevice->SetVertexDeclaration(m_pD3DVertexDeclaration);}

	// 3) Attribue
			bool				IsCreated() const						{	return m_pD3DVertexDeclaration.exist();}
			bool				IsDestroyed() const						{	return m_pD3DVertexDeclaration.empty();}

	// 4) Attributes
			CGPTR<D3DVERTEXDECL> GetVertexdeclaration() const			{	return m_pD3DVertexDeclaration;}

	// 5) Vertex Formats
	//		- Vertex Element�� ���� �Լ��̴�.
	//		- p_pDecl��  ��ü������ �޸𸮸� �Ҵ��ϰų� ���� �ʱ� ������ �����
	//		  ũ�⸦ �Ҵ��Ͽ� �����͸� �־�����Ѵ�.
	//		- ������ Error�� �߻��ϸ� THROW�� ������...
			void				GetDeclaration(D3DVERTEXELEMENT9* p_pDecl, UINT* p_pNumElements) const;

	// 6) Vertex Element����Ȯ��
	//		- FVF�� ������ Ư���� Format�� �� VertexDecl�� �����ϴ����� Ȯ���ϴ� �Լ��̴�.
	//		- VertexElement�� ���� �� �� Vertex Element �߿� FVF������ �ִ����� Ȯ���Ͽ� ������ TRUE�� �����ش�.
			bool				HasVertexElement(DWORD p_dwFVF) const;
			DWORD				ConvertToFVF() const;

	// 7) operation
			CVertexdecl&		operator=(const CVertexdecl& p_rhs)		{	Duplicate(p_rhs); return *this;}


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
			CGPTR<D3DVERTEXDECL>	m_pD3DVertexDeclaration;
};


}

