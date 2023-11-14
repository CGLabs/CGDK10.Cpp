//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
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

namespace CGDK
{
////-----------------------------------------------------------------------------
////
//// VAR
////
//// - Repository의 대상 객체가 될수 있는 Interface
//// 
////-----------------------------------------------------------------------------
//enum class FIELD_STATE : int
//{
//	NONE	 = 0,
//	NORMAL	 = 1,
//	UPDATE	 = 2,
//	CREATE	 = 3,
//	REMOVE	 = 4
//};
//
//struct FIELD
//{
//public:
//	FIELD() noexcept : iState(FIELD_STATE::NONE), idField(-1), revision(0) 	{}
//	FIELD(int _field_id, FIELD_STATE _state=FIELD_STATE::NONE) noexcept : iState(_state), idField(_field_id), revision(0)  	{}
//
//public:
//			FIELD_STATE			iState;
//			int					idField;
//			int64_t				revision;
//};
//
//class IValue
//{
//public: 
//			IValue() noexcept : m_state(), m_pParent(nullptr)				{}
//			IValue(int _field_id) noexcept : m_state(_field_id), m_pParent(nullptr)	{}
//
//public: 
//			void				SetIndex(int _index) noexcept				{	m_state.idField=_index;}
//			void				SetParent(IValue* _pparent) noexcept		{	m_pParent=_pparent;}
//			IValue*				SetParent() noexcept						{	return m_pParent;}
//
//			bool				IsNormal() const noexcept					{	return m_state.iState!=FIELD_STATE::NORMAL;}
//			FIELD_STATE			GetFieldState() const noexcept				{	return m_state.iState;}
//
//public: 
//			FIELD				m_state;
//			IValue*				m_pParent;
//
//public: 
//	virtual	int					process_append(shared_buffer& _buffer, uint32_t _Condition) PURE;
//	virtual	void				process_extract(buffer_view& _buffer, const FIELD& _NewState) PURE;
//};
//
//
//template <class TTYPE>
//class VAR : public IValue
//{
//public:
//			using TYPE = TTYPE;
//public:
//			VAR() noexcept : IValue(), m_value()							{}
//			VAR(const TTYPE& _value) noexcept : IValue(), m_value(_value)	{}
//			VAR(TTYPE&& _value) noexcept : IValue(), m_value(std::forward<TTYPE>(_value)) {}
//public:
//			VAR<TTYPE>&		operator = (const TTYPE& _rhs)					{	/*if(m_value!=_rhs)*/ {m_value=_rhs; m_state.iState =FIELD_STATE::UPDATE;} /*else ;*/ return *this;}
//
//								operator const TTYPE&() const noexcept		{	return m_value;}
//								operator const FIELD&() const noexcept		{	return m_state;}
//
//			const TTYPE&		get() const noexcept						{	return m_value;}
//
//			bool				IsNormal() const noexcept					{	return m_state.iState !=FIELD_STATE::NORMAL;}
//			FIELD_STATE			GetFieldState() const noexcept				{	return m_state.iState;}
//
//public:
//			TTYPE				m_value;
//
//public:
//			int					process_append(shared_buffer& _buffer, uint32_t _Condition) override
//			{
//				// declare) 
//				int	value	 = 0;
//
//				switch(m_state.iState)
//				{
//				case	FIELD_STATE::NONE:
//				case	FIELD_STATE::NORMAL:
//					break;
//
//				case	FIELD_STATE::UPDATE:
//						if(_Condition & static_cast<uint32_t>(FIELD_STATE::UPDATE))
//						{
//							_buffer.append<FIELD>(m_state);
//							_buffer.append<TTYPE>(m_value);
//							value	 = 1;
//						}
//						break;
//
//				case	FIELD_STATE::CREATE:
//						if(_Condition & static_cast<uint32_t>(FIELD_STATE::CREATE))
//						{
//							_buffer.append<FIELD>(m_state);
//							_buffer.append<TTYPE>(m_value);
//							value	 = 1;
//						}
//						break;
//
//				case	FIELD_STATE::REMOVE:
//						if(_Condition & static_cast<uint32_t>(FIELD_STATE::REMOVE))
//						{
//							_buffer.append<FIELD>(m_state);
//							value	 = 1;
//						}
//						break;
//
//				default:
//						break;
//				}
//
//				return	0;
//			}
//			void				process_extract(shared_buffer& _buffer, const FIELD& _NewState) override
//			{
//				// check) 
//				CGASSERT_ERROR(_NewState.revision>m_state.revision);
//
//				// 1) 상황에 따른 처리
//				switch(_NewState.iState)
//				{
//				case	FIELD_STATE::NONE:
//				case	FIELD_STATE::NORMAL:
//						m_value			 = _buffer.extract<TTYPE>();
//						break;
//
//				case	FIELD_STATE::UPDATE:
//						m_value			 = _buffer.extract<TTYPE>();
//						break;
//
//				case	FIELD_STATE::CREATE:
//						break;
//
//				case	FIELD_STATE::REMOVE:
//						m_state.iState	 = FIELD_STATE::REMOVE;
//						break;
//
//				default:
//						break;
//				}
//
//				// 2) revision과 State를 설정한다.
//				m_state.revision	 = _NewState.revision;
//				m_state.iState		 = _NewState.iState;
//			}
//};
//
//
//template <int ICOUNT>
//class VAR<wchar_t[ICOUNT]> : public IValue
//{
//public:
//	using TYPE = wchar_t*;
//public:
//			VAR() noexcept : IValue(), m_value()	{ m_value[0]=L'\0';}
//public:
//			VAR<wchar_t[ICOUNT]>& operator=(const wchar_t* _rhs)	
//			{
//				//if(m_value!=_rhs) 
//				{
//					wcscpy_s(m_value, ICOUNT, _rhs);
//					m_state.iState = FIELD_STATE::UPDATE;
//				}
//				//else
//				{
//				}
//		
//				return *this;
//			}
//
//			template<size_t IICOUNT>
//			VAR<wchar_t[ICOUNT]>& operator=(const wchar_t (&_rhs)[IICOUNT])
//			{
//				//if(m_value!=_rhs) 
//				{
//					wcscpy_s(m_value, IICOUNT, _rhs);
//					m_state.iState = FIELD_STATE::UPDATE;
//				}
//				//else
//				{
//				}
//
//				return *this;
//			}
//
//			//template <int IDEST_COUNT, int IDEST_INDEX>
//			//VAR<wchar_t[ICOUNT]>& operator=(const VAR<wchar_t[IDEST_COUNT], IDEST_INDEX>& _rhs)	{	/*if(m_value!=_rhs)*/ {m_value=_rhs; m_state.iState=FIELD_STATE::UPDATE;} /*else ;*/ return *this;}
//		
//			operator const wchar_t*() const noexcept						{	return m_value;}
//			operator const FIELD&() const noexcept							{	return m_state;}
//		
//			const wchar_t*		get() const noexcept						{	return m_value;}
//		
//			bool				IsNormal() const noexcept					{	return m_state.iState !=FIELD_STATE::NORMAL;}
//			FIELD_STATE			GetFieldState() const noexcept				{	return m_state.iState;}
//		
//public:
//			wchar_t				m_value[ICOUNT];
//
//public:
//	virtual	int					process_append(shared_buffer& _buffer, uint32_t _Condition) override
//			{
//				// declare) 
//				int	value	 = 0;
//		
//				switch(m_state.iState)
//				{
//				case	FIELD_STATE::NONE:
//				case	FIELD_STATE::NORMAL:
//						break;
//		
//				case	FIELD_STATE::UPDATE:
//						if(_Condition & static_cast<uint32_t>(FIELD_STATE::UPDATE))
//						{
//							_buffer.append<FIELD>(m_state);
//							_buffer.append<const wchar_t*>(m_value);
//							value	 = 1;
//						}
//						break;
//		
//				case	FIELD_STATE::CREATE:
//						if(_Condition & static_cast<uint32_t>(FIELD_STATE::UPDATE))
//						{
//							_buffer.append<FIELD>(m_state);
//							_buffer.append<const wchar_t*>(m_value);
//							value	 = 1;
//						}
//						break;
//		
//				case	FIELD_STATE::REMOVE:
//						if(_Condition & static_cast<uint32_t>(FIELD_STATE::UPDATE))
//						{
//							_buffer.append<FIELD>(m_state);
//							value	 = 1;
//						}
//						break;
//		
//				default:
//						break;
//				}
//
//				return	0;
//			}
//	virtual	void				process_extract(buffer_view& _buffer, const FIELD& _NewState) override
//			{
//				// check) 
//				CGASSERT_ERROR(_NewState.revision>m_state.revision);
//		
//				// 1) 상황에 따른 처리
//				switch(_NewState.iState)
//				{
//				case	FIELD_STATE::NONE:
//				case	FIELD_STATE::NORMAL:
//						{
//							const wchar_t* pstring	 = _buffer.extract<const wchar_t*>();
//							wcscpy_s(m_value, ICOUNT, pstring);
//						}
//						break;
//		
//				case	FIELD_STATE::UPDATE:
//						{
//							const wchar_t* pstring	 = _buffer.extract<const wchar_t*>();
//							wcscpy_s(m_value, ICOUNT, pstring);
//						}
//						break;
//		
//				case	FIELD_STATE::CREATE:
//						break;
//		
//				case	FIELD_STATE::REMOVE:
//						m_state.iState = FIELD_STATE::NORMAL;
//						break;
//		
//				default:
//						break;
//				}
//		
//				// 2) revision과 State를 설정한다.
//				m_state.revision	 = _NewState.revision;
//				m_state.iState		 = _NewState.iState;
//			}
//};
//
//template <class TA, class TB>
//class VAR<std::vector<TA, TB>> : public IValue
//{
//public:
//			using TYPE = std::vector<TA, TB>;
//public:
//			VAR() noexcept : IValue(), m_value()	{}
//			VAR(const std::vector<TA, TB>& _value) : IValue(), m_value(_value) {}
//			VAR(std::vector<TA, TB>&& _value) noexcept : std::vector<TA, TB>(), m_value(std::forward<std::vector<TA, TB>>(_value)) {}
//public:
//			VAR<std::vector<TA, TB>>& operator = (const std::vector<TA, TB>& _rhs)
//			{
//				//if(m_value!=_rhs) 
//				{
//					m_value			 = _rhs;
//					m_state.iState = FIELD_STATE::UPDATE;
//				} 
//				//else
//				{
//				}
//		
//				return *this;
//			}
//
//			operator const TYPE&() const noexcept				{	return m_value;}
//			operator const FIELD&() const noexcept				{	return m_state;}
//		
//			const TYPE&			get() const noexcept			{	return m_value;}
//
//			using ITERATOR = typename std::vector<TA, TB>::iterator;
//			using CONST_ITERATOR = typename std::vector<TA, TB>::const_iterator;
//
//public:
//			std::vector<TA, TB>	m_value;
//
//public:
//	virtual	int					process_append(shared_buffer& _buffer, uint32_t _Condition) override
//			{
//				// declare) 
//				int	value	 = 0;
//		
//				switch(m_state.iState)
//				{
//				case	FIELD_STATE::NONE:
//				case	FIELD_STATE::NORMAL:
//						break;
//		
//				case	FIELD_STATE::UPDATE:
//						if(_Condition & static_cast<uint32_t>(FIELD_STATE::UPDATE))
//						{
//							_buffer.append<FIELD>(m_state);
//							_buffer.append<TYPE>(m_value);
//							value	 = 1;
//						}
//						break;
//		
//				case	FIELD_STATE::CREATE:
//						if(_Condition & static_cast<uint32_t>(FIELD_STATE::UPDATE))
//						{
//							_buffer.append<FIELD>(m_state);
//							_buffer.append<TYPE>(m_value);
//							value	 = 1;
//						}
//						break;
//		
//				case	FIELD_STATE::REMOVE:
//						if(_Condition & static_cast<uint32_t>(FIELD_STATE::UPDATE))
//						{
//							_buffer.append<FIELD>(m_state);
//							value	 = 1;
//						}
//						break;
//		
//				default:
//						break;
//				}
//
//				return	0;
//			}
//	virtual	void				process_extract(buffer_view& _buffer, const FIELD& _NewState) override
//			{
//				// check) 
//				CGASSERT_ERROR(_NewState.revision>m_state.revision);
//		
//				// 1) 상황에 따른 처리
//				switch(_NewState.iState)
//				{
//				case	FIELD_STATE::NONE:
//				case	FIELD_STATE::NORMAL:
//						m_value			 = _buffer.extract<TYPE>();;
//						break;
//		
//				case	FIELD_STATE::UPDATE:
//						m_value			 = _buffer.extract<TYPE>();;
//						break;
//		
//				case	FIELD_STATE::CREATE:
//						break;
//		
//				case	FIELD_STATE::REMOVE:
//						m_state.iState = FIELD_STATE::NORMAL;
//						break;
//		
//				default:
//						break;
//				}
//		
//				// 2) revision과 State를 설정한다.
//				m_state.revision	 = _NewState.revision;
//				m_state.iState		 = _NewState.iState;
//			}
//		
//public:
//			void				push_back(const TA& _Val)		{	m_value.push_back(_Val);}
//			void				push_back(TA&& _Val )			{	m_value.push_back(_Val);}
//		
//			void				emplace_back(const TA& _Val)	{	m_value.emplace_back(_Val);}
//			void				emplace_back(TA&& _Val )		{	m_value.emplace_back(_Val);}
//		
//			void				pop_back() noexcept				{	m_value.pop_back();}
//		
//			TA&					front() noexcept				{	return m_value.front();}
//			const TA&			front() const noexcept			{	return m_value.front();}
//			TA&					back() noexcept					{	return m_value.back();}
//			const TA&			back() const noexcept			{	return m_value.back();}
//		
//			ITERATOR			begin() noexcept				{	return m_value.begin();}
//			CONST_ITERATOR		begin() const noexcept			{	return m_value.begin();}
//			ITERATOR			end() noexcept					{	return m_value.end();}
//			CONST_ITERATOR		end() const noexcept			{	return m_value.end();}
//		
//			void				erase(const typename std::vector<TA, TB>::iterator& _Where) noexcept		{	m_value.erase(_Where);}
//			void				erase(const typename std::vector<TA, TB>::const_iterator& _Where) noexcept	{	m_value.erase(_Where);}
//		
//			//auto				insert(const TA& _Val)
//};
//
//#if !defined(__linux__)
//template <class TA, class TB>
//class VAR<std::list<TA, TB>> : public IValue
//{
//public:
//	using TYPE = std::list<TA, TB>;
//public:
//			VAR() : IValue(), m_value()	{}
//public:
//			VAR<TYPE>& operator = (const TYPE& _rhs)
//			{
//				//if(m_value!=_rhs) 
//				{
//					m_value			 = _rhs;
//					m_state.iState = FIELD_STATE::UPDATE;
//				} 
//				//else
//				{
//				}
//		
//				return *this;
//			}
//		
//			operator const TYPE&() const noexcept				{	return m_value;}
//			operator const FIELD&() const noexcept				{	return m_state;}
//		
//			const TYPE&			get() const noexcept			{	return m_value;}
//		
//			bool				IsNormal() const noexcept		{	return m_state.iState !=FIELD_STATE::NORMAL;}
//			FIELD_STATE			GetFieldState() const noexcept	{	return m_state.iState;}
//
//			using ITERATOR = typename std::vector<TA, TB>::iterator;
//			using CONST_ITERATOR = typename std::vector<TA, TB>::const_iterator;
//
//public:
//			TYPE				m_value;
//			FIELD				m_state;
//
//public:
//	virtual	int					process_append(shared_buffer& _buffer, uint32_t _Condition) override
//			{
//				// declare) 
//				int	value	 = 0;
//		
//				switch(m_state.iState)
//				{
//				case	FIELD_STATE::NONE:
//				case	FIELD_STATE::NORMAL:
//						break;
//		
//				case	FIELD_STATE::UPDATE:
//						if(_Condition & static_cast<uint32_t>(FIELD_STATE::UPDATE))
//						{
//							_buffer.append<FIELD>(m_state);
//							_buffer.append<TYPE>(m_value);
//							value	 = 1;
//						}
//						break;
//		
//				case	FIELD_STATE::CREATE:
//						if(_Condition & static_cast<uint32_t>(FIELD_STATE::UPDATE))
//						{
//							_buffer.append<FIELD>(m_state);
//							_buffer.append<TYPE>(m_value);
//							value	 = 1;
//						}
//						break;
//		
//				case	FIELD_STATE::REMOVE:
//						if(_Condition & static_cast<uint32_t>(FIELD_STATE::UPDATE))
//						{
//							_buffer.append<FIELD>(m_state);
//							value	 = 1;
//						}
//						break;
//		
//				default:
//						break;
//				}
//
//				return	0;
//			}
//	virtual	void				process_extract(buffer_view& _buffer, const FIELD& _NewState) override
//			{
//				// check) 
//				CGASSERT_ERROR(_NewState.revision>m_state.revision);
//		
//				// 1) 상황에 따른 처리
//				switch(_NewState.iState)
//				{
//				case	FIELD_STATE::NONE:
//				case	FIELD_STATE::NORMAL:
//						m_value			 = _buffer.extract<TYPE>();;
//						break;
//		
//				case	FIELD_STATE::UPDATE:
//						m_value			 = _buffer.extract<TYPE>();;
//						break;
//		
//				case	FIELD_STATE::CREATE:
//						break;
//		
//				case	FIELD_STATE::REMOVE:
//						m_state.iState = FIELD_STATE::NORMAL;
//						break;
//		
//				default:
//						break;
//				}
//		
//				// 2) revision과 State를 설정한다.
//				m_state.revision = _NewState.revision;
//				m_state.iState = _NewState.iState;
//			}
//		
//public:
//			void				push_back(const TA& _Val)		{ m_value.push_back(_Val);}
//			void				push_back(TA&& _Val )			{ m_value.push_back(_Val);}
//																  
//			void				emplace_back(const TA& _Val)	{ m_value.emplace_back(_Val);}
//			void				emplace_back(TA&& _Val )		{ m_value.emplace_back(_Val);}
//																  
//			void				pop_back() noexcept				{ m_value.pop_back();}
//																  
//			TA&					front() noexcept				{ return m_value.front();}
//			const TA&			front() const noexcept			{ return m_value.front();}
//			TA&					back() noexcept					{ return m_value.back();}
//			const TA&			back() const noexcept			{ return m_value.back();}
//																  
//			ITERATOR			begin() noexcept				{ return m_value.begin();}
//			CONST_ITERATOR		begin() const noexcept			{ return m_value.begin();}
//			ITERATOR			end() noexcept					{ return m_value.end();}
//			CONST_ITERATOR		end() const noexcept			{ return m_value.end();}
//		
//			void				erase(const typename TYPE::iterator& _Where) noexcept		{ m_value.erase(_Where);}
//			void				erase(const typename TYPE::const_iterator& _Where) noexcept { m_value.erase(_Where);}
//		
//			//auto				insert(const TA& _Val)
//};
//#endif
//
//template <class TA, class TB, class TC, class TD>
//class VAR<std::map<TA, TB, TC, TD>> : public IValue
//{
//public:
//	using TYPE = std::map<TA, TB, TC, TD>;
//public:
//			VAR() noexcept : IValue(), m_value() {}
//public:
//			VAR<TYPE>& operator = (const TYPE& _rhs)
//			{
//				//if(m_value!=_rhs) 
//				{
//					m_value			 = _rhs;
//					m_state.iState = FIELD_STATE::UPDATE;
//				} 
//				//else
//				{
//				}
//
//				return *this;
//			}
//		
//			operator const TYPE&() const noexcept				{ return m_value;}
//			operator const FIELD&() const noexcept				{ return m_state;}
//																  
//			const TYPE&			get() const noexcept			{ return m_value;}
//																  
//			bool				IsNormal() const noexcept		{ return m_state.iState !=FIELD_STATE::NORMAL;}
//			FIELD_STATE			GetFieldState() const noexcept	{ return m_state.iState;}
//		
//
//			using ITERATOR = typename std::map<TA, TB, TC, TD>::iterator;
//			using CONST_ITERATOR = typename std::map<TA, TB, TC, TD>::const_iterator;
//
//public:
//			TYPE				m_value;
//			FIELD				m_state;
//
//public:
//			int					process_append(shared_buffer& _buffer, uint32_t _Condition)
//			{
//				// declare) 
//				int	value = 0;
//		
//				switch(m_state.iState)
//				{
//				case	FIELD_STATE::NONE:
//				case	FIELD_STATE::NORMAL:
//						break;
//		
//				case	FIELD_STATE::UPDATE:
//						if(_Condition & static_cast<uint32_t>(FIELD_STATE::UPDATE))
//						{
//							_buffer.append<FIELD>(m_state);
//							_buffer.append<TYPE>(m_value);
//							value = 1;
//						}
//						break;
//		
//				case	FIELD_STATE::CREATE:
//						if(_Condition & static_cast<uint32_t>(FIELD_STATE::UPDATE))
//						{
//							_buffer.append<FIELD>(m_state);
//							_buffer.append<TYPE>(m_value);
//							value = 1;
//						}
//						break;
//		
//				case	FIELD_STATE::REMOVE:
//						if(_Condition & static_cast<uint32_t>(FIELD_STATE::UPDATE))
//						{
//							_buffer.append<FIELD>(m_state);
//							value = 1;
//						}
//						break;
//		
//				default:
//						break;
//				}
//
//				return	0;
//			}
//			void				process_extract(buffer_view& _buffer, const FIELD& _NewState)
//			{
//				// check) 
//				CGASSERT_ERROR(_NewState.revision>m_state.revision);
//		
//				// 1) 상황에 따른 처리
//				switch(_NewState.iState)
//				{
//				case	FIELD_STATE::NONE:
//				case	FIELD_STATE::NORMAL:
//						m_value = _buffer.extract<TYPE>();;
//						break;
//		
//				case	FIELD_STATE::UPDATE:
//						m_value = _buffer.extract<TYPE>();;
//						break;
//		
//				case	FIELD_STATE::CREATE:
//						break;
//		
//				case	FIELD_STATE::REMOVE:
//						m_state.iState = FIELD_STATE::NORMAL;
//						break;
//		
//				default:
//						break;
//				}
//		
//				// 2) revision과 State를 설정한다.
//				m_state.revision	 = _NewState.revision;
//				m_state.iState = _NewState.iState;
//			}
//		
//public:
//			//void				push_back(const TA& _Val)		{ m_value.push_back(_Val);}
//			//void				push_back(TA&& _Val )			{ m_value.push_back(_Val);}
//			//void				emplace_back(const TA& _Val)	{ m_value.emplace_back(_Val);}
//			//void				emplace_back(TA&& _Val )		{ m_value.emplace_back(_Val);}
//			//void				pop_back()						{ m_value.pop_back();}
//		
//			ITERATOR			begin() noexcept								{ return m_value.begin();}
//			CONST_ITERATOR		begin() const noexcept							{ return m_value.begin();}
//			ITERATOR			end() noexcept									{ return m_value.end();}
//			CONST_ITERATOR		end() const noexcept							{ return m_value.end();}
//																				  
//			void				erase(const ITERATOR& _Where) noexcept			{ m_value.erase(_Where);}
//			void				erase(const CONST_ITERATOR& _Where) noexcept	{ m_value.erase(_Where);}
//		
//			//auto	insert(const TA& _Val)
//};
//
//template <int ICOUNT>
//class VAR<char16_t[ICOUNT]> : public IValue
//{
//public:
//	using TYPE = char16_t*;
//public:
//	VAR() noexcept : IValue(), m_value() { m_value[0] = L'\0'; }
//public:
//	VAR<char16_t[ICOUNT]>& operator=(const char16_t* _rhs)
//	{
//		//if(m_value!=_rhs) 
//		{
//			//wcscpy_s(m_value, ICOUNT, _rhs);
//			memcpy(m_value, _rhs, ICOUNT * 2);
//			m_state.iState = FIELD_STATE::UPDATE;
//		}
//		//else
//		{
//		}
//
//		return *this;
//	}
//
//	template<size_t IICOUNT>
//	VAR<char16_t[ICOUNT]>& operator=(const char16_t(&_rhs)[IICOUNT])
//	{
//		//if(m_value!=_rhs) 
//		{
//			wcscpy_s(m_value, IICOUNT, _rhs);
//			m_state.iState = FIELD_STATE::UPDATE;
//		}
//		//else
//		{
//		}
//
//		return *this;
//	}
//
//	//template <int IDEST_COUNT, int IDEST_INDEX>
//	//VAR<char16_t[ICOUNT]>& operator=(const VAR<char16_t[IDEST_COUNT], IDEST_INDEX>& _rhs)	{	/*if(m_value!=_rhs)*/ {m_value=_rhs; m_state.iState=FIELD_STATE::UPDATE;} /*else ;*/ return *this;}
//
//	operator const char16_t*() const noexcept { return m_value; }
//	operator const FIELD&() const noexcept { return m_state; }
//
//	const char16_t*		get() const noexcept { return m_value; }
//
//	bool				IsNormal() const noexcept { return m_state.iState != FIELD_STATE::NORMAL; }
//	FIELD_STATE			GetFieldState() const noexcept { return m_state.iState; }
//
//public:
//			char16_t			m_value[ICOUNT];
//
//public:
//	virtual	int					process_append(shared_buffer& _buffer, uint32_t _Condition) override
//	{
//		// declare) 
//		int	value = 0;
//
//		switch (m_state.iState)
//		{
//		case	FIELD_STATE::NONE:
//		case	FIELD_STATE::NORMAL:
//				break;
//
//		case	FIELD_STATE::UPDATE:
//				if (_Condition & static_cast<uint32_t>(FIELD_STATE::UPDATE))
//				{
//					_buffer.append<FIELD>(m_state);
//					_buffer.append<const char16_t*>(m_value);
//					value = 1;
//				}
//				break;
//
//		case	FIELD_STATE::CREATE:
//				if (_Condition & static_cast<uint32_t>(FIELD_STATE::UPDATE))
//				{
//					_buffer.append<FIELD>(m_state);
//					_buffer.append<const char16_t*>(m_value);
//					value = 1;
//				}
//				break;
//
//		case	FIELD_STATE::REMOVE:
//				if (_Condition & static_cast<uint32_t>(FIELD_STATE::UPDATE))
//				{
//					_buffer.append<FIELD>(m_state);
//					value = 1;
//				}
//				break;
//
//		default:
//				break;
//		}
//
//		return	0;
//	}
//
//	virtual	void				process_extract(buffer_view& _buffer, const FIELD& _NewState) override
//	{
//		// check) 
//		CGASSERT_ERROR(_NewState.revision > m_state.revision);
//
//		// 1) 상황에 따른 처리
//		switch (_NewState.iState)
//		{
//		case	FIELD_STATE::NONE:
//		case	FIELD_STATE::NORMAL:
//				{
//					char16_t* pstring = _buffer.extract<char16_t*>();
//					//wcscpy_s(m_value, ICOUNT, pstring);
//					memcpy(m_value, pstring, ICOUNT * 2);
//
//				}
//				break;
//
//		case	FIELD_STATE::UPDATE:
//				{
//						char16_t* pstring = _buffer.extract< char16_t*>();
//					//wcscpy_s(m_value, ICOUNT, pstring);
//					memcpy(m_value, pstring, ICOUNT * 2);
//				}
//				break;
//
//		case	FIELD_STATE::CREATE:
//				break;
//
//		case	FIELD_STATE::REMOVE:
//				m_state.iState = FIELD_STATE::NORMAL;
//				break;
//
//		default:
//				break;
//		}
//
//		// 2) revision과 State를 설정한다.
//		m_state.revision = _NewState.revision;
//		m_state.iState = _NewState.iState;
//	}
//};


}