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
  ParsedJson::iterator pjh(pj);
  return simdjson::makeJSONObject(env, pjh);
}

Napi::Object simdjson::makeJSONObject(Napi::Env env, ParsedJson::iterator & pj) {
  return Napi::Object::New(env);
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