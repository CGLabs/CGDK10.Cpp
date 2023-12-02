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

*/
//-----------------------------------------------------------------------------
#if defined(_WIN32)
	using CGHANDLE = HANDLE;
	using FILE_HANDLE = HANDLE;
	using THREAD_HANDLE = HANDLE;
	const FILE_HANDLE	INVALID_FILE_HANDLE		 = INVALID_HANDLE_VALUE;
	const HANDLE		INVALID_CGHANDLE_VALUE	 = INVALID_HANDLE_VALUE;
#elif defined(__ANDROID__)
	#include <android/native_activity.h>
	using CGHANDLE = int;
	struct FILE_HANDLE
	{
	public:
		AAsset*			hRead;
		FILE*			hWrite;

	public:
		FILE_HANDLE() : hRead(nullptr), hWrite(nullptr)	{}
		FILE_HANDLE(const FILE_HANDLE& _copy) : hRead(_copy.hRead), hWrite(_copy.hWrite) {}
		FILE_HANDLE(AAsset* _Asset) : hRead(_Asset), hWrite(nullptr) {}
		FILE_HANDLE(FILE* _pFile) : hRead(nullptr), hWrite(_pFile) {}
		FILE_HANDLE(AAsset* _Asset, FILE* _pFile) : hRead(_Asset), hWrite(_pFile) {}
	public:
		[[nodiscard]] bool operator == (const FILE_HANDLE& _rhs) { return _rhs.hRead==hRead && _rhs.hWrite==hWrite;}
		[[nodiscard]] bool operator != (const FILE_HANDLE& _rhs) { return _rhs.hRead!=hRead || _rhs.hWrite!=hWrite;}

		FILE_HANDLE&	operator = (AAsset* _rhs) { hRead=_rhs; return *this;}
		FILE_HANDLE&	operator = (FILE* _rhs) { hWrite=_rhs; return *this;}

		[[nodiscard]]	operator const AAsset*() const { return hRead;}
		[[nodiscard]]	operator AAsset*() { return hRead;}
		[[nodiscard]]	operator const FILE*() const { return hWrite;}
		[[nodiscard]]	operator FILE*() { return hWrite;}
		[[nodiscard]]	operator bool() { return hRead!=nullptr || hWrite!=nullptr;}
	};
	using THREAD_HANDLE = uint64_t;
	const FILE_HANDLE	INVALID_FILE_HANDLE		 = FILE_HANDLE();
	const CGHANDLE		INVALID_CGHANDLE_VALUE	 = -1;

#elif defined(__APPLE__)
	using CGHANDLE		= CGHANDLE;
	using FILE_HANDLE	= uint64_t;
	using THREAD_HANDLE	= uint64_t;
	const FILE_HANDLE	INVALID_FILE_HANDLE		 = ((FILE_HANDLE)nullptr);
	const CGHANDLE		INVALID_CGHANDLE_VALUE	 = -1;

#elif defined(__linux__)
	using CGHANDLE		= int;
	using FILE_HANDLE	= FILE*;
	using THREAD_HANDLE	= __gthread_t;
	const FILE_HANDLE	INVALID_FILE_HANDLE		 = ((FILE_HANDLE)nullptr);
	const int			INVALID_CGHANDLE_VALUE	 = -1;
#else
	#error "[CGDK10] Not supported platform"
#endif

//-----------------------------------------------------------------------------
/**

@class		File Operation

*/
//-----------------------------------------------------------------------------
enum class eFILE_OPERATION : uint32_t
{
	NONE			 = 0,
	READ			 = 1,
	WRITE			 = 2,
	APPEND			 = 3,
	UPDATE			 = 4,
	READ_ASYNC		 = 5,
	WRITE_ASYNC		 = 6,
	APPEND_ASYNC	 = 7,
	MAX
};

enum class eFILE_ORIGIN : int32_t
{
	BEGIN			 = 0,
	CURRENT			 = 1,
	END				 = 2
};

enum class eFILE_LOCATION : uint32_t
{
	NONE			 = 0,
	NOW				 = 0x0001,
	RESOURCE		 = 0x0002,
	SYSTEM			 = 0x0004,
	INTERNAL		 = 0x0008,
	EXTERNAL		 = 0x0010,

	DEFAULT			 = NOW,
};
[[nodiscard]] inline eFILE_LOCATION operator & (const eFILE_LOCATION& a, const eFILE_LOCATION& b)	{ return eFILE_LOCATION(((uint32_t)a) & (uint32_t)b); }
[[nodiscard]] inline eFILE_LOCATION operator & (const eFILE_LOCATION& a, uint32_t b)				{ return eFILE_LOCATION(((uint32_t)a) & (uint32_t)b); }
[[nodiscard]] inline eFILE_LOCATION operator | (const eFILE_LOCATION& a, const eFILE_LOCATION& b)	{ return eFILE_LOCATION(((uint32_t)a) | (uint32_t)b); }
[[nodiscard]] inline eFILE_LOCATION operator | (const eFILE_LOCATION& a, uint32_t b)				{ return eFILE_LOCATION(((uint32_t)a) | (uint32_t)b); }


namespace api
{
namespace file
{
	[[nodiscard]] FILE_HANDLE	open (const std::filesystem::path&, eFILE_OPERATION _operation, eFILE_LOCATION _file_location=eFILE_LOCATION::NOW) noexcept;
	void						close (FILE_HANDLE _handle_file) noexcept;
	size_t						read (FILE_HANDLE _handle_file, size_t _size, void* _data) noexcept;
	size_t						write (FILE_HANDLE _handle_file, size_t _size, const void* _data) noexcept;
	size_t						seek (FILE_HANDLE _handle_file, size_t _offset, eFILE_ORIGIN _origin = eFILE_ORIGIN::BEGIN) noexcept;
	[[nodiscard]] size_t		get_length (FILE_HANDLE _handle_file) noexcept;
	[[nodiscard]] size_t		get_length(const std::filesystem::path& _filename) noexcept;
	bool						truncate (FILE_HANDLE _handle_file, size_t _length) noexcept;
	bool						truncate (FILE_HANDLE _handle_file) noexcept;

	std::filesystem::file_time_type get_last_write_time(const std::filesystem::path& _filename);
	void						set_last_write_time(const std::filesystem::path& _filename, std::filesystem::file_time_type _write_time);
}
}

}