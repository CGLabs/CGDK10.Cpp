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
// query::rdb::oledb::Cquery
//
// 1. query::rdb::oledb::Cquery��!
//    1) Iserver_query�� Command�� ��ӹ޾� ���� �⺻ Query��.
//    2) Querier�� Query�� Post�ϰų� request�ϰ� �Ǹ� session�� �Ҵ�ް� �ȴ�.
//    3) session�� �Ҵ�ް� �Ǹ� Query String�� �Ѱ� execute_query�Լ��� ȣ�������ν�
//       Query�� ������ �� �ִ�.
//    4) �׸��� Query�� �Ϸ�� �� close_query�� ȣ���Ͽ� Query�� ������ �� �ִ�.
//    5) start�� stop�� ���ϴ� ��ŭ ������ �� ������ ���������� ProcessQuery()
//       �Լ��� ����Ǹ� session�� �ݳ��ǰ� �ȴ�.
//
// 2. Accessor�� ����
//    1) ����� �� �ִ� Accessor�� �⺻������ ũ�� �ΰ����� �ִ�.
//					
//       - ATL::CAccessor<TACCESSOR>	�⺻ Accessor�� Query�� ���� �� ������� Ŭ����
//										���� ������ �޵��� �̸� ������ ������ �� ���̴�.
//       - ATL::CDynamicAccessor		Query�� ���� �� ����� �ʿ信 ���� ��� ���� 
//										�ֵ��� �� ������ ������ Query�� �����ϴ�.
//
// 3. Rowset�� ����
//    1) Query�� ��� 1���� �ϳ��� Row�̴�. �̰��� ó���ϱ� ���� ���� RowSet�̴�.
//       �⺻������ 3������ RowSet�� ����� �� �ִ�.
//      
//       - ATL::CNoRowset				Rowset�� ������� �ʴ´�.
//		 - ATL::CRowset					Rowset�� ����Ѵ�.
//		 - ATL::CMultiRowset			���� ���� Rowset�� ���� �� �ֵ��� �Ѵ�.
//
// 4. CMultipleResults�� ����
//	  1) ������ ����� ������ �����ϴ� ���̴�. ��ü������ ó���Ǵ� ������ ����
//		 �ٸ� ������ ���� Class�� ���û����� �Ʒ��� ����.
//
//		 - ATL::CNoMultipleResults		�Ѳ����� ���� ���� ������� ���� �ʴ´�.
//		 - ATL::CMultipleResults		�Ѳ����� ���� ���� ������� �޴´�.
//
// 
//-----------------------------------------------------------------------------
template<class TACCESSOR, template <class T> class TROWSET, class TMULTIPLE>
class query::rdb::oledb::_query :
	// inherited classes)
	public						Nquery <TACCESSOR,TROWSET,TMULTIPLE>
{
// public) 
public:
	// 4) For DefaultCommand
	__if_exists(GetDefaultCommand)
	{
	[[nodiscard]] virtual std::wstring_view get_query_string() const noexcept override { wchar_t* temp; GetDefaultCommand((LPCWSTR*)&temp); return temp; }
	virtual	void				set_query_string(const wstring_param /*_command*/) override { CGASSERT_ERROR(false); throw throwable::failure (eRESULT::FAIL); }

	}																	 
	__if_not_exists(GetDefaultCommand)									 
	{																	 
	[[nodiscard]] virtual std::string_view get_query_string() const noexcept override { return m_query_string;}
	virtual void				set_query_string(const std::string_view _command) override { m_query_string = _command;}
	virtual	void				close_query() noexcept { Nquery<TACCESSOR, TROWSET, TMULTIPLE>::close_query(); m_query_string.clear(); }

			std::string			m_query_string;
	}																	 
																		 
	virtual	void				process_execute_query() override { this->execute_query(get_query_string()); }
};


}