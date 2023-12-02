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
// 1. query::rdb::oledb::Cquery란!
//    1) Iserver_query와 Command를 상속받아 만든 기본 Query다.
//    2) Querier에 Query를 Post하거나 request하게 되면 session을 할당받게 된다.
//    3) session을 할당받게 되면 Query String을 넘겨 execute_query함수를 호출함으로써
//       Query를 수행할 수 있다.
//    4) 그리고 Query가 완료된 후 close_query를 호출하여 Query를 종료할 수 있다.
//    5) start와 stop은 원하는 만큼 수행할 수 있으며 최종적으로 ProcessQuery()
//       함수가 종료되면 session도 반납되게 된다.
//
// 2. Accessor의 선택
//    1) 사용할 수 있는 Accessor는 기본적으로 크게 두가지가 있다.
//					
//       - ATL::CAccessor<TACCESSOR>	기본 Accessor로 Query의 설정 및 결과값을 클래스
//										내부 변수에 받도록 미리 정의해 놓도록 한 것이다.
//       - ATL::CDynamicAccessor		Query의 내용 및 결과를 필요에 따라 얻어 쓸수 
//										있도록 한 것으로 간단한 Query에 유용하다.
//
// 3. Rowset의 선택
//    1) Query의 결과 1개가 하나의 Row이다. 이것을 처리하기 위한 것이 RowSet이다.
//       기본적으로 3가지의 RowSet을 사용할 수 있다.
//      
//       - ATL::CNoRowset				Rowset을 사용하지 않는다.
//		 - ATL::CRowset					Rowset을 사용한다.
//		 - ATL::CMultiRowset			여러 개의 Rowset을 가질 수 있도록 한다.
//
// 4. ATL::CMultipleResults의 선택
//	  1) 선택한 결과의 갯수를 선정하는 것이다. 자체적으로 처리되는 내용은 없고
//		 다만 선택을 위한 Class로 선택사항은 아래와 같다.
//
//		 - ATL::CNoMultipleResults		한꺼번에 여러 개의 결과물을 받지 않는다.
//		 - ATL::CMultipleResults		한꺼번에 여러 개의 결과물을 받는다.
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
	//				// - 기존의 Buffer의 내용을 버퍼에 복사
	//				if(buf_total.size_!=0)
	//				{
	//					bufNew.append(buf_total.size_, buf_total.data_);
	//				}
	//
	//				// - 새로 받은 데이터를 버퍼에 복사
	//				bufNew.append(bytesIO, myBuffer);
	//
	//				// - 교체
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