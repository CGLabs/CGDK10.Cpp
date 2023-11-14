//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                             Archive Classes                               *
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
// context
//
//
//-----------------------------------------------------------------------------
enum class eCONTEXT_VALUE_TYPE : uint32_t
{
	NULL_				 = 0,
	NUMBER_				 = 1,
	DOUBLE_				 = 2,
	STRING_				 = 3,
	BOOL_				 = 4,
	OBJECT_				 = 5,
	ARRAY_				 = 6,
	BINARY_				 = 7,
	NODE_				 = 8,
	BUFFER_				 = 9,
	PTR_				 = 10,
	CHRONO_DURATION_	 = 11,
	CHRONO_TIME_POINT_	 = 12,
};

class context
{
public:
			struct VALUE
			{
			public:
				VALUE() {}
				VALUE(const VALUE& _copy) { this->operator = (_copy); }
				VALUE(VALUE&& _move) noexcept { this->operator = (std::move(_move)); }
				~VALUE() { this->_free_value_object(); }

				VALUE& operator = (const VALUE& _copy)
				{
					this->_free_value_object();
					this->type = _copy.type;

					if (this->type == eCONTEXT_VALUE_TYPE::STRING_)
					{
						this->value_string = new std::string(*_copy.value_string);
					}
					else
					{
						this->value_buffer = _copy.value_buffer;
					}

					return *this;
				}
				VALUE& operator = (VALUE&& _move) noexcept
				{
					this->_free_value_object();

					this->value_buffer = _move.value_buffer;
					_move.value_buffer = buffer_view{};

					this->type = _move.type;
					_move.type = eCONTEXT_VALUE_TYPE::NULL_; 

					return *this;
				}

				void clear() noexcept 
				{
					this->_free_value_object();
					
					this->value_buffer = buffer_view{};
					this->type = eCONTEXT_VALUE_TYPE::NULL_;
				}

			public:
				void _free_value_object() noexcept 
				{
					if (type == eCONTEXT_VALUE_TYPE::STRING_ && value_string != nullptr)
					{
						delete value_string;
					}
				}

			public:
				union
				{
					std::string*		value_string;
					int8_t				value_int8;
					uint8_t				value_uint8;
					int16_t				value_int16;
					uint16_t			value_uint16;
					int32_t				value_int32;
					uint32_t			value_uint32;
					int64_t				value_int64;
					uint64_t			value_uint64;
					double				value_double;
					buffer_view			value_buffer {0,0};
					void*				value_ptr;
				};

				eCONTEXT_VALUE_TYPE	type = eCONTEXT_VALUE_TYPE::NULL_;
			};

			VALUE				v;
			context*			pnode_parent = nullptr;
			std::map<const std::string, context> map_node;

			using iterator = std::map<std::string, context>::iterator;
			using const_iterator = std::map<std::string, context>::const_iterator;
public:
			context() noexcept {}
			context(const context& _copy) : v{ _copy.v }, pnode_parent{ _copy.pnode_parent }, map_node{ _copy.map_node } { for (auto& iter : map_node) { iter.second.pnode_parent = this; } }
			context(context&& _move) noexcept : v{ std::move(_move.v) }, pnode_parent{ nullptr }, map_node{ std::move(_move.map_node) } { _move.pnode_parent = nullptr; }
	explicit context(const buffer_view& _buffer) noexcept { v.type = eCONTEXT_VALUE_TYPE::BUFFER_; v.value_buffer = _buffer; }
	explicit context(std::string_view _json_filename, eFILE_LOCATION _file_location = eFILE_LOCATION::DEFAULT) { this->read_from_json_file(_json_filename, _file_location); }
			~context() noexcept {}

public:
	[[nodiscard]] iterator		begin() noexcept { return map_node.begin(); }
	[[nodiscard]] iterator		end() noexcept { return map_node.end(); }
	[[nodiscard]] const_iterator begin() const noexcept { return map_node.begin(); }
	[[nodiscard]] const_iterator end() const noexcept { return map_node.end(); }
	[[nodiscard]] size_t		size() const noexcept { return map_node.size(); }
	[[nodiscard]] eCONTEXT_VALUE_TYPE type() const noexcept { return v.type; }

			bool				read_from_json_file (std::string_view _filename, eFILE_LOCATION _file_location = eFILE_LOCATION::DEFAULT);
			bool				read_from_json_string (std::string_view _data);
			bool				write_to_json_file (std::string_view _filename, eFILE_LOCATION _file_location = eFILE_LOCATION::DEFAULT);
			template <class T = char>
			shared_buffer		write_to_json_string (bool _is_file = false);
			shared_buffer		write_to_json_string_char (bool _is_file = false);
			shared_buffer		write_to_json_string_wchar (bool _is_file = false);
			shared_buffer		write_to_json_string_u16char (bool _is_file = false);
			shared_buffer		write_to_json_string_u32char (bool _is_file = false);

