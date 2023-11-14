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
//
// CGMessageMap
//
// 1. CGMessageMap�̶�...?
//    1) Message�� ó���� ���Ǹ� Map���·� �ۼ��� �� �ֵ��� �� ���̴�.
//
// 2. CGMessageMap�� ����
//    CGCII Message Map�� ����ϱ� ���ؼ��� �Ʒ��� ���� ������ �ۼ��� �ʿ��ϴ�.
//		
//    1) ���� Message Map�� ����ϰ����ϴ� Ŭ������ ���ǿ� �Ʒ��� ���� 
//       'DECLARE_CGMESSAGE_MAP'�� �߰��� �ش�.
//       �Ϲ������� �� ���� Class�� �����ϴ� ������Ͽ� �ۼ��Ѵ�.
//
//       class foo
//       {
//          ....
//
//          DECLARE_CGMASSAGE_MAP
//          ....
//       };
//
//    2) CPP���Ͽ� Message Map�� �Ʒ��� ���� �ۼ��Ѵ�.
//       Message Map ������ ������ 'BEGIN_CGMESAAGE_MAP(Ŭ������)' Ű���带
//       �ۼ��Ѵ�.
//       �׸��� �ʿ��� Message�� �� Message�� �޾��� �� ó���� �Լ����
//       �Լ��� �Ķ���͸� �Ʒ��� ���� ���ش�.
//             ON_MESSAGE(�޽���, �Լ���, �Ķ������)
//       �̶� �Ķ���ʹ� �ݵ�� sMESSAGE�� ��ӹ��� ���̾�� �ϰ� �޽����� ������ ��
//       ���� ��ġ�ؾ� �Ѵ�.
//       �⺻���� ���� �Ʒ��� ����.
//
//       BEGIN_CGMESSAGE_MAP(foo)
//             CGMESSAGE_TYPE(MESSAGE_SEND_A, on_message_A, sMESSAGE);
//             CGMESSAGE_TYPE(MESSAGE_SEND_B, on_message_B, sMESSAGE);
//       END_CGMESSAGE_MAP
//
//    3) �� �� on_message_A�Լ��� �Ʒ��� ���� �ۼ��Ѵ�.
//
//       int foo::on_message_A(sMESSAGE& _msg)
//       {
//           ...
//       }
//
//       *����: BEGIN_MESSAGE_MAP�� �ݵ�� CPP���Ͽ� �ۼ��ؾ� �ϸ� �������(.h)��
//              �ۼ��ؼ��� �ȵȴ�.
//    
//    4) ���������� �� Message Map�� ����ϱ� ���ؼ��� �ݵ�� �޽����� �޴� �Լ�
//       �� on_message()�Լ��� �Ʒ��� ���� Ű���带 �߰��� �־�� �Ѵ�.
//
//       int foo::on_message(sMESSAGE& _msg)
//       {
//           EXECUTE_CGMESSAGE_MAP(_msg);
//
//           ...
//
//           return 0;
//       }
//
//
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// ...
//-----------------------------------------------------------------------------
#if defined(_MSC_VER)
	#pragma warning(disable:4065)
#endif


//-----------------------------------------------------------------------------
// message map
//-----------------------------------------------------------------------------
// 1) declare message map
#define	DECLARE_CGMESSAGE_MAP	CGDK::result_code __execute_message(sMESSAGE& _msg);

// 2) declare message map
#define	DEFINE_PROCESS_MESSAGE			virtual	CGDK::result_code process_message(sMESSAGE& _msg) override	{ EXECUTE_CGMESSAGE_MAP(_msg); return eRESULT::BYPASS;}
#define	DEFINE_PROCESS_MESSAGE_BLOCK	virtual	CGDK::result_code process_message(sMESSAGE& _msg) override	{ EXECUTE_CGMESSAGE_MAP(_msg); return eRESULT::DONE;}
#define	DEFINE_ON_MESSAGE				virtual	CGDK::result_code on_message(sMESSAGE& _msg) override		{ EXECUTE_CGMESSAGE_MAP(_msg); return eRESULT::BYPASS;}
#define	DEFINE_ON_MESSAGE_BLOCK			virtual	CGDK::result_code on_message(sMESSAGE& _msg) override		{ EXECUTE_CGMESSAGE_MAP(_msg); return eRESULT::DONE;}

// 3) message mask
const CGDK::message_t eMESSAGE_MASK = 0x00ffffff;

