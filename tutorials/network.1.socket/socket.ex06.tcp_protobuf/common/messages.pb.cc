// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: messages.proto

#include "messages.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

namespace tutorial {
PROTOBUF_CONSTEXPR SendA::SendA(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.testvalue_)*/0
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct SendADefaultTypeInternal {
  PROTOBUF_CONSTEXPR SendADefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~SendADefaultTypeInternal() {}
  union {
    SendA _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 SendADefaultTypeInternal _SendA_default_instance_;
PROTOBUF_CONSTEXPR SendB::SendB(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.testvalue1_)*/0
  , /*decltype(_impl_.testvalue2_)*/0u
  , /*decltype(_impl_.testvalue3_)*/0
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct SendBDefaultTypeInternal {
  PROTOBUF_CONSTEXPR SendBDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~SendBDefaultTypeInternal() {}
  union {
    SendB _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 SendBDefaultTypeInternal _SendB_default_instance_;
PROTOBUF_CONSTEXPR SendC::SendC(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.testvalue3_)*/{}
  , /*decltype(_impl_._testvalue3_cached_byte_size_)*/{0}
  , /*decltype(_impl_.testvalue2_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.testvalue1_)*/0
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct SendCDefaultTypeInternal {
  PROTOBUF_CONSTEXPR SendCDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~SendCDefaultTypeInternal() {}
  union {
    SendC _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 SendCDefaultTypeInternal _SendC_default_instance_;
}  // namespace tutorial
static ::_pb::Metadata file_level_metadata_messages_2eproto[3];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_messages_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_messages_2eproto = nullptr;

const uint32_t TableStruct_messages_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::tutorial::SendA, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::tutorial::SendA, _impl_.testvalue_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::tutorial::SendB, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::tutorial::SendB, _impl_.testvalue1_),
  PROTOBUF_FIELD_OFFSET(::tutorial::SendB, _impl_.testvalue2_),
  PROTOBUF_FIELD_OFFSET(::tutorial::SendB, _impl_.testvalue3_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::tutorial::SendC, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::tutorial::SendC, _impl_.testvalue1_),
  PROTOBUF_FIELD_OFFSET(::tutorial::SendC, _impl_.testvalue2_),
  PROTOBUF_FIELD_OFFSET(::tutorial::SendC, _impl_.testvalue3_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::tutorial::SendA)},
  { 7, -1, -1, sizeof(::tutorial::SendB)},
  { 16, -1, -1, sizeof(::tutorial::SendC)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::tutorial::_SendA_default_instance_._instance,
  &::tutorial::_SendB_default_instance_._instance,
  &::tutorial::_SendC_default_instance_._instance,
};

const char descriptor_table_protodef_messages_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\016messages.proto\022\010tutorial\"\032\n\005SendA\022\021\n\tT"
  "estValue\030\002 \001(\005\"C\n\005SendB\022\022\n\nTestValue1\030\002 "
  "\001(\005\022\022\n\nTestValue2\030\003 \001(\r\022\022\n\nTestValue3\030\004 "
  "\001(\002\"C\n\005SendC\022\022\n\nTestValue1\030\002 \001(\005\022\022\n\nTest"
  "Value2\030\003 \001(\t\022\022\n\nTestValue3\030\004 \003(\005BH\n\024com."
  "example.tutorialB\014SimpleProtos\252\002!Google."
  "Protobuf.Examples.tutorialb\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_messages_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_messages_2eproto = {
    false, false, 274, descriptor_table_protodef_messages_2eproto,
    "messages.proto",
    &descriptor_table_messages_2eproto_once, nullptr, 0, 3,
    schemas, file_default_instances, TableStruct_messages_2eproto::offsets,
    file_level_metadata_messages_2eproto, file_level_enum_descriptors_messages_2eproto,
    file_level_service_descriptors_messages_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_messages_2eproto_getter() {
  return &descriptor_table_messages_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_messages_2eproto(&descriptor_table_messages_2eproto);
namespace tutorial {

// ===================================================================

class SendA::_Internal {
 public:
};

SendA::SendA(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:tutorial.SendA)
}
SendA::SendA(const SendA& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  SendA* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.testvalue_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _this->_impl_.testvalue_ = from._impl_.testvalue_;
  // @@protoc_insertion_point(copy_constructor:tutorial.SendA)
}

inline void SendA::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.testvalue_){0}
    , /*decltype(_impl_._cached_size_)*/{}
  };
}

SendA::~SendA() {
  // @@protoc_insertion_point(destructor:tutorial.SendA)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void SendA::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void SendA::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void SendA::Clear() {
// @@protoc_insertion_point(message_clear_start:tutorial.SendA)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.testvalue_ = 0;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* SendA::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int32 TestValue = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          _impl_.testvalue_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* SendA::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:tutorial.SendA)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 TestValue = 2;
  if (this->_internal_testvalue() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(2, this->_internal_testvalue(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:tutorial.SendA)
  return target;
}

size_t SendA::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:tutorial.SendA)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // int32 TestValue = 2;
  if (this->_internal_testvalue() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_testvalue());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData SendA::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    SendA::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*SendA::GetClassData() const { return &_class_data_; }


void SendA::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<SendA*>(&to_msg);
  auto& from = static_cast<const SendA&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:tutorial.SendA)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_testvalue() != 0) {
    _this->_internal_set_testvalue(from._internal_testvalue());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void SendA::CopyFrom(const SendA& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:tutorial.SendA)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SendA::IsInitialized() const {
  return true;
}

void SendA::InternalSwap(SendA* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_impl_.testvalue_, other->_impl_.testvalue_);
}

::PROTOBUF_NAMESPACE_ID::Metadata SendA::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_messages_2eproto_getter, &descriptor_table_messages_2eproto_once,
      file_level_metadata_messages_2eproto[0]);
}

// ===================================================================

class SendB::_Internal {
 public:
};

SendB::SendB(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:tutorial.SendB)
}
SendB::SendB(const SendB& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  SendB* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.testvalue1_){}
    , decltype(_impl_.testvalue2_){}
    , decltype(_impl_.testvalue3_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&_impl_.testvalue1_, &from._impl_.testvalue1_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.testvalue3_) -
    reinterpret_cast<char*>(&_impl_.testvalue1_)) + sizeof(_impl_.testvalue3_));
  // @@protoc_insertion_point(copy_constructor:tutorial.SendB)
}

inline void SendB::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.testvalue1_){0}
    , decltype(_impl_.testvalue2_){0u}
    , decltype(_impl_.testvalue3_){0}
    , /*decltype(_impl_._cached_size_)*/{}
  };
}

SendB::~SendB() {
  // @@protoc_insertion_point(destructor:tutorial.SendB)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void SendB::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void SendB::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void SendB::Clear() {
// @@protoc_insertion_point(message_clear_start:tutorial.SendB)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&_impl_.testvalue1_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&_impl_.testvalue3_) -
      reinterpret_cast<char*>(&_impl_.testvalue1_)) + sizeof(_impl_.testvalue3_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* SendB::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int32 TestValue1 = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          _impl_.testvalue1_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // uint32 TestValue2 = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 24)) {
          _impl_.testvalue2_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // float TestValue3 = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 37)) {
          _impl_.testvalue3_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* SendB::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:tutorial.SendB)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 TestValue1 = 2;
  if (this->_internal_testvalue1() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(2, this->_internal_testvalue1(), target);
  }

  // uint32 TestValue2 = 3;
  if (this->_internal_testvalue2() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt32ToArray(3, this->_internal_testvalue2(), target);
  }

  // float TestValue3 = 4;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_testvalue3 = this->_internal_testvalue3();
  uint32_t raw_testvalue3;
  memcpy(&raw_testvalue3, &tmp_testvalue3, sizeof(tmp_testvalue3));
  if (raw_testvalue3 != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteFloatToArray(4, this->_internal_testvalue3(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:tutorial.SendB)
  return target;
}

size_t SendB::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:tutorial.SendB)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // int32 TestValue1 = 2;
  if (this->_internal_testvalue1() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_testvalue1());
  }

  // uint32 TestValue2 = 3;
  if (this->_internal_testvalue2() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt32SizePlusOne(this->_internal_testvalue2());
  }

  // float TestValue3 = 4;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_testvalue3 = this->_internal_testvalue3();
  uint32_t raw_testvalue3;
  memcpy(&raw_testvalue3, &tmp_testvalue3, sizeof(tmp_testvalue3));
  if (raw_testvalue3 != 0) {
    total_size += 1 + 4;
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData SendB::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    SendB::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*SendB::GetClassData() const { return &_class_data_; }


void SendB::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<SendB*>(&to_msg);
  auto& from = static_cast<const SendB&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:tutorial.SendB)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_testvalue1() != 0) {
    _this->_internal_set_testvalue1(from._internal_testvalue1());
  }
  if (from._internal_testvalue2() != 0) {
    _this->_internal_set_testvalue2(from._internal_testvalue2());
  }
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_testvalue3 = from._internal_testvalue3();
  uint32_t raw_testvalue3;
  memcpy(&raw_testvalue3, &tmp_testvalue3, sizeof(tmp_testvalue3));
  if (raw_testvalue3 != 0) {
    _this->_internal_set_testvalue3(from._internal_testvalue3());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void SendB::CopyFrom(const SendB& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:tutorial.SendB)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SendB::IsInitialized() const {
  return true;
}

void SendB::InternalSwap(SendB* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(SendB, _impl_.testvalue3_)
      + sizeof(SendB::_impl_.testvalue3_)
      - PROTOBUF_FIELD_OFFSET(SendB, _impl_.testvalue1_)>(
          reinterpret_cast<char*>(&_impl_.testvalue1_),
          reinterpret_cast<char*>(&other->_impl_.testvalue1_));
}

::PROTOBUF_NAMESPACE_ID::Metadata SendB::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_messages_2eproto_getter, &descriptor_table_messages_2eproto_once,
      file_level_metadata_messages_2eproto[1]);
}

