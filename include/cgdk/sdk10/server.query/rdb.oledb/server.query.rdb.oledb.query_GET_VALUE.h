//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                        Server Query oledb Classes                         *
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
//
// query::rdb::odbc::OLEDB_GET_VALUE
//
//  1) Iserver_query와 Command를 상속받아 만든 기본 Query다.
//  2) Querier에 Query를 Post하거나 request하게 되면 session을 할당받게 된다.
//  3) session을 할당받게 되면 Query String을 넘겨 execute_query함수를 호출함으로써
//     Query를 수행할 수 있다.
//  4) 그리고 Query가 완료된 후 close_query를 호출하여 Query를 종료할 수 있다.
//  5) start와 stop은 원하는 만큼 수행할 수 있으며 최종적으로 ProcessQuery()
//     함수가 종료되면 session도 반납되게 된다.
//
// 
//-----------------------------------------------------------------------------
// 1) general
template <class T, class F = void>
class _OLEDB_DEFAULT_PARAM
{
public:
	using type = T;
};

// 2) for wchar_t
#if defined(__linux__)
template <>
class _OLEDB_DEFAULT_PARAM<std::wstring, std::enable_if_t<sizeof(wchar_t) != sizeof(char16_t)>>
{
public:
	using type = char16_t*;
};

template <>
class _OLEDB_DEFAULT_PARAM<std::wstring_view, std::enable_if_t<sizeof(wchar_t) != sizeof(char16_t)>>
{
public:
	using type = char16_t*;
};

template <>
class _OLEDB_DEFAULT_PARAM<wchar_t*, std::enable_if_t<sizeof(wchar_t) != sizeof(char16_t)>>
{
public:
	using type = char16_t*;
};
#endif

// 3) 
template <class T>
class _OLEDB_DEFAULT_PARAM<std::basic_string<T>, void>
{
public:
	using type = T*;
};

template <class T>
class _OLEDB_DEFAULT_PARAM<std::basic_string_view<T>, void>
{
public:
	using type = T*;
};

template <class T>
class _OLEDB_DEFAULT_PARAM<T*, typename std::enable_if<is_string_type_v<T>>::type>
{
public:
	using type = T*;
};


//-----------------------------------------------------------------------------
//
// general
//
//-----------------------------------------------------------------------------
template <class TSOURCE, class TDEST, class F = void> 
class OLEDB_GET_VALUE
{
public:
	using TRETURN = TDEST;
	template<class TQUERY>
	static TRETURN get(TQUERY* _pquery, std::size_t _ordinal) { return _get<TQUERY, TDEST>(_pquery, _ordinal); }

	template <class TQUERY, class T>
	[[nodiscard]] static std::enable_if_t<std::is_same_v<TSOURCE, T>, TRETURN>
	_get(TQUERY* _pquery, std::size_t _ordinal)
	{
		return *(T*)_pquery->GetValue(static_cast<DBORDINAL>(_ordinal));
	} 

	template <class TQUERY, class T>
	[[nodiscard]] static std::enable_if_t<!std::is_same_v<TSOURCE, T>, TRETURN>
	_get(TQUERY* _pquery, std::size_t _ordinal)
	{
		return static_cast<T>(*(TSOURCE*)_pquery->GetValue(_ordinal));
	} 
};


//-----------------------------------------------------------------------------
//
// bool
//
//-----------------------------------------------------------------------------
template <class TDEST>
class OLEDB_GET_VALUE<bool, TDEST, void>
{
public:
	using TRETURN = TDEST;
	template<class TQUERY>
	static TRETURN get(TQUERY* _pquery, std::size_t _ordinal) { return _get<TQUERY, TDEST>(_pquery, _ordinal); }

	template <class TQUERY, class T>
	[[nodiscard]] static std::enable_if_t<std::is_same_v<bool, T>, TRETURN>
	_get(TQUERY* _pquery, std::size_t _ordinal)
	{
		return *(VARIANT_BOOL*)_pquery->GetValue(static_cast<DBORDINAL>(_ordinal));
	}

	template <class TQUERY, class T>
	[[nodiscard]] static std::enable_if_t<!std::is_same_v<bool, T>, TRETURN>
	_get(TQUERY* _pquery, std::size_t _ordinal)
	{
		return static_cast<T>(_get<bool,bool>(_pquery, _ordinal));
	}
};


