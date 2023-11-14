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
//-----------------------------------------------------------------------------
//
// eOBJECT_STATE
//
//    1) initialize	eOBJECT_STATE::NONE    ->eOBJECT_STATE::INITIALIZING_PENDING ->eOBJECT_STATE::STOPPED
//    2) start		eOBJECT_STATE::STOPPED ->eOBJECT_STATE::START_PENDING        ->eOBJECT_STATE::RUNNING
//    3) stop		eOBJECT_STATE::RUNNING ->eOBJECT_STATE::STOP_PENDING		 ->eOBJECT_STATE::STOPPED
//    4) Destory	eOBJECT_STATE::STOPPED ->eOBJECT_STATE::DESTROYING_PENDING   ->eOBJECT_STATE::NONE
//    5) pause		eOBJECT_STATE::RUNNING ->eOBJECT_STATE::PAUSE_PENDING		 ->eOBJECT_STATE::PAUSED
//    6) continue	eOBJECT_STATE::PAUSED  ->eOBJECT_STATE::CONTINUE_PENDING	 ->eOBJECT_STATE::RUNNING
//
//-----------------------------------------------------------------------------
enum class eOBJECT_STATE : int32_t
{
	NONE									 = 0,
	STOPPED									 = 1,	// SERVICE_STOPPED
	READY									 = 1,
	START_PENDING							 = 2,	// SERVICE_START_PENDING
	REQUESTING								 = 2,
	STOP_PENDING							 = 3,	// SERVICE_STOP_PENDING
	CLOSE_PENDING							 = 3,
	RUNNING									 = 4,	// SERVICE_RUNNING
	PROCESSED								 = 4,
	CONTINUE_PENDING						 = 5,	// SERVICE_CONTINUE_PENDING
	PAUSE_PENDING							 = 6,	// SERVICE_PAUSE_PENDING
	PAUSED									 = 7,	// SERVICE_PAUSED
	INITIALIZING_PENDING					 = 8,
	DESTROYING_PENDING						 = 9,
	UPDATE									 = 10,
	COMMIT									 = 11,
	NOT_CONNECT								 = 12,
	ESTABLISHED								 = 13,
	DEFAULT									 = 0xff
};

[[nodiscard]] inline eOBJECT_STATE operator & (eOBJECT_STATE _lhs, eOBJECT_STATE _rhs) { return static_cast<eOBJECT_STATE>(static_cast<uint32_t>(_lhs) & static_cast<uint32_t>(_rhs));}
[[nodiscard]] inline eOBJECT_STATE operator | (eOBJECT_STATE _lhs, eOBJECT_STATE _rhs) { return static_cast<eOBJECT_STATE>(static_cast<uint32_t>(_lhs) | static_cast<uint32_t>(_rhs));}
[[nodiscard]] inline eOBJECT_STATE operator & (eOBJECT_STATE _lhs, uint32_t _rhs) { return static_cast<eOBJECT_STATE>(static_cast<uint32_t>(_lhs) && _rhs);}
[[nodiscard]] inline eOBJECT_STATE operator | (eOBJECT_STATE _lhs, uint32_t _rhs) { return static_cast<eOBJECT_STATE>(static_cast<uint32_t>(_lhs) || _rhs);}


//-----------------------------------------------------------------------------
//
// eRESULT
//
//-----------------------------------------------------------------------------
enum class  eRESULT : int
{
	// - Default
	NONE									 = 0x00000000,	//            = SUCCESS
	BYPASS									 = 0x00000000,	//            = SUCCESS

	// - Success
	SUCCESS									 = 0x00000000,	// 0x0******* Success
	DONE									 = 0x00000001,	//            Success - Done
	PENDED									 = 0x00000201,	//            Success - setting and Execution Pended
	SUCCESS_CREATE							 = 0x00000202,	//            Success - on creation new account
	SUCCESS_RESTORE							 = 0x00000203,	//            Success - on Restore
	PENDING									 = 0x00000204,	//            Pending
	TRANSFER								 = 0x00000205,	//            Transfer
	_SUCCESS_USER							 = 0x00010000,	// 0x0001**** for user definition

	// - Fail = result of trying
	FAIL									 = 0x03000000,	// 0x3******* Fail
	FAIL_DISABLED							 = 0x03000001,
	TIME_OUT								 = 0x03000012,
	ALEADY_EXIST							 = 0x03000003,
	EXPIRED									 = 0x03000014,
	NOT_EXIST								 = 0x03000005,
	NOT_READY								 = 0x03000006,
	BANNED_MEMBER							 = 0x03000017,
	MEMBER_FULL								 = 0x03000018,
	INVALID_MEMBER							 = 0x03000019,
	INVALID_PASSWORD						 = 0x0300001a,
	INVALID_PLATFORM						 = 0x0300001b,
	ALEADY_EXIST_NICKNAME					 = 0x0300001c,
	ALEADY_DONE								 = 0x0300001d,
	API_FAILURE								 = 0x0300001e,
	FAIL_TO_ACCEPT_SOCKET					 = 0x0300001f,
	FAIL_TO_ATTACHING_TO_EXECUTOR			 = 0x03000020,
	CONNECTION_FAILURE						 = 0x03000021,
	FAIL_TO_CREATE							 = 0x03000022,
	FAIL_TO_OPEN							 = 0x03000023,
	FAIL_TO_OPERATION						 = 0x03000024,
	FAIL_TO_CONNECT							 = 0x03000025,
	FAIL_NO_WEBSOCKET_KEY					 = 0x03010026,
	INVALID_VALUE							 = 0x03010027,
	INVALID_SERVER							 = 0x03010028,
	INVALID_REQUEST							 = 0x03010029,
	BUSY									 = 0x0301002a,
	EXCEED_RETRY_LIMIT						 = 0x0301002b,
	NO_MEMBER_INFO							 = 0x0301002c,
	RETRY_OUT								 = 0x0301002d,
	FULL									 = 0x0301002e,
	_FAIL_USER								 = 0x030f0000,	// 0x030f**** for user definition

