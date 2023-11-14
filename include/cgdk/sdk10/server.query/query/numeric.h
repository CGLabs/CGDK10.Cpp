//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                           Server Query Classes                            *
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
// 1. NUMERIC
//
//    1) Used to large scale number value with no error
//       
//    2) two variable is used to each integer part and fraction part.
//       floating point variable is not used because of error
//
//-----------------------------------------------------------------------------
const int64_t	_FRACTION_MAX	 = 100000000;	// pow (10, 8)
const int		_FRACTION_SCALE	 = 8;

struct NUMERIC
{
public:
			int64_t	value;		// 정수부
			int64_t	fraction;	// 소수부

public:
				NUMERIC() noexcept : value(0), fraction(0)							{}
	explicit	NUMERIC(int64_t _value, int64_t _fraction=0) noexcept : value(_value), fraction(_fraction) {}
	explicit	NUMERIC(const float& _value) noexcept : value(), fraction()			{ from_float(_value);}
	explicit	NUMERIC(const double& _value) noexcept : value(), fraction()		{ from_double(_value);}
	explicit	NUMERIC(const char* _value) noexcept : value(), fraction()			{ from_string(_value);}
				NUMERIC(const NUMERIC& _copy) noexcept : value(_copy.value), fraction(_copy.fraction) {}

public:
	[[nodiscard]] bool			empty() const noexcept								{ return value==0 && fraction==0;}
	[[nodiscard]] bool			exist() const noexcept								{ return value!=0 || fraction!=0;}
				void			clear() noexcept									{ value=0; fraction=0;}

				template<class _T>
				std::basic_string<_T>	to_string() const							{ _T temp[64]; to_string(temp, 64); return std::basic_string<_T>(temp);}
				char*			to_string			(char* _Out, std::size_t _sizeBuffer) const;
				wchar_t*		to_string			(wchar_t* _Out, std::size_t _sizeBuffer) const;

				void			from_string			(const char* _string);
				void			from_string			(const wchar_t* _string);
				void			from_string			(const std::string& _string);
				void			from_string			(const std::wstring& _string);
				void			from_float			(const float& _value) noexcept	{ float i, f; f=modf(_value, &i); value = static_cast<int64_t>(i); fraction = static_cast<int64_t>(f);}
				void			from_double			(const double& _value) noexcept	{ double i, f; f=modf(_value, &i); value = static_cast<int64_t>(i); fraction = static_cast<int64_t>(f);}

	static		float			get_change_ratio	(const NUMERIC& _now, const NUMERIC& _origin) noexcept;

public:
				NUMERIC&		operator = (const NUMERIC& _rhs) noexcept			{ value = _rhs.value; fraction = _rhs.fraction; return *this;}
				NUMERIC&		operator = (const char* _rhs) noexcept				{ from_string(_rhs); return *this;}
				NUMERIC&		operator = (const std::string& _rhs) noexcept		{ from_string(_rhs); return *this;}

	[[nodiscard]] bool			operator ==(const NUMERIC& _rhs) const noexcept		{ return (value == _rhs.value) && (fraction == _rhs.fraction);}
	[[nodiscard]] bool			operator !=(const NUMERIC& _rhs) const noexcept		{ return (value != _rhs.value) || (fraction != _rhs.fraction);}
	[[nodiscard]] bool			operator > (const NUMERIC& _rhs) const noexcept		{ return (value >  _rhs.value) || ((value == _rhs.value) && (fraction >  _rhs.fraction));}
	[[nodiscard]] bool			operator >=(const NUMERIC& _rhs) const noexcept		{ return (value >  _rhs.value) || ((value == _rhs.value) && (fraction >= _rhs.fraction));}
	[[nodiscard]] bool			operator < (const NUMERIC& _rhs) const noexcept		{ return (value <  _rhs.value) || ((value == _rhs.value) && (fraction <  _rhs.fraction));}
	[[nodiscard]] bool			operator <=(const NUMERIC& _rhs) const noexcept		{ return (value <  _rhs.value) || ((value == _rhs.value) && (fraction <= _rhs.fraction));}

	[[nodiscard]] NUMERIC		operator + (const NUMERIC& _rhs) const noexcept		{ return _operate_additive(*this, _rhs);}
	[[nodiscard]] NUMERIC		operator - (const NUMERIC& _rhs) const noexcept		{ return _operate_substract(*this, _rhs);}
	[[nodiscard]] NUMERIC		operator * (const NUMERIC& _rhs) const noexcept		{ return _operate_multiply(*this, _rhs);}
	[[nodiscard]] NUMERIC		operator / (const NUMERIC& _rhs) const				{ return _operate_divide(*this, _rhs);}
	[[nodiscard]] NUMERIC		operator % (const NUMERIC& _rhs) const				{ return _operate_modurate(*this, _rhs);}
				NUMERIC&		operator +=(const NUMERIC& _rhs) noexcept			{ *this= _operate_additive(*this, _rhs); return *this;}
				NUMERIC&		operator -=(const NUMERIC& _rhs) noexcept			{ *this= _operate_substract(*this, _rhs); return *this;}
				NUMERIC&		operator *=(const NUMERIC& _rhs) noexcept			{ *this= _operate_multiply(*this, _rhs); return *this;}
				NUMERIC&		operator /=(const NUMERIC& _rhs)					{ *this= _operate_divide(*this, _rhs); return *this;}
				NUMERIC&		operator %=(const NUMERIC& _rhs)					{ *this= _operate_modurate(*this, _rhs); return *this;}

	[[nodiscard]] NUMERIC		operator  +() const noexcept						{ return NUMERIC(value, fraction);}
	[[nodiscard]] NUMERIC		operator  -() const noexcept						{ return NUMERIC(-value, -fraction);}

	[[nodiscard]] 				operator bool() const noexcept						{ return value != 0 || fraction != 0;}
	[[nodiscard]] 				operator float() const noexcept						{ return (float)value + (float)fraction * (1.0f / _FRACTION_MAX);}
	[[nodiscard]] 				operator double() const noexcept					{ return (double)value + (double)fraction * (1.0f / _FRACTION_MAX);}

		static	NUMERIC			_operate_additive	(const NUMERIC& _lhs, const NUMERIC& _rhs) noexcept;
		static	NUMERIC			_operate_substract	(const NUMERIC& _lhs, const NUMERIC& _rhs) noexcept;
		static	NUMERIC			_operate_multiply	(const NUMERIC& _lhs, const NUMERIC& _rhs) noexcept;
		static	NUMERIC			_operate_divide		(const NUMERIC& _lhs, const NUMERIC& _rhs);
		static	NUMERIC			_operate_modurate	(const NUMERIC& _lhs, const NUMERIC& _rhs) noexcept;
		static	NUMERIC			_operate_additive	(const NUMERIC& _lhs, int64_t _rhs) noexcept;
		static	NUMERIC			_operate_substract	(const NUMERIC& _lhs, int64_t _rhs) noexcept;
		static	NUMERIC			_operate_multiply	(const NUMERIC& _lhs, int64_t _rhs) noexcept;
		static	NUMERIC			_operate_divide		(const NUMERIC& _lhs, int64_t _rhs) noexcept;
		static	NUMERIC			_operate_modurate	(const NUMERIC& _lhs, int64_t _rhs) noexcept;
		static	void			_operate_normalize	(NUMERIC& _InOut) noexcept;
};


}