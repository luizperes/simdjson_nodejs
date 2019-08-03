#if defined __AVX2__ || defined __SSE42__
#include "bindings.h"

Napi::Boolean simdjsonnode::HasAVX2Wrapped(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  return Napi::Boolean::New(env, true);
}

bool simdjsonnode::isValid(std::string p) {
  ParsedJson pj = build_parsed_json(p);
  return pj.is_valid();
}

Napi::Boolean simdjsonnode::IsValidWrapped(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  std::string jstr = info[0].As<Napi::String>();
  Napi::Boolean returnValue = Napi::Boolean::New(env, simdjsonnode::isValid(jstr));
  return returnValue;
}

Napi::Object simdjsonnode::parse(Napi::Env env, std::string p) {
  ParsedJson pj = build_parsed_json(p);
  if (!pj.is_valid()) {
    Napi::Error::New(env, "Invalid JSON Exception").ThrowAsJavaScriptException();
  }
  ParsedJson::Iterator pjh(pj);
  return simdjsonnode::makeJSONObject(env, pjh).As<Napi::Object>();
}

Napi::Value simdjsonnode::makeJSONObject(Napi::Env env, ParsedJson::Iterator & pjh) {
  Napi::Value v;
  if (pjh.is_object()) {
    Napi::Object obj = Napi::Object::New(env); // {
    if (pjh.down()) {
      // must be a string
      Napi::String key = Napi::String::New(env, pjh.get_string());
      // :
      pjh.next();
      Napi::Value value = simdjsonnode::makeJSONObject(env, pjh); // let us recurse
      obj.Set(key, value);
      while (pjh.next()) { // ,
        key = Napi::String::New(env, pjh.get_string());
        pjh.next();
        // :
        value = simdjsonnode::makeJSONObject(env, pjh); // let us recurse
        obj.Set(key, value);
      }
      pjh.up();
    }
    v = obj; // }
  } else if (pjh.is_array()) {
    std::vector<Napi::Value> arr;
    if (pjh.down()) {
      // [
      Napi::Value value = simdjsonnode::makeJSONObject(env, pjh); // let us recurse
      arr.push_back(value);
      while (pjh.next()) { // ,
        value = simdjsonnode::makeJSONObject(env, pjh); // let us recurse
        arr.push_back(value);
      }
      pjh.up();
    }
    // ]
    Napi::Array array = Napi::Array::New(env, arr.size());
    for (std::size_t i{ 0 }; i < arr.size(); i++) array.Set(i, arr[i]);
    v = array;
  } else if (pjh.is_string()) {
    v = Napi::String::New(env, pjh.get_string());
  } else if (pjh.is_double()) {
    v = Napi::Number::New(env, pjh.get_double());
  } else if (pjh.is_integer()) {
    v = Napi::Number::New(env, pjh.get_integer());
  } else {
    switch (pjh.get_type()) {
      case 't':  {
        v = Napi::Boolean::New(env, true);
        break;
      }
      case 'f': {
        v = Napi::Boolean::New(env, false);
        break;
      }
      case 'n': {
        v = env.Null();
        break;
      }
      default : break;
    }
  }
  
  return v;
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

Napi::Value simdjsonnode::findKeyPath(Napi::Env env, std::vector<std::string> subpaths, ParsedJson::Iterator & pjh) {
  if (subpaths.empty()) return simdjsonnode::makeJSONObject(env, pjh).As<Napi::Object>();
  std::string subpath = subpaths.front();
  subpaths.erase(subpaths.begin());
  bool isArray = isNumber(subpath);
  bool found = false;
  if (!(pjh.is_array() && isArray) && !pjh.is_object()) {
    std::string error = "Invalid keypath " + subpath;
    Napi::Error::New(env, error).ThrowAsJavaScriptException();
  }
  if (pjh.is_object()) {
    if (pjh.down()) {
      do {
        if (subpath.compare(pjh.get_string()) == 0) {
          found = true;
          pjh.next();
          break;
        }
        pjh.next(); // need to do twice for the key-path
      } while (pjh.next());
    }
  } else if (pjh.is_array() && isArray) {
    if (pjh.down()) {
      int n = std::stoi(subpath);
      do {
        if (n == 0) {
          found = true;
          break;
        }
        n--;
      } while (pjh.next());
    }
  }
  if (!found) {
    std::string error = "Could not find subpath " + subpath;
    Napi::Error::New(env, error).ThrowAsJavaScriptException();
  }
  return findKeyPath(env, subpaths, pjh);
}

Napi::Value simdjsonnode::ValueForKeyPathWrapped(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  std::string path = info[0].As<Napi::String>();
  Napi::Object _this = info.This().As<Napi::Object>();
  Napi::External<ParsedJson> buffer = _this.Get("buffer").As<Napi::External<ParsedJson>>();
  ParsedJson * pj = buffer.Data();
  ParsedJson::Iterator pjh(*pj);
  return simdjsonnode::findKeyPath(env, parseKeyPath(path), pjh);
}

Napi::Object simdjsonnode::ParseWrapped(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  std::string jstr = info[0].As<Napi::String>();
  Napi::Object json = simdjsonnode::parse(env, jstr);
  return json;
}

Napi::Object simdjsonnode::LazyParseWrapped(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  std::string jstr = info[0].As<Napi::String>();
  ParsedJson pj = build_parsed_json(jstr);
  if (!pj.is_valid()) {
    Napi::Error::New(env, "Invalid JSON Exception").ThrowAsJavaScriptException();
  }
  Napi::Object json = Napi::Object::New(env);
  Napi::String key = Napi::String::New(env, "buffer");
  ParsedJson *pjh = new ParsedJson(std::move(pj));
  Napi::External<ParsedJson> buffer = Napi::External<ParsedJson>::New(env, pjh,
    [](Napi::Env /*env*/, ParsedJson * data) {
      delete data;
    });
  json.Set(key, buffer);
  json.Set("valueForKeyPath", Napi::Function::New(env, simdjsonnode::ValueForKeyPathWrapped));
  return json;  
}

Napi::Object simdjsonnode::Init(Napi::Env env, Napi::Object exports) {
  exports.Set("hasAVX2", Napi::Function::New(env, simdjsonnode::HasAVX2Wrapped));
  exports.Set("isValid", Napi::Function::New(env, simdjsonnode::IsValidWrapped));
  exports.Set("parse", Napi::Function::New(env, simdjsonnode::ParseWrapped));
  exports.Set("lazyParse", Napi::Function::New(env, simdjsonnode::LazyParseWrapped));
  return exports;
}

#endif