// ===================================================================

class SendC::_Internal {
 public:
};

SendC::SendC(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:tutorial.SendC)
}
SendC::SendC(const SendC& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  SendC* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.testvalue3_){from._impl_.testvalue3_}
    , /*decltype(_impl_._testvalue3_cached_byte_size_)*/{0}
    , decltype(_impl_.testvalue2_){}
    , decltype(_impl_.testvalue1_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.testvalue2_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.testvalue2_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_testvalue2().empty()) {
    _this->_impl_.testvalue2_.Set(from._internal_testvalue2(), 
      _this->GetArenaForAllocation());
  }
  _this->_impl_.testvalue1_ = from._impl_.testvalue1_;
  // @@protoc_insertion_point(copy_constructor:tutorial.SendC)
}

inline void SendC::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.testvalue3_){arena}
    , /*decltype(_impl_._testvalue3_cached_byte_size_)*/{0}
    , decltype(_impl_.testvalue2_){}
    , decltype(_impl_.testvalue1_){0}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.testvalue2_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.testvalue2_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

SendC::~SendC() {
  // @@protoc_insertion_point(destructor:tutorial.SendC)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void SendC::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.testvalue3_.~RepeatedField();
  _impl_.testvalue2_.Destroy();
}

void SendC::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void SendC::Clear() {
// @@protoc_insertion_point(message_clear_start:tutorial.SendC)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.testvalue3_.Clear();
  _impl_.testvalue2_.ClearToEmpty();
  _impl_.testvalue1_ = 0;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* SendC::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int32 TestValue1 = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          _impl_.testvalue1_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // string TestValue2 = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 26)) {
          auto str = _internal_mutable_testvalue2();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "tutorial.SendC.TestValue2"));
        } else
          goto handle_unusual;
        continue;
      // repeated int32 TestValue3 = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 34)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::PackedInt32Parser(_internal_mutable_testvalue3(), ptr, ctx);
          CHK_(ptr);
        } else if (static_cast<uint8_t>(tag) == 32) {
          _internal_add_testvalue3(::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* SendC::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:tutorial.SendC)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 TestValue1 = 2;
  if (this->_internal_testvalue1() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(2, this->_internal_testvalue1(), target);
  }

  // string TestValue2 = 3;
  if (!this->_internal_testvalue2().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_testvalue2().data(), static_cast<int>(this->_internal_testvalue2().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "tutorial.SendC.TestValue2");
    target = stream->WriteStringMaybeAliased(
        3, this->_internal_testvalue2(), target);
  }

  // repeated int32 TestValue3 = 4;
  {
    int byte_size = _impl_._testvalue3_cached_byte_size_.load(std::memory_order_relaxed);
    if (byte_size > 0) {
      target = stream->WriteInt32Packed(
          4, _internal_testvalue3(), byte_size, target);
    }
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:tutorial.SendC)
  return target;
}

size_t SendC::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:tutorial.SendC)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated int32 TestValue3 = 4;
  {
    size_t data_size = ::_pbi::WireFormatLite::
      Int32Size(this->_impl_.testvalue3_);
    if (data_size > 0) {
      total_size += 1 +
        ::_pbi::WireFormatLite::Int32Size(static_cast<int32_t>(data_size));
    }
    int cached_size = ::_pbi::ToCachedSize(data_size);
    _impl_._testvalue3_cached_byte_size_.store(cached_size,
                                    std::memory_order_relaxed);
    total_size += data_size;
  }

  // string TestValue2 = 3;
  if (!this->_internal_testvalue2().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_testvalue2());
  }

  // int32 TestValue1 = 2;
  if (this->_internal_testvalue1() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_testvalue1());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData SendC::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    SendC::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*SendC::GetClassData() const { return &_class_data_; }


void SendC::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<SendC*>(&to_msg);
  auto& from = static_cast<const SendC&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:tutorial.SendC)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  _this->_impl_.testvalue3_.MergeFrom(from._impl_.testvalue3_);
  if (!from._internal_testvalue2().empty()) {
    _this->_internal_set_testvalue2(from._internal_testvalue2());
  }
  if (from._internal_testvalue1() != 0) {
    _this->_internal_set_testvalue1(from._internal_testvalue1());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void SendC::CopyFrom(const SendC& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:tutorial.SendC)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SendC::IsInitialized() const {
  return true;
}

void SendC::InternalSwap(SendC* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  _impl_.testvalue3_.InternalSwap(&other->_impl_.testvalue3_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.testvalue2_, lhs_arena,
      &other->_impl_.testvalue2_, rhs_arena
  );
  swap(_impl_.testvalue1_, other->_impl_.testvalue1_);
}

::PROTOBUF_NAMESPACE_ID::Metadata SendC::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_messages_2eproto_getter, &descriptor_table_messages_2eproto_once,
      file_level_metadata_messages_2eproto[2]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace tutorial
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::tutorial::SendA*
Arena::CreateMaybeMessage< ::tutorial::SendA >(Arena* arena) {
  return Arena::CreateMessageInternal< ::tutorial::SendA >(arena);
}
template<> PROTOBUF_NOINLINE ::tutorial::SendB*
Arena::CreateMaybeMessage< ::tutorial::SendB >(Arena* arena) {
  return Arena::CreateMessageInternal< ::tutorial::SendB >(arena);
}
template<> PROTOBUF_NOINLINE ::tutorial::SendC*
Arena::CreateMaybeMessage< ::tutorial::SendC >(Arena* arena) {
  return Arena::CreateMessageInternal< ::tutorial::SendC >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