	// - Cancel = canceling
	CANCEL									 = 0x03100000,	// 0x2******* Cancel
	_CANCEL_USER							 = 0x031f0000,	// 0x031f**** for user definition

	// - Error of process
	ERROR_									 = 0x03200000,	// 0x3******* Error
	LOGIC_ERROR								 = 0x03200001,
	LENGTH_ERROR							 = 0x03200002,
	DOMAIN_ERROR							 = 0x03200003,
	OUT_OF_RANGE							 = 0x03200004,
	RUNTIME_ERROR							 = 0x03200005,
	OVERFLOW_ERROR							 = 0x03200006,
	UNDERFLOW_ERROR							 = 0x03200007,
	RANGE_ERROR								 = 0x03200008,
	BAD_ALLOC								 = 0x03200009,
	BAD_FUNCTION_CALL						 = 0x0320000a,
	CONCURRENT_LOCK_ERROR					 = 0x0320000b,
	ACCESS_DENIED							 = 0x0320000c,
	NO_INITIALIZED							 = 0x0320000d,
	INVALID_ARGUMENT						 = 0x0320000e,
	NOT_ALLOWED								 = 0x03200010,
	INVALID_PARAMETER_HANDLE				 = 0x03200011,
	INVALID_MESSAGE_LENGTH					 = 0x03200012,
	INVALID_MESSAGE_BUFFER_IS_NULL			 = 0x03200013,
	INVALID_MESSAGE_TOO_SHORT_LENGTH		 = 0x03200014,
	INVALID_MESSAGE_TOO_LONG_LENGTH			 = 0x03200015,
	INVALID_STATE							 = 0x03200016,
	INVALID_HANDLE							 = 0x03200017,
	INVALID_CHECK_KEY						 = 0x03200018,
	INVALID_RESOURCE						 = 0x03200019,
	FORMAT_ERROR							 = 0x0320001a,
	_ERROR_USER								 = 0x032f0000,	// 0x032f**** for user definition

	// - Exception of process
	EXCEPTION								 = 0x03400000,	// 0x4*** Exception
	BAD_EXCEPTION							 = 0x03400001,
	FORCE_CLOSE								 = 0x03400002,
	NOT_SUPPORT								 = 0x03400003,
	INVALID_CALL							 = 0x03400004,
	INVALID_LICENSE							 = 0x03400005,
	ABNORMAL_STATE							 = 0x03400006,
	BUFFER_INVALID							 = 0x034d0007,
	BUFFER_INVALID_STRING					 = 0x034d0008,
	UNEXPECTED_EXCEPTION					 = 0x034d0000,
	_EXCEPTION_USER							 = 0x034f0000,	// 0x034f**** for user definition

	PROCESS									 = 0x03500000,	// 0x5*** Process
	REQUEST									 = 0x03500001,
	COMPLETE								 = 0x03500002,
	RESET									 = 0x03500003,
	RESTORE									 = 0x03500004,
	_PROCESS_USER							 = 0x035f0000,	// 0x035f**** for user definition

	_USER									 = 0x03600000,

	CGCII_EXPIRED							 = 0x7e000000,
	NOT_DEFINED								 = 0x7f000000	// 0xff** Not Defined
};
[[nodiscard]] inline eRESULT operator & (eRESULT _lhs, eRESULT _rhs) noexcept { return static_cast<eRESULT>(static_cast<uint32_t>(_lhs) & static_cast<uint32_t>(_rhs));}
[[nodiscard]] inline eRESULT operator | (eRESULT _lhs, eRESULT _rhs) noexcept { return static_cast<eRESULT>(static_cast<uint32_t>(_lhs) | static_cast<uint32_t>(_rhs));}
[[nodiscard]] inline eRESULT operator & (eRESULT _lhs, uint32_t _rhs) noexcept { return static_cast<eRESULT>(static_cast<uint32_t>(_lhs) && _rhs);}
[[nodiscard]] inline eRESULT operator | (eRESULT _lhs, uint32_t _rhs) noexcept { return static_cast<eRESULT>(static_cast<uint32_t>(_lhs) || _rhs);}

template <> struct CGDK::is_result_code_enum<eRESULT> : std::true_type {};




//-----------------------------------------------------------------------------
//
// eOBJECT_TYPE
//
//-----------------------------------------------------------------------------
enum class  eOBJECT_TYPE : uint32_t
{
	// 1) not defined
	NOT_DEFINED								 = 0x00000000,

	// 2) common
	EXECUTOR								 = 0x00100000,
	EXECUTOR_THREAD							 = 0x00100001,
	EXECUTOR_SCHEDULABLE					 = 0x00100002,
	EXECUTOR_COMPLETION_PORT				 = 0x00100003,
	EXECUTOR_COMPLETION_PORT_THREAD			 = 0x00100004,
	EXECUTOR_LIST							 = 0x00100005,
	EXECUTOR_LIST_PRIORITY					 = 0x00100006,
	EXECUTOR_LIST_THREAD					 = 0x00100007,
	EXECUTOR_QUEUED							 = 0x00100008,
	EXECUTOR_QUEUED_THREAD					 = 0x00100009,
	EXECUTOR_SINGLE_EXECUTE					 = 0x0010000a,
	EXECUTOR_SINGLE_EXECUTE_THREAD			 = 0x0010000b,

