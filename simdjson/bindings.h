#include <napi.h>
namespace simdjson {
  bool isValid(std::string_view p);
  Napi::Boolean IsValidWrapped(const Napi::CallbackInfo& info);
  Napi::Object Init(Napi::Env env, Napi::Object exports);
}