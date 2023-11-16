//*****************************************************************************
//*                                                                           *
//*                               project GRUMA                               *
//*                                                                           *
//*                               notify server                               *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                  ¨Ï2017. Cho SangHyun. All rights reserved                *
//*                          http://www.CGCIII.co.kr                          *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//  definitions
//-----------------------------------------------------------------------------
const uint32_t	CGNOTIFY_SERVER_UPDATE					 = (eMESSAGE::USER | 1);
const uint32_t	CGNOTIFY_SOCKET_USER_ADD				 = (eMESSAGE::USER | 2);
const uint32_t	CGNOTIFY_SOCKET_USER_REMOVE				 = (eMESSAGE::USER | 3);
const uint32_t	CGNOTIFY_SOCKET_USER_UPDATE				 = (eMESSAGE::USER | 4);
const uint32_t	CGNOTIFY_UPDATABLE_RESOURCE_ADD			 = (eMESSAGE::USER | 5);
const uint32_t	CGNOTIFY_UPDATABLE_RESOURCE_REMOVE		 = (eMESSAGE::USER | 6);
const uint32_t	CGNOTIFY_UPDATABLE_RESOURCE_UPDATE		 = (eMESSAGE::USER | 7);


//-----------------------------------------------------------------------------
//
// defintion
//
//-----------------------------------------------------------------------------
