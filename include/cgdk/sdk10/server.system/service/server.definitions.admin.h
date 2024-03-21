

//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                           Server Admin Classes                            *
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
//-----------------------------------------------------------------
// admin_client info (Server의 정보)
//-----------------------------------------------------------------
#pragma pack(1)


#if defined(__linux__)
using  LPSERVICE_MAIN_FUNCTIONA = void*;
#endif

namespace CGDK
{
//-----------------------------------------------------------------
// definitions
//-----------------------------------------------------------------
#if defined(_WIN32)

#elif defined(__linux)
	#define	WINAPI
	#if !defined(CALLBACK)
		#define CALLBACK __stdcall
	#endif
	#define	__callback

	#define MAX_PATH								260

	// Controls
	#define SERVICE_CONTROL_STOP					0x00000001
	#define SERVICE_CONTROL_PAUSE					0x00000002
	#define SERVICE_CONTROL_CONTINUE				0x00000003
	#define SERVICE_CONTROL_INTERROGATE				0x00000004
	#define SERVICE_CONTROL_SHUTDOWN				0x00000005
	#define SERVICE_CONTROL_PARAMCHANGE				0x00000006
	#define SERVICE_CONTROL_NETBINDADD				0x00000007
	#define SERVICE_CONTROL_NETBINDREMOVE			0x00000008
	#define SERVICE_CONTROL_NETBINDENABLE			0x00000009
	#define SERVICE_CONTROL_NETBINDDISABLE			0x0000000A
	#define SERVICE_CONTROL_DEVICEEVENT				0x0000000B
	#define SERVICE_CONTROL_HARDWAREPROFILECHANGE	0x0000000C
	#define SERVICE_CONTROL_POWEREVENT				0x0000000D
	#define SERVICE_CONTROL_SESSIONCHANGE			0x0000000E
	#define SERVICE_CONTROL_PRESHUTDOWN				0x0000000F
	#define SERVICE_CONTROL_TIMECHANGE				0x00000010
	#define SERVICE_CONTROL_TRIGGEREVENT			0x00000020

	// begin_wdm
	#define DELETE									(0x00010000L)
	#define READ_CONTROL							(0x00020000L)
	#define WRITE_DAC								(0x00040000L)
	#define WRITE_OWNER								(0x00080000L)
	#define SYNCHRONIZE								(0x00100000L)
	#define STANDARD_RIGHTS_REQUIRED				(0x000F0000L)
	#define STANDARD_RIGHTS_READ					(READ_CONTROL)
	#define STANDARD_RIGHTS_WRITE					(READ_CONTROL)
	#define STANDARD_RIGHTS_EXECUTE					(READ_CONTROL)
	#define STANDARD_RIGHTS_ALL						(0x001F0000L)
	#define SPECIFIC_RIGHTS_ALL						(0x0000FFFFL)