	EXECUTABLE								 = 0x0011000c,
	EXECUTABLE_BATCH_FUNCTION				 = 0x0011000d,
	EXECUTABLE_BATCH_FUNCTION_MEMBER		 = 0x0011000e,
	EXECUTABLE_BATCH_NOTIFY					 = 0x0011000f,
	EXECUTABLE_BATCH_WAIT					 = 0x00110010,
	EXECUTABLE_FUNCTION						 = 0x00110011,
	EXECUTABLE_FUNCTION_MEMBER				 = 0x00110012,
	EXECUTABLE_LIST							 = 0x00110013,
	EXECUTABLE_EXECUTABLE					 = 0x00110014,
	EXECUTABLE_SOCKET						 = 0x00110015,
	EXECUTABLE_CONNECT_REQUSTABLE			 = 0x00110016,
	EXECUTABLE_RECEIVE						 = 0x00110017,
	EXECUTABLE_RECEIVING					 = 0x00110018,
	EXECUTABLE_RECEIVED						 = 0x00110019,
	EXECUTABLE_BUFFER						 = 0x0011001a,
	EXECUTABLE_DISCONNECT					 = 0x0011001b,
	EXECUTABLE_CONNECTIVE					 = 0x0011001c,
	EXECUTABLE_ACCEPT						 = 0x0011001d,
	EXECUTABLE_RESEND						 = 0x0011001e,

	SCHEDULABLE								 = 0x00120000,
	SCHEDULABLE_EXECUTABLE					 = 0x00120001,
	SCHEDULABLE_FUNCTION					 = 0x00120002,
	SCHEDULABLE_FUNCTION_MEMBER				 = 0x00120003,
	SCHEDULABLE_LIST						 = 0x00120004,
	SCHEDULABLE_EXCEPTION_OBSERVER			 = 0x00120005,
	SCHEDULABLE_FACTORY_GARBAGE				 = 0x00120006,
	SCHEDULABLE_ENTITY						 = 0x00120007,

	UPDATABLE								 = 0x00130000,
	UPDATABLE_BATCH							 = 0x00130001,

	FILE									 = 0x00140000,

	// 3) socket
	SOCKET									 = 0x00200000,
	ACCEPTOR								 = 0x00210000,
	CONNECTOR								 = 0x00220000,

	// 4) time event
	TIME_EVENT_ENTITY						 = 0x0030000,
	TIME_EVENT_ENTITY_ITERATION				 = 0x0030001,
	TIME_EVENT_ENTITY_SCHEDULE				 = 0x0030002,
	TIME_EVENT_ENTITY_BEGIN_END				 = 0x0030003,
	TIME_EVENT_ENTITY_BEGIN_ITERATION_END	 = 0x0030004,
	TIME_EVENT_EVENT						 = 0x0031000,
	TIME_EVENT_EVENT_ITERATION				 = 0x0031001,
	TIME_EVENT_EVENT_BEGIN_END				 = 0x0031002,
	TIME_EVENT_EVENT_BEGIN_ITERATION_END	 = 0x0031003,

	// 5) server System
	GROUP									 = 0x00400000,
	GROUP_COUNT								 = 0x00410000,
	GROUP_LIST								 = 0x00420000,
	GROUP_ARRAY								 = 0x00430000,
	GROUP_MAP								 = 0x00440000,

	// 6) object
	REPOSITORY								 = 0x00500000,
	REPOSITORY_DB							 = 0x00511000,
	REPOSITORY_REDIS						 = 0x00512000,
	REPOSITORY_HUB							 = 0x00513000,
	REPOSITORY_REMOTE						 = 0x00514000,
	REPOSITORY_ORM							 = 0x00515000,
	ACCESSABLE								 = 0x00520000,
	ACCESSABLE_HOLDER						 = 0x00521000,
	DEPOT									 = 0x00530000,
	DEPOT_REMOTE							 = 0x00531000,

	// 7) querier
	QUERIER									 = 0x006000000,
	QUERIER_DB_SQL							 = 0x006100000,
	QUERIER_DB_CASSANDRA					 = 0x006200001,
	QUERIER_DB_MONGODB						 = 0x006200002,
	QUERIER_REDIS							 = 0x006200003,
	QUERIER_HTTP							 = 0x006300000,
	QUERIER_OAUTH							 = 0x006300001,
	QUERIER_KAKAO							 = 0x006300002,
	QUERIER_LINE							 = 0x006300003,

	// 8) 3d - bounding 
	BOUNDING								 = 0x010000000,
	BOUNDING_SPHERE							 = (BOUNDING | 0x0001),
	BOUNDING_ELLIPSOID						 = (BOUNDING | 0x0002),
	BOUNDING_SAABB							 = (BOUNDING | 0x0003),
	BOUNDING_AABB							 = (BOUNDING | 0x0004),
	BOUNDING_OBB							 = (BOUNDING | 0x0005),
	BOUNDING_CYLINDER						 = (BOUNDING | 0x0006),
	BOUNDING_CONE							 = (BOUNDING | 0x0007),
	BOUNDING_CAPSULE						 = (BOUNDING | 0x0008),
	BOUNDING_CONVAX							 = (BOUNDING | 0x0009),
	BOUNDING_LINE							 = (BOUNDING | 0x000a),
	BOUNDING_SEGMENT						 = (BOUNDING | 0x000b),
	BOUNDING_CIRCLE							 = (BOUNDING | 0x000c),
	BOUNDING_ELLIPSE						 = (BOUNDING | 0x000d),
	BOUNDING_TRIANGLE						 = (BOUNDING | 0x000e),
	BOUNDING_RECTANGLE						 = (BOUNDING | 0x000f),
	BOUNDING_PLANE							 = (BOUNDING | 0x0010),
	BOUNDING_PLANES							 = (BOUNDING | 0x0011),
	BOUNDING_TERRAIN						 = (BOUNDING | 0x0012),
	BOUNDING_POTAL							 = (BOUNDING | 0x0013),

