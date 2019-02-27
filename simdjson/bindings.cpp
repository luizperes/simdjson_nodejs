#include "bindings.h"
#include "src/simdjson.h"

bool simdjson::isValid(std::string_view p) {
  ParsedJson pj = build_parsed_json(p);
  return pj.isValid();
}

Napi::Boolean simdjson::IsValidWrapped(const Napi::CallbackInfo& info) 
{
  Napi::Env env = info.Env();
  std::string jstr = info[0].As<Napi::String>();
  Napi::Boolean returnValue = Napi::Boolean::New(env, simdjson::isValid(jstr));
  return returnValue;
}

Napi::Object simdjson::Init(Napi::Env env, Napi::Object exports) 
{
  exports.Set("isValid", Napi::Function::New(env, simdjson::IsValidWrapped));
  return exports;
}