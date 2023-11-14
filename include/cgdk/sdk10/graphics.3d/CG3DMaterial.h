//*****************************************************************************
//*                                                                           *
//*                      Cho SangHyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                             CG Object Classes                             *
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
// 1. CG3D::MATERIAL란!
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
namespace CG3D
{

#define	MAX_MATERIAL_FACTOR		8
const int	MATERIAL_FACTOR_DIFFUSE	 = 0;
const int	MATERIAL_FACTOR_SPECULAR = 1;
const int	MATERIAL_FACTOR_AMBIENT	 = 2;
const int	MATERIAL_FACTOR_EMISSIVE = 3;
const int	MATERIAL_FACTOR_FRESNEL	 = 4;

struct MATERIAL : public FACTOR_ARRAY<MAX_MATERIAL_FACTOR>
{
public:
			template<int IFACTOR>
			void		SetRGB(const COLOR3& _Color)						{	static_assert(IFACTOR<MAX_MATERIAL_FACTOR, "IFACTOR is out of range"); Factor[IFACTOR]=_Color;}
			void		SetRGB(int _index, const COLOR3& _Color)			{	CGASSERT_ERROR(_index<MAX_MATERIAL_FACTOR); Factor[_index]=_Color;}
			template<int IFACTOR>
			void		SetRGB(float _R, float _G, float _B)				{	SetRGB<IFACTOR>(COLOR3(_R, _G, _B));}
			void		SetRGB(int _index, float _R, float _G, float _B)	{	SetRGB(_index, COLOR3(_R, _G, _B));}

			template<int IFACTOR>
			void		SetA(float _A)										{	static_assert(IFACTOR<MAX_MATERIAL_FACTOR, "IFACTOR is out of range"); Factor[IFACTOR].a=_A;}
			void		SetA(int _index, float _A)							{	CGASSERT_ERROR(_index<MAX_MATERIAL_FACTOR); Factor[_index].a=_A;}

			float		GetAlpha() const									{	return Factor[MATERIAL_FACTOR_EMISSIVE].a;}
			void		SetAlpha(float _A)									{	SetA<MATERIAL_FACTOR_EMISSIVE>(_A);}
			bool		IsUseAlpha() const									{	return Factor[MATERIAL_FACTOR_EMISSIVE].a!=0.0f;}
			void		SetAsDefault()
						{
							SetFactor<MATERIAL_FACTOR_DIFFUSE>	(COLOR4(1.0f, 1.0f, 1.0f, 0.0f));
							SetFactor<MATERIAL_FACTOR_SPECULAR>	(COLOR4(0.0f, 0.0f, 0.0f, 0.0f));
							SetFactor<MATERIAL_FACTOR_AMBIENT>	(COLOR4(0.0f, 0.0f, 0.0f, 0.0f));
							SetFactor<MATERIAL_FACTOR_EMISSIVE>	(COLOR4(0.0f, 0.0f, 0.0f, 1.0f));
							SetFactor<MATERIAL_FACTOR_FRESNEL>	(COLOR4(0.0f, 0.0f, 0.0f, 0.0f));
			}

			void		SetAsWhite()
						{
							SetFactor<MATERIAL_FACTOR_DIFFUSE>	(COLOR4(0.0f, 0.0f, 0.0f, 0.0f));
							SetFactor<MATERIAL_FACTOR_SPECULAR>	(COLOR4(0.0f, 0.0f, 0.0f, 0.0f));
							SetFactor<MATERIAL_FACTOR_AMBIENT>	(COLOR4(0.0f, 0.0f, 0.0f, 0.0f));
							SetFactor<MATERIAL_FACTOR_EMISSIVE>	(COLOR4(1.0f, 1.0f, 1.0f, 1.0f));
							SetFactor<MATERIAL_FACTOR_FRESNEL>	(COLOR4(0.0f, 0.0f, 0.0f, 0.0f));
			}

			void		SetAsBlack()
						{
							SetFactor<MATERIAL_FACTOR_DIFFUSE>	(COLOR4(0.0f, 0.0f, 0.0f, 0.0f));
							SetFactor<MATERIAL_FACTOR_SPECULAR>	(COLOR4(0.0f, 0.0f, 0.0f, 0.0f));
							SetFactor<MATERIAL_FACTOR_AMBIENT>	(COLOR4(0.0f, 0.0f, 0.0f, 0.0f));
							SetFactor<MATERIAL_FACTOR_EMISSIVE>	(COLOR4(0.0f, 0.0f, 0.0f, 1.0f));
							SetFactor<MATERIAL_FACTOR_FRESNEL>	(COLOR4(0.0f, 0.0f, 0.0f, 0.0f));
			}
};

}
