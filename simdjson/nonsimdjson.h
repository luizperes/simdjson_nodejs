#if !defined __AVX2__ || !defined __SSE42__
#include <napi.h>

namespace simdjsonnode {
  Napi::Boolean HasAVX2Wrapped(const Napi::CallbackInfo& info);
  Napi::Object Init(Napi::Env env, Napi::Object exports);
}

#endif