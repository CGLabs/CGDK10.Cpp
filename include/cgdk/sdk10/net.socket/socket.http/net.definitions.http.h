//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                        network socket http classes                        *
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
// 1. http definitions
//-----------------------------------------------------------------------------
// 1) ...
constexpr uint32_t HTTP_VERSION(uint32_t _major, uint32_t _minor) noexcept { return (_major << 16) | _minor; }
constexpr uint32_t HTTP_VERSION_MAJOR(uint32_t _version) noexcept { return (_version>>16); }
constexpr uint32_t HTTP_VERSION_MINOR(uint32_t _version) noexcept { return (_version & 0x0000ffff); }


//-----------------------------------------------------------------------------
// 2. http message
//-----------------------------------------------------------------------------
namespace eMESSAGE
{
	namespace SYSTEM
	{
		const uint32_t	HTTP_REQUEST	 = NETWORK |  16;
		const uint32_t	HTTP_RESPONSE	 = NETWORK |  17;
		const uint32_t	WEBSOCKET		 = NETWORK |  18;
	}
}


//-----------------------------------------------------------------------------
// 3. http emum
//-----------------------------------------------------------------------------

enum class eHTTP_PROTOCOL : uint32_t
{
	NOT_DEFINED_		 = 0,
	HTTP_				 = 1,
	WEBSOCKET_			 = 2,
	MAX_
};
template<class T> std::basic_string_view<T> to_string(eHTTP_PROTOCOL _protocol) noexcept;

enum class eHTTP_SCHEME_TYPE : uint32_t
{
	NOT_DEFINED_		 = 0,
	FTP_				 = 1,
	GOPHER_				 = 2,
	HTTP_				 = 3,
	HTTPS_				 = 4,
	FILE_				 = 5,
	NEWS_				 = 6,
	MAILTO_				 = 7,
	SOCKS_				 = 8,
	JAVASCRIPT_			 = 9,
	VBSCRIPT_			 = 10,
	RES_				 = 11,
	WS_					 = 12,
	WSS_				 = 13,
};
template<class T> std::basic_string_view<T> to_string(eHTTP_SCHEME_TYPE _scheme_type) noexcept;

enum class eHTTP_METHOD : uint32_t
{
	NONE_				 = 0,
	GET_				 = 1,
	POST_				 = 2,
	PUT_				 = 3,
	PATCH_				 = 4,
	DELETE_				 = 5,
	COPY_				 = 6,
	HEAD_				 = 7,
	OPTIONS_			 = 8,
	LINK_				 = 9,
	UNLINK_				 = 10,
	PURGE_				 = 11,
	LOCK_				 = 12,
	UNLOCK_				 = 13,
	PROPFIND_			 = 14,
	VIEW_				 = 15,
	TRACE_				 = 16,
	BINARY_				 = 17,
	TEXT_				 = 18,
	MAX_,

	DEFAULT_			 = GET_
};
template<class T> std::basic_string_view<T> to_string(eHTTP_METHOD _http_method) noexcept;

enum class eHTTP_STATUS_CODE : uint32_t
{
	NOT_DEFINED_							 = 0,	//			"Not defined"

	CONTINUE_								 = 100,	//			"Continue"

	SWITCHING_PROTOCOLS_					 = 101,	//			"Switching Protocols"
	PROCESSING_								 = 102,	//			"Processing"
	EARLY_HINTS_							 = 103,	//			"Early Hints"

	OK_										 = 200,	//			"OK"
	CREATED_								 = 201,	//			"Created"
	ACCEPTED_								 = 202,	//			"Accepted"
	NON_AUTHORITATIVE_INFORMAMTION_			 = 203,	//			"Non-Authoritative Information"
	NO_CONTENT_								 = 204,	//			"No Content"
	RESET_CONTENT_							 = 205,	//			"Reset Content"
	PARTIAL_CONTENT_						 = 206,	//			"Partial Content"
	MULTI_STATUS_							 = 207,	//			"Multi-Status"
	ALEADY_REPORTED_						 = 208,	//			"Already Reported"
	THIS_IS_FINE_							 = 218,	// (Apache>	"This is fine"
	IM_USED_								 = 226,	//			"IM Used"

