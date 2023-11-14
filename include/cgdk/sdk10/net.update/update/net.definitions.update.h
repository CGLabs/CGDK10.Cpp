//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                          network update classes                           *
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
//----------------------------------------------------------------------------
//
// Definitions
//
//----------------------------------------------------------------------------
namespace CGDK
{
	namespace update
	{
		using UPDATABLE_ID		 = uint64_t;
		using RECEIVER_ID		 = uint64_t;
		using SENDER_ID			 = uint64_t;
		using UPDATE_RESOURCE_ID = uint64_t;

		struct sUPDATE_VERSION
		{
			int32_t	major = 0;
			int32_t	minor = 0;
		};

		const size_t _FILE_BLOCK_SIZE = (65536 * 16);

		struct sUPDATE_REQUEST_INFO
		{
			int32_t				total_count = 0;
			int64_t				total_bytes = 0;
		};
	}

	namespace resource
	{
		enum class eTYPE : int
		{
			NONE = 0,
			FILE = 1,
			FOLDER = 2,
			REFERENCE = 3,
		};

		enum class eFILE_FLAG : uint32_t
		{
			NONE = 0,
			RECREATE = 1,
		};
		[[nodiscard]] inline eFILE_FLAG operator |  (const eFILE_FLAG& _lhs, const eFILE_FLAG& _rhs) noexcept { return eFILE_FLAG(static_cast<uint32_t>(_lhs) | static_cast<uint32_t>(_rhs)); }
		[[nodiscard]] inline eFILE_FLAG operator &  (const eFILE_FLAG& _lhs, const eFILE_FLAG& _rhs) noexcept { return eFILE_FLAG(static_cast<uint32_t>(_lhs) & static_cast<uint32_t>(_rhs)); }
		[[nodiscard]] inline eFILE_FLAG operator ^  (const eFILE_FLAG& _lhs, const eFILE_FLAG& _rhs) noexcept { return eFILE_FLAG(static_cast<uint32_t>(_lhs) ^ static_cast<uint32_t>(_rhs)); }

		enum class eOPTION : uint64_t
		{
			NONE = 0,
			BLOCK_COMPRESSED = 1,
			STREAM = 2,
			RECURSIVE = 3,
			REMOVE = 4,
			REMOVE_FOLDER = 5,
			FIND = 6,
			MOVE = 7,
		};
		[[nodiscard]] inline eOPTION operator |  (const eOPTION& _lhs, const eOPTION& _rhs) noexcept { return eOPTION(static_cast<uint64_t>(_lhs) | static_cast<uint64_t>(_rhs)); }
		[[nodiscard]] inline eOPTION operator &  (const eOPTION& _lhs, const eOPTION& _rhs) noexcept { return eOPTION(static_cast<uint64_t>(_lhs) & static_cast<uint64_t>(_rhs)); }
		[[nodiscard]] inline eOPTION operator ^  (const eOPTION& _lhs, const eOPTION& _rhs) noexcept { return eOPTION(static_cast<uint64_t>(_lhs) ^ static_cast<uint64_t>(_rhs)); }
		[[nodiscard]] inline eOPTION operator ~  (const eOPTION& _rhs) noexcept { return eOPTION(~static_cast<uint64_t>(_rhs)); }

		struct sUPDATABLE_FILE_META_INFO
		{
			ENABLE_STRUCT_SERIALIZABLE

			update::UPDATABLE_ID		id = 0;
			uint64_t					size = 0;
			uint64_t					block_size = update::_FILE_BLOCK_SIZE;

			eTYPE						type = eTYPE::NONE;
			eFILE_FLAG					flag = eFILE_FLAG::NONE;
			std::string					path;
			std::string					filename;

			std::filesystem::file_time_type time_write;
		};


		struct sMETA_FILE_BLOCK
		{
			update::UPDATABLE_ID		id = 0;

			uint64_t					pos = 0;
			uint64_t					size = 0;

			eOPTION						flag = eOPTION::NONE;
		};
	}

	struct sUPDATABLE_PREPARE_INFO
	{
		ENABLE_STRUCT_SERIALIZABLE

		uint64_t					size = 0;
		MD5							check_code;
		eRESULT						result = eRESULT::SUCCESS;
	};

	struct sUPDATABLE_FILE_COMPLETION_INFO
	{
		ENABLE_STRUCT_SERIALIZABLE

		update::UPDATABLE_ID		id = 0;
		MD5							check_code;
	};

	struct resource_pos_src
	{
		std::string path_base;
		std::string path;
		std::string filename;
	};

	struct resource_pos_dst
	{
		std::string path;
		std::string filename;
	};

	struct sINITIALIZE_INFO_UPDATABLE_RESOURCE
	{
		resource_pos_src src;
		resource_pos_dst dst;
		resource::eOPTION options = resource::eOPTION::RECURSIVE;
		uint64_t block_size = update::_FILE_BLOCK_SIZE;
	};
}

