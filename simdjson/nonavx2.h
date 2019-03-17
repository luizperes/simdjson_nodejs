#ifndef __AVX2__
#include <napi.h>

namespace simdjsonnode {
  Napi::Boolean hasAVX2Wrapped(const Napi::CallbackInfo& info);
  Napi::Object Init(Napi::Env env, Napi::Object exports);
}

#endif