	// Service object specific access type
	#define SERVICE_QUERY_CONFIG					0x0001
	#define SERVICE_CHANGE_CONFIG					0x0002
	#define SERVICE_QUERY_STATUS					0x0004
	#define SERVICE_ENUMERATE_DEPENDENTS			0x0008
	#define SERVICE_START							0x0010
	#define SERVICE_STOP							0x0020
	#define SERVICE_PAUSE_CONTINUE					0x0040
	#define SERVICE_INTERROGATE						0x0080
	#define SERVICE_USER_DEFINED_CONTROL			0x0100
	#define SERVICE_ALL_ACCESS						(STANDARD_RIGHTS_REQUIRED     | \
													 SERVICE_QUERY_CONFIG         | \
													 SERVICE_CHANGE_CONFIG        | \
													 SERVICE_QUERY_STATUS         | \
													 SERVICE_ENUMERATE_DEPENDENTS | \
													 SERVICE_START                | \
													 SERVICE_STOP                 | \
													 SERVICE_PAUSE_CONTINUE       | \
													 SERVICE_INTERROGATE          | \
													 SERVICE_USER_DEFINED_CONTROL)

	// Service Types (Bit Mask)
	#define SERVICE_KERNEL_DRIVER					0x00000001
	#define SERVICE_FILE_SYSTEM_DRIVER				0x00000002
	#define SERVICE_ADAPTER							0x00000004
	#define SERVICE_RECOGNIZER_DRIVER				0x00000008
	#define SERVICE_DRIVER							(SERVICE_KERNEL_DRIVER | \
													 SERVICE_FILE_SYSTEM_DRIVER | \
													 SERVICE_RECOGNIZER_DRIVER)
	#define SERVICE_WIN32_OWN_PROCESS				0x00000010
	#define SERVICE_WIN32_SHARE_PROCESS				0x00000020
	#define SERVICE_WIN32							 (SERVICE_WIN32_OWN_PROCESS | \
													  SERVICE_WIN32_SHARE_PROCESS)
	#define SERVICE_INTERACTIVE_PROCESS				0x00000100
	#define SERVICE_TYPE_ALL			            (SERVICE_WIN32  | \
													 SERVICE_ADAPTER | \
													 SERVICE_DRIVER  | \
													 SERVICE_INTERACTIVE_PROCESS)

	// start type
	#define SERVICE_BOOT_START						0x00000000
	#define SERVICE_SYSTEM_START					0x00000001
	#define SERVICE_AUTO_START						0x00000002
	#define SERVICE_DEMAND_START					0x00000003
	#define SERVICE_DISABLED						0x00000004

	// Error control type
	#define SERVICE_ERROR_IGNORE					0x00000000
	#define SERVICE_ERROR_NORMAL					0x00000001
	#define SERVICE_ERROR_SEVERE					0x00000002
	#define SERVICE_ERROR_CRITICAL					0x00000003

	//struct SYSTEM_INFO
	//{
	//};

	// temporary) 
	#define	PDH_FMT_1000	0

	using HQUERY = int;
	using LPHANDLER_FUNCTION_EX = int*;
	using LPSERVICE_STATUS = int*;
	using SERVICE_STATUS_HANDLE = int;
#endif


namespace server_admin
{
	//-----------------------------------------------------------------------------
	/**

	@class		iid_t (instance id)
	@brief		
	@todo
	@ref		sSETTING_INFO, sSERVICE_INSTANCE_INFO
	@details	\n

	*/
	//-----------------------------------------------------------------------------
	// 1) instance id (매번 객체화될 때마다 할당되는 id이다. (0:비객체화, >0:객체화))
	typedef uint64_t iid_t;


	//-----------------------------------------------------------------------------
	/**

	@class		sRANK
	@brief		설정 정보의 기본 내용
	@todo
	@ref		sHOST_SETTING_INFO, sSERVICE_INSTANCE_INFO, SERVICE_SETTING
	@details	\n

	*/
	//-----------------------------------------------------------------------------
	// 1) instance의 타입
	namespace eINSTANCE_TYPE
	{
		constexpr static int NONE = 0;
		constexpr static int HOST = 1;
		constexpr static int SERVICE = 2;
		constexpr static int ADMIN_SERVER = 3;
		constexpr static int ADMON_CIENT = 4;
	};

	// 2) revision
	struct sREVISION
	{
		ENABLE_STRUCT_SERIALIZABLE

		std::string			url;						// - URL
		int64_t				revision{ 0 };				// - version
		chrono::time::utc::time_point time;				// - time
	};

	// 3) rank(역할)
	struct sRANK
	{
		// 1) group/field
		int32_t				group{ 0 };
		int32_t				field{ 0 };

		// 2) role/Index
		int32_t				role{ 0 };
		int32_t				index{ 0 };

		// function)
		bool				empty() const noexcept { return this->group == 0 && this->field == 0 && this->role == 0 && this->index == 0; }
		bool				exist() const noexcept { return !this->empty(); }
		void				clear() noexcept;

		std::string			to_string() const { return NFMT::format("{}.{}.{}.{}"sv, group, field, role, index); }
	};
	inline bool operator == (const sRANK& _lhs, const sRANK& _rhs) noexcept { return _lhs.group == _rhs.group && _lhs.field == _rhs.field && _lhs.role == _rhs.role && _lhs.index == _rhs.index; }
	inline bool operator != (const sRANK& _lhs, const sRANK& _rhs) noexcept { return !(_lhs == _rhs); }
	inline bool operator >  (const sRANK& _lhs, const sRANK& _rhs) noexcept { return (_lhs.group > _rhs.group) ? true : (_lhs.group < _rhs.group) ? false : (_lhs.field > _rhs.field) ? true : (_lhs.field < _rhs.field) ? false : (_lhs.role > _rhs.role) ? true : (_lhs.role < _rhs.role) ? false : (_lhs.index > _rhs.index); }
	inline bool operator <= (const sRANK& _lhs, const sRANK& _rhs) noexcept { return !(_lhs > _rhs); }
	inline bool operator <  (const sRANK& _lhs, const sRANK& _rhs) noexcept { return  (_rhs > _lhs); }
	inline bool operator >= (const sRANK& _lhs, const sRANK& _rhs) noexcept { return !(_lhs > _rhs); }