	MULTIPLE_CHOICES_						 = 300,	//			"Multiple Choices"
	MOVED_PERMANENTLY_						 = 301,	//			"Moved Permanently"
	FOUND_									 = 302,	//			"Found"
	SEE_OTHER_								 = 303,	//			"See Other"
	NOT_MODIFIED_							 = 304,	//			"Not Modified"
	USE_PROXY_								 = 305,	//			"Use Proxy"
	TEMPORARY_REDIRECT_						 = 307,	//			"Temporary Redirect"
	PERMANENT_REDIRECT_						 = 308,	//			"Permanent Redirect"

	BAD_REQUEST_							 = 400,	//			"Bad Request"
	UNAUTHORIZED_							 = 401,	//			"Unauthorized"
	PAYMENT_REQUIRED_						 = 402,	//			"Payment Required"
	FORBIDDEN_								 = 403,	//			"Forbidden"
	NOT_FOUND_								 = 404,	//			"Not Found"
	METHOD_NOT_ALLOWED_						 = 405,	//			"Method Not Allowed"
	NOT_ACCEPTABLE_							 = 406,	//			"Not Acceptable"
	PROXY_AUTHENTICATION_REQUIRED_			 = 407,	//			"Proxy Authentication Required"
	REQUEST_TIMEOUT_						 = 408,	//			"Request Timeout"
	CONFLICT_								 = 409,	//			"Conflict"
	GONE_									 = 410,	//			"Gone"
	LENGTH_REQURIED_						 = 411,	//			"Length Required"
	PRECONDITION_FAILED_					 = 412,	//			"Precondition Failed"
	PAYLOAD_TOO_LARGE_						 = 413,	//			"Payload Too Large"
	URI_TOO_LONG_							 = 414,	//			"URI Too Long"
	UNSUPPORTED_MEDIA_TYPE_					 = 415,	//			"Unsupported Media Type"
	RANGE_NOT_SATISFIABLE_					 = 416,	//			"Range Not Satisfiable"
	EXPECTATION_FAILED_						 = 417,	//			"Expectation Failed"
	PAGE_EXPIRED_							 = 419,	// (Laravel)"Page Expired"
	METHOD_FAILURE_							 = 420,	// (Spring)	"Method Failure/Enhance YOur Calm"
	MISDIRECTED_REQUEST_					 = 421,	//			"Misdirected Request"
	UNPROCESSABLE_ENTITY_					 = 422,	//			"Unprocessable Entity"
	LOCKED_									 = 423,	//			"Locked"
	FAILED_DEPENDENCY_						 = 424,	//			"Failed Dependency"
	TOO_EARLY_								 = 425,	//			"Too Early"
	UPGRADE_REQUIRED_						 = 426,	//			"Upgrade Required"
	PRECONDITION_REQUIRED_					 = 428,	//			"Precondition Required"
	TOO_MANY_REQUESTS_						 = 429,	//			"Too Many Requests"
	REQUEST_HEADER_FIELDS_TOO_LARGE_SHOPIFY_ = 430,	// (Shopify)"Request Header Fields Too Large"
	REQUEST_HEADER_FIELDS_TOO_LARGE_		 = 431,	//			"Request Header Fields Too Large"
	LOGIN_TIME_OUT_							 = 440,	// (Inter-)	"Login Time-out"
	NO_RESPONSE_							 = 444,	// (nginx)	"No Response"
	RETRY_WWITH_							 = 449,	// (Inter-)	"Retry With"
	BLOCKED_BY_WINDOWS_PARENTAL_CONTROL_	 = 450,	// (MS)		"Blocked by Windows Parental Controls"
	UNAVAILABLE_FOR_LEGAL_REASONS_			 = 451,	//			"Unavailable For Legal Reasons"
	AWS_ELASTIC_460							 = 460,	// (AWS)	"ASW_ELASTIC_460"
	AWS_ELASTIC_463							 = 463,	// (AWS)	"ASW_ELASTIC_463"
	REQUEST_HEADER_TOO_LARGE_				 = 494,	// (nginx)	"Request header too large"
	SSL_CERTIFICATED_ERROR_					 = 495,	// (nginx)	"SSL Certificate Error"
	SSL_CERTIFICATED_REQUIRED_				 = 496,	// (nginx)	"SSL Certificate Required"
	HTTP_REQUEST_SEND_TO_HTTPS_PORT_		 = 497,	// (nginx)	"HTTP Request Send to HTTPS Port"
	INVALID_TOKEN_							 = 498,	// (Esri)	"Invalid Token"
	CLIENT_CLOSED_REQUEST_					 = 499,	// (nginx)	"Client Closed Request"

