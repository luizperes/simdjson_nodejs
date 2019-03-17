#include <napi.h>
#ifdef __AVX2__
#include "bindings.h"
#else
#include "nonavx2.h"
#endif

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  return simdjsonnode::Init(env, exports);
}

NODE_API_MODULE(simdjson, InitAll)