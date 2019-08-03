#if defined __AVX2__ || defined __SSE42__
#include <napi.h>
#include "src/simdjson.h"

namespace simdjsonnode {
  using namespace simdjson;

  Napi::Boolean HasAVX2Wrapped(const Napi::CallbackInfo& info);

  bool isValid(std::string p);
  Napi::Boolean IsValidWrapped(const Napi::CallbackInfo& info);

  Napi::Object parse(Napi::Env env, std::string p);
  Napi::Value makeJSONObject(Napi::Env env, ParsedJson::Iterator & pj);
  Napi::Object ParseWrapped(const Napi::CallbackInfo& info);

  Napi::Object LazyParseWrapped(const Napi::CallbackInfo& info);
  Napi::Value ValueForKeyPathWrapped(const Napi::CallbackInfo& info);
  Napi::Value findKeyPath(Napi::Env env, std::vector<std::string> subpaths, ParsedJson::Iterator & pjh);

  Napi::Object Init(Napi::Env env, Napi::Object exports);
}

#endif