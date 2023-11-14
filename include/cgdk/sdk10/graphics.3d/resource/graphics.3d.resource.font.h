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
// CGResource::CFont
//
// 1. CGResource::CFont��!
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
// 2. CGResource::CFont�� �ٽ�! Function�� ��� ����
//    1) Run   ������ �ô��ؿ� Socket�� ó���ϰ� I/O�� ó���ϴ� ���̴�.
//             �̰��� Loop�� �־ ���� �ð��������� ó���� �� �־�� �Ѵ�.
//             ���� �ҷ��ָ� �׸�ŭ �����ӵ��� ��������.
//
// 3. ���� ����
//  Run�� �׻� ���� �ð����� ������ ���� I/O�� ���� ó���� �ݵ��� ���־�� �Ѵ�.
//
//-----------------------------------------------------------------------------
namespace CG3D
{
enum OUTLINE_TYPE
{
	OUTLINE_TYPE_NORMAL,
	OUTLINE_TYPE_DROPSHADOW,			// +1 Drop Shaodw�� ���� �ѹ������� Outline�� ����� �� 
	OUTLINE_TYPE_OUTLINE_ONESIDE,		// +2 �»�, ���� �ι������� Outline�� ����� ��
	OUTLINE_TYPE_OUTLINE_DOUBLESIDE,	// +4 �»�, ���, ����, ������ �׹����� Outline�� ����� ��
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