//-----------------------------------------------------------------------------
//
// integer
//
//-----------------------------------------------------------------------------
template <class TSOURCE, class TDEST>
class OLEDB_GET_VALUE<TSOURCE, TDEST, std::enable_if_t<is_integer_type<TSOURCE>::value>>
{
public:
	using TRETURN = TDEST;
	template<class TQUERY>
	[[nodiscard]] static TRETURN get(TQUERY* _pquery, std::size_t _ordinal) { return _get<TQUERY, TDEST>(_pquery, _ordinal); }

	template <class TQUERY, class T>
	[[nodiscard]] static std::enable_if_t<std::is_same_v<TSOURCE, T>, TRETURN>
		_get(TQUERY* _pquery, std::size_t _ordinal)
	{
		// declare)
		DBTYPE type;
		T value;

		// 1) colume type을 읽는다.
		_pquery->GetColumnType((DBORDINAL)_ordinal, &type);

		// 2) colume type에 따른 처리를 한다.
		switch (type)
		{
		case	DBTYPE_I1:
				value = static_cast<T>(*reinterpret_cast<uint8_t*>(_pquery->GetValue(static_cast<DBORDINAL>(_ordinal))));
				break;

		case	DBTYPE_I2:
				value = static_cast<T>(*reinterpret_cast<uint16_t*>(_pquery->GetValue(static_cast<DBORDINAL>(_ordinal))));
				break;

		case	DBTYPE_I4:
				value = static_cast<T>(*reinterpret_cast<uint32_t*>(_pquery->GetValue(static_cast<DBORDINAL>(_ordinal))));
				break;

		case	DBTYPE_R4:
				value = static_cast<T>(*reinterpret_cast<float*>(_pquery->GetValue(static_cast<DBORDINAL>(_ordinal))));
				break;

		case	DBTYPE_R8:
				value = static_cast<T>(*reinterpret_cast<double*>(_pquery->GetValue(static_cast<DBORDINAL>(_ordinal))));
				break;

		case	DBTYPE_I8:
				value = static_cast<T>(*reinterpret_cast<uint64_t*>(_pquery->GetValue(static_cast<DBORDINAL>(_ordinal))));
				break;

		case	DBTYPE_UI1:
				value = static_cast<T>(*reinterpret_cast<int8_t*>(_pquery->GetValue(static_cast<DBORDINAL>(_ordinal))));
				break;

		case	DBTYPE_UI2:
				value = static_cast<T>(*reinterpret_cast<int16_t*>(_pquery->GetValue(static_cast<DBORDINAL>(_ordinal))));
				break;

		case	DBTYPE_UI4:
				value = static_cast<T>(*reinterpret_cast<int32_t*>(_pquery->GetValue(static_cast<DBORDINAL>(_ordinal))));
				break;

		case	DBTYPE_UI8:
				value = static_cast<T>(*reinterpret_cast<int64_t*>(_pquery->GetValue(static_cast<DBORDINAL>(_ordinal))));
				break;

		default:
				throw throwable::failure(eRESULT::INVALID_ARGUMENT);
		}

		// return)
		return value;
	}

	template <class TQUERY, class T>
	[[nodiscard]] static std::enable_if_t<!std::is_same_v<TSOURCE, T>, TRETURN>
		_get(TQUERY* _pquery, std::size_t _ordinal)
	{
		return static_cast<T>(*(TSOURCE*)_pquery->GetValue(_ordinal));
	}
};


//-----------------------------------------------------------------------------
//
// float/real/ ...
//
//-----------------------------------------------------------------------------
template <class TSOURCE, class TDEST>
class OLEDB_GET_VALUE<TSOURCE, TDEST, std::enable_if_t<is_float_type<TSOURCE>::value>>
{
public:
	using TRETURN = TDEST;
	template<class TQUERY>
	[[nodiscard]] static TRETURN get(TQUERY* _pquery, std::size_t _ordinal) { return _get<TQUERY, TDEST>(_pquery, _ordinal); }