	// 9) resource
	RESOURCE								 = 0x011000000,
	RESOURCE_VERTEXATTRIB					 = (eOBJECT_TYPE::RESOURCE | 0x0001),
	RESOURCE_BUFFER							 = (eOBJECT_TYPE::RESOURCE | 0x0010),
	RESOURCE_SHADER							 = (eOBJECT_TYPE::RESOURCE | 0x0020),
	RESOURCE_PROGRAM						 = (eOBJECT_TYPE::RESOURCE | 0x0030),
	RESOURCE_MESH							 = (eOBJECT_TYPE::RESOURCE | 0x0200),
	RESOURCE_MESH_PRIMITIVE					 = (eOBJECT_TYPE::RESOURCE_MESH | 0),
	RESOURCE_MESH_ARRAY						 = (eOBJECT_TYPE::RESOURCE_MESH | 0),
	RESOURCE_MESH_INDEXEDPRIMITIVE			 = (eOBJECT_TYPE::RESOURCE_MESH | 1),
	RESOURCE_MESH_ELEMENT					 = (eOBJECT_TYPE::RESOURCE_MESH | 1),
	RESOURCE_MESH_TRIPATCH					 = (eOBJECT_TYPE::RESOURCE_MESH | 2),
	RESOURCE_MESH_RECTPATCH					 = (eOBJECT_TYPE::RESOURCE_MESH | 3),
	RESOURCE_MESH_DISPLACEMENT				 = (eOBJECT_TYPE::RESOURCE_MESH | 4),
	RESOURCE_MESH_TERRAIN					 = (eOBJECT_TYPE::RESOURCE_MESH | 5),
	RESOURCE_TEXTURE						 = (eOBJECT_TYPE::RESOURCE | 0x0300),
	RESOURCE_SAMPLER						 = (eOBJECT_TYPE::RESOURCE | 0x0400),
	RESOURCE_SURFACE						 = (eOBJECT_TYPE::RESOURCE | 0x0500),
	RESOURCE_VERTEXDECL						 = (eOBJECT_TYPE::RESOURCE | 0x0600),
	RESOURCE_FONT							 = (eOBJECT_TYPE::RESOURCE | 0x0700),
	RESOURCE_BONEINFO						 = (eOBJECT_TYPE::RESOURCE | 0x0800),
	RESOURCE_TIME_SET_ARRAY					 = (eOBJECT_TYPE::RESOURCE | 0x0850),
	RESOURCE_SPRITE							 = (eOBJECT_TYPE::RESOURCE | 0x0900),
	RESOURCE_SPRITEBUNDLE					 = (eOBJECT_TYPE::RESOURCE | 0x0a00),
	RESOURCE_KEYFRAME						 = (eOBJECT_TYPE::RESOURCE | 0x0b00),
	RESOURCE_KEYFRAME_TRANSFORM				 = (eOBJECT_TYPE::RESOURCE_KEYFRAME),
	RESOURCE_KEYFRAME_TRANSFORM_PRESET		 = (eOBJECT_TYPE::RESOURCE_KEYFRAME | 1),
	RESOURCE_KEYFRAME_VECTOR3				 = (eOBJECT_TYPE::RESOURCE_KEYFRAME | 2),
	RESOURCE_KEYFRAME_VECTOR4				 = (eOBJECT_TYPE::RESOURCE_KEYFRAME | 3),
	RESOURCE_KEYFRAME_LIGHT					 = (eOBJECT_TYPE::RESOURCE_KEYFRAME | 4),
	RESOURCE_KEYFRAME_VIEW					 = (eOBJECT_TYPE::RESOURCE_KEYFRAME | 5),
	RESOURCE_TIMESET_ARRAY					 = (eOBJECT_TYPE::RESOURCE | 0x0d00),
	RESOURCE_PLANELIST						 = (eOBJECT_TYPE::RESOURCE | 0x0e00),
	RESOURCE_SCENEINFO						 = (eOBJECT_TYPE::RESOURCE | 0x0f00),

	// 10) modifier
	MODIFIER								 = 0x012000000,
	MODIFIER_LOCAL							 = (eOBJECT_TYPE::MODIFIER | 0x0000),
	MODIFIER_KEYFRAME					 	 = (eOBJECT_TYPE::MODIFIER | 0x0100),
	MODIFIER_KEYFRAME_LIGHT			 		 = (eOBJECT_TYPE::MODIFIER_KEYFRAME | 0),
	MODIFIER_KEYFRAME_TRANSFORM		 		 = (eOBJECT_TYPE::MODIFIER_KEYFRAME | 1),
	MODIFIER_KEYFRAME_VIEW				 	 = (eOBJECT_TYPE::MODIFIER_KEYFRAME | 2),
	MODIFIER_CONSTRAINT_IK				 	 = (eOBJECT_TYPE::MODIFIER | 0x0300),

	// 11) controller
	CONTROL									 = 0x013000000,
	CONTROL_TIME							 = (eOBJECT_TYPE::MODIFIER | 0x0200),
	CONTROL_TIME_SET						 = (eOBJECT_TYPE::MODIFIER | 0x0201),
	CONTROL_TIME_SET_ARRAY					 = (eOBJECT_TYPE::MODIFIER | 0x0202),