	//-----------------------------------------------------------------------------
	/**

	@class		sCERTIFY_INFO
	@brief		네트워크로 송수신 시 사용되는 구조체
	@todo
	@ref		sHOST_SETTING_INFO, sSERVICE_INSTANCE_INFO, SERVICE_SETTING
	@details	\n

	*/
	//-----------------------------------------------------------------------------
	// 2) 인증 종류
	struct sCERTIFY_INFO
	{
		ENABLE_STRUCT_SERIALIZABLE

		int					 instance_type{ eINSTANCE_TYPE::NONE };
	};


	//-----------------------------------------------------------------------------
	/**

	@class		sSERVICE_SETTING_INFO
	@brief		설정 정보의 기본 내용
	@todo
	@ref		sHOST_SETTING_INFO, sSERVICE_INSTANCE_INFO, SERVICE_SETTING
	@details	\n

	*/
	//-----------------------------------------------------------------------------
	// 1. 사용자가 설정할 수 있는 instance 정보들
	struct sSERVICE_SETTING
	{
		ENABLE_STRUCT_SERIALIZABLE

		// 1) instance id
		iid_t				iid{ 0 };					// - sSERVICE_INSTANCE_INFO의 iid값과 같은 값

		// 2) name/comment
		std::string			nickname;
		std::string			comment;

		// 3) setting
		sRANK				rank;						// - server rank (서버 소속(group, field), 서버의 역할 및 순번(role, index), 서버속성(attribute)
		std::array<uint64_t, 8>	parameter{};			// - options
		shared_buffer		buf_configure;				// - configure (JSON setting info)
		shared_buffer		buf_setting;				// - configure (setting info)

		// 4) version
		sREVISION			revision;					// - reversion
		sVERSION_EX			version;					// - version

		// 5) execute info
		std::string			file_execute;				// - execute filename
		std::string			str_path;					// - File Path
		std::string			str_path_working;			// - Working Directory
		shared_buffer		buf_command_line;			// - Commandline(UNICODE, 1 NULL Terminate line, 2 NULL is Terminate Block)
		shared_buffer		buf_environment;			// - Environmennt block(UNICODE, 1 NULL Terminate line, 2 NULL is Terminate Block)

		// funcions)
		bool load(std::string_view _path = "."sv);
		bool load(std::wstring_view _path);
		bool save();
		void clear() noexcept;
	};


	//-----------------------------------------------------------------------------
	/**


	*/
	//-----------------------------------------------------------------------------
	// 1) factory
	struct factory_update_snap
	{
		ENABLE_STRUCT_SERIALIZABLE

		uint64_t				id{ 0};

		int64_t					stacked{ 0 };

		statistics::unit_factory_snap now;
	};

	struct factory_now_snap
	{
		ENABLE_STRUCT_SERIALIZABLE

		std::string				name;

		eFACTORY_TYPE			type{ eFACTORY_TYPE::DEFAULT };

		eOBJECT_TYPE			object_type{ eOBJECT_TYPE::NOT_DEFINED };
		int64_t					object_size{ 0 };

		factory_update_snap		updatable;
		statistics::unit_factory_snap now;
	};

	struct factory_snap
	{
		ENABLE_STRUCT_SERIALIZABLE

		std::string				name;

		eFACTORY_TYPE			type{ eFACTORY_TYPE::DEFAULT };

		eOBJECT_TYPE			object_type{ eOBJECT_TYPE::NOT_DEFINED };
		int64_t					object_size{ 0 };

		factory_update_snap		updatable;
		std::vector<statistics::unit_factory_snap> period;
	};

	// 2) thread
	struct unit_thread
	{
		ENABLE_STRUCT_SERIALIZABLE

		uint64_t				id_thread{ 0};

		uint64_t				count_executed{ 0 };
		uint64_t				count_error{ 0 };

		chrono::tick::time_point tick_last_execute{ chrono::tick::duration::zero() };
		bool					is_executing{ false };
	};
	unit_thread					get_snap(api::Nthread* _pthread) noexcept;
	std::vector<unit_thread>	get_snap(api::manager_thread* _pthread_manager);


