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
// CGResource::CFont
//
// 1. CGResource::CFont란!
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
// 2. CGResource::CFont의 핵심! Function의 기능 설명
//    1) Run   접속을 시대해온 Socket을 처리하고 I/O를 처리하는 것이다.
//             이것을 Loop에 넣어서 일정 시간간격으로 처리를 해 주어야 한다.
//             자주 불러주면 그만큼 반응속도가 빨라진다.
//
// 3. 주의 사항
//  Run을 항상 일정 시간마다 실행을 시켜 I/O에 대한 처리를 반듯이 해주어야 한다.
//
//-----------------------------------------------------------------------------
namespace CG3D
{
enum OUTLINE_TYPE
{
	OUTLINE_TYPE_NORMAL,
	OUTLINE_TYPE_DROPSHADOW,			// +1 Drop Shaodw로 우하 한번만으로 Outline을 만드는 것 
	OUTLINE_TYPE_OUTLINE_ONESIDE,		// +2 좌상, 우하 두번만으로 Outline을 만드는 것
	OUTLINE_TYPE_OUTLINE_DOUBLESIDE,	// +4 좌상, 우상, 좌하, 우하의 네벗으로 Outline을 만드는 것
};
}

namespace CGResource
{

class CFont : 
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
			CFont();
			CFont(_In_z_ const _CHAR*	lpszFace,
				  INT	Height,
				  UINT	Width			 = 0,
				  UINT	Weight			 = FW_NORMAL,
				  UINT	MipLevels		 = 0,
				  BOOL	Italic			 = FALSE,
				  DWORD	CharSet			 = HANGUL_CHARSET,
				  DWORD	OutputPrecision	 = OUT_DEFAULT_PRECIS,
				  DWORD	Quality			 = PROOF_QUALITY,
				  DWORD	PitchAndFamily	 = DEFAULT_PITCH);
			CFont(_In_z_ const _CHAR_SUB* lpszFace,
				  INT	Height,
				  UINT	Width			 = 0,
				  UINT	Weight			 = FW_NORMAL,
				  UINT	MipLevels		 = 0,
				  BOOL	Italic			 = FALSE,
				  DWORD	CharSet			 = HANGUL_CHARSET,
				  DWORD	OutputPrecision	 = OUT_DEFAULT_PRECIS,
				  DWORD	Quality			 = PROOF_QUALITY,
				  DWORD	PitchAndFamily	 = DEFAULT_PITCH);
			CFont(const CFont& p_rFont);
	virtual	~CFont();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Create/Duplicate/Destroy
			void				Create(LPD3DXFONT_DESC p_pD3DFontDesc);
			void				Create( _In_z_ const _CHAR* lpszFace,
										INT		Height,
										UINT	Width			= 0,
										UINT	Weight			= FW_NORMAL,
										UINT	MipLevels		= 0,
										BOOL	Italic			= FALSE,
										DWORD	CharSet			= HANGUL_CHARSET,
										DWORD	OutputPrecision	= OUT_DEFAULT_PRECIS,
										DWORD	Quality			= PROOF_QUALITY,
										DWORD	PitchAndFamily	= DEFAULT_PITCH
								);
			void				Create( _In_z_ const _CHAR_SUB*	lpszFace,
										INT		Height,
										UINT	Width			= 0,
										UINT	Weight			= FW_NORMAL,
										UINT	MipLevels		= 0,
										BOOL	Italic			= FALSE,
										DWORD	CharSet			= HANGUL_CHARSET,
										DWORD	OutputPrecision	= OUT_DEFAULT_PRECIS,
										DWORD	Quality			= PROOF_QUALITY,
										DWORD	PitchAndFamily	= DEFAULT_PITCH
								);
			void				Duplicate(const CFont& p_rFont);
	virtual	void				Destroy();

	// 2) Draw Functions
			void				RenderText(const char* p_strText, OUTLINE_TYPE p_OutlineType, COLOR p_TextColor, COLOR p_OutlineColor, RECT2D* p_Rect, LONG p_Length = -1, DWORD p_Flag = DT_LEFT) const;
			void				RenderText(const wchar_t* p_strText, OUTLINE_TYPE p_OutlineType, COLOR p_TextColor, COLOR p_OutlineColor, RECT2D* p_Rect, LONG p_Length = -1, DWORD p_Flag = DT_LEFT) const;

