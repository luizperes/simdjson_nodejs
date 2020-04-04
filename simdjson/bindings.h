#include <napi.h>
#include "src/simdjson.h"

namespace simdjsonnode {
  using namespace simdjson;

  bool isValid(std::string p);
  Napi::Boolean IsValidWrapped(const Napi::CallbackInfo& info);

  Napi::Object parse(Napi::Env env, std::string p);
  Napi::Value makeJSONObject(Napi::Env env, dom::element element);
  Napi::Value ParseWrapped(const Napi::CallbackInfo& info);

  Napi::Object LazyParseWrapped(const Napi::CallbackInfo& info);
  Napi::Value ValueForKeyPathWrapped(const Napi::CallbackInfo& info);
  Napi::Value findKeyPath(Napi::Env env, std::vector<std::string> subpaths, dom::element pjh);

  Napi::Object Init(Napi::Env env, Napi::Object exports);
}
