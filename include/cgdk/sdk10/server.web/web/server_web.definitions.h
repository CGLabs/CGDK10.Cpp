//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 9.0 / Release 2017.01.03                        *
//*                                                                           *
//*                           Network Base Classes                            *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                 (c) 2016 Cho Sanghyun All right reserved.                 *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once

namespace CGDK
{
//----------------------------------------------------------------------------
//  Disable Warnning
//
// 1) Warnning C4250 Disable
//    - C4250은 다중 상속의 virtual 상속된 interface에 대해서 어떤 것을 선택
//      했는지에 대해서 표시해주는 Warnning이다. 이 부분에 대한 표시가
//      필요 없으므로 이 부분은 Disable한다.
//----------------------------------------------------------------------------
namespace server
{
namespace web
{

enum class eENTITY_TYPE : uint32_t
{
	// 1) none
	NONE					 = 0x00000000,

	// 2) text
	TEXT					 = 0x00010000,
	TEXT_HTML				 = 0x00010001,
	TEXT_CSS				 = 0x00010002,
	TEXT_PLAIN				 = 0x00010003,

	// 3) application
	APPLICATION				 = 0x00020000,
	APPLICATION_SCRIPT		 = 0x00020001,

	// 4) resourrce
	RESOURCE				 = 0x00030000,

	//   - resource file
	RESOURCE_FILE			 = 0x00031000,

	//   - resourceimage
	RESOURCE_IMAGE			 = 0x00032000,
	RESOURCE_IMAGE_BMP		 = 0x00032001,
	RESOURCE_IMAGE_GIF		 = 0x00032002,
	RESOURCE_IMAGE_JPEG		 = 0x00032003,
	RESOURCE_IMAGE_PNG		 = 0x00032004,
	RESOURCE_IMAGE_ETC		 = 0x00032005,

	//   - resourceaudio
	RESOURCE_AUDIO			 = 0x00033000,
	RESOURCE_AUDIO_WAV		 = 0x00033001,
	RESOURCE_AUDIO_XWAV		 = 0x00033002,
	RESOURCE_AUDIO_XPNWAV	 = 0x00033003,
	RESOURCE_AUDIO_MP3		 = 0x00033004,
	RESOURCE_AUDIO_OGG		 = 0x00033005,
	RESOURCE_AUDIO_WEBM		 = 0x00033006,

	//   - resource video
	RESOURCE_VIDEO			 = 0x00034000,
	RESOURCE_VIDEO_MOV		 = 0x00034001,
	RESOURCE_VIDEO_MPEG		 = 0x00034002,
	RESOURCE_VIDEO_AVI		 = 0x00034003,
	RESOURCE_VIDEO_OGG		 = 0x00034004,
	RESOURCE_VIDEO_WEBM		 = 0x00034005,

	// 5) folder
	FOLDER					 = 0x00040000,

};

struct sWEB_SERVER_CONTEXT
{
	std::string_view		server_name { "CGCII" };
	uint32_t				server_version_high { 1 };
	uint32_t				server_version_low { 0 };
};


}
}
}