			void				RenderText(int p_iLeft, int p_iTop, int p_iRight, int p_iBottom, COLOR p_TextColor, const CHAR* p_String, ...) const;
			void				RenderText(int p_iLeft, int p_iTop, int p_iRight, int p_iBottom, COLOR p_TextColor, const WCHAR* p_String, ...) const;

			void				RenderText_Shaodowed(int p_iLeft, int p_iTop, int p_iRight, int p_iBottom, COLOR p_TextColor, COLOR p_OutlineColor, const CHAR* p_String, ...) const;
			void				RenderText_Shaodowed(int p_iLeft, int p_iTop, int p_iRight, int p_iBottom, COLOR p_TextColor, COLOR p_OutlineColor, const WCHAR* p_String, ...) const;

			void				RenderText_OutlineOneside(int p_iLeft, int p_iTop, int p_iRight, int p_iBottom, COLOR p_TextColor, COLOR p_OutlineColor, const CHAR* p_String, ...) const;
			void				RenderText_OutlineOneside(int p_iLeft, int p_iTop, int p_iRight, int p_iBottom, COLOR p_TextColor, COLOR p_OutlineColor, const WCHAR* p_String, ...) const;

			void				RenderText_OutlineTwoside(int p_iLeft, int p_iTop, int p_iRight, int p_iBottom, COLOR p_TextColor, COLOR p_OutlineColor, const CHAR* p_String, ...) const;
			void				RenderText_OutlineTwoside(int p_iLeft, int p_iTop, int p_iRight, int p_iBottom, COLOR p_TextColor, COLOR p_OutlineColor, const WCHAR* p_String, ...) const;

	// 3) Transform
			void				SetTrasform(MATRIX* p_pTransformMatrix)	{	m_pD3DSprite->SetTransform((LPD3DXMATRIX)p_pTransformMatrix);}
	// 4) Attribute
			LPD3DXFONT			GetD3DFont() const						{	return m_pD3DFont;}

	// 5) Operator
			CFont&				operator=(const CFont& p_rhs)			{	Duplicate(p_rhs); return *this;}


// ****************************************************************************
// Protected) 
// ----------------------------------------------------------------------------
public:
	// 1) Process Render
	virtual	int					ProcessMessage(CGMSG& /*_Msg*/) override 	{	return 0;}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
			LPD3DXFONT			m_pD3DFont;
			LPD3DXSPRITE		m_pD3DSprite;

protected:
			void				RenderText_Normal(const char* p_strText, COLOR p_TextColor, RECT2D* p_Rect, LONG p_Length=-1, DWORD p_Flag=DT_LEFT) const;
			void				RenderText_Normal(const wchar_t* p_strText, COLOR p_TextColor, RECT2D* p_Rect, LONG p_Length=-1, DWORD p_Flag=DT_LEFT) const;

			void				RenderText_Shaodowed(const char* p_strText, COLOR p_TextColor, COLOR p_ShadowColor, RECT2D* p_Rect, LONG p_Length=-1, DWORD p_Flag=DT_LEFT) const;
			void				RenderText_Shaodowed(const wchar_t* p_strText, COLOR p_TextColor, COLOR p_ShadowColor, RECT2D* p_Rect, LONG p_Length=-1, DWORD p_Flag=DT_LEFT) const;

			void				RenderText_OutlineOneside(const char* p_strText, COLOR p_TextColor, COLOR p_OutlineColor, RECT2D* p_Rect, LONG p_Length=-1, DWORD p_Flag=DT_LEFT) const;
			void				RenderText_OutlineOneside(const wchar_t* p_strText, COLOR p_TextColor, COLOR p_OutlineColor, RECT2D* p_Rect, LONG p_Length=-1, DWORD p_Flag=DT_LEFT) const;

			void				RenderText_OutlineTwoside(const char* p_strText, COLOR p_TextColor, COLOR p_OutlineColor, RECT2D* p_Rect, LONG p_Length=-1, DWORD p_Flag=DT_LEFT) const;
			void				RenderText_OutlineTwoside(const wchar_t* p_strText, COLOR p_TextColor, COLOR p_OutlineColor, RECT2D* p_Rect, LONG p_Length=-1, DWORD p_Flag=DT_LEFT) const;
};


}