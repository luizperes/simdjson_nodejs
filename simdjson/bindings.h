#ifdef __AVX2__
#include <napi.h>
#include "src/simdjson.h"

namespace simdjsonnode {
  Napi::Boolean hasAVX2Wrapped(const Napi::CallbackInfo& info);

  bool isValid(std::string_view p);
  Napi::Boolean IsValidWrapped(const Napi::CallbackInfo& info);

  Napi::Object parse(Napi::Env env, std::string_view p);
  Napi::Value makeJSONObject(Napi::Env env, ParsedJson::iterator & pj);
  Napi::Object ParseWrapped(const Napi::CallbackInfo& info);

  Napi::Object Init(Napi::Env env, Napi::Object exports);
}

#endif