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
// 4. ATL::CMultipleResults�� ����
//	  1) ������ ����� ������ �����ϴ� ���̴�. ��ü������ ó���Ǵ� ������ ����
//		 �ٸ� ������ ���� Class�� ���û����� �Ʒ��� ����.
//
//		 - ATL::CNoMultipleResults		�Ѳ����� ���� ���� ������� ���� �ʴ´�.
//		 - ATL::CMultipleResults		�Ѳ����� ���� ���� ������� �޴´�.
//
// 
//-----------------------------------------------------------------------------
template<class TACCESSOR, template <class T> class TROWSET, class TMULTIPLE>
class query::rdb::oledb::_query_dynamic :
// inherited classes)
	public						Nquery<TACCESSOR, TROWSET, TMULTIPLE>
{
// public) 
public:
	[[nodiscard]]  DBORDINAL	get_ordinal(const wstring_param _column) { DBORDINAL ordinal; if (this->GetOrdinal(_column.data(), &ordinal) == false) throw throwable::failure(eRESULT::INVALID_ARGUMENT); return ordinal; }

	[[nodiscard]] virtual std::wstring_view	get_query_string() const noexcept { return m_query_string; }
	virtual	void				set_query_string(const wstring_param _command) { m_query_string = (std::wstring_view)_command; }

	virtual	void				close_query() noexcept { Nquery<TACCESSOR, TROWSET, TMULTIPLE>::close_query(); m_query_string.clear(); }

// public) 
public:
			template <class TOBJECT>
			struct _ITEM
			{
			public:
				TOBJECT*			pquery;

			public:
				[[nodiscard]] bool	exist(std::size_t _ordinal) const noexcept { DBLENGTH l=0; pquery->GetLength(_ordinal, &l); return l!=0; }
				[[nodiscard]] bool	empty(std::size_t _ordinal) const noexcept { DBLENGTH l=0; pquery->GetLength(_ordinal, &l); return l==0; }
				[[nodiscard]] std::size_t get_length(int _ordinal) const noexcept { DBLENGTH l=0; pquery->GetLength(_ordinal, &l); return l;}

				[[nodiscard]] bool	is_success() const noexcept { return pquery != nullptr; }
				[[nodiscard]] bool	is_failed() const noexcept { return !this->is_success(); }
				[[nodiscard]] 		operator bool() const noexcept { return this->is_success(); }
			
				// - get_value (Nullable) 
				template<class TDEST, class TSOURCE = typename _OLEDB_DEFAULT_PARAM<TDEST>::type>
				[[nodiscard]] typename OLEDB_GET_VALUE<TSOURCE, TDEST>::TRETURN
									get_value(std::size_t _ordinal = 1) const { return (exist(_ordinal)) ? OLEDB_GET_VALUE<TSOURCE, TDEST>::template get(pquery, _ordinal) : OLEDB_GET_VALUE<TSOURCE, TDEST>::TRETURN(); }
				template<class TDEST, class TSOURCE = typename _OLEDB_DEFAULT_PARAM<TDEST>::type>
				[[nodiscard]] typename OLEDB_GET_VALUE<TSOURCE, TDEST>::TRETURN
									get_value(wstring_param _column_name) const { return this->get_value(pquery->get_ordinal(_column_name)); }
			};

			template <class TOBJECT>
			struct _ITERATOR
			{
			public:
				_ITERATOR(const _ITERATOR& _copy) : item { _copy.item }, result(_copy.result) {}
				_ITERATOR(TOBJECT* _query, result_code _result) : item { _query }, result(_result) {}

			public:
				_ITEM<TOBJECT>	item;
				result_code		result;

			public:
				auto			operator =  (const _ITERATOR& _rhs) noexcept { item=_rhs.item; result=_rhs.result; return (*this); }
				[[nodiscard]] auto&	operator -> () const noexcept { return item; }
				[[nodiscard]] auto&	operator *  () noexcept { return item; }
				[[nodiscard]] auto&	operator *  () const noexcept { return item; }
				[[nodiscard]] bool operator == (const _ITERATOR& _rhs) const { return result != _rhs.result; }
				[[nodiscard]] bool operator != (const _ITERATOR& _rhs) const { return result == _rhs.result; }
				auto			operator ++ () { result = item.pquery->move_next(); return *this; }
				auto			operator ++ (int) { result = item.pquery->move_next(); return *this; }
			};
			template <typename TOBJECT> using ITERATOR = _ITERATOR<TOBJECT>;

	//static	shared_buffer		read_sequencial_stream(ISequentialStream* _pStream)
	//		{
	//			// Definition
	//			const int	SIZE_OF_BUFFER	 = 65536;
	//
	//			// declare) 
	//			shared_buffer	buf_total;
	//
	//			for(;;)
	//			{
	//				// declare) 
	//				ULONG	bytesIO;
	//				BYTE	myBuffer[SIZE_OF_BUFFER];
	//
	//				// - Read stream
	//				_pStream->Read(myBuffer, SIZE_OF_BUFFER, &bytesIO);
	//
	//				// check)
	//				BREAK_IF(bytesIO==0);
	//
	//				// - Bytes IO
	//				shared_buffer	bufNew	 = alloc_shared_buffer(buf_total.size_+ bytesIO);
	//
	//				// - ������ Buffer�� ������ ���ۿ� ����
	//				if(buf_total.size_!=0)
	//				{
	//					bufNew.append(buf_total.size_, buf_total.data_);
	//				}
	//
	//				// - ���� ���� �����͸� ���ۿ� ����
	//				bufNew.append(bytesIO, myBuffer);
	//
	//				// - ��ü
	//				buf_total	 = bufNew;
	//			}
	//
	//			// - Release
	//			_pStream->release();
	//
	//			// return) 
	//			return	buf_total;
	//		}

public:
	// 4) ...
			auto				result() noexcept { return _ITEM<_query_dynamic> {this};}

	// 5) ...
	virtual	void				process_execute_query() override { this->_execute_query(m_query_string);}

protected:
			std::wstring		m_query_string;
};


}