	// 12) applier
	APPLIER									 = 0x014000000,
	APPLIER_CAMERA							 = (eOBJECT_TYPE::APPLIER | 0x0000),
	APPLIER_EFFECT							 = (eOBJECT_TYPE::APPLIER | 0x0100),
	APPLIER_LIGHT						 	 = (eOBJECT_TYPE::APPLIER | 0x0200),
	APPLIER_MATERIAL					 	 = (eOBJECT_TYPE::APPLIER | 0x0300),
	APPLIER_TEXTURE					 		 = (eOBJECT_TYPE::APPLIER | 0x0400),
	APPLIER_BONEINFO					 	 = (eOBJECT_TYPE::APPLIER | 0x0500),
	APPLIER_RENDERTARGET				 	 = (eOBJECT_TYPE::APPLIER | 0x0600),
	APPLIER_VERTEXSTREAM				 	 = (eOBJECT_TYPE::APPLIER | 0x0700),
	APPLIER_STATEBLOCK					 	 = (eOBJECT_TYPE::APPLIER | 0x0800),
	APPLIER_SCENEINFO					 	 = (eOBJECT_TYPE::APPLIER | 0x0900),

	// 13) renderer
	RENDERER								 = 0x015000000,
	RENDERER_MESH						 	 = (eOBJECT_TYPE::RENDERER | 0x0000),
	RENDERER_WIRE						 	 = (eOBJECT_TYPE::RENDERER | 0x0100),
	RENDERER_TEXT						 	 = (eOBJECT_TYPE::RENDERER | 0x0200),
	RENDERER_BILLBOARD					 	 = (eOBJECT_TYPE::RENDERER | 0x0300),
	RENDERER_PARTICLE					 	 = (eOBJECT_TYPE::RENDERER | 0x0400),
	RENDERER_RAY						 	 = (eOBJECT_TYPE::RENDERER | 0x0500),
	RENDERER_SKYBOX					 		 = (eOBJECT_TYPE::RENDERER | 0x0600),
	RENDERER_VIEW						 	 = (eOBJECT_TYPE::RENDERER | 0x0700),
	RENDERER_SCENE							 = (eOBJECT_TYPE::RENDERER | 0x0800),
	RENDERER_SPRITE							 = (eOBJECT_TYPE::RENDERER | 0x0900),

	// 14) scene_node
	SCENENODE								 = 0x016000000,
	SCENENODE_TM						 	 = (eOBJECT_TYPE::SCENENODE | 0x0100),		// Scene을 총괄하는 Scene임 - 일반적으로 Render시 root로 쓰임
	SCENENODE_BLENDING,							// Scene을 총괄하는 Scene임 - 일반적으로 Render시 root로 쓰임
	SCENENODE_TREE,								// Tree Node
	SCENENODE_TREE_TERRAIN,						// Tree Node with Terrain
	SCENENODE_GRAPH,							// Graph
	SCENENODE_PORTAL,							// Portal의 Node
	SCENENODE_SPRITE,							// Sprite
	SCENENODE_BACKGROUND,						// Background
	SCENENODE_VIEW,								// View
	SCENENODE_LINK,								// Link

	// 15) entity
	ENTITY									 = 0x017000000,
	ENTITY_GENERAL							 = (eOBJECT_TYPE::ENTITY | 0x0100),
	ENTITY_ADDITIONAL						 = (eOBJECT_TYPE::ENTITY | 0x0101),

	// 16) ui
	UI										 = 0x018000000,
	UI_STATIC							 	 = (eOBJECT_TYPE::UI | 0x0100),
	UI_EDIT							 		 = (eOBJECT_TYPE::UI | 0x0200),
	UI_BUTTON							 	 = (eOBJECT_TYPE::UI | 0x0300),
	UI_LIST							 		 = (eOBJECT_TYPE::UI | 0x0400),
	UI_SCROLLBAR						 	 = (eOBJECT_TYPE::UI | 0x0500),
	UI_SLIDER							 	 = (eOBJECT_TYPE::UI | 0x0600),
	UI_COMBO							 	 = (eOBJECT_TYPE::UI | 0x0700),
	UI_FORM							 		 = (eOBJECT_TYPE::UI | 0x0800),
	UI_CHECKBOX							 	 = (eOBJECT_TYPE::UI | 0x0900),   //  [9/2/2016 BSH_CGCIII]
	UI_LISTVIEW							 	 = (eOBJECT_TYPE::UI | 0x1000),   //  [9/8/2016 BSH_CGCIII]
	UI_IMAGE							 	 = (eOBJECT_TYPE::UI | 0x1100),   //  [9/27/2016 BSH_CGCIII]

