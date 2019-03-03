#include <nan.h>

#ifdef __AVX2__
#include "bindings.h"
namespace simdjson {
  Napi::Boolean hasAVX2(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    return Napi::Boolean::New(env, true);
  }
}
#else
NAN_METHOD(hasAVX2) {
    auto r = Nan::New(false);
    info.GetReturnValue().Set(r);
}
NAN_MODULE_INIT(simdjsonInit) {
    NAN_EXPORT(target, hasAVX2);
}
NODE_MODULE(simdjson, simdjsonInit);
#endif