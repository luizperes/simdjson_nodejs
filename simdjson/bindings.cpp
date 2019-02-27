#include "bindings.h"

std::string simdjson::hello(){
  return "Hello World";
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