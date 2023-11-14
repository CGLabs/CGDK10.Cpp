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
// Generalized Scenenode
//
//-----------------------------------------------------------------------------
//template<class TA=ICG3DSceneNode, class TB = ICG3DModifier, class TC = ICG3DRenderer, class TD = void>
//class SCENENODE {};
//
//template<class TSCENENODE>
//class SCENENODE<TSCENENODE, typename std::enable_if<std::is_base_of<ICG3DSceneNode, TSCENENODE>::value>::type> : public CG3DScenenode::CBase<TSCENENODE> {};
//template<class TMODIFIER>
//class SCENENODE<TMODIFIER, typename std::enable_if<std::is_base_of<ICG3DModifier, TMODIFIER>::value>::type> : public CG3DScenenode::CBase<ICG3DSceneNode, TMODIFIER> {};
//template<class TRENDERER>
//class SCENENODE<TRENDERER, typename std::enable_if<std::is_base_of<ICG3DRenderer, TRENDERER>::value>::type> : public CG3DScenenode::CRenderer<ICG3DSceneNode, ICG3DModifier, TRENDERER> {};
//
//
//template<class TSCENENODE, class TMODIFIER>
//class SCENENODE<TSCENENODE, TMODIFIER, typename std::enable_if<std::is_base_of<ICG3DSceneNode, TSCENENODE>::value && std::is_base_of<ICG3DModifier, TMODIFIER>::value>::type> : public CG3DScenenode::CBase<TSCENENODE, TMODIFIER>{};
//template<class TMODIFIER, class TSCENENODE>
//class SCENENODE<TSCENENODE, TMODIFIER, typename std::enable_if<std::is_base_of<ICG3DSceneNode, TSCENENODE>::value && std::is_base_of<ICG3DModifier, TMODIFIER>::value>::type> : public CG3DScenenode::CBase<TSCENENODE, TMODIFIER>{};
//
//template<class TSCENENODE, class TRENDERER>
//class SCENENODE<TSCENENODE, TRENDERER, typename std::enable_if<std::is_base_of<ICG3DSceneNode, TSCENENODE>::value && std::is_base_of<ICG3DRenderer, TRENDERER>::value>::type> : public CG3DScenenode::CRenderer<TSCENENODE, ICG3DModifier, TRENDERER>{};
//template<class TRENDERER, class TSCENENODE>
//class SCENENODE<TSCENENODE, TRENDERER, typename std::enable_if<std::is_base_of<ICG3DSceneNode, TSCENENODE>::value && std::is_base_of<ICG3DRenderer, TRENDERER>::value>::type> : public CG3DScenenode::CRenderer<TSCENENODE, ICG3DModifier, TRENDERER>{};
//
//template<class TMODIFIER, class TRENDERER>
//class SCENENODE<TMODIFIER, TRENDERER, typename std::enable_if<std::is_base_of<ICG3DModifier, TMODIFIER>::value && std::is_base_of<ICG3DRenderer, TRENDERER>::value>::type> : public CG3DScenenode::CRenderer<ICG3DSceneNode, ICG3DModifier, TRENDERER> {};
//template<class TRENDERER, class TMODIFIER>
//class SCENENODE<TMODIFIER, TRENDERER, typename std::enable_if<std::is_base_of<ICG3DModifier, TMODIFIER>::value && std::is_base_of<ICG3DRenderer, TRENDERER>::value>::type> : public CG3DScenenode::CRenderer<ICG3DSceneNode, ICG3DModifier, TRENDERER> {};
//
//
//template<class TSCENENODE, class TMODIFIER, class TRENDERER>
//class SCENENODE<TSCENENODE, TMODIFIER, TRENDERER, typename std::enable_if<std::is_base_of<ICG3DSceneNode, TSCENENODE>::value && std::is_base_of<ICG3DModifier, TMODIFIER>::value && std::is_base_of<ICG3DRenderer, TRENDERER>::value>::type> : public CG3DScenenode::CRenderer<TSCENENODE, TMODIFIER, TRENDERER>{};
//template<class TSCENENODE, class TRENDERER, class TMODIFIER>
//class SCENENODE<TSCENENODE, TMODIFIER, TRENDERER, typename std::enable_if<std::is_base_of<ICG3DSceneNode, TSCENENODE>::value && std::is_base_of<ICG3DModifier, TMODIFIER>::value && std::is_base_of<ICG3DRenderer, TRENDERER>::value>::type> : public CG3DScenenode::CRenderer<TSCENENODE, TMODIFIER, TRENDERER>{};
//template<class TMODIFIER, class TRENDERER, class TSCENENODE>
//class SCENENODE<TSCENENODE, TMODIFIER, TRENDERER, typename std::enable_if<std::is_base_of<ICG3DSceneNode, TSCENENODE>::value && std::is_base_of<ICG3DModifier, TMODIFIER>::value && std::is_base_of<ICG3DRenderer, TRENDERER>::value>::type> : public CG3DScenenode::CRenderer<TSCENENODE, TMODIFIER, TRENDERER>{};
//template<class TMODIFIER, class TSCENENODE, class TRENDERER>
//class SCENENODE<TSCENENODE, TMODIFIER, TRENDERER, typename std::enable_if<std::is_base_of<ICG3DSceneNode, TSCENENODE>::value && std::is_base_of<ICG3DModifier, TMODIFIER>::value && std::is_base_of<ICG3DRenderer, TRENDERER>::value>::type> : public CG3DScenenode::CRenderer<TSCENENODE, TMODIFIER, TRENDERER>{};
//template<class TRENDERER, class TSCENENODE, class TMODIFIER>
//class SCENENODE<TSCENENODE, TMODIFIER, TRENDERER, typename std::enable_if<std::is_base_of<ICG3DSceneNode, TSCENENODE>::value && std::is_base_of<ICG3DModifier, TMODIFIER>::value && std::is_base_of<ICG3DRenderer, TRENDERER>::value>::type> : public CG3DScenenode::CRenderer<TSCENENODE, TMODIFIER, TRENDERER>{};
//template<class TRENDERER, class TMODIFIER, class TSCENENODE>
//class SCENENODE<TSCENENODE, TMODIFIER, TRENDERER, typename std::enable_if<std::is_base_of<ICG3DSceneNode, TSCENENODE>::value && std::is_base_of<ICG3DModifier, TMODIFIER>::value && std::is_base_of<ICG3DRenderer, TRENDERER>::value>::type> : public CG3DScenenode::CRenderer<TSCENENODE, TMODIFIER, TRENDERER>{};
//
//