	// 17) refernece 
	REFERENCE								 = 0x019000000,
	REFERENCE_SPHERE						 = (eOBJECT_TYPE::REFERENCE | 0x0001),
	REFERENCE_ELLIPSOID						 = (eOBJECT_TYPE::REFERENCE | 0x0002),
	REFERENCE_AABB							 = (eOBJECT_TYPE::REFERENCE | 0x0003),
	REFERENCE_OBB							 = (eOBJECT_TYPE::REFERENCE | 0x0004),
	REFERENCE_CYLINDER						 = (eOBJECT_TYPE::REFERENCE | 0x0005),
	REFERENCE_CONE							 = (eOBJECT_TYPE::REFERENCE | 0x0006),
	REFERENCE_CAPSULE						 = (eOBJECT_TYPE::REFERENCE | 0x0007),
	REFERENCE_CONVAX						 = (eOBJECT_TYPE::REFERENCE | 0x0008),
	REFERENCE_LINE							 = (eOBJECT_TYPE::REFERENCE | 0x0009),
	REFERENCE_SEGMENT						 = (eOBJECT_TYPE::REFERENCE | 0x000a),
	REFERENCE_CIRCLE						 = (eOBJECT_TYPE::REFERENCE | 0x000b),
	REFERENCE_ELLIPSE						 = (eOBJECT_TYPE::REFERENCE | 0x000c),
	REFERENCE_TRIANGLE						 = (eOBJECT_TYPE::REFERENCE | 0x000d),
	REFERENCE_RECTANGLE						 = (eOBJECT_TYPE::REFERENCE | 0x000e),
	REFERENCE_PLANE							 = (eOBJECT_TYPE::REFERENCE | 0x000f),
	REFERENCE_PLANES						 = (eOBJECT_TYPE::REFERENCE | 0x0010),
	REFERENCE_TERRAIN						 = (eOBJECT_TYPE::REFERENCE | 0x0011),
	REFERENCE_PORTAL						 = (eOBJECT_TYPE::REFERENCE | 0x0012),
	REFERENCE_POINT							 = (eOBJECT_TYPE::REFERENCE | 0x0013),
	REFERENCE_TRANSFORMMATRIX				 = (eOBJECT_TYPE::REFERENCE | 0x0014),

	// 16) 
	MASK									 = 0x00ffff00,
	MASK_ALL								 = 0xffffffff

};// end of enum class  eOBJECT_TYPE : uint32_t

#define	CG3DOBJECT_TYPE_MASK		0x0ff000000

[[nodiscard]] constexpr eOBJECT_TYPE operator & (eOBJECT_TYPE _lhs, eOBJECT_TYPE _rhs) noexcept { return static_cast<eOBJECT_TYPE>(static_cast<uint32_t>(_lhs) & static_cast<uint32_t>(_rhs));}
[[nodiscard]] constexpr eOBJECT_TYPE operator | (eOBJECT_TYPE _lhs, eOBJECT_TYPE _rhs) noexcept { return static_cast<eOBJECT_TYPE>(static_cast<uint32_t>(_lhs) | static_cast<uint32_t>(_rhs));}
[[nodiscard]] constexpr eOBJECT_TYPE operator & (eOBJECT_TYPE _lhs, uint32_t _rhs) noexcept { return static_cast<eOBJECT_TYPE>(static_cast<uint32_t>(_lhs) && _rhs);}
[[nodiscard]] constexpr eOBJECT_TYPE operator | (eOBJECT_TYPE _lhs, uint32_t _rhs) noexcept { return static_cast<eOBJECT_TYPE>(static_cast<uint32_t>(_lhs) || _rhs);}
																				  
template <class T>	[[nodiscard]] std::basic_string_view<T>	to_string(eOBJECT_STATE _eState) noexcept;
template <>			[[nodiscard]] std::string_view			to_string<char>(eOBJECT_STATE _eState) noexcept;
template <>			[[nodiscard]] std::wstring_view			to_string<wchar_t>(eOBJECT_STATE _eState) noexcept;

template <class T>	[[nodiscard]] std::basic_string_view<T>	to_string(eRESULT _result) noexcept;
template <>			[[nodiscard]] std::string_view			to_string<char>(eRESULT _result) noexcept;
template <>			[[nodiscard]] std::wstring_view			to_string<wchar_t>(eRESULT _result) noexcept;

template <class T>	[[nodiscard]] std::basic_string_view<T>	to_string(eOBJECT_TYPE _type) noexcept;
template <>			[[nodiscard]] std::string_view			to_string<char>(eOBJECT_TYPE _type) noexcept;
template <>			[[nodiscard]] std::wstring_view			to_string<wchar_t>(eOBJECT_TYPE _type) noexcept;


//-----------------------------------------------------------------------------
//
// sOBJECT_TYPE
//
//-----------------------------------------------------------------------------
#if defined(_MSC_VER)
	#pragma warning(disable:4201)
	#pragma warning(disable:26495)
#endif

struct sOBJECT_TYPE
{
public:
			eOBJECT_TYPE		object_type = eOBJECT_TYPE::NOT_DEFINED;
			uint32_t			factory_id = 0;

public:
	constexpr sOBJECT_TYPE() noexcept {}
	constexpr sOBJECT_TYPE(const sOBJECT_TYPE& _rhs) noexcept : object_type(_rhs.object_type), factory_id(_rhs.factory_id) {}
	constexpr sOBJECT_TYPE(eOBJECT_TYPE _type) noexcept : object_type(_type) {}
	constexpr sOBJECT_TYPE(eOBJECT_TYPE _type, uint32_t _factory_id) noexcept : object_type(_type), factory_id(_factory_id) {}
public:
	constexpr  sOBJECT_TYPE& operator=(const sOBJECT_TYPE& _rhs) noexcept { object_type =_rhs.object_type; factory_id =_rhs.factory_id; return *this;}
};

