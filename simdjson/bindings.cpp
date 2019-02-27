#include "bindings.h"
#include "src/simdjson.h"

std::string simdjson::hello() {
  std::string_view p = get_corpus("/Users/luizperes/Projects/simdjson/jsonexamples/twitter.json");
  ParsedJson pj = build_parsed_json(p);
  if( ! pj.isValid() ) {
    return "not valid";
  } else {
    return "valid";
  }
}

Napi::String simdjson::HelloWrapped(const Napi::CallbackInfo& info) 
{
  Napi::Env env = info.Env();
  Napi::String returnValue = Napi::String::New(env, simdjson::hello());
  
  return returnValue;
}

Napi::Object simdjson::Init(Napi::Env env, Napi::Object exports) 
{
  exports.Set("hello", Napi::Function::New(env, simdjson::HelloWrapped));
  return exports;
}