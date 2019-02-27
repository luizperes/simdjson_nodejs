#include "bindings.h"

bool simdjson::isValid(std::string_view p) {
  ParsedJson pj = build_parsed_json(p);
  return pj.isValid();
}

Napi::Boolean simdjson::IsValidWrapped(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  std::string jstr = info[0].As<Napi::String>();
  Napi::Boolean returnValue = Napi::Boolean::New(env, simdjson::isValid(jstr));
  return returnValue;
}

Napi::Object simdjson::parse(Napi::Env env, std::string_view p) {
  ParsedJson pj = build_parsed_json(p);
  if (!pj.isValid()) {
    Napi::Error::New(env, "Invalid JSON Exception").ThrowAsJavaScriptException();
  }
  ParsedJson::iterator pjh(pj);
  return simdjson::makeJSONObject(env, pjh).As<Napi::Object>();
}

Napi::Value simdjson::makeJSONObject(Napi::Env env, ParsedJson::iterator & pjh) {
  Napi::Value v;
  if (pjh.is_object()) {
    Napi::Object obj = Napi::Object::New(env); // {
    if (pjh.down()) {
      // must be a string
      Napi::String key = Napi::String::New(env, pjh.get_string());
      // :
      pjh.next();
      Napi::String value = Napi::String::New(env, pjh.get_string());
      obj.Set(key, value);
    }
    v = obj;
  }
  return v;
  //     Napi:Value value = simdjson::makeJSONObject(env, pjh); // let us recurse

  //     while (pjh.next()) {
  //       std::cout << ",";
  //       pjh.print(std::cout);
  //       std::cout << ":";
  //       pjh.next();
  //       compute_dump(pjh); // let us recurse
  //     }
  //     pjh.up();
  //   }
  //   v = obj; // }
  // } else if (pjh.is_array()) {
  //   std::cout << "[";
  //   if (pjh.down()) {
  //     compute_dump(pjh); // let us recurse
  //     while (pjh.next()) {
  //       std::cout << ",";
  //       compute_dump(pjh); // let us recurse
  //     }
  //     pjh.up();
  //   }
  //   std::cout << "]";
  // } else {
  //   pjh.print(std::cout); // just print the lone value
  // }
  // 
  // return v;
}

Napi::Object simdjson::ParseWrapped(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  std::string jstr = info[0].As<Napi::String>();
  Napi::Object json = simdjson::parse(env, jstr);
  return json;
}

Napi::Object simdjson::Init(Napi::Env env, Napi::Object exports) {
  exports.Set("isValid", Napi::Function::New(env, simdjson::IsValidWrapped));
  exports.Set("parse", Napi::Function::New(env, simdjson::ParseWrapped));
  return exports;
}