	// 3) executor
	struct executor_update_snap
	{
		ENABLE_STRUCT_SERIALIZABLE

		uint64_t				id{ 0 };
		int64_t					count_execute{ 0 };

		std::vector<unit_thread> vector_threads;
	};

	struct executor_snap
	{
		ENABLE_STRUCT_SERIALIZABLE

		std::string				name;
		eEXECUTOR_TYPE			type{ eEXECUTOR_TYPE::USER };

		executor_update_snap	updatable;
	};


	// 4) schedulable
	struct schedulable_update_snap
	{
		ENABLE_STRUCT_SERIALIZABLE

		uint64_t				id{ 0};

		chrono::tick::duration	duration_interval{ chrono::tick::duration::zero() };
		chrono::tick::time_point tick_next{ (chrono::tick::max)() };

		int64_t					count_execute{ 0 };
	};

	struct schedulable_snap
	{
		ENABLE_STRUCT_SERIALIZABLE

		std::string				name;

		eSCHEDULABLE_TYPE		type{ eSCHEDULABLE_TYPE::USER };

		schedulable_update_snap	updatable;
	};

	// 5) connective snap
	struct connective_snap
	{
		ENABLE_STRUCT_SERIALIZABLE

		uint64_t				index{ 0 };
		std::vector<statistics::unit_connective_snap> vector_unit_connective_snap;
	};

	// 6) traffic snap
	struct traffic_snap
	{
		ENABLE_STRUCT_SERIALIZABLE

		uint64_t				index{ 0 };
		std::vector<statistics::unit_traffic_snap> vector_unit_traffic_snap;
	};


	//-----------------------------------------------------------------------------
	/**


	*/
	//-----------------------------------------------------------------------------
	struct connective_status_snap
	{
		ENABLE_STRUCT_SERIALIZABLE

		uint64_t				id{ 0 };			// - id

		chrono::time::utc::time_point time_start;	// - time: start
		chrono::time::utc::time_point time_stop;	// - time: stop
		net::sockaddr			addr_local;			// - address: local(bind)
		eSOCKET_STATE			state{ eSOCKET_STATE::CLOSED };

		int						is_enable{ 0 };		// - 상태정보
	};

	// 3) unit_connective_snap
	struct connective_info_update_snap
	{
		ENABLE_STRUCT_SERIALIZABLE

		connective_status_snap	status;
		statistics::unit_connective_snap now;
	};

	// 2) connective_info_snap
	struct connective_info_snap
	{
		ENABLE_STRUCT_SERIALIZABLE

		std::string				name;
		chrono::time::utc::time_point time_create;

		connective_status_snap	status;

		uint64_t				index{ 0 };
		statistics::unit_connective_snap now;
	};

	// 3) connective_info_store
	struct connective_info_store
	{
		ENABLE_STRUCT_SERIALIZABLE

		std::string				name;
		chrono::time::utc::time_point time_create;

		connective_status_snap	status;

		uint64_t				index{ 0 };
		std::vector<statistics::unit_connective_snap> period;

		const auto& now() const noexcept { return period[index]; }
	};


	//-----------------------------------------------------------------
	// binder
	//-----------------------------------------------------------------
	// 2) socket info (sSOCKET_INFO)
	struct socket_info
	{
		ENABLE_STRUCT_SERIALIZABLE

		static_string<64>		name;					// - name
		CGSOCKET				socket_handle;			// - socket handle

		net::sockaddr			addr_local;				// - address: local(bind)
		net::sockaddr			addr_remote;			// - address: remote

		chrono::time::utc::time_point time_create;		// - time: create
	};

	// 3) socket status (sSOCKET_STATUS)
	struct socket_status
	{
		ENABLE_STRUCT_SERIALIZABLE

		CGSOCKET				id;						// - id (socket handle)
		eSOCKET_STATE			state_socket;			// - Socket State

		chrono::time::utc::time_point time_connect;		// - connect time
		chrono::time::utc::time_point time_close;		// - close time

		statistics::unit_traffic traffic;				// - I/O Status
	};

	// 4) socket info updatable snap
	struct socket_info_update_snap
	{
		ENABLE_STRUCT_SERIALIZABLE

		uint64_t				id{ 0 };

		chrono::time::utc::time_point time_bind;
		chrono::time::utc::time_point time_connect;
		chrono::tick::duration	tick_send { chrono::tick::duration::zero() };
		chrono::tick::duration	tick_receive { chrono::tick::duration::zero() };

