#include <napi.h>
#if defined __AVX2__ || defined __SSE42__
#include "bindings.h"
#else
#include "nonsimdjson.h"
#endif

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  return simdjsonnode::Init(env, exports);
}

NODE_API_MODULE(simdjson, InitAll)