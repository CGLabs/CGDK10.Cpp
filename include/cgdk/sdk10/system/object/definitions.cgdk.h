//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                                  Common                                   *
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
//-----------------------------------------------------------------------------
/**

	object_ptr
 
*/
//-----------------------------------------------------------------------------
namespace CGDK
{

//----------------------------------------------------------------------------
// CGDK
//----------------------------------------------------------------------------
enum class eCOMPILER : uint64_t
{
	NOT_DEFINED					 = 0x0000000000000000,
	VISUALSTUDIO_8				 = 0x0000000000000001,
	VISUALSTUDIO_9				 = 0x0000000000000002,
	VISUALSTUDIO_10				 = 0x0000000000000004,
	VISUALSTUDIO_11				 = 0x0000000000000008,
	VISUALSTUDIO_12				 = 0x0000000000000010,
	VISUALSTUDIO_14				 = 0x0000000000000020,
	VISUALSTUDIO_15				 = 0x0000000000000040,
	VISUALSTUDIO_16				 = 0x0000000000000080,
	VISUALSTUDIO_17				 = 0x0000000000000100,
	ECLIPS						 = 0x0000000000010000,
	GCC							 = 0x0000000000020000,
	ALL							 = 0xffffffffffffffff
};

enum class eCONFIGURATION : uint64_t
{
	NOT_DEFINED					 = 0x0000000000000000,
	DEBUG_						 = 0x0000000000000001,
	DEBUG_DLL_					 = 0x0000000000000002,
	RELEASE_					 = 0x0000000000000004,
	RELEASE_DLL_				 = 0x0000000000000008,
	ALL_						 = 0xffffffffffffffff
};

enum class ePLATFORM : uint64_t
{
	NOT_DEFINED					 = 0x0000000000000000,
	WINDOWS_X86					 = 0x0000000000000001,
	WINDOWS_X64					 = 0x0000000000000002,
	LINUX						 = 0x0000000000000004,
	ANDROID						 = 0x0000000000000008,
	MACOS						 = 0x0000000000000010,
	IOS							 = 0x0000000000000020,
	ALL							 = 0xffffffffffffffff
};

// 4) component info
struct sCOMPONENT
{
public:
	// 1) name
	std::string					name;

	// 2) version
	uint64_t					version_package = 0;
	uint64_t					version_sub = 0;
	uint64_t					version_build = 0;
	chrono::time::utc::time_point time_build;

	// 3) revision/compiler/configuration
	eCOMPILER					compiler = eCOMPILER::NOT_DEFINED;
	ePLATFORM					platform = ePLATFORM::NOT_DEFINED;
	eCONFIGURATION				configuration = eCONFIGURATION::NOT_DEFINED;

	chrono::time::utc::time_point time_create;

	// enable struct serialize
	ENABLE_STRUCT_SERIALIZABLE
};

struct sCOMPONENT_INFO
{
public:
	// 1) component info
	sCOMPONENT					component_info;

	// enable struct serialize
	ENABLE_STRUCT_SERIALIZABLE
};


}


//----------------------------------------------------------------------------
// CGDK functions
//----------------------------------------------------------------------------
namespace CGDK
{
	[[nodiscard]] int											get_version() noexcept;
	[[nodiscard]] const std::vector<sCOMPONENT_INFO>&			get_component_info() noexcept;
	[[nodiscard]] sCOMPONENT_INFO								get_component_info(std::string_view _name) noexcept;

	template <class T>	[[nodiscard]] std::basic_string_view<T> to_string(eCOMPILER _compiler) noexcept;
	template <class T>	[[nodiscard]] std::basic_string_view<T> to_string(eCONFIGURATION _configuration) noexcept;
	template <class T>	[[nodiscard]] std::basic_string_view<T> to_string(ePLATFORM _platform) noexcept;
}