		net::sockaddr			addr_local;				// - address: local(bind)
		net::sockaddr			addr_remote;			// - address: remote
		net::sockaddr			addr_public;			// - address: public (accept address of acceptor)

		eSOCKET_STATE			state{ eSOCKET_STATE ::CLOSED};
		uint32_t				flag_socket{ 0 };
		statistics::unit_traffic_snap traffic;
	};

	// 6) socket info snap
	struct socket_info_snap
	{
		ENABLE_STRUCT_SERIALIZABLE

		std::string				name;

		socket_info_update_snap updatable;
	};


	//-----------------------------------------------------------------
	// time_event
	//-----------------------------------------------------------------
	struct time_event_update_snap
	{
		ENABLE_STRUCT_SERIALIZABLE

		uint64_t			id{ 0};

		time_event::sENTITY_SETTING	entity_setting;
		time_event::sENTITY_STATUS	entity_status;
	};

	struct time_event_snap
	{
		ENABLE_STRUCT_SERIALIZABLE

		time_event_update_snap updatable;
	};


	//-----------------------------------------------------------------------------
	/**

	@class		sHOST_SETTING_INFO
	@brief		HOST의 설정 내용
	@todo
	@ref		sSERVICE_INSTANCE_INFO, SERVICE_SETTING
	@details	\n

	*/
	//-----------------------------------------------------------------------------
	// 1) Host setting - 호스트 설정, 사용자가 설정하는 값(Host에 대해서는 설정값이 거의 없다.)
	struct sHOST_SETTING_INFO
	{
		ENABLE_STRUCT_SERIALIZABLE

		// 1) host sID
		iid_t				iid{ 0 };

		// 2) name/comment
		std::string			name;
		std::string			comment;
	};

	// 2) Host Info - 호스트의 기본 값(호스트 명, 하드웨어 정보, O/S정보 등)
	struct sHOST_INSTANCE_INFO
	{
		ENABLE_STRUCT_SERIALIZABLE

		// 1) system/OS Info
		SYSTEM::sINFO		system_info;
		sOS_INFO			os_info;

		// 2) host address
		sMAC_ADDRESS		mac;
		net::sockaddr		addr_host;
		std::string			uid_host;
		std::string			uid_os;

		// 3) host name
		std::string			host_name;

		// 4) start Time
		chrono::time::utc::time_point time_start;
	};

	// 3) Host Status - Host의 상태(CPU사용량,메모리 사용량,네트워크 사용랴), 지속적으로 Host에서 전송되어오는 정보.
	struct sHOST_INSTANCE_STATUS
	{
		// 1) host instance id
		iid_t				iid{ 0 };

		// 2) usage info
		SYSTEM::sINFO		system_info;
		std::vector<SYSTEM::sSTATUS> vector_status;

		// 3) status
		eOBJECT_STATE	state{ eOBJECT_STATE::NONE };
	};

	// 4) status header
	struct sSERVICE_INSTANCE_INFO_BASIC
	{
		ENABLE_STRUCT_SERIALIZABLE

		// 1) instance id
		std::string			name;						// - application name
		iid_t				host_iid{ 0 };				// - host id
		uint64_t			pid{ 0 };					// - process_id

		// 2) version
		sREVISION			revision;					// - repository 정보
		sVERSION_EX			version;					// - veersion

		// 3) settings
		chrono::time::utc::time_point time_register;	// - 서버 정보를 등록한 시간.
		chrono::time::utc::time_point time_update;		// - 서버 정보를 업데이트한 시간.

		// funcions)
		void				clear() noexcept;
	};

	// 5) 현재 적용된 instance 정보들
	struct sSERVICE_INSTANCE_INFO : public sSERVICE_INSTANCE_INFO_BASIC
	{
		// 1) execute file/directory
		std::string			file_execute;				// - execute filename
		std::string			str_path;					// - File Path
		std::string			str_path_working;			// - Working Directory
		shared_buffer		buf_command_line;			// - Commandline(UNICODE, 1 NULL Terminate line, 2 NULL is Terminate Block)
		shared_buffer		buf_environment;			// - Environmennt block(UNICODE, 1 NULL Terminate line, 2 NULL is Terminate Block)

		// funcions)
		void				clear() noexcept;
	};