	INTERNAL_SERVER_ERROR_					 = 500,	//			"Internal Server Error"
	NOT_IMPLEMENTED_						 = 501,	//			"Not Implemented"
	BAD_GATEWAY_							 = 502,	//			"Bad Gateway"
	SERVICE_UNAVAILABLE_					 = 503,	//			"Service Unavailable"
	GATEWAY_TIMEOUT_						 = 504,	//			"Gateway Timeout"
	HTTP_VERSION_NOT_SUPPORTED_				 = 505,	//			"HTTP Version Not Supported"
	VARIANT_ALSO_NEGOTIATES_				 = 506,	//			"Variant Also Negotiates"
	INSUFFICIENT_STORAGE_					 = 507,	//			"Insufficient Storage"
	LOOP_DETECTED_							 = 508,	//			"Loop Detected"
	BANDWIDTH_LIMIT_EXCEEDED_				 = 509,	// (Apache)	"Bandwidth Limit Exceeded"
	NOT_EXTENDED_							 = 510,	//			"Not Extended"
	NETWORK_AUTHENTIICATION_REQUIRED_		 = 511,	//			"Network Authentication Required"
	UNKNOWN_ERROR_							 = 520, // (Cloudf)	"Unknown Error"
	WEB_SERVER_IS_DOWN_						 = 521, // (Cloudf)	"Web Server id Down"
	CONNECTION_TIMED_OUT_					 = 522, // (Cloudf)	"Connection Timed Out"
	ORIGIN_IS_UNREACHABLE_					 = 523, // (Cloudf)	"Origin is Unreachable"
	A_TIMEOUT_OCCURED_						 = 524, // (Cloudf)	"A Timeout Occured"
	SSL_HAND_SHAKE_FAILED_					 = 525, // (Cloudf)	"SSL Handshake Failed"
	INVALID_SSL_CERTIFICATE_				 = 526, // (Cloudf)	"Invalid SSL Certificate"
	RAILGUN_ERROR_							 = 527, // (Cloudf)	"Railgun Error"
	ORIGIN_DNS_ERROR_						 = 530, // (Cloudf)	"Origin DNS Error"
	NETWORK_READ_TIMEOUT_ERROR_				 = 598, // (Inf..)	"Network read timeout error"
};
template<class T> std::basic_string_view<T> to_string(eHTTP_STATUS_CODE _http_status_code) noexcept;
template<> struct is_result_code_enum<CGDK::eHTTP_STATUS_CODE> : std::true_type {};


//-----------------------------------------------------------------------------
// 3. http struct
//-----------------------------------------------------------------------------
struct sHTTP_HEADER_ITEM
{
public:
	std::string_view	key;
	std::string_view	value;
};

struct sHTTP_PATH_ITEM : public sHTTP_HEADER_ITEM
{
public:
	sHTTP_PATH_ITEM() : sHTTP_HEADER_ITEM(), type(0) {}

public:
	char				type;
};


}
