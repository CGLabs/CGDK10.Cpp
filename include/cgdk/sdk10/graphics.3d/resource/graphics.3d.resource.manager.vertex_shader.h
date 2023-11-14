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
// 1. CGResource::VertexShader::Manager��!
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
class CGResource::CVertexshader::Manager : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	protected					ICGDeviceGraphic,
	virtual public				ICGMessageable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			Manager();
	virtual ~Manager();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Vertex Shader�� �߰��� ����.
			CGPTR<VERTEXSHADER>	RegisterVertexshader(DWORD p_dwID, VERTEXSHADER* p_pVertexShader);
			void				UnregisterVertexshader(VERTEXSHADER* p_pVertexShader);

	// 2) ã��/���
			CGPTR<VERTEXSHADER>	FindVertexshader(int p_iIndex) const;
			CGPTR<VERTEXSHADER>	GetVertexshader(int p_iIndex);

	// 3) Default Shader FileName
	static	const _CHAR*		GetDefaultShaderFileName(DWORD p_dwID);

	// 4) Init Instance/RunExecutor
	static	CGPTR<Manager>		GetInstance()							{	if(m_pInstance.empty()){ InitInstance();} return m_pInstance;}
	static	void				SetInstance(Manager* p_pInstance)		{	m_pInstance=p_pInstance;}
	static	void				ResetInstance()							{	m_pInstance.reset();}


// ****************************************************************************
// Protected) 
// ----------------------------------------------------------------------------
public:
	// 1) Process Render
	virtual	int					ProcessMessage(CGMSG& /*_Msg*/) override {	return 0;}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
	// 1) Map Vertexbuffer
			mutable LOCKABLE
			<std::map<DWORD, CGPTR<VERTEXSHADER>>>	m_mapVertexshader;

	// 2) Instance
	static	CGPTR<Manager>		m_pInstance;
	static	void				InitInstance();

public:
			void				InitShaderConstant();
};