	//-----------------------------------------------------------------------------
	/**

	@class		sSERVICE_INSTANCE_STATUS

	*/
	//-----------------------------------------------------------------------------
	// 3. 변경되는 instance 현재 상태값
	struct sSERVICE_INSTANCE_STATUS
	{
		ENABLE_STRUCT_SERIALIZABLE

		// 1) instance id
		iid_t				iid{ 0 };					// - sSERVICE_INSTANCE_INFO의 iid값과 같은 값

		// 2) service state
		eOBJECT_STATE		state{ eOBJECT_STATE::NONE };
		uint32_t			dummy{ 0 };

		// 3) process id
		uint64_t			pid{ 0 };

		// 4) process/memory/network ...
		std::vector<PROCESS::sSTATUS> vector_process_status;

		// 5) entity status
		std::vector<server_admin::factory_snap>				vector_factory;
		std::vector<server_admin::executor_snap>			vector_executor;
		std::vector<server_admin::schedulable_snap>			vector_schedulable;
		std::vector<server_admin::connective_info_snap>		vector_connective;
		std::vector<server_admin::socket_info_snap>			vector_binder;
		std::vector<server_admin::time_event_snap>			vector_time_event;
		statistics::unit_connective_snap					connective_info;
		statistics::unit_traffic_snap						traffic_info;

		// 6) log status
		circular_list<object_ptr<LOG_RECORD>>				vector_log_record;

		// 7) time updated
		chrono::time::utc::time_point time_update;		// - 데이터가 작성된 시간

		void clear() noexcept
		{
			this->vector_factory.clear();
			this->vector_executor.clear();
			this->vector_schedulable.clear();
			this->vector_connective.clear();
			this->vector_binder.clear();
			this->vector_time_event.clear();
			this->connective_info = statistics::unit_connective_snap();
			this->traffic_info = statistics::unit_traffic_snap();
			this->vector_log_record.clear();
		}
	};


	//-----------------------------------------------------------------
	// all in one
	//-----------------------------------------------------------------
	// - server setting/status
	struct sSERVICE_INSTANCE_STATUS_UPDATE
	{
		ENABLE_STRUCT_SERIALIZABLE