	template <class TQUERY, class T>
	[[nodiscard]] static std::enable_if_t<std::is_same_v<TSOURCE, T>, TRETURN>
		_get(TQUERY* _pquery, std::size_t _ordinal)
	{
		// declare)
		DBTYPE type;
		T value;

		// 1) colume type을 읽는다.
		_pquery->GetColumnType((DBORDINAL)_ordinal, &type);

		// 2) colume type에 따른 처리를 한다.
		switch (type)
		{
		case	DBTYPE_I1:
				value = static_cast<T>(*reinterpret_cast<uint8_t*>(_pquery->GetValue(static_cast<DBORDINAL>(_ordinal))));
				break;

		case	DBTYPE_I2:
				value = static_cast<T>(*reinterpret_cast<uint16_t*>(_pquery->GetValue(static_cast<DBORDINAL>(_ordinal))));
				break;

		case	DBTYPE_I4:
				value = static_cast<T>(*reinterpret_cast<uint32_t*>(_pquery->GetValue(static_cast<DBORDINAL>(_ordinal))));
				break;

		case	DBTYPE_R4:
				value = static_cast<T>(*reinterpret_cast<float*>(_pquery->GetValue(static_cast<DBORDINAL>(_ordinal))));
				break;

		case	DBTYPE_R8:
				value = static_cast<T>(*reinterpret_cast<double*>(_pquery->GetValue(static_cast<DBORDINAL>(_ordinal))));
				break;

		case	DBTYPE_I8:
				value = static_cast<T>(*reinterpret_cast<uint64_t*>(_pquery->GetValue(static_cast<DBORDINAL>(_ordinal))));
				break;

		case	DBTYPE_UI1:
				value = static_cast<T>(*reinterpret_cast<int8_t*>(_pquery->GetValue(static_cast<DBORDINAL>(_ordinal))));
				break;

		case	DBTYPE_UI2:
				value = static_cast<T>(*reinterpret_cast<int16_t*>(_pquery->GetValue(static_cast<DBORDINAL>(_ordinal))));
				break;

		case	DBTYPE_UI4:
				value = static_cast<T>(*reinterpret_cast<int32_t*>(_pquery->GetValue(static_cast<DBORDINAL>(_ordinal))));
				break;

		case	DBTYPE_UI8:
				value = static_cast<T>(*reinterpret_cast<int64_t*>(_pquery->GetValue(static_cast<DBORDINAL>(_ordinal))));
				break;

		default:
				throw throwable::failure(eRESULT::INVALID_ARGUMENT);
		}

		// return)
		return value;
	}

	template <class TQUERY, class T>
	[[nodiscard]] static std::enable_if_t<!std::is_same_v<TSOURCE, T>, TRETURN>
		_get(TQUERY* _pquery, std::size_t _ordinal)
	{
		return static_cast<T>(_pquery->GetValue(static_cast<DBORDINAL>(_ordinal)));
	}
};


//-----------------------------------------------------------------------------
//
// string
//
//-----------------------------------------------------------------------------
template <class T, class F = void> class _value_type											{};
template <class T> class				 _value_type<T*, std::enable_if_t<is_string_type_v<T>>> { public: using type = T; };
template <class T> class				 _value_type<std::basic_string_view<T>, void>			{ public: using type = T; };
template <class T> class				 _value_type<std::basic_string<T>, void>				{ public: using type = T; };

template <class TSOURCE, class TDEST>
class OLEDB_GET_VALUE<TSOURCE*, TDEST, std::enable_if_t<is_string_type_v<TSOURCE>>>
{
public:
	using value_type = typename _value_type<TDEST>::type;
	using TRETURN = std::basic_string<value_type>;

	template<class TQUERY>
	[[nodiscard]] static TRETURN get(TQUERY* _pquery, std::size_t _ordinal)
	{
		// declare)
		DBTYPE type;
		TRETURN value;

		// 1) colume type을 읽는다.
		_pquery->GetColumnType((DBORDINAL)_ordinal, &type);

		// 2) colume type에 따른 처리를 한다.
		switch (type)
		{
		case	DBTYPE_STR:
				value = _get<TQUERY, value_type, char>(_pquery, _ordinal);
				break;

		case	DBTYPE_WSTR:
				value = _get<TQUERY, value_type, wchar_t>(_pquery, _ordinal);
				break;

		default:
				throw throwable::failure(eRESULT::INVALID_ARGUMENT);
		}

		// return)
		return value;
	}

	template <class TQUERY, class T_D, class T_S>
	[[nodiscard]] static std::enable_if_t<std::is_same_v<std::decay_t<T_S>, T_D>, TRETURN>
	_get(TQUERY* _pquery, std::size_t _ordinal)
	{
		return TRETURN((T_D*)_pquery->GetValue(_ordinal));
	}
	   
	template <class TQUERY, class T_D, class T_S>
	[[nodiscard]] static std::enable_if_t<!std::is_same_v<std::decay_t<T_S>, T_D>, TRETURN>
	_get(TQUERY* _pquery, std::size_t _ordinal)
	{
		// 1) 
		T_S* psource = (T_S*)_pquery->GetValue(_ordinal);

		// declare)
		DBLENGTH length = 0;

		// declare)
		TRETURN str_dest;

		// 2) get length
		_pquery->GetLength(_ordinal, &length);

		// check) ...
		RETURN_IF(length == 0, str_dest)

		// 3) reserve
		str_dest.resize(length);

		// 4) ...
		encode_string(&str_dest.front(), std::basic_string_view<T_S>{ psource, length / sizeof(T_S) }, length + 1);

		// return) 
		return str_dest;
	}
};