			context&			insert(std::string_view _key, eCONTEXT_VALUE_TYPE _value_type = eCONTEXT_VALUE_TYPE::NULL_);
			context&			insert_bool(std::string_view _key, bool _value);
			context&			insert_string(std::string_view _key, std::string_view _value);
			context&			insert_integer(std::string_view _key, int64_t _value);
			context&			insert_double(std::string_view _key, double _value);
			bool				erase(std::string_view _key) noexcept;
	[[nodiscard]] bool			has_key(std::string_view _key) const noexcept;
	[[nodiscard]] context&		find(std::string_view _key);
			template <class T>
	[[nodiscard]] context&		find(std::string_view _key_a, T _key_b);
			template <class... TARGS>
	[[nodiscard]] context&		find(std::string_view _key_a, TARGS... _key_args);
	[[nodiscard]] const context& find(std::string_view _key) const;
			template <class T>
	[[nodiscard]] const context& find(std::string_view _key_a, T _key_b) const;
			template <class... TARGS>
	[[nodiscard]] const context& find(std::string_view _key_a, TARGS... _key_args) const;
	[[nodiscard]] bool			is_valid() const noexcept { return v.type != eCONTEXT_VALUE_TYPE::NULL_; }
	[[nodiscard]] bool			is_invalid() const noexcept { return v.type == eCONTEXT_VALUE_TYPE::NULL_; }
																  
			template<class T>
	[[nodiscard]] T&			ref_value() const;

			void				clear() noexcept { v.clear(); pnode_parent = nullptr; map_node.clear(); }
			void				swap(context& _rhs) noexcept { SWAP(v.value_string, _rhs.v.value_string); SWAP(pnode_parent, _rhs.pnode_parent); map_node.swap(_rhs.map_node);}

			context&			operator [] (const std::string_view _key) { return this->find(_key); }
			const context&		operator [] (const std::string_view _key) const { return this->find(_key); }
			context&			operator [] (int _index);
			const context&		operator [] (int _index) const;
																					  
			context&			operator =	(std::string&& _rhs);
			context&			operator =	(const std::string_view _rhs);
			context&			operator =	(bool _rhs);
			context&			operator =	(char _rhs);
			context&			operator =	(unsigned char _rhs);
			context&			operator =	(int16_t _rhs);
			context&			operator =	(uint16_t _rhs);
			context&			operator =	(int32_t _rhs);
			context&			operator =	(uint32_t _rhs);
			context&			operator =	(int64_t _rhs);
			context&			operator =	(uint64_t _rhs);
			context&			operator =	(float _rhs);
			context&			operator =	(double _rhs);
			context&			operator =	(const buffer_view& _rhs) noexcept;
			template <class A, class B>
			context&			operator =	(const std::chrono::duration<A,B>& _rhs) noexcept;
			template <class A, class B = typename A::duration>
			context&			operator =	(const std::chrono::time_point<A,B>& _rhs) noexcept;
			context&			operator =  (const context& _rhs);
			context&			operator =  (context&& _rhs) noexcept;
			template <class T>
			std::enable_if_t<!is_string_type<T>::value, context&>
								operator =  (const T* _rhs) noexcept
								{
									// 1) delete old value
									if (v.type == eCONTEXT_VALUE_TYPE::BUFFER_)
										SAFE_DELETE(v.value_string);

									// 2) Value
									v.value_ptr = const_cast<T*>(_rhs);
									v.type = eCONTEXT_VALUE_TYPE::PTR_;

									// return)  
									return *this;
								}

			template <class T> 
	[[nodiscard]] static T		__get_value_from_value(const VALUE& _value)
								{
									switch (_value.type)
									{
									case	eCONTEXT_VALUE_TYPE::NUMBER_:
											return static_cast<T>(_value.value_int64);
									case	eCONTEXT_VALUE_TYPE::DOUBLE_:
											return static_cast<T>(_value.value_double);
									case	eCONTEXT_VALUE_TYPE::STRING_:
											{
												if (_value.value_string == nullptr) throw std::exception();
												return __from_string<T>(_value.value_string->c_str());
											}
									case	eCONTEXT_VALUE_TYPE::BOOL_:
											return static_cast<T>(_value.value_int64 != 0);
									case	eCONTEXT_VALUE_TYPE::CHRONO_DURATION_:
											return static_cast<T>(_value.value_int64);
									case	eCONTEXT_VALUE_TYPE::CHRONO_TIME_POINT_:
											return static_cast<T>(_value.value_int64);
									default:
											throw std::exception();
									};
								}

