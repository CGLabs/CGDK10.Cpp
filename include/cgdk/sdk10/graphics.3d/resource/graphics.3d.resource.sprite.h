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
// 1. CGResource::CSprite��!
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


class CSprite : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICGResource,							// (I) Resource 
	public						CGNameable::NString						// (@) Nameable	
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CSprite();
			CSprite(const CSprite& p_rSprite);
	virtual	~CSprite();

public:
			CSprite(TEXTURE* p_rTexture);
			CSprite(_In_z_ const _CHAR* p_strFileName);
			CSprite(_In_z_ const _CHAR_SUB* p_strFileName);


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Create/Duplicate/Destroy
			void				Create(TEXTURE* p_pTexture);
			void				Create(_In_z_ const _CHAR* p_strFileName);
			void				Create(_In_z_ const _CHAR_SUB* p_strFileName);
			void				Duplicate(const CSprite& p_rSprite);
	virtual	void				Destroy();

	// 2) Draw Function
			void				Draw(const VECTOR2& p_Location, const RECT2D* p_Rect = NULL);
			void				Draw();

	// 3) Texture
			void				SetTexture(TEXTURE* p_Texture);
			CGPTR<TEXTURE>		GetTexture() const						{	return m_Texture;}

			BOOL				Apply(int p_Stage=0);

	// 4) Attribute
			float				GetWidth() const						{	return m_v2Size.x;}
			void				SetWidth(float p_fWidth)				{	m_v2Size.x=p_fWidth;}
			float				GetHeight() const						{	return m_v2Size.y;}
			void				SetHeight(float p_fHeight)				{	m_v2Size.y=p_fHeight;}

			float				GetX() const							{	return m_v2Position.x;}
			void				SetX(float p_fX)						{	m_v2Position.x=p_fX;}
			float				GetY() const							{	return m_v2Position.y;}
			void				SetY(float p_fY)						{	m_v2Position.y=p_fY;}

			void				SetRect(const VECTOR2& p_rv2Position, const VECTOR2& p_rv2Size)			{	m_v2Position=p_rv2Position; m_v2Size=p_rv2Size;}
			void				SetRect(float p_fWidth, float p_fHeight, float p_fX=0.0f, float p_fY=0.0f)	{	m_v2Position.x=p_fX; m_v2Position.y=p_fY; m_v2Size.x=p_fWidth; m_v2Size.y=p_fHeight;}
			void				SetRect(const VECTOR4& p_v4Rect)		{	m_v2Position.x=p_v4Rect.x; m_v2Position.y=p_v4Rect.y; m_v2Size.x=(p_v4Rect.z-p_v4Rect.x); m_v2Size.y=(p_v4Rect.w-p_v4Rect.y);}

			//void				SetSpriteData(LPFILE_RESOURCE_2DSPRITE p_pSpriteData, const TEXTURE& p_pTexture);

			const VECTOR4&		GetTexCoord() const						{	return m_v4TexCoord;}


	// 3) Operator overriding
			CSprite&			operator=(const CSprite& p_rhs)			{	Duplicate(p_rhs); return *this;}


// ****************************************************************************
// Protected) 
// ----------------------------------------------------------------------------
public:
	// 1) Process Render
	virtual	int					ProcessMessage(CGMSG& /*_Msg*/) override	{	return 0;}

	// 2) Compute Texture Coord
			void				ComputeTextureCoord();


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
	// 1) Original Info
			CGPTR<TEXTURE>		m_Texture;				// Texture�� ������.

public:
	// 2) Setting Info
			VECTOR2				m_v2Position;	// x,  y
			VECTOR2				m_v2Size;		// width, height

			VECTOR4				m_v4TexCoord;
};


} // namespace CGResource
