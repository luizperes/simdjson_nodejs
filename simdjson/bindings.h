#include <napi.h>
#include "src/simdjson.h"

namespace simdjson {
    
  bool isValid(std::string_view p);
  Napi::Boolean IsValidWrapped(const Napi::CallbackInfo& info);
    
  Napi::Object parse(Napi::Env env, std::string_view p);
  Napi::Object makeJSONObject(Napi::Env env, ParsedJson::iterator & pj);
  Napi::Object ParseWrapped(const Napi::CallbackInfo& info);

  Napi::Object Init(Napi::Env env, Napi::Object exports);

}