	[[nodiscard]] 				operator std::string() const
								{
									switch (v.type)
									{
									case	eCONTEXT_VALUE_TYPE::NUMBER_:
											return __to_string<std::string>(v.value_int64);
									case	eCONTEXT_VALUE_TYPE::DOUBLE_:
											return __to_string<std::string>(v.value_double);
									case	eCONTEXT_VALUE_TYPE::STRING_:
											return *v.value_string;
									case	eCONTEXT_VALUE_TYPE::BOOL_:
											return std::string((v.value_int64 != 0) ? "true" : "false");
									case	eCONTEXT_VALUE_TYPE::CHRONO_DURATION_:
											return __to_string<std::string>(v.value_int64);
									case	eCONTEXT_VALUE_TYPE::CHRONO_TIME_POINT_:
											return __to_string<std::string>(v.value_int64);
									default:
											return std::string();
									};
								}
	[[nodiscard]] 				operator std::wstring() const { if (v.value_string == nullptr) return std::wstring(); return encode_string<wchar_t>(std::string_view(*v.value_string)); }
	[[nodiscard]] 				operator std::u16string() const { if (v.value_string == nullptr) return std::u16string(); return encode_string<char16_t>(std::string_view(*v.value_string)); }
	[[nodiscard]] 				operator std::u32string() const { if (v.value_string == nullptr) return std::u32string(); return encode_string<char32_t>(std::string_view(*v.value_string)); }
	[[nodiscard]] 				operator bool() const { if (v.value_string == nullptr) throw std::exception(); if(__strcmp(v.value_string->c_str(), "true")==0) return true; if (__strcmp(v.value_string->c_str(), "1") == 0) return true; return false; }
	[[nodiscard]] 	explicit	operator char() const { return __get_value_from_value<char>(v); }
	[[nodiscard]] 				operator unsigned char() const { return __get_value_from_value<unsigned char>(v); }
	[[nodiscard]] 				operator int16_t() const { return __get_value_from_value<int16_t>(v); }
	[[nodiscard]] 				operator uint16_t() const { return __get_value_from_value<uint16_t>(v); }
	[[nodiscard]] 				operator int32_t() const { return __get_value_from_value<int32_t>(v); }
	[[nodiscard]] 				operator uint32_t() const { return __get_value_from_value<uint32_t>(v); }
	[[nodiscard]] 				operator int64_t() const { return __get_value_from_value<int64_t>(v); }
	[[nodiscard]] 				operator uint64_t() const { return __get_value_from_value<uint64_t>(v); }
	[[nodiscard]] 				operator float() const { return __get_value_from_value<float>(v); }
	[[nodiscard]] 				operator double() const { return __get_value_from_value<double>(v); }
	[[nodiscard]] 				operator buffer_view() const { return (v.type == eCONTEXT_VALUE_TYPE::BUFFER_) ? v.value_buffer : buffer_view(); }
								template <class A, class B>
	[[nodiscard]] 				operator std::chrono::duration<A, B>() const { if (v.type != eCONTEXT_VALUE_TYPE::CHRONO_DURATION_) throw std::exception(); return std::chrono::duration<A, B>(v.value_int64); }
								template <class A, class B = typename A::duration>
	[[nodiscard]] 				operator std::chrono::time_point<A, B>() const { if (v.type != eCONTEXT_VALUE_TYPE::CHRONO_TIME_POINT_) throw std::exception(); return std::chrono::time_point<A, B>(B(v.value_int64)); }
								template <class T>
	[[nodiscard]]	explicit	operator T* () const { if (v.type != eCONTEXT_VALUE_TYPE::PTR_) throw std::exception(); return reinterpret_cast<T*>(v.value_ptr); }
private:
				void			_validate_child() { if (v.type == eCONTEXT_VALUE_TYPE::NULL_) v.type = eCONTEXT_VALUE_TYPE::NODE_; if (pnode_parent != nullptr) pnode_parent->_validate_child(); }
};

template<>
inline shared_buffer context::write_to_json_string<char>(bool _is_file)
{
	return write_to_json_string_char(_is_file);
}

template<>
inline shared_buffer context::write_to_json_string<wchar_t>(bool _is_file)
{
	return write_to_json_string_wchar(_is_file);
}

template<>
inline shared_buffer context::write_to_json_string<char16_t>(bool _is_file)
{
	return write_to_json_string_u16char(_is_file);
}

template<>
inline shared_buffer context::write_to_json_string<char32_t>(bool _is_file)
{
	return write_to_json_string_u32char(_is_file);
}

template <class T>
context& context::find(std::string_view _key_a, T _key_b)
{
	// 1) to lowercase
	char temp_key[256]{};
	__to_lower<char>(temp_key, _key_a.data());

	// 2) find key
	auto iter_find = map_node.find(temp_key);

	// check) return if find
	if (iter_find != map_node.end())
	{
		return iter_find->second;
	}

	// 3) find 
	return find(_key_b);
}

