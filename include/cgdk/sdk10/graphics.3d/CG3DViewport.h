//*****************************************************************************
//*                                                                           *
//*                      Cho SangHyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                           CG 3D Object Classes                            *
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
// 1. CG3D::CViewport��!
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
namespace CG3D
{

class CViewport : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	public						USE_D3DVIEWPORT,
	virtual public				ICGReferenceable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CViewport()													{}
			CViewport(const USE_D3DVIEWPORT& p_rViewport) : USE_D3DVIEWPORT(p_rViewport)	{}
			CViewport(int const x, int const y, int w, int h, float p_fMinZ=0.0f, float p_fMaxZ=1.0f)	{	SetPosition(x, y); SetSize(w, h); SetZ(p_fMinZ, p_fMaxZ);}
			~CViewport()													{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Position
			void				Set(int const x, int const y, int w, int h, float p_fMinZ=0.0f, float p_fMaxZ=1.0f)	{	SetPosition(x, y); SetSize(w, h); SetZ(p_fMinZ, p_fMaxZ);}
			void				SetPosition(int p_iX, int p_iY)			{	X=p_iX; Y=p_iY;}
			void				SetSize(int p_iWidth, int p_iHeight)	{	Width=p_iWidth; Height=p_iHeight;}
			void				SetPosSize(int l, int t, int r, int b)	{	SetPosition(l, t); SetSize(r-l, b-t);}
			void				SetRect(int x, int y, int w, int h)		{	SetPosition(x, y); SetSize(w, h);}
			void				SetRect(const ::RECT& p_rRect)			{	X=p_rRect.left; Y=p_rRect.top; Width=p_rRect.right-p_rRect.left; Height=p_rRect.bottom-p_rRect.top;}

			int					GetLeft() const							{	return X;}
			int					GetTop() const							{	return Y;}
			int					GetRight() const						{	return X + Width;}
			int					GetBottom() const						{	return Y + Height;}
			int					GetWidth() const						{	return Width;}
			int					GetHeight() const						{	return Height;}
			void				GetRect(::RECT& p_rRect) const			{	p_rRect.left=GetLeft(); p_rRect.top=GetTop(); p_rRect.right=GetRight(); p_rRect.bottom=GetBottom();}
			::RECT				GetRect() const							{	::RECT rect; GetRect(rect); return rect;}
			::RECT				GetRectWithOffset(int p_dx, int p_dy)	{	::RECT rect; rect.left=GetLeft()+p_dx; rect.top=GetTop()+p_dy; rect.right=rect.left+Width; rect.bottom=rect.top+Height; return rect;}

			void				Move(int p_dX, int p_dY)				{	X+=p_dX; Y+=p_dY;}
			void				MoveX(int p_dX)							{	X+=p_dX;}
			void				MoveY(int p_dY)							{	Y+=p_dY;}

	// 2) Aspect
			float				GetAspect() const						{	return ((float)Width)/((float)Height);}

	// 3) MinZ/MaxZ
			void				SetZ(float p_fMinZ, float p_fMaxZ)		{	MinZ=p_fMinZ; MaxZ=p_fMaxZ;}
			void				SetMinZ(float p_fMinZ)					{	MinZ=p_fMinZ;}
			void				SetMaxZ(float p_fMaxZ)					{	MaxZ=p_fMaxZ;}
			float				GetMinZ() const							{	return MinZ;}
			float				GetMaxZ() const							{	return MaxZ;}

	// 4) Clear
			void				ClearViewport(DWORD p_dwClearOption=D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, COLOR p_colorClear=0xff000000, RECT2D* p_Rect=nullptr, int p_iRectCount=0);

	// 5) Apply
			void				ApplyViewport();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Operator - assignment
			CViewport&			operator=(const CViewport& rhs)			{	*(CG3D::MATRIX*)this=(const CG3D::MATRIX&)rhs; return *this;}
			CViewport&			operator=(const USE_D3DVIEWPORT& rhs)	{	*(USE_D3DVIEWPORT*)this=rhs; return *this;}
			CViewport&			operator=(const ::RECT& rhs)			{	SetRect(rhs);}

	// 2) Operator - type casting
								operator const USE_D3DVIEWPORT&() const	{	return *(USE_D3DVIEWPORT*)this;}
								operator ::RECT() const					{	::RECT rect; GetRect(rect); return rect;}
};


}
