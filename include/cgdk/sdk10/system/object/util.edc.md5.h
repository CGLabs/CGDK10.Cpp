//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                              Utility Classes                              *
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
// CGDK::MD5
//
// 1. CGDK::MD5
//    1) md5(Message Diegest 5)를 얻는 클래스이다.
//    2) 
//    3) 
//
// 2. 사용방법
//    1) 먼저 initialize()함수를 호출하여 초기화한다.
//    2) push_MD5()함수를 호출하여 데이터들을 누적시킨다.
//       push_MD5로 File의 md5를 얻을 수도 있다.
//    3) 모든 데이터를 누적시킨 후 padding()함수를 호출하여 마무리한다.
//    4) 얻어진 md5를 md5()함수를 사용하여 얻는다. 
//    5) 파일의 MD5를 구할 때는 이 과정들 필요 없이 calculate_MD5()함수를 호출하면
//       된다.
//
//-----------------------------------------------------------------------------
struct MD5
{
public:
	std::array<uint32_t,4> data;

public:
	[[nodiscard]] bool operator==(const MD5& _rhs) const
			{
				return (data.at(0)==_rhs.data.at(0)) && (data.at(1) == _rhs.data.at(1)) && (data.at(2) == _rhs.data.at(2)) && (data.at(3) == _rhs.data.at(3));
			}
	[[nodiscard]] bool operator!=(const MD5& _rhs) const
			{
				return (data.at(0)!=_rhs.data.at(0)) || (data.at(1) != _rhs.data.at(1)) || (data.at(2) != _rhs.data.at(2)) || (data.at(3) != _rhs.data.at(3));
			}
	[[nodiscard]] bool operator>=(const MD5& _rhs) const
			{
				for(int i=0; i<4; ++i)
				{
					RETURN_IF(data.at(i) > _rhs.data.at(i), true);
					RETURN_IF(data.at(i) < _rhs.data.at(i), false);
				}
				return true;
			}
	[[nodiscard]] bool operator>(const MD5& _rhs) const
			{
				for(int i=0; i<4; ++i)
				{
					RETURN_IF(data.at(i) > _rhs.data.at(i), true);
					RETURN_IF(data.at(i) < _rhs.data.at(i), false);
				}
				return	false;
			}
	[[nodiscard]] bool operator<=(const MD5& _rhs) const
			{
				for(int i=0; i<4; ++i)
				{
					RETURN_IF(data.at(i) < _rhs.data.at(i), true);
					RETURN_IF(data.at(i) > _rhs.data.at(i), false);
				}
				return true;
			}
	[[nodiscard]] bool operator<(const MD5& _rhs) const
			{
				for(int i=0; i<4; ++i)
				{
					RETURN_IF(data.at(i) < _rhs.data.at(i), true);
					RETURN_IF(data.at(i) > _rhs.data.at(i), false);
				}
				return	false;
			}

	[[nodiscard]] bool empty() const noexcept { return data.at(0) == 0 && data.at(1) == 0 && data.at(2) == 0 && data.at(3) == 0; }
	[[nodiscard]] bool exist() const noexcept { return !empty(); }

public:
	MD5() noexcept : data{ 0,0,0,0 } {}
	MD5(const MD5& _copy) = default;
	MD5(uint32_t _a, uint32_t _b, uint32_t _c, uint32_t _d) noexcept : data{ _a, _b, _c, _d}	{}
};

namespace edc
{

class md5
{
// constructor/destructor)
public:
			md5() noexcept;
	virtual ~md5() noexcept;

// public)
public:
	// 1) 기본적 md5 순서...
	//    - initialize() -> push_md5() -> padding() 의 과정을 거치면 md5값이 계산된다.
			bool				initialize();
			void				push_md5(const void* _buffer, uint32_t _size);
			bool				push_md5(FILE_HANDLE _handle_file, uint32_t _Start, uint32_t _End);
			void				padding();

	// 2) File을 이용해서 한꺼번에 일련과정을 처리한다.
			bool				calculate_md5(const std::string_view _filename);
			bool				calculate_md5(const std::wstring_view _filename);
			bool				calculate_md5(const std::u16string_view _filename);
			bool				calculate_md5(const std::u32string_view _filename);

	// 3) MD5값 얻기(MD5는 16Byte이므로 이것을 감안해야 한다.)
			void				get_md5(MD5* _out) const noexcept { *_out = m_state;}
	[[nodiscard]] const MD5&	get_md5() const noexcept { return m_state;}
			void				set_md5(const MD5& _md5) noexcept { m_state = _md5;}

// implementation)
protected:
			// 1) MD5를 보관하고 있는 변수.
			uint8_t				m_buffer[64];

			// 2) A, B, C, D값
			bool				m_is_process;
			MD5					m_state;

			// 3) Data의 크기를 Bit단위로 보관하고 있는 변수.
			uint32_t			m_count[2];

protected:
			// 1) MD5를 Block단위로 계산하는 함수.
			void				transform_md5(void* _buffer, const void* _from);
};


}
}