[[nodiscard]] constexpr bool operator == (const sOBJECT_TYPE& _lhs, const sOBJECT_TYPE& _rhs) noexcept { return _lhs.factory_id == _rhs.factory_id; }
[[nodiscard]] constexpr bool operator != (const sOBJECT_TYPE& _lhs, const sOBJECT_TYPE& _rhs) noexcept { return _lhs.factory_id != _rhs.factory_id; }
[[nodiscard]] constexpr bool operator >  (const sOBJECT_TYPE& _lhs, const sOBJECT_TYPE& _rhs) noexcept { return _lhs.factory_id >  _rhs.factory_id; }
[[nodiscard]] constexpr bool operator >= (const sOBJECT_TYPE& _lhs, const sOBJECT_TYPE& _rhs) noexcept { return _lhs.factory_id >= _rhs.factory_id; }
[[nodiscard]] constexpr bool operator <  (const sOBJECT_TYPE& _lhs, const sOBJECT_TYPE& _rhs) noexcept { return _lhs.factory_id <  _rhs.factory_id; }
[[nodiscard]] constexpr bool operator <= (const sOBJECT_TYPE& _lhs, const sOBJECT_TYPE& _rhs) noexcept { return _lhs.factory_id <= _rhs.factory_id; }
			  	 
[[nodiscard]] constexpr bool operator == (const sOBJECT_TYPE& _lhs, const uint64_t& _rhs) noexcept { return _lhs.factory_id == _rhs; }
[[nodiscard]] constexpr bool operator != (const sOBJECT_TYPE& _lhs, const uint64_t& _rhs) noexcept { return _lhs.factory_id != _rhs; }
[[nodiscard]] constexpr bool operator >  (const sOBJECT_TYPE& _lhs, const uint64_t& _rhs) noexcept { return _lhs.factory_id >  _rhs; }
[[nodiscard]] constexpr bool operator >= (const sOBJECT_TYPE& _lhs, const uint64_t& _rhs) noexcept { return _lhs.factory_id >= _rhs; }
[[nodiscard]] constexpr bool operator <  (const sOBJECT_TYPE& _lhs, const uint64_t& _rhs) noexcept { return _lhs.factory_id <  _rhs; }
[[nodiscard]] constexpr bool operator <= (const sOBJECT_TYPE& _lhs, const uint64_t& _rhs) noexcept { return _lhs.factory_id <= _rhs; }


namespace std
{
	template <>
	struct hash<sOBJECT_TYPE>
	{
		[[nodiscard]] constexpr std::size_t operator() (const sOBJECT_TYPE& _key) const noexcept
		{
			return	static_cast<size_t>(_key.factory_id);
		}
	};
}



//-----------------------------------------------------------------------------
//
// sOBJECT_ID
//
//-----------------------------------------------------------------------------
class sOBJECT_ID
{
public:
	constexpr sOBJECT_ID() noexcept : value(0) {}
	constexpr sOBJECT_ID(const sOBJECT_ID& _copy) noexcept : value(_copy.value){}
	constexpr sOBJECT_ID(uint64_t _sid) noexcept : value(_sid) {}

public:
	[[nodiscard]] static sOBJECT_ID	generate() noexcept { return sOBJECT_ID(_generate()); }
	constexpr void		reset() noexcept { value = 0; }

	[[nodiscard]] constexpr bool empty() const noexcept { return value == 0; }
	[[nodiscard]] constexpr bool exist() const noexcept { return value != 0; }

public:
	constexpr sOBJECT_ID&	operator =  (const sOBJECT_ID& _rhs) noexcept { value =_rhs.value; return *this; }
	constexpr sOBJECT_ID&	operator =  (uint64_t _rhs) noexcept { value =_rhs; return *this; }
	[[nodiscard]] constexpr operator uint64_t() const noexcept { return static_cast<uint64_t>(value);}

private:
	[[nodiscard]] static uint64_t _generate() noexcept { static std::atomic<uint64_t> sid(0); uint64_t temp = ++sid; if (temp == 0) temp = ++sid; return temp; }

public:
			uint64_t	value;
};

[[nodiscard]] constexpr bool operator == (const sOBJECT_ID& _lhs, const sOBJECT_ID& _rhs) noexcept { return _lhs.value == _rhs.value; }
[[nodiscard]] constexpr bool operator != (const sOBJECT_ID& _lhs, const sOBJECT_ID& _rhs) noexcept { return _lhs.value != _rhs.value; }
[[nodiscard]] constexpr bool operator >= (const sOBJECT_ID& _lhs, const sOBJECT_ID& _rhs) noexcept { return _lhs.value >= _rhs.value; }
[[nodiscard]] constexpr bool operator >  (const sOBJECT_ID& _lhs, const sOBJECT_ID& _rhs) noexcept { return _lhs.value >  _rhs.value; }
[[nodiscard]] constexpr bool operator <= (const sOBJECT_ID& _lhs, const sOBJECT_ID& _rhs) noexcept { return _lhs.value <= _rhs.value; }
[[nodiscard]] constexpr bool operator <  (const sOBJECT_ID& _lhs, const sOBJECT_ID& _rhs) noexcept { return _lhs.value <  _rhs.value; }

namespace std
{
	template <>
	struct hash<sOBJECT_ID>
	{
		[[nodiscard]] constexpr std::size_t operator() (const sOBJECT_ID& _key) const noexcept
		{
			return	static_cast<size_t>(_key.value);
		}
	};
}


//-----------------------------------------------------------------------------
//
// sMAC_ADDRESS
//
//-----------------------------------------------------------------------------
struct sMAC_ADDRESS
{
public:
	union 
	{
		std::array<uint8_t, 8>	sll_addr;
		uint64_t				sll_mac;
	};

public:
	constexpr sMAC_ADDRESS() noexcept : sll_mac(0) {}

public:	
	[[nodiscard]] constexpr bool empty() const noexcept	{ return sll_mac == 0;}
	[[nodiscard]] constexpr bool exist() const noexcept	{ return sll_mac != 0;}
			constexpr void clear() noexcept { sll_mac = 0;}

public:
	constexpr sMAC_ADDRESS&	operator =  (const sMAC_ADDRESS& _rhs) noexcept	{ sll_mac =_rhs.sll_mac; return *this; }
	constexpr sMAC_ADDRESS&	operator =  (uint64_t _rhs) noexcept { sll_mac =_rhs; return *this; }
	[[nodiscard]] constexpr	operator uint64_t() const noexcept { return static_cast<uint64_t>(sll_mac);}
};