		PROCESS::sSTATUS										process_status;
		std::vector<server_admin::factory_update_snap>			vector_factory_update;
		std::vector<server_admin::executor_update_snap>			vector_executor_update;
		std::vector<server_admin::schedulable_update_snap>		vector_schedulable_update;
		std::vector<server_admin::connective_info_update_snap>	vector_connective_update;
		std::vector<server_admin::socket_info_update_snap>		vector_binder_update;
		statistics::unit_connective_snap						connective_info;
		statistics::unit_traffic_snap							traffic_info;
	};


//-----------------------------------------------------------------
// get snap functions
//-----------------------------------------------------------------
// 1) factory
factory_snap							get_snap				(const Ifactory* _pfactory) noexcept;
factory_update_snap						get_update_snap			(const Ifactory* _pfactory) noexcept;
std::vector<factory_snap>				get_snap				(factory::manager* _pmanager);
std::vector<factory_update_snap>		get_update_snap			(factory::manager* _pmanager);
std::vector<factory_snap>				get_snap				(factory::manager* _pmanager, eOBJECT_TYPE _object_type);
std::vector<factory_update_snap>		get_update_snap			(factory::manager* _pmanager, eOBJECT_TYPE _object_type);

// 2) executor
executor_snap							get_snap				(Iexecutor* _pexector) noexcept;
executor_update_snap					get_update_snap			(Iexecutor* _pexector) noexcept;
std::vector<executor_snap>				get_snap				(executor::manager* _pexecutor_manager);
std::vector<executor_update_snap>		get_update_snap			(executor::manager* _pexecutor_manager);

// 3) schedulable
schedulable_snap						get_snap				(const Ischedulable* _pschedulable) noexcept;
schedulable_update_snap					get_update_snap			(const Ischedulable* _pschedulable) noexcept;
std::vector<schedulable_snap>			get_snap				(schedulable::manager* _pschedulable_manager);
std::vector<schedulable_update_snap>	get_update_snap			(schedulable::manager* _pschedulable_manager);

// 4) connective
statistics::unit_connective_snap		get_snap				(const statistics::unit_connective& _unit_connective) noexcept;
statistics::unit_connective_snap		get_update_snap			(const statistics::unit_connective& _connective) noexcept;
connective_info_snap					get_snap				(const net::io::Iconnective* _pconnective) noexcept;
connective_info_update_snap				get_update_snap			(const net::io::Iconnective* _pconnective) noexcept;
std::vector<connective_info_snap>		get_snap				(net::io::connective::manager* _pconnective_manager);
std::vector<connective_info_update_snap> get_update_snap		(net::io::connective::manager* _pconnective_manager);

// 5) traffic
statistics::unit_traffic_snap			get_snap				(const statistics::unit_traffic& _traffic_info) noexcept;
statistics::unit_traffic_snap			get_update_snap			(const statistics::unit_traffic& _traffic_info) noexcept;

// 6) socket info (binder)
socket_info_snap						get_snap				(const net::io::Ibinder* _pbinder) noexcept;
socket_info_snap						get_snap				(const net::io::Ibinder* _pbinder, net::io::statistics::Nsocket* _pstatistics_socket) noexcept;
socket_info_update_snap					get_update_snap			(const net::io::Ibinder* _pbinder) noexcept;
std::vector<socket_info_snap>			get_snap				(net::io::binder::manager* _pbinder_manager);
std::vector<socket_info_update_snap> get_update_snap			(net::io::binder::manager* _pbinder_manager);

// 7) time_event
time_event_snap							get_snap				(const time_event::Ientity* _ptime_event) noexcept;
time_event_update_snap					get_update_snap			(const time_event::Ientity* _ptime_event) noexcept;
std::vector<time_event_snap>			get_snap				(time_event::entity_manager* _pentity_manager);
std::vector<time_event_update_snap>		get_update_snap(time_event::entity_manager * _pentity_manager);

// 8) logger
std::vector<object_ptr<LOG_RECORD>>		get_records_of_default_logger();
circular_list<object_ptr<LOG_RECORD>>	get_records_of_default_logger_circular_list();


//-----------------------------------------------------------------
// message functions
//-----------------------------------------------------------------
// 1) certify
shared_buffer message_SERVER_ADMIN_CERTIFY_REQUEST				(const sCERTIFY_INFO& _certify_info);
shared_buffer message_SERVER_ADMIN_CERTIFY_RESPONSE				(eRESULT _result);

// 2) admin request
shared_buffer message_SERVER_ADMIN_REQUEST_UPDATE_SETTING		(iid_t _instance_iid, iid_t _host_iid, const server_admin::sSERVICE_SETTING& _server_setting);
shared_buffer message_SERVER_ADMIN_REQUEST_INIT_SERVICE			(iid_t _instance_iid);
shared_buffer message_SERVER_ADMIN_REQUEST_DESTROY_SERVICE		(iid_t _instance_iid);
shared_buffer message_SERVER_ADMIN_REQUEST_KILL_SERVICE			(iid_t _instance_iid);
shared_buffer message_SERVER_ADMIN_REQUEST_START_SERVICE		(iid_t _instance_iid, const std::string_view _setting);
shared_buffer message_SERVER_ADMIN_REQUEST_STOP_SERVICE			(iid_t _instance_iid);
shared_buffer message_SERVER_ADMIN_REQUEST_PAUSE_SERVICE		(iid_t _instance_iid);
shared_buffer message_SERVER_ADMIN_REQUEST_CONTINUE_SERVICE		(iid_t _instance_iid);
shared_buffer message_SERVER_ADMIN_INSTANCE_VERSION_UPDATE		(iid_t _instance_iid);

// 3) admin instance process
shared_buffer message_SERVER_ADMIN_INSTANCE_CERTIFY_REQUEST		(uint64_t _pid, server_admin::sRANK _rank);
shared_buffer message_SERVER_ADMIN_INSTANCE_CERTIFY_RESPONSE	(const server_admin::sSERVICE_SETTING& _instance_setting);
shared_buffer message_SERVER_ADMIN_INSTANCE_CERTIFY_RESPONSE	(eRESULT _result);

shared_buffer message_SERVER_ADMIN_INSTANCE_ENTER				(const std::vector<sINSTANCE_SERVICE>& _vector_instance);
shared_buffer message_SERVER_ADMIN_INSTANCE_LEAVE				(iid_t _service_iid);

// 4) admin instance info
shared_buffer message_SERVER_ADMIN_INSTANCE_REGISTER			(Ibuffer_serializable* _pinstance);
shared_buffer message_SERVER_ADMIN_INSTANCE_UNREGISTER			(iid_t _instance_iid);
shared_buffer message_SERVER_ADMIN_INSTANCE_UPDATE				(iid_t _instance_iid, Ibuffer_serializable& _instance);
shared_buffer message_SERVER_ADMIN_INSTANCE_UPDATE_SETTING		(iid_t _instance_iid, Ibuffer_serializable& _instance);
shared_buffer message_SERVER_ADMIN_INSTANCE_UPDATE_INFO			(iid_t _instance_iid, Ibuffer_serializable& _instance);
shared_buffer message_SERVER_ADMIN_INSTANCE_UPDATE_INFO			(iid_t _service_iid);
shared_buffer message_SERVER_ADMIN_INSTANCE_UPDATE_STATUS		(iid_t _service_iid, Ibuffer_serializable& _instance);
shared_buffer message_SERVER_ADMIN_INSTANCE_UPDATE_STATE		(iid_t _service_iid, eOBJECT_STATE _status_new, eOBJECT_STATE _status_old);
shared_buffer message_SERVER_ADMIN_INSTANCE_UPDATE_PID			(iid_t _instance_iid, uint64_t _pid);
shared_buffer message_SERVER_ADMIN_ERROR						(iid_t _service_iid, uint32_t _request, int _error_code, const std::string_view _error_message);

shared_buffer message_FACTORY_FACTORY_REGISTER					(iid_t _instance_iid, Ifactory* _pfactory);
shared_buffer message_FACTORY_FACTORY_UNREGISTER				(iid_t _instance_iid, Ifactory* _pfactory);
shared_buffer message_FACTORY_FACTORY_UPDATE					(iid_t _instance_iid, Ifactory* _pfactory);

shared_buffer message_EXECUTOR_REGISTER							(iid_t _instance_iid, Iexecutor* _pexecutor);
shared_buffer message_EXECUTOR_UNREGISTER						(iid_t _instance_iid, Iexecutor* _pexecutor);
shared_buffer message_EXECUTOR_UPDATE							(iid_t _instance_iid, Iexecutor* _pexecutor);

shared_buffer message_NETWORK_SOCKET_CONNECTIVE_REGISTER		(iid_t _instance_iid, const net::io::Iconnective* _pconnective);
shared_buffer message_NETWORK_SOCKET_CONNECTIVE_UNREGISTER		(iid_t _instance_iid, const net::io::Iconnective* _pconnective);
shared_buffer message_NETWORK_SOCKET_CONNECTIVE_UPDATE			(iid_t _instance_iid, const net::io::Iconnective* _pconnective);

shared_buffer message_NETWORK_SOCKET_BINDER_REGISTER			(iid_t _instance_iid, net::io::Ibinder* _pbinder, net::io::statistics::Nsocket* _pstatistics_socket);
shared_buffer message_NETWORK_SOCKET_BINDER_UNREGISTER			(iid_t _instance_iid, net::io::Ibinder* _pbinder);
shared_buffer message_NETWORK_SOCKET_BINDER_UPDATE				(iid_t _instance_iid, net::io::Ibinder* _pbinder);

shared_buffer message_SERVER_TIME_EVENT_EVENT_REGISTER			(iid_t _instance_iid, time_event::Ientity* _ptime_event);
shared_buffer message_SERVER_TIME_EVENT_EVENT_UNREGISTER		(iid_t _instance_iid, time_event::Ientity* _ptime_event);
shared_buffer message_SERVER_TIME_EVENT_EVENT_EXECUTE			(iid_t _instance_iid, time_event::Ientity* _ptime_event);

shared_buffer message_SERVER_ADMIN_DUMP_INFO_LIST				(iid_t _instance_iid);
shared_buffer message_SERVER_ADMIN_DUMP_INFO					(iid_t _instance_iid);

shared_buffer message_SYSTEM_LOG								(iid_t _instance_iid, const LOG_RECORD* _plog_record);
shared_buffer message_SYSTEM_LOG								(iid_t _instance_iid, const std::vector<object_ptr<LOG_RECORD>>& _vector_log_record);
}
shared_buffer message_SERVER_CERTIFY_REQUEST					(const server_admin::sSERVICE_SETTING& _server_setting_info);
shared_buffer message_SERVER_CERTIFY_RESPONSE					(eRESULT _result, const server_admin::sSERVICE_SETTING& _server_setting_info);
shared_buffer message_SERVER_CERTIFY_RESPONSE					(eRESULT _result);
}

#pragma pack()

#define	CONFIGURE_JSON_FILENAME	"host_agent_info.json"
