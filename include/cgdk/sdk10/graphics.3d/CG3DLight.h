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
// 1. CG3D::LIGHT란!
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
//
//
//-----------------------------------------------------------------------------
namespace CG3D
{

enum LIGHTTYPE
{
	LIGHT_POINT			 = 0,			// Point light
	LIGHT_SPOT			 = 1,			// Spot light
	LIGHT_DIRECTIONAL	 = 2,			// Directional light
	LIGHT_FREE			 = 3,			// Free Light
	LIGHT_FORCE_DWORD	 = 0x7fffffff,	// force 32-bit size enum
};

#define	MAX_LIGHT_FACTOR		8

const int	LIGHT_FACTOR_DIRECTION	 = 0;
const int	LIGHT_FACTOR_POSITION	 = 1;
const int	LIGHT_FACTOR_DIFFUSE	 = 2;
const int	LIGHT_FACTOR_SPECULAR	 = 3;
const int	LIGHT_FACTOR_AMBIENT	 = 4;
const int	LIGHT_FACTOR_ATTENUATION = 5;
const int	LIGHT_FACTOR_SPOTEFFECT	 = 6;


class LIGHT : public FACTOR_ARRAY<MAX_LIGHT_FACTOR>
{
public:
			//VECTOR3				Direction;		// Direction
			//float				Direction_W;	// 

			//VECTOR3				Position;		// Position
			//float				Position_W;		// 

			//COLOR4				Diffuse;		// Diffuse color
			//COLOR4				Specular;		// Specular color
			//COLOR4				Ambient;		// Ambient color
			//VECTOR4				Attenuation;	// attenuation
			//VECTOR4				SpotEffect;		// FallOff, Theta, Phi -> For Spot light

			float				fRange;			// Range (-1.0f/Attenuation.y)
			LIGHTTYPE			Type;			// Type of light source
			DWORD				flagLighting;	// Light ID로 Object와 Bit연산에 쓰임.
			BOOL				bMakeShadow;	// 그림자를 만듭니까?
			BOOL				bEnabled;		// Light 켜고/끄고

public:
			LIGHT()														{}
			LIGHT(BOOL p_Use) : bEnabled(p_Use)							{	Reset();}

			void				Reset();

			void				Modify(MATRIX* p_pTransformMatrix);
			void				SetLocation(MATRIX* p_Matrix);

			void				UpdateRange();
			void				SetAttenuation(float p_fLinear, float p_fQuardra);
			//void				SetAttenuationRange(float p_fRadius, float p_fRatio=2.0f);
			void				SetIntensity(float p_fScale);
			void				SetDirection(const VECTOR3& _v3Direction);
			void				SetPosition(const VECTOR3& _v3Direction);

			void				ApplyLightForPPL();
			void				ApplyLightForLightingPrePass(CG3DApplier::CCamera* p_pCamera);
			void				ApplyLightForShadowVolume(const CG3DApplier::CCamera* p_pCamera);

			BOOL				IsInViewfrustum();
			void				SetDefaultForDirectional();
			void				SetDefaultForSpot();
			void				SetDefaultForPoint();
public:
			LIGHT&				operator*=(float _Rhs)					{	SetIntensity(_Rhs); return *this;}
			LIGHT				operator*(float _Rhs)					{	CG3D::LIGHT temp=*this; temp.SetIntensity(_Rhs); return temp;}

};


}