//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                              object classes                               *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                (c) 2003. Cho Sanghyun. All right reserved.                *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once

namespace CGDK
{
//-----------------------------------------------------------------------------
/**

@class		File System
@brief		'�ڿ� ��ü'�� �����ϴ� Ŭ����
@todo		
@ref		
@details	\n
'�ڿ� ��ü'�� ����� �����ϴ� Ŭ�����̴�.
��Ŭ������ �����Ǿ� �ִ�.

*/
//-----------------------------------------------------------------------------
namespace api
{
namespace file
{
	buffer_view		read(FILE_HANDLE _handle_file, buffer_view _buffer) noexcept;
	buffer_view		write(FILE_HANDLE _handle_file, buffer_view _buffer) noexcept;
	shared_buffer	read (std::string_view _filename, eFILE_LOCATION _file_location = eFILE_LOCATION::DEFAULT) noexcept;
	buffer_view		write(std::string_view _filename, buffer_view _buffer, eFILE_LOCATION _file_location = eFILE_LOCATION::DEFAULT) noexcept;

	[[nodiscard]] std::string make_full_path(std::string_view _path, std::string_view _file_name);
}
}


}