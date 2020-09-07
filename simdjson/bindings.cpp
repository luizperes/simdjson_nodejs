#include "bindings.h"

bool simdjsonnode::isValid(std::string json) {
  dom::parser parser;
  return !parser.parse(json).error();
}

Napi::Boolean simdjsonnode::IsValidWrapped(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  std::string jstr = info[0].As<Napi::String>();
  Napi::Boolean returnValue = Napi::Boolean::New(env, simdjsonnode::isValid(jstr));
  return returnValue;
}

Napi::Value simdjsonnode::makeJSONObject(Napi::Env env, dom::element element) {
  Napi::Value v;
  switch (element.type()) {
    case dom::element_type::ARRAY: {
      Napi::Array arr = Napi::Array::New(env);
      std::size_t i = 0;
      for (dom::element child : dom::array(element)) {
        arr.Set(i, makeJSONObject(env, child));
        i++;
      }
      return arr;
    }
    case dom::element_type::OBJECT: {
      Napi::Object obj = Napi::Object::New(env); // {
      for (auto field : dom::object(element)) {
        // TODO not 8-bit clean, but likely faster than making a new JS string ... figure out how to
        // do this without allocating a whole new std::string
        obj.Set(field.key.data(), makeJSONObject(env, field.value));
      }
      return obj;
    }
    case dom::element_type::STRING: {
      std::string_view str = element;
      return Napi::String::New(env, str.data(), str.length());
    }
    case dom::element_type::INT64:
      return Napi::Value::From<int64_t>(env, element);
    case dom::element_type::UINT64:
      return Napi::Value::From<uint64_t>(env, element);
    case dom::element_type::DOUBLE:
      return Napi::Value::From<double>(env, element);
    case dom::element_type::BOOL:
      return Napi::Value::From<bool>(env, element);
    case dom::element_type::NULL_VALUE:
      return env.Null();
  }
  Napi::Error::New(env, "Internal error: Unexpected JSON type from simdjson").ThrowAsJavaScriptException();
  return env.Null();
}

static std::vector<std::string> parseKeyPath(std::string str) {
    char * cstr = const_cast<char *>(str.c_str());
    char * current;
    std::string delimiters = ".[]";
    std::vector<std::string> arr;
    current = strtok(cstr, delimiters.c_str());
    while(current != NULL) {
        arr.push_back(current);
        current=strtok(NULL, delimiters.c_str());
    }
    return arr;
}

static bool isNumber(std::string s) {
  for(std::string::size_type i = 0; i < s.size(); ++i) {
    if (!isdigit(s[i])) return false;
  }
  return true;
}

Napi::Value simdjsonnode::findKeyPath(Napi::Env env, std::vector<std::string> subpaths, dom::element element) {
  if (subpaths.empty()) return makeJSONObject(env, element).As<Napi::Object>();
  std::string subpath = subpaths.front();
  subpaths.erase(subpaths.begin());
  switch (element.type()) {
    case dom::element_type::ARRAY: {
      if (!isNumber(subpath)) {
        std::string error = "Invalid keypath " + subpath + ": must be a number when accessing an array";
        Napi::Error::New(env, error).ThrowAsJavaScriptException();
      }
      return findKeyPath(env, subpaths, element.at(std::stoi(subpath)));
    }
    case dom::element_type::OBJECT: {
      return findKeyPath(env, subpaths, element.at_key(subpath));
    }
    default: {
      std::string error = "Invalid keypath " + subpath + ": keys only work on arrays and objects";
      Napi::Error::New(env, error).ThrowAsJavaScriptException();
      return env.Null();
    }
  }
}

Napi::Value simdjsonnode::ValueForKeyPathWrapped(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  std::string path = info[0].As<Napi::String>();
  Napi::Object _this = info.This().As<Napi::Object>();
  Napi::External<dom::document> buffer = _this.Get("buffer").As<Napi::External<dom::document>>();
  dom::document * doc = buffer.Data();
  try {
    return simdjsonnode::findKeyPath(env, parseKeyPath(path), doc->root());
  } catch (simdjson_error &error) {
    Napi::Error::New(env, error_message(error.error())).ThrowAsJavaScriptException();
    return env.Null();
  }
}

Napi::Value simdjsonnode::ParseWrapped(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  std::string json = info[0].As<Napi::String>();
  try {

    dom::parser parser;
    return makeJSONObject(env, parser.parse(json));

  } catch (simdjson_error &error) {
    Napi::Error::New(env, error_message(error.error())).ThrowAsJavaScriptException();
    return env.Null();
  }
}

Napi::Object simdjsonnode::LazyParseWrapped(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  std::string json = info[0].As<Napi::String>();
  dom::parser parser;
  error_code error = parser.parse(json).error();
  if (error) {
    Napi::Error::New(env, error_message(error)).ThrowAsJavaScriptException();
    return Napi::Object::New(env);
  }
  Napi::External<dom::document> buffer = Napi::External<dom::document>::New(env, new dom::document(std::move(parser.doc)),
    [](Napi::Env /*env*/, dom::document * doc) {
      delete doc;
    });
  Napi::Object result = Napi::Object::New(env);
  result.Set("buffer", buffer);
  result.Set("valueForKeyPath", Napi::Function::New(env, simdjsonnode::ValueForKeyPathWrapped));
  return result;  
}

Napi::Object simdjsonnode::Init(Napi::Env env, Napi::Object exports) {
  exports.Set("isValid", Napi::Function::New(env, simdjsonnode::IsValidWrapped));
  exports.Set("parse", Napi::Function::New(env, simdjsonnode::ParseWrapped));
  exports.Set("lazyParse", Napi::Function::New(env, simdjsonnode::LazyParseWrapped));
  return exports;
}
