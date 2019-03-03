#include <nan.h>

NAN_METHOD(hasAVX2) {
    auto r = Nan::New(false);
    info.GetReturnValue().Set(r);
}

NAN_MODULE_INIT(simdjsonInit) {
    NAN_EXPORT(target, hasAVX2);
}

NODE_MODULE(simdjson, simdjsonInit);