[[nodiscard]] constexpr bool operator == (const sMAC_ADDRESS& _lhs, const sMAC_ADDRESS& _rhs) noexcept { return _lhs.sll_mac == _rhs.sll_mac; }
[[nodiscard]] constexpr bool operator != (const sMAC_ADDRESS& _lhs, const sMAC_ADDRESS& _rhs) noexcept { return _lhs.sll_mac != _rhs.sll_mac; }
[[nodiscard]] constexpr bool operator <  (const sMAC_ADDRESS& _lhs, const sMAC_ADDRESS& _rhs) noexcept { return _lhs.sll_mac <  _rhs.sll_mac; }
[[nodiscard]] constexpr bool operator <= (const sMAC_ADDRESS& _lhs, const sMAC_ADDRESS& _rhs) noexcept { return _lhs.sll_mac <= _rhs.sll_mac; }
[[nodiscard]] constexpr bool operator >  (const sMAC_ADDRESS& _lhs, const sMAC_ADDRESS& _rhs) noexcept { return _lhs.sll_mac >  _rhs.sll_mac; }
[[nodiscard]] constexpr bool operator >= (const sMAC_ADDRESS& _lhs, const sMAC_ADDRESS& _rhs) noexcept { return _lhs.sll_mac >= _rhs.sll_mac; }

namespace CGDK
{
	template <class T>[[nodiscard]] std::basic_string_view<T> to_string(T* _str_address, std::size_t _max_length, const sMAC_ADDRESS& _mac_address) noexcept;
	template<> [[nodiscard]] std::string_view to_string<char>(char* _str_address, std::size_t _max_length, const sMAC_ADDRESS& _mac_address) noexcept;
	template<> [[nodiscard]] std::wstring_view to_string<wchar_t>(wchar_t* _str_address, std::size_t _max_length, const sMAC_ADDRESS& _mac_address) noexcept;

	template <class T>
	[[nodiscard]] std::basic_string<T>
	to_string(const sMAC_ADDRESS& _address) noexcept { T temp_str[256]; return std::basic_string<T>(CGDK::to_string(temp_str, 256, _address)); }

	template <class T, class Allocator = std::allocator<T>>
	[[nodiscard]] std::basic_string<T, std::char_traits<T>, Allocator>
	to_string(const sMAC_ADDRESS& _mac_address, const Allocator& _allocator) noexcept { T temp_str[256]; return std::basic_string<T, std::char_traits<T>, Allocator>(to_string<T>(temp_str, 256, _mac_address), _allocator); }
}

namespace std
{
	template <>
	struct hash<sMAC_ADDRESS>
	{
		[[nodiscard]] constexpr std::size_t operator() (const sMAC_ADDRESS& _key) const noexcept
		{
			return static_cast<size_t>(_key.sll_mac);
		}
	};
}


//-----------------------------------------------------------------------------
//
// sMAC_ADDRESS
//
//-----------------------------------------------------------------------------
namespace CGDK
{
	class Iquerier;
	class group_taits;

	namespace time_event
	{
		class Ientity;
	}
}

template <class T> struct is_general_object_type
{
	static const bool value = !std::is_base_of_v<CGDK::Iexecutable, T>
						   && !std::is_base_of_v<CGDK::Iexecutor, T>
						   && !std::is_base_of_v<CGDK::Iquerier, T>
						   //&& !std::is_base_of_v<CGDK::group_taits, T>
						   //&& !std::is_base_of_v<CGDK::time_event::Ientity, T>
							;
};

template <class T> [[nodiscard]] std::enable_if_t<is_general_object_type<T>::value, eOBJECT_TYPE> _get_object_type() noexcept { return eOBJECT_TYPE::NOT_DEFINED; }
template <class T> [[nodiscard]] std::enable_if_t<std::is_base_of_v<CGDK::Iexecutable, T> && !std::is_base_of_v<CGDK::Iexecutor, T> && !std::is_base_of_v<CGDK::Iquerier, T>, eOBJECT_TYPE> _get_object_type() noexcept { return eOBJECT_TYPE::EXECUTABLE; }
template <class T> [[nodiscard]] std::enable_if_t<std::is_base_of_v<CGDK::Iexecutor, T> && !std::is_base_of_v<CGDK::Iquerier, T>, eOBJECT_TYPE> _get_object_type() noexcept { return eOBJECT_TYPE::EXECUTOR; }
template <class T> [[nodiscard]] std::enable_if_t<std::is_base_of_v<CGDK::Iquerier, T>, eOBJECT_TYPE> _get_object_type() noexcept { return eOBJECT_TYPE::QUERIER; }
//template <class T> [[nodiscard]] std::enable_if_t<std::is_base_of_v<CGDK::group_taits, T>, eOBJECT_TYPE> _get_object_type() noexcept { return eOBJECT_TYPE::GROUP; }
//template <class T> [[nodiscard]] std::enable_if_t<std::is_base_of_v<CGDK::time_event::Ientity, T>, eOBJECT_TYPE> _get_object_type() noexcept { return eOBJECT_TYPE::EVENT_OBJECT; }

#if defined(_MSC_VER)
	#pragma warning(default:4201)
	#pragma warning(default:26495)
#endif