// 4) execute message function
#define EXECUTE_PARENT_CGMESSAGE_MAP(parent, msg)				\
{																\
	auto _mm_result = parent::on_message(_msg);					\
																\
	if (_mm_result != eRESULT::BYPASS)							\
		return result;											\
}

#define	EXECUTE_CGMESSAGE_MAP(msg)								\
{																\
	auto xcg_result = __execute_message(msg);					\
																\
	if(xcg_result != eRESULT::BYPASS)							\
		return xcg_result;										\
}

// 5) execute message function
#define	EXECUTE_CLASS_CGMESSAGE_MAP(class_type, msg)			\
{																\
	auto xcg_result = class_type::__execute_message(msg);		\
																\
	if(xcg_result != eRESULT::BYPASS)							\
		return xcg_result;										\
}

// 6) begin mssage map head
#define	CGMESSAGE_MAP_HEAD										\
	{															\
		result_code _mm_result;									\
		switch(static_cast<CGDK::message_t>(_msg.message))		\
		{														\
		default:												\
				{												\
					_mm_result = eRESULT::BYPASS;				\
					break;

#define	CGMESSAGE_MAP_HEAD_MASK(mask)							\
	{															\
		result_code _mm_result;									\
		switch(static_cast<CGDK::message_t>(_msg.message) & mask)\
		{														\
		default:												\
				{												\
					_mm_result = eRESULT::BYPASS;				\
					break;


// head) execute message function
#define	BEGIN_CGMESSAGE_MAP(class_name)							\
	CGDK::result_code class_name::__execute_message(sMESSAGE& _msg)\
	CGMESSAGE_MAP_HEAD

#define	BEGIN_CGMESSAGE_MAP_MASK(class_name)					\
	CGDK::result_code class_name::__execute_message(sMESSAGE& _msg)\
	CGMESSAGE_MAP_HEAD_MASK(eMESSAGE_MASK)


#define	BEGIN_CGMESSAGE_MAP_TEMPLATE(class_name, type_a, type_b)		\
	CGDK::result_code class_name<type_a, type_b>::__execute_message(sMESSAGE& _msg) \
	CGMESSAGE_MAP_HEAD

#define	BEGIN_CGMESSAGE_MAP_TEMPLATE3(class_name, type_a, type_b, type_c)		\
	CGDK::CGDK::result_code class_name<type_a, type_b, type_c>::__execute_message(sMESSAGE& _msg) \
	CGMESSAGE_MAP_HEAD

#define	BEGIN_CGMESSAGE_MAP_TEMPLATE4(class_name, type_a, type_b, type_c, type_d) \
	CGDK::result_code class_name<type_a, type_b, type_c, type_d>::__execute_message(sMESSAGE& _msg) \
	CGMESSAGE_MAP_HEAD

#define	BEGIN_CGMESSAGE_MAP_TEMPLATE5(class_name, type_a, type_b, type_c, type_d, type_e) \
	CGDK::result_code class_name<type_a, type_b, type_c, type_d, type_e>::__execute_message(sMESSAGE& _msg) \
	CGMESSAGE_MAP_HEAD


#define	BEGIN_CGMESSAGE_MAP_MASK_TEMPLATE(class_name, type_a, type_b)	\
	CGDK::result_code class_name<type_a, type_b>::__execute_message(sMESSAGE& _msg) \
	CGMESSAGE_MAP_HEAD_MASK(eMESSAGE_MASK)

#define	BEGIN_CGMESSAGE_MAP_MASK_TEMPLATE3(class_name, type_a, type_b, type_c)	\
	CGDK::result_code class_name<type_a, type_b, type_c>::__execute_message(sMESSAGE& _msg)	\
	CGMESSAGE_MAP_HEAD_MASK(eMESSAGE_MASK)

#define	BEGIN_CGMESSAGE_MAP_MASK_TEMPLATE4(class_name, type_a, type_b, type_c, type_d)	\
	CGDK::result_code class_name<type_a, type_b, type_c, type_d>::__execute_message(sMESSAGE& _msg)	\
	CGMESSAGE_MAP_HEAD_MASK(eMESSAGE_MASK)

#define	BEGIN_CGMESSAGE_MAP_MASK_TEMPLATE5(class_name, type_a, type_b, type_c, type_d, type_e)	\
	CGDK::result_code class_name<type_a, type_b, type_c, type_d, type_e>::__execute_message(sMESSAGE& _msg)	\
	CGMESSAGE_MAP_HEAD_MASK(eMESSAGE_MASK)


#define	CGMESSAGE_TYPE(msg_type, function, type)				\
				}												\
		case	static_cast<CGDK::message_t>(msg_type):			\
				{												\
					_mm_result = function((type&)_msg);			\
					break;

#define	CGMESSAGE_TYPE_SUB(msg_type, msg_def)					\
				}												\
		case	static_cast<CGDK::message_t>(msg_type):			\
				{												\
					switch(static_cast<CGDK::message_t>(msg_def))\
					{											\
					default:									\
							{									\
								_mm_result = eRESULT::BYPASS;	\
								break;

// body) execute Message Function
#define	ON_CGMESSAGE(message, function, type)					\
						}										\
				case	static_cast<CGDK::message_t>(message):	\
						{										\
							_mm_result = function((type&)_msg);	\
							break;

#define	ON_CGMETHOD_RETURN(message, function, return_type)		\
						}										\
				case	static_cast<CGDK::message_t>(message):	\
						{										\
							auto temp_buffer = alloc_shared_buffer(sizeof(return_type));\
							temp_buffer.append<return_type>(function());\
							((sMESSAGE_BUFFER&)_msg).buf_message = temp_buffer;\
							_mm_result = eRESULT::DONE;			\
							break;

#define	ON_CGMETHOD(message, function)							\
						}										\
				case	static_cast<CGDK::message_t>(message):	\
						{										\
							function();							\
							_mm_result = eRESULT::DONE;			\
							break;

#define	END_SUB_CGMESSAGE_MAP									\
						}										\
				};												\
				break;

// tail) execute Message Function
#define	END_CGMESSAGE_MAP										\
				};												\
		};														\
		return _mm_result;										\
	}

// nested message map
#define	BEGIN_NESTED_CGMESSAGE_MAP								\
	CGMESSAGE_MAP_HEAD

#define	END_NESTED_CGMESSAGE_MAP								\
				};												\
		};														\
		if(_mm_result != eRESULT::BYPASS)						\
			return _mm_result;									\
	}

