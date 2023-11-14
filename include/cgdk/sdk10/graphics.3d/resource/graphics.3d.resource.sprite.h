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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// 1. CGResource::CSprite란!
//    1) Client에 사용되게 하기 위해 Performance보다는 Client와의 동기를 중요 
//       점을 두어 다른 Program이 동작하는 중간에 Run을 실행함으로써 각종 처리
//       를 할 수 있도록 한 것이다.
//    2) 기본적으로 이것은 Connect만 지원할 뿐 Listen은 지원하지 않는다.
//    3) 소량의 연결처리르 전제로 하였으므로 Socket Manager와 Socket Pool 등은
//       지원하지 않는다.
//    4) 그래도 과거에 비해 반응속도가 크게 증가하였고 각종 Pending현상으로 인한
//       Failure를 거의 없앴다.
//
//
// 2. CGNetRoot의 핵심! Function의 기능 설명
//    1) Run   접속을 시대해온 Socket을 처리하고 I/O를 처리하는 것이다.
//             이것을 Loop에 넣어서 일정 시간간격으로 처리를 해 주어야 한다.
//             자주 불러주면 그만큼 반응속도가 빨라진다.
//
// 3. 주의 사항
//  Run을 항상 일정 시간마다 실행을 시켜 I/O에 대한 처리를 반듯이 해주어야 한다.
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
			CGPTR<TEXTURE>		m_Texture;				// Texture를 설정함.

public:
	// 2) Setting Info
			VECTOR2				m_v2Position;	// x,  y
			VECTOR2				m_v2Size;		// width, height

			VECTOR4				m_v4TexCoord;
};


} // namespace CGResource
