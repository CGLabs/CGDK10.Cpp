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
//*                 ¨Ï 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// 1. CGSting
//
//
//
//-----------------------------------------------------------------------------

#define	TYPE_MAX_EDITBOXLENGTH	1024
#define	DEFUALT_STRING_BUFFER_SIZE	256

namespace CG3D
{

class STRING
{
//-----------------------------------------------------------------------------
// Dummy Functions
//-----------------------------------------------------------------------------
public:
	// Dummy
	static HRESULT WINAPI		Dummy_ScriptApplyDigitSubstitution(const SCRIPT_DIGITSUBSTITUTE*, SCRIPT_CONTROL*, SCRIPT_STATE*) { return E_NOTIMPL;}
	static HRESULT WINAPI		Dummy_ScriptStringAnalyse(HDC, const void *, int, int, int, DWORD, int, SCRIPT_CONTROL*, SCRIPT_STATE*, const int*, SCRIPT_TABDEF*, const BYTE*, SCRIPT_STRING_ANALYSIS*) { return E_NOTIMPL;}
	static HRESULT WINAPI		Dummy_ScriptStringCPtoX(SCRIPT_STRING_ANALYSIS, int, BOOL, int*)	{ return E_NOTIMPL;}
	static HRESULT WINAPI		Dummy_ScriptStringXtoCP(SCRIPT_STRING_ANALYSIS, int, int*, int*)	{ return E_NOTIMPL;}
	static HRESULT WINAPI		Dummy_ScriptStringFree(SCRIPT_STRING_ANALYSIS*)						{ return E_NOTIMPL;}
	static const SCRIPT_LOGATTR* WINAPI	Dummy_ScriptString_pLogAttr(SCRIPT_STRING_ANALYSIS)					{ return NULL;}
	static const int* WINAPI	Dummy_ScriptString_pcOutChars(SCRIPT_STRING_ANALYSIS)				{ return NULL;}


//-----------------------------------------------------------------------------
// String Functions
//-----------------------------------------------------------------------------
	// static member
	static HINSTANCE			s_hDll;  // Uniscribe DLL handle

	// Function pointers
	static HRESULT				(WINAPI *_ScriptApplyDigitSubstitution)( const SCRIPT_DIGITSUBSTITUTE*, SCRIPT_CONTROL*, SCRIPT_STATE* );
	static HRESULT				(WINAPI *_ScriptStringAnalyse)( HDC, const void *, int, int, int, DWORD, int, SCRIPT_CONTROL*, SCRIPT_STATE*, const int*, SCRIPT_TABDEF*, const BYTE*, SCRIPT_STRING_ANALYSIS* );
	static HRESULT				(WINAPI *_ScriptStringCPtoX)( SCRIPT_STRING_ANALYSIS, int, BOOL, int* );
	static HRESULT				(WINAPI *_ScriptStringXtoCP)( SCRIPT_STRING_ANALYSIS, int, int*, int* );
	static HRESULT				(WINAPI *_ScriptStringFree)( SCRIPT_STRING_ANALYSIS* );
	static const SCRIPT_LOGATTR* (WINAPI *_ScriptString_pLogAttr)( SCRIPT_STRING_ANALYSIS );
	static const int*			(WINAPI *_ScriptString_pcOutChars)( SCRIPT_STRING_ANALYSIS );

	static	void				InitializeUniscribe();
	static	void				UninitializeUniscribe();



//-----------------------------------------------------------------------------
// Main Base
//-----------------------------------------------------------------------------
protected:
	// Buffer°ü·Ã
			WCHAR*				m_pwszBuffer;		// Buffer to hold text
			int					m_nBufferSize;		// Size of the buffer allocated, in characters
			int					m_nTextSize;		// Size of the text in buffer excluding

	// Uniscribe-specific
			bool				m_bAnalyseRequired;	// True if the string has changed since last analysis.
			SCRIPT_STRING_ANALYSIS	m_Analysis;			// Analysis for the current string


protected:
			HRESULT				Analyse(FONT* p_Font);
			BOOL				Grow(int nNewSize = -1);


public:
			STRING(WCHAR* p_String=NULL);
			STRING(long p_SizeOfBuffer);
			~STRING();


			// ----------------
			// Buffer Operation
			// ----------------
			BOOL				CreateBuffer(int p_SizeOfBuffer);
			BOOL				CreateBuffer(const WCHAR* p_String);

			WCHAR*				GetBuffer()							{	return m_pwszBuffer;}
			int					GetBufferSize()						{	return m_nBufferSize;}
			BOOL				SetBufferSize( int nSize );


			// ----------------
			// Char Operation
			// ----------------
			int					GetTextSize()						{	return m_nTextSize;}

			void				Clear();

			// Inserts the char at specified index.
			// If nIndex == -1, insert to the end.
		    BOOL				InsertChar(int nIndex, WCHAR wChar);

			// Removes the char at specified index.
			// If nIndex == -1, remove the last char.
			BOOL				RemoveChar(int nIndex);

			// Inserts the first nCount characters of the string pStr at specified index.
			// If nCount == -1, the entire string is inserted.
			// If nIndex == -1, insert to the end.
			BOOL				InsertString(int nIndex, const WCHAR* pStr, int nCount = -1);

			BOOL				SetString(const WCHAR* wszText);
			void				Format(const WCHAR* p_FormatString, ...);

			const WCHAR&		operator[](int n) const				{	return m_pwszBuffer[n];}
			WCHAR&				operator[](int n);


			// ----------------
			// Uniscribe
			// ----------------
			HRESULT				CPtoX(int nCP, BOOL bTrail, int *pX, FONT* p_Font);
			HRESULT				XtoCP(int nX, int *pCP, int *pnTrail, FONT* p_Font);
			void				GetPriorItemPos(int nCP, int *pPrior, FONT* p_Font);
			void				GetNextItemPos(int nCP, int *pPrior, FONT* p_Font);

};

}