// attribute�� Message Map
#define	CGMESSAGE_TYPE_ATTRIBUTE								CGMESSAGE_TYPE_SUB(static_cast<CGDK::message_t>(CGMESSAGE::ATTRIBUTE), ((const sMESSAGE_BUFFER&)_msg).data()fer.front<CGDK::message_t>(4) & CGMESSAGE::SYSTEM::MASK)


//-----------------------------------------------------------------------------
// sub-message type
//-----------------------------------------------------------------------------
// 1) buffer message
#define	CGMESSAGE_TYPE_SUB_BUFFER								CGMESSAGE_TYPE_SUB(static_cast<CGDK::message_t>(CGMESSAGE::BUFFER), ((const sMESSAGE_BUFFER&)_msg).data()fer.front<CGDK::message_t>(4) & CGMESSAGE::SYSTEM::MASK)
#define	CGMESSAGE_TYPE_SUB_BUFFER_MESSAGE(msg)					CGMESSAGE_TYPE_SUB(msg, ((const sMESSAGE_BUFFER&)_msg).data()fer.front<CGDK::message_t>(4) & CGMESSAGE::SYSTEM::MASK)

// 2) declare message map
#define	DECLARE_CGMESSAGE_MAP_SUB(name)	CGDK::result_code __execute_message##name(sMESSAGE& _msg);

// 3) execute message function
#define	EXECUTE_CGMESSAGE_MAP_SUB(name, msg)					\
{																\
	auto xcg_result = __execute_message##name(msg);				\
																\
	if(xcg_result != eRESSULT::BYPASS)							\
		return xcg_result;										\
}

// head) execute message function
#define	BEGIN_CGMESSAGE_MAP_SUB(class_name, name)				\
	CGDK::result_code class_name::__execute_message##name(sMESSAGE& _msg) \
	{															\
		switch(_msg.message)									\
		{														\
		default:												\
				{												\
					return eRESSULT::BYPASS;

// head) execute message function
#define	BEGIN_CGMESSAGE_MAP_SUB_MASK(class_name, name)			\
	CGDK::result_code class_name::__execute_message##name(sMESSAGE& _msg) \
	{															\
		switch(static_cast<CGDK::message_t>(_msg.message) & eMESSAGE_MASK)	\
		{														\
		default:												\
				{												\
					return eRESSULT::BYPASS;
