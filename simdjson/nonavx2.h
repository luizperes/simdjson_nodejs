#ifndef __AVX2__
#include <napi.h>

namespace simdjsonnode {
  Napi::Boolean HasAVX2Wrapped(const Napi::CallbackInfo& info);
  Napi::Object Init(Napi::Env env, Napi::Object exports);
}

#endif