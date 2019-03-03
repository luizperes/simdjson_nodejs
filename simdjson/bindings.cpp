#include <nan.h>
#include "src/simdjson.h"

#ifdef __AVX2__
NAN_METHOD(hasAVX2) {
  auto r = Nan::True();
  info.GetReturnValue().Set(r);
}

NAN_METHOD(isValid) {
  std::string p = *Nan::Utf8String(info[0]);
  ParsedJson pj = build_parsed_json(p);
  auto r = Nan::New(pj.isValid());
  info.GetReturnValue().Set(r);
}
#endif

static v8::Local<v8::Value> makeJSONObject(ParsedJson::iterator & pjh) {
  v8::Local<v8::Value> v;
  if (pjh.is_object()) {
    v8::Local<v8::Object> obj = Nan::New<v8::Object>(); // {
    if (pjh.down()) {
      // must be a string
      v8::Local<v8::String> key = Nan::New(pjh.get_string()).ToLocalChecked();
      // :
      pjh.next();
      v8::Local<v8::Value> value = makeJSONObject(pjh); // let us recurse
      Nan::Set(obj, key, value);
      while (pjh.next()) { // ,
        key = Nan::New(pjh.get_string()).ToLocalChecked();
        pjh.next();
        // :
        value = makeJSONObject(pjh); // let us recurse
        Nan::Set(obj, key, value);
      }
      pjh.up();
    }
    v = obj; // }
  } else if (pjh.is_array()) {
    std::vector<v8::Local<v8::Value>> arr;
    if (pjh.down()) {
      // [
      v8::Local<v8::Value> value = makeJSONObject(pjh); // let us recurse
      arr.push_back(value);
      while (pjh.next()) { // ,
        value = makeJSONObject(pjh); // let us recurse
        arr.push_back(value);
      }
      pjh.up();
    }
    // ]
    v8::Local<v8::Array> array = Nan::New<v8::Array>(arr.size());
    for (std::size_t i{ 0 }; i < arr.size(); i++) array->Set(i, arr[i]);
    v = array;
  } else if (pjh.is_string()) {
    v = Nan::New(pjh.get_string()).ToLocalChecked();
  } else if (pjh.is_double()) {
    v = Nan::New<v8::Number>(pjh.get_double());
  } else if (pjh.is_integer()) {
    v = Nan::New<v8::Number>(pjh.get_integer());
  } else {
    switch (pjh.get_type()) {
      case 't':  {
        v = Nan::True();
        break;
      }
      case 'f': {
        v = Nan::False();
        break;
      }
      case 'n': {
        v = Nan::Null();
        break;
      }
      default : break;
    }
  }
  return v;
}

NAN_METHOD(parse) {
  std::string p = *Nan::Utf8String(info[0]);
  ParsedJson pj = build_parsed_json(p);
  if (!pj.isValid()) {
    Nan::ThrowError("Invalid JSON Exception");
  }
  ParsedJson::iterator pjh(pj);
  v8::Local<v8::Value> obj = makeJSONObject(pjh);
  info.GetReturnValue().Set(obj);
}

NAN_MODULE_INIT(simdjsonInit) {
#ifdef __AVX2__
  NAN_EXPORT(target, hasAVX2);
  NAN_EXPORT(target, isValid);
#endif
  NAN_EXPORT(target, parse);
}

NODE_MODULE(simdjson, simdjsonInit);