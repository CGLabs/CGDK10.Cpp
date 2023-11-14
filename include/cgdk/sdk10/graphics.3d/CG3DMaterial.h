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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// 1. CG3D::MATERIAL��!
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
