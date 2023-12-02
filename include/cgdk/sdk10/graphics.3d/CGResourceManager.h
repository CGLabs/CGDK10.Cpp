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
namespace CGResource
{

class Manager : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	protected					ICGDeviceGraphic,
	virtual public				ICGReferenceable
{
// ****************************************************************************
// Definitions)
// ----------------------------------------------------------------------------
public:
	typedef	vector<_STRING>				CONTAINER;
	typedef	CONTAINER::iterator			ITERATOR;
	typedef	CONTAINER::const_iterator	CONST_ITERATOR;


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
	// 1) Register/Unregister path
				bool			RegisterResourcePath(const TCHAR* p_strPath);
				bool			UnregisterResourcePath(const TCHAR* p_strPath);

	// 2) Registered Path
				ITERATOR		begin()									{	return m_vectorPath.begin();}
				CONST_ITERATOR	begin() const							{	return m_vectorPath.begin();}
				ITERATOR		end()									{	return m_vectorPath.end();}
				CONST_ITERATOR	end() const								{	return m_vectorPath.end();}

				int				GetRegisteredPathCount() const			{	return m_vectorPath.size();}

				const _STRING&	GetResourcePath(int p_iIndex)			{	return m_vectorPath[p_iIndex];}

	// 3) Init Instance/RunExecutor
	static	CGPTR<Manager>		GetInstance()							{	if(m_pInstance.empty()){ InitInstance();} return m_pInstance;}
	static	void				SetInstance(Manager* p_pInstance)		{	m_pInstance=p_pInstance;}
	static	void				ResetInstance()							{	m_pInstance.reset();}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
	// 1) Path list
				CONTAINER		m_vectorPath;

	// 2) Instance
	static	CGPTR<Manager>		m_pInstance;
	static	void				InitInstance();
};


}