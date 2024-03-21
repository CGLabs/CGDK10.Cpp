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
//    1) md5(Message Diegest 5)�� ��� Ŭ�����̴�.
//    2) 
//    3) 
//
// 2. �����
//    1) ���� initialize()�Լ��� ȣ���Ͽ� �ʱ�ȭ�Ѵ�.
//    2) push_MD5()�Լ��� ȣ���Ͽ� �����͵��� ������Ų��.
//       push_MD5�� File�� md5�� ���� ���� �ִ�.
//    3) ��� �����͸� ������Ų �� padding()�Լ��� ȣ���Ͽ� �������Ѵ�.
//    4) ����� md5�� md5()�Լ��� ����Ͽ� ��´�. 
//    5) ������ MD5�� ���� ���� �� ������ �ʿ� ���� calculate_MD5()�Լ��� ȣ���ϸ�
//       �ȴ�.
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
	// 1) �⺻�� md5 ����...
	//    - initialize() -> push_md5() -> padding() �� ������ ��ġ�� md5���� ���ȴ�.
			bool				initialize();
			void				push_md5(const void* _buffer, uint32_t _size);
			bool				push_md5(FILE_HANDLE _handle_file, uint32_t _Start, uint32_t _End);
			void				padding();

	// 2) File�� �̿��ؼ� �Ѳ����� �Ϸð����� ó���Ѵ�.
			bool				calculate_md5(const std::string_view _filename);
			bool				calculate_md5(const std::wstring_view _filename);
			bool				calculate_md5(const std::u16string_view _filename);
			bool				calculate_md5(const std::u32string_view _filename);

	// 3) MD5�� ���(MD5�� 16Byte�̹Ƿ� �̰��� �����ؾ� �Ѵ�.)
			void				get_md5(MD5* _out) const noexcept { *_out = m_state;}
	[[nodiscard]] const MD5&	get_md5() const noexcept { return m_state;}
			void				set_md5(const MD5& _md5) noexcept { m_state = _md5;}

// implementation)
protected:
			// 1) MD5�� �����ϰ� �ִ� ����.
			uint8_t				m_buffer[64];

			// 2) A, B, C, D��
			bool				m_is_process;
			MD5					m_state;

			// 3) Data�� ũ�⸦ Bit������ �����ϰ� �ִ� ����.
			uint32_t			m_count[2];

protected:
			// 1) MD5�� Block������ ����ϴ� �Լ�.
			void				transform_md5(void* _buffer, const void* _from);
};


}
}