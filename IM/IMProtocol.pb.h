// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: IMProtocol.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_IMProtocol_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_IMProtocol_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3007000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3007001 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_IMProtocol_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_IMProtocol_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[4]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_IMProtocol_2eproto;
class Request_login;
class Request_loginDefaultTypeInternal;
extern Request_loginDefaultTypeInternal _Request_login_default_instance_;
class Request_logout;
class Request_logoutDefaultTypeInternal;
extern Request_logoutDefaultTypeInternal _Request_logout_default_instance_;
class Request_sendmsg;
class Request_sendmsgDefaultTypeInternal;
extern Request_sendmsgDefaultTypeInternal _Request_sendmsg_default_instance_;
class Response_login;
class Response_loginDefaultTypeInternal;
extern Response_loginDefaultTypeInternal _Response_login_default_instance_;
PROTOBUF_NAMESPACE_OPEN
template<> ::Request_login* Arena::CreateMaybeMessage<::Request_login>(Arena*);
template<> ::Request_logout* Arena::CreateMaybeMessage<::Request_logout>(Arena*);
template<> ::Request_sendmsg* Arena::CreateMaybeMessage<::Request_sendmsg>(Arena*);
template<> ::Response_login* Arena::CreateMaybeMessage<::Response_login>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

enum Response_login_STAT : int {
  Response_login_STAT_SUCCESS = 0,
  Response_login_STAT_ACCOUNT_NULL = 1,
  Response_login_STAT_ACCOUNT_LOCK = 2,
  Response_login_STAT_PASSWORD_ERROR = 3,
  Response_login_STAT_ERROR = 10,
  Response_login_STAT_Response_login_STAT_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  Response_login_STAT_Response_login_STAT_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool Response_login_STAT_IsValid(int value);
constexpr Response_login_STAT Response_login_STAT_STAT_MIN = Response_login_STAT_SUCCESS;
constexpr Response_login_STAT Response_login_STAT_STAT_MAX = Response_login_STAT_ERROR;
constexpr int Response_login_STAT_STAT_ARRAYSIZE = Response_login_STAT_STAT_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* Response_login_STAT_descriptor();
template<typename T>
inline const std::string& Response_login_STAT_Name(T enum_t_value) {
  static_assert(::std::is_same<T, Response_login_STAT>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function Response_login_STAT_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    Response_login_STAT_descriptor(), enum_t_value);
}
inline bool Response_login_STAT_Parse(
    const std::string& name, Response_login_STAT* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<Response_login_STAT>(
    Response_login_STAT_descriptor(), name, value);
}
// ===================================================================

class Request_login :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Request_login) */ {
 public:
  Request_login();
  virtual ~Request_login();

  Request_login(const Request_login& from);
  Request_login(Request_login&& from) noexcept
    : Request_login() {
    *this = ::std::move(from);
  }