template <class... TARGS>
context& context::find(std::string_view _key_a, TARGS... _key_args)
{
	// 1) to lowercase
	char temp_key[256]{};
	__to_lower<char>(temp_key, _key_a.data());

	// 2) find key
	auto iter_find = map_node.find(temp_key);

	// check) return if find
	if (iter_find != map_node.end())
	{
		return iter_find->second;
	}

	// 3) find 
	return find(_key_args...);
}

template <class T>
const context& context::find(std::string_view _key_a, T _key_b) const
{
	// 1) to lowercase
	char temp_key[256]{};
	__to_lower<char>(temp_key, _key_a.data());

	// 2) find key
	auto iter_find = map_node.find(temp_key);

	// check) return if find
	if (iter_find != map_node.end())
		return iter_find->second;

	// 3) find and return
	return find(_key_b);
}

template <class... TARGS>
const context& context::find(std::string_view _key_a, TARGS... _key_args) const
{
	// 1) to lowercase
	char temp_key[256]{};
	__to_lower<char>(temp_key, _key_a.data());

	// 2) find key
	auto iter_find = map_node.find(temp_key);

	// check) return if find
	if (iter_find != map_node.end())
	{
		return iter_find->second;
	}

	// 3) find 
	return find(_key_args...);
}

template <class T>
 T& context::ref_value() const
{
	// check)
	if (v.value_string == nullptr)
		throw std::exception();

	// check)
	if (v.type != eCONTEXT_VALUE_TYPE::PTR_)
		throw std::exception();

	// 1) ...
	return *reinterpret_cast<T*>(v.value_ptr);
}

 template <class A, class B>
 context& context::operator = (const std::chrono::duration<A, B>& _rhs) noexcept
 {
	 // 1) prepare value object
	 v._free_value_object();

	 // 2) set value
	 v.value_int64 = _rhs.count();
	 v.type = eCONTEXT_VALUE_TYPE::CHRONO_DURATION_;

	 // 3) validate child
	 _validate_child();

	 // return)  
	 return *this;
 }

 template <class A, class B>
 context& context::operator = (const std::chrono::time_point<A, B>& _rhs) noexcept
 {
	// 1) prepare value object
	v._free_value_object();

	// 2) set value
	v.value_int64 = _rhs.time_since_epoch().count();
	v.type = eCONTEXT_VALUE_TYPE::CHRONO_TIME_POINT_;

	// 3) validate child
	_validate_child();

	// return)  
	return *this;
 }



class sMESSAGE_CONTEXT : public sMESSAGE
{
public:
	sMESSAGE_CONTEXT() noexcept : sMESSAGE{ eMESSAGE::SYSTEM::CONTEXT }, setting{ &root } {}
	sMESSAGE_CONTEXT(const context& _context) noexcept : sMESSAGE{ eMESSAGE::SYSTEM::CONTEXT }, root{ _context }, setting{ &root } {}
			sMESSAGE_CONTEXT(context&& _context) noexcept : sMESSAGE{ eMESSAGE::SYSTEM::CONTEXT }, root{ _context }, setting{ &root } {}
			sMESSAGE_CONTEXT(uint32_t _message) noexcept : sMESSAGE{ _message }, setting{ &root } {}
			sMESSAGE_CONTEXT(std::string_view _filename) noexcept : sMESSAGE{ eMESSAGE::SYSTEM::CONTEXT }, setting{ &root } { root.read_from_json_file(_filename); }
			sMESSAGE_CONTEXT(std::string_view _str_json, bool /*_is_string*/) noexcept : sMESSAGE{ eMESSAGE::SYSTEM::CONTEXT }, setting{ &root }	{ root.read_from_json_string(_str_json); }
			sMESSAGE_CONTEXT(const sMESSAGE_CONTEXT& _copy) noexcept : sMESSAGE{ _copy }, setting{ &root }, plog{ _copy.plog } { root = _copy.root; }

public:
			void				clear() noexcept { root.clear();}
																							  
			bool				read(std::string_view _filename) { return setting->read_from_json_file(_filename); }
			bool				read_from_json_string(std::string_view _str_json) { return setting->read_from_json_string(_str_json); }

			sMESSAGE_CONTEXT&	operator=(const sMESSAGE_CONTEXT& _rhs) noexcept			
			{
				message = _rhs.message;
				plog = _rhs.plog;
				root = _rhs.root;

				return	*this;
			}
			sMESSAGE_CONTEXT&	operator=(sMESSAGE_CONTEXT&& _rhs) noexcept
			{
				message = _rhs.message;
				plog = std::move(_rhs.plog);
				root = std::move(_rhs.root);

				return	*this;
			}

public:
			context				root;
			context*			setting;
			object_ptr<Imessageable> plog;
};


}