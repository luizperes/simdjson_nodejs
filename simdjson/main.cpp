#include <napi.h>

#ifdef __AVX2__
#include "bindings.h"
namespace simdjson {
  Napi::Boolean hasAVX2(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    return Napi::Boolean::New(env, true);
  }
}
#else
namespace simdjson {
  Napi::Boolean hasAVX2(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    return Napi::Boolean::New(env, false);
  }
}
#endif

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  exports.Set("hasAVX2", Napi::Function::New(env, simdjson::hasAVX2));
#ifdef __AVX2__
  return simdjson::Init(env, exports);
#else
  return exports;
#endif
}

NODE_API_MODULE(simdjson, InitAll)