  inline Request_login& operator=(const Request_login& from) {
    CopyFrom(from);
    return *this;
  }
  inline Request_login& operator=(Request_login&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const Request_login& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Request_login* internal_default_instance() {
    return reinterpret_cast<const Request_login*>(
               &_Request_login_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(Request_login* other);
  friend void swap(Request_login& a, Request_login& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Request_login* New() const final {
    return CreateMaybeMessage<Request_login>(nullptr);
  }

  Request_login* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Request_login>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Request_login& from);
  void MergeFrom(const Request_login& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Request_login* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Request_login";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_IMProtocol_2eproto);
    return ::descriptor_table_IMProtocol_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string password = 2;
  void clear_password();
  static const int kPasswordFieldNumber = 2;
  const std::string& password() const;
  void set_password(const std::string& value);
  void set_password(std::string&& value);
  void set_password(const char* value);
  void set_password(const char* value, size_t size);
  std::string* mutable_password();
  std::string* release_password();
  void set_allocated_password(std::string* password);

  // uint64 ID = 1;
  void clear_id();
  static const int kIDFieldNumber = 1;
  ::PROTOBUF_NAMESPACE_ID::uint64 id() const;
  void set_id(::PROTOBUF_NAMESPACE_ID::uint64 value);

  // @@protoc_insertion_point(class_scope:Request_login)
 private:
  class HasBitSetters;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr password_;
  ::PROTOBUF_NAMESPACE_ID::uint64 id_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_IMProtocol_2eproto;
};
// -------------------------------------------------------------------

class Response_login :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Response_login) */ {
 public:
  Response_login();
  virtual ~Response_login();

  Response_login(const Response_login& from);
  Response_login(Response_login&& from) noexcept
    : Response_login() {
    *this = ::std::move(from);
  }

  inline Response_login& operator=(const Response_login& from) {
    CopyFrom(from);
    return *this;
  }
  inline Response_login& operator=(Response_login&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const Response_login& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Response_login* internal_default_instance() {
    return reinterpret_cast<const Response_login*>(
               &_Response_login_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(Response_login* other);
  friend void swap(Response_login& a, Response_login& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Response_login* New() const final {
    return CreateMaybeMessage<Response_login>(nullptr);
  }

  Response_login* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Response_login>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Response_login& from);
  void MergeFrom(const Response_login& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Response_login* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Response_login";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_IMProtocol_2eproto);
    return ::descriptor_table_IMProtocol_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  typedef Response_login_STAT STAT;
  static constexpr STAT SUCCESS =
    Response_login_STAT_SUCCESS;
  static constexpr STAT ACCOUNT_NULL =
    Response_login_STAT_ACCOUNT_NULL;
  static constexpr STAT ACCOUNT_LOCK =
    Response_login_STAT_ACCOUNT_LOCK;
  static constexpr STAT PASSWORD_ERROR =
    Response_login_STAT_PASSWORD_ERROR;
  static constexpr STAT ERROR =
    Response_login_STAT_ERROR;
  static inline bool STAT_IsValid(int value) {
    return Response_login_STAT_IsValid(value);
  }
  static constexpr STAT STAT_MIN =
    Response_login_STAT_STAT_MIN;
  static constexpr STAT STAT_MAX =
    Response_login_STAT_STAT_MAX;
  static constexpr int STAT_ARRAYSIZE =
    Response_login_STAT_STAT_ARRAYSIZE;
  static inline const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor*
  STAT_descriptor() {
    return Response_login_STAT_descriptor();
  }
  template<typename T>
  static inline const std::string& STAT_Name(T enum_t_value) {
    static_assert(::std::is_same<T, STAT>::value ||
      ::std::is_integral<T>::value,
      "Incorrect type passed to function STAT_Name.");
    return Response_login_STAT_Name(enum_t_value);
  }
  static inline bool STAT_Parse(const std::string& name,
      STAT* value) {
    return Response_login_STAT_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // .Response_login.STAT stat = 1;
  void clear_stat();
  static const int kStatFieldNumber = 1;
  ::Response_login_STAT stat() const;
  void set_stat(::Response_login_STAT value);

  // @@protoc_insertion_point(class_scope:Response_login)
 private:
  class HasBitSetters;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  int stat_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_IMProtocol_2eproto;
};
// -------------------------------------------------------------------

class Request_logout :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Request_logout) */ {
 public:
  Request_logout();
  virtual ~Request_logout();

  Request_logout(const Request_logout& from);
  Request_logout(Request_logout&& from) noexcept
    : Request_logout() {
    *this = ::std::move(from);
  }

  inline Request_logout& operator=(const Request_logout& from) {
    CopyFrom(from);
    return *this;
  }
  inline Request_logout& operator=(Request_logout&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const Request_logout& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Request_logout* internal_default_instance() {
    return reinterpret_cast<const Request_logout*>(
               &_Request_logout_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  void Swap(Request_logout* other);
  friend void swap(Request_logout& a, Request_logout& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Request_logout* New() const final {
    return CreateMaybeMessage<Request_logout>(nullptr);
  }

  Request_logout* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Request_logout>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Request_logout& from);
  void MergeFrom(const Request_logout& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Request_logout* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Request_logout";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_IMProtocol_2eproto);
    return ::descriptor_table_IMProtocol_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // uint64 ID = 1;
  void clear_id();
  static const int kIDFieldNumber = 1;
  ::PROTOBUF_NAMESPACE_ID::uint64 id() const;
  void set_id(::PROTOBUF_NAMESPACE_ID::uint64 value);

  // @@protoc_insertion_point(class_scope:Request_logout)
 private:
  class HasBitSetters;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::uint64 id_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_IMProtocol_2eproto;
};
// -------------------------------------------------------------------

class Request_sendmsg :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Request_sendmsg) */ {
 public:
  Request_sendmsg();
  virtual ~Request_sendmsg();

  Request_sendmsg(const Request_sendmsg& from);
  Request_sendmsg(Request_sendmsg&& from) noexcept
    : Request_sendmsg() {
    *this = ::std::move(from);
  }

  inline Request_sendmsg& operator=(const Request_sendmsg& from) {
    CopyFrom(from);
    return *this;
  }
  inline Request_sendmsg& operator=(Request_sendmsg&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const Request_sendmsg& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Request_sendmsg* internal_default_instance() {
    return reinterpret_cast<const Request_sendmsg*>(
               &_Request_sendmsg_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    3;

  void Swap(Request_sendmsg* other);
  friend void swap(Request_sendmsg& a, Request_sendmsg& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Request_sendmsg* New() const final {
    return CreateMaybeMessage<Request_sendmsg>(nullptr);
  }

  Request_sendmsg* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Request_sendmsg>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Request_sendmsg& from);
  void MergeFrom(const Request_sendmsg& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Request_sendmsg* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Request_sendmsg";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_IMProtocol_2eproto);
    return ::descriptor_table_IMProtocol_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string msg = 3;
  void clear_msg();
  static const int kMsgFieldNumber = 3;
  const std::string& msg() const;
  void set_msg(const std::string& value);
  void set_msg(std::string&& value);
  void set_msg(const char* value);
  void set_msg(const char* value, size_t size);
  std::string* mutable_msg();
  std::string* release_msg();
  void set_allocated_msg(std::string* msg);

  // uint64 ID = 1;
  void clear_id();
  static const int kIDFieldNumber = 1;
  ::PROTOBUF_NAMESPACE_ID::uint64 id() const;
  void set_id(::PROTOBUF_NAMESPACE_ID::uint64 value);

  // uint64 objID = 2;
  void clear_objid();
  static const int kObjIDFieldNumber = 2;
  ::PROTOBUF_NAMESPACE_ID::uint64 objid() const;
  void set_objid(::PROTOBUF_NAMESPACE_ID::uint64 value);

  // @@protoc_insertion_point(class_scope:Request_sendmsg)
 private:
  class HasBitSetters;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr msg_;
  ::PROTOBUF_NAMESPACE_ID::uint64 id_;
  ::PROTOBUF_NAMESPACE_ID::uint64 objid_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_IMProtocol_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Request_login

// uint64 ID = 1;
inline void Request_login::clear_id() {
  id_ = PROTOBUF_ULONGLONG(0);
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 Request_login::id() const {
  // @@protoc_insertion_point(field_get:Request_login.ID)
  return id_;
}
inline void Request_login::set_id(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  
  id_ = value;
  // @@protoc_insertion_point(field_set:Request_login.ID)
}

// string password = 2;
inline void Request_login::clear_password() {
  password_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& Request_login::password() const {
  // @@protoc_insertion_point(field_get:Request_login.password)
  return password_.GetNoArena();
}
inline void Request_login::set_password(const std::string& value) {
  
  password_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Request_login.password)
}
inline void Request_login::set_password(std::string&& value) {
  
  password_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:Request_login.password)
}
inline void Request_login::set_password(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  password_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Request_login.password)
}
inline void Request_login::set_password(const char* value, size_t size) {
  
  password_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Request_login.password)
}
inline std::string* Request_login::mutable_password() {
  
  // @@protoc_insertion_point(field_mutable:Request_login.password)
  return password_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* Request_login::release_password() {
  // @@protoc_insertion_point(field_release:Request_login.password)
  
  return password_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void Request_login::set_allocated_password(std::string* password) {
  if (password != nullptr) {
    
  } else {
    
  }
  password_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), password);
  // @@protoc_insertion_point(field_set_allocated:Request_login.password)
}

// -------------------------------------------------------------------

// Response_login

// .Response_login.STAT stat = 1;
inline void Response_login::clear_stat() {
  stat_ = 0;
}
inline ::Response_login_STAT Response_login::stat() const {
  // @@protoc_insertion_point(field_get:Response_login.stat)
  return static_cast< ::Response_login_STAT >(stat_);
}
inline void Response_login::set_stat(::Response_login_STAT value) {
  
  stat_ = value;
  // @@protoc_insertion_point(field_set:Response_login.stat)
}

// -------------------------------------------------------------------

// Request_logout

// uint64 ID = 1;
inline void Request_logout::clear_id() {
  id_ = PROTOBUF_ULONGLONG(0);
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 Request_logout::id() const {
  // @@protoc_insertion_point(field_get:Request_logout.ID)
  return id_;
}
inline void Request_logout::set_id(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  
  id_ = value;
  // @@protoc_insertion_point(field_set:Request_logout.ID)
}

// -------------------------------------------------------------------

// Request_sendmsg

// uint64 ID = 1;
inline void Request_sendmsg::clear_id() {
  id_ = PROTOBUF_ULONGLONG(0);
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 Request_sendmsg::id() const {
  // @@protoc_insertion_point(field_get:Request_sendmsg.ID)
  return id_;
}
inline void Request_sendmsg::set_id(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  
  id_ = value;
  // @@protoc_insertion_point(field_set:Request_sendmsg.ID)
}

// uint64 objID = 2;
inline void Request_sendmsg::clear_objid() {
  objid_ = PROTOBUF_ULONGLONG(0);
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 Request_sendmsg::objid() const {
  // @@protoc_insertion_point(field_get:Request_sendmsg.objID)
  return objid_;
}
inline void Request_sendmsg::set_objid(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  
  objid_ = value;
  // @@protoc_insertion_point(field_set:Request_sendmsg.objID)
}

// string msg = 3;
inline void Request_sendmsg::clear_msg() {
  msg_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& Request_sendmsg::msg() const {
  // @@protoc_insertion_point(field_get:Request_sendmsg.msg)
  return msg_.GetNoArena();
}
inline void Request_sendmsg::set_msg(const std::string& value) {
  
  msg_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Request_sendmsg.msg)
}
inline void Request_sendmsg::set_msg(std::string&& value) {
  
  msg_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:Request_sendmsg.msg)
}
inline void Request_sendmsg::set_msg(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  msg_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Request_sendmsg.msg)
}
inline void Request_sendmsg::set_msg(const char* value, size_t size) {
  
  msg_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Request_sendmsg.msg)
}
inline std::string* Request_sendmsg::mutable_msg() {
  
  // @@protoc_insertion_point(field_mutable:Request_sendmsg.msg)
  return msg_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* Request_sendmsg::release_msg() {
  // @@protoc_insertion_point(field_release:Request_sendmsg.msg)
  
  return msg_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void Request_sendmsg::set_allocated_msg(std::string* msg) {
  if (msg != nullptr) {
    
  } else {
    
  }
  msg_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), msg);
  // @@protoc_insertion_point(field_set_allocated:Request_sendmsg.msg)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::Response_login_STAT> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Response_login_STAT>() {
  return ::Response_login_STAT_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_IMProtocol_2eproto