//-----------------------------------------------------------------------------
//
// numeric
//
//-----------------------------------------------------------------------------
template <class TDEST>
class OLEDB_GET_VALUE<NUMERIC, TDEST, void>
{
public:
	using TRETURN = TDEST;

	template<class TQUERY>
	[[nodiscard]] static TRETURN get(TQUERY* _pquery, std::size_t _ordinal) { return _get<TQUERY, TDEST>(_pquery, _ordinal);	}

	template <class TQUERY, class T>
	[[nodiscard]] static std::enable_if_t<std::is_same_v<NUMERIC, T>, TRETURN>
	_get(TQUERY* _pquery, std::size_t _ordinal)
	{
		return __to_numeric(*(DB_NUMERIC*)_pquery->GetValue(static_cast<DBORDINAL>(_ordinal)));
	}

	template <class TQUERY, class T>
	[[nodiscard]] static std::enable_if_t<!std::is_same_v<NUMERIC, T>, TRETURN>
	_get(TQUERY* _pquery, std::size_t _ordinal)
	{
		// 1) get ...
		auto num_source = __to_numeric(*(DB_NUMERIC*)_pquery->GetValue(static_cast<DBORDINAL>(_ordinal)));

		// return) 
		return T(num_source);
	}
};


//-----------------------------------------------------------------------------
//
// time_point (time_stamp, datetime)
//
//-----------------------------------------------------------------------------
template <class TDEST>
class OLEDB_GET_VALUE<chrono::time::time_point, TDEST, void>
{
public:
	using TRETURN = TDEST;
	template<class TQUERY>
	[[nodiscard]] static TRETURN get(TQUERY* _pquery, std::size_t _ordinal) { return _get<TQUERY, TDEST>(_pquery, _ordinal); }

	template <class TQUERY, class T>
	[[nodiscard]] static std::enable_if_t<std::is_same_v<chrono::time::time_point, T>, TRETURN>
	_get(TQUERY* _pquery, std::size_t _ordinal)
	{
		// declare) 
		DBTYPE type;
		chrono::time::time_point result;

		// 1) colume type을 읽는다.
		_pquery->GetColumnType((DBORDINAL)_ordinal, &type);

		// 2) colume type에 따른 처리를 한다.
		switch(type)
		{
		case	DBTYPE_FILETIME:
				{
					FILETIME temp_time;
					_pquery->GetValue<FILETIME>(static_cast<DBORDINAL>(_ordinal), &temp_time);

					SYSTEMTIME time_dest;
					FileTimeToSystemTime(&temp_time, &time_dest);

					result = chrono::from_SYSTEMTIME<chrono::time::time_point>(time_dest);
				}
				break;

		case	DBTYPE_BYTES:
				{
					result = chrono::from_date_time<chrono::time::time_point>(*(chrono::date_time*)_pquery->GetValue(_ordinal));
				}
				break;

		case	DBTYPE_STR:
				{
					auto temp = (char*)_pquery->GetValue(_ordinal);
					result = from_string<chrono::time::time_point>(temp);
				}
				break;

		case	DBTYPE_WSTR:
				{
					auto temp = (wchar_t*)_pquery->GetValue(_ordinal);
					result = from_string<chrono::time::time_point>(temp);
				}
				break;

		case	DBTYPE_DBDATE:
				{
					tagDBDATE temp_time;
					_pquery->GetValue<tagDBDATE>(static_cast<DBORDINAL>(_ordinal), &temp_time);

					chrono::date_time temp_dt;
					temp_dt.t_year  = temp_time.year;
					temp_dt.t_month = temp_time.month;
					temp_dt.t_day   = temp_time.day;

					result = chrono::from_date_time<chrono::time::time_point>(temp_dt);
				}
				break;

		case	DBTYPE_DBTIME:
				{
					tagDBTIME temp_time;
					_pquery->GetValue<tagDBTIME>(static_cast<DBORDINAL>(_ordinal), &temp_time);

					chrono::date_time temp_dt;
					temp_dt.t_hour   = temp_time.hour;
					temp_dt.t_minute = temp_time.minute;
					temp_dt.t_second = temp_time.second;

					result = chrono::from_date_time<chrono::time::time_point>(temp_dt);
				}
				break;

		case	DBTYPE_DBTIMESTAMP:
				{
					result = chrono::from_date_time<chrono::time::time_point>(*(chrono::date_time*)_pquery->GetValue(static_cast<DBORDINAL>(_ordinal)));
				}
				break;



		default:
				throw throwable::failure(eRESULT::INVALID_ARGUMENT);
		}

		// return) 
		return result;
	}

	template <class TQUERY, class T>
	[[nodiscard]] static std::enable_if_t<!std::is_same_v<chrono::time::time_point, T>, TRETURN>
	_get(TQUERY* _pquery, std::size_t _ordinal)
	{
		return T(_get<chrono::time::time_point, chrono::time::time_point>(_pquery, _ordinal));
	}
};

template <class TDEST>
class OLEDB_GET_VALUE<chrono::time::utc::time_point, TDEST, void>
{
public:
	using TRETURN = TDEST;
	template<class TQUERY>
	[[nodiscard]] static TRETURN get(TQUERY* _pquery, std::size_t _ordinal) { return _get<TQUERY, TDEST>(_pquery, _ordinal); }

	template <class TQUERY, class T>
	[[nodiscard]] static std::enable_if_t<std::is_same_v<chrono::time::utc::time_point, T>, TRETURN>
	_get(TQUERY* _pquery, std::size_t _ordinal)
	{
		return T(OLEDB_GET_VALUE<chrono::time::time_point, chrono::time::time_point>::get(_pquery, _ordinal));
	}

	template <class TQUERY, class T>
	[[nodiscard]] static std::enable_if_t<!std::is_same_v<chrono::time::utc::time_point, T>, TRETURN>
	_get(TQUERY* _pquery, std::size_t _ordinal)
	{
		return T(_get<chrono::time::time_point, chrono::time::time_point>(_pquery, _ordinal));
	}
};

template <class TDEST>
class OLEDB_GET_VALUE<chrono::time::local::time_point, TDEST, void>
{
public:
	using TRETURN = TDEST;
	template<class TQUERY>
	[[nodiscard]] static TRETURN get(TQUERY* _pquery, std::size_t _ordinal) { return _get<TQUERY, TDEST>(_pquery, _ordinal); }

	template <class TQUERY, class T>
	[[nodiscard]] static std::enable_if_t<std::is_same_v<chrono::time::local::time_point, T>, TRETURN>
	_get(TQUERY* _pquery, std::size_t _ordinal)
	{
		return T(OLEDB_GET_VALUE<chrono::time::time_point, chrono::time::time_point>::get(_pquery, _ordinal));
	}

	template <class TQUERY, class T>
	[[nodiscard]] static std::enable_if_t<!std::is_same_v<chrono::time::local::time_point, T>, TRETURN>
	_get(TQUERY* _pquery, std::size_t _ordinal)
	{
		return  T(_get<chrono::time::time_point, chrono::time::time_point>(_pquery, _ordinal));
	}
};


//-----------------------------------------------------------------------------
//
// struct
//
//-----------------------------------------------------------------------------
template <class TQUERY, std::size_t INDEX>
struct any_constructor_get_value
{
	TQUERY* pquery;
	std::size_t ordinal;
	template <class Type>
	constexpr operator Type() const
	{
		return OLEDB_GET_VALUE<typename _OLEDB_DEFAULT_PARAM<Type>::type, Type>::get(pquery, ordinal + INDEX);
	}
};

template <class TQUERY, class T, std::size_t... I>
constexpr T get_value_member_impl(TQUERY* _pquery, std::size_t _ordinal, std::index_sequence<I...>)
{
	return T{ any_constructor_get_value<TQUERY,I>{_pquery, _ordinal}... };
}

template <class T, class TDEST>
class OLEDB_GET_VALUE<T, TDEST, std::enable_if_t<is_struct_serializable_v<T>>>
{
public:
	using TRETURN = TDEST;
	template<class TQUERY>
	static TRETURN get(TQUERY* _pquery, std::size_t _ordinal)
	{
		// check)
		static_assert(!std::is_polymorphic<T>::value, "'struct_serializable' class must not be polymorphic (no virtual fuction)");

		// check)
		static_assert(std::is_default_constructible<T>::value, "'struct_serializable' class must have default constructor (remove construtor)");

		return get_value_member_impl<TQUERY,T>(_pquery, _ordinal, std::make_index_sequence<constexpr_field_count<T>>());
	}
};


}