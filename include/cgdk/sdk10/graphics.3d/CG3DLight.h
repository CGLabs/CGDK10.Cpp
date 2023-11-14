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
// 1. CG3D::LIGHT��!
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
			DWORD				flagLighting;	// Light ID�� Object�� Bit���꿡 ����.
			BOOL				bMakeShadow;	// �׸��ڸ� ����ϱ�?
			BOOL				bEnabled;		// Light �Ѱ�/����

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