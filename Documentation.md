### API Documentation
Below you will find the API documentation for the NodeJS bindings of `simdjson`. For more information on `Usage`, please refer to the [README.md](README.md) file.

#### isValid
- **doc**: Checks whether or not a json string is valid. It is a very very fast operation, since it is only a validation in parallel of a json string. It validates the documents, but doesn't necessarily parses it (such as numbers and etc).  
-  **type**: `(jsonString: string) => boolean`

#### parse
- **doc**: Constructs a JavaScript object described by the JSON string that is given as input. This does the same as the standard `JSON.parse` as well as have the same signature.
- **type**:  (jsonString: string) => JSONDataType
- **observation**: This method is **not** preferable because there exists a lot of overhead in the conversion of C++ data into JS data (package `node-addon-api`). For more details, check issue #5

#### lazyParse 
- **doc**: Parses a JSON string but does not construct a JavaScript object. Instead, it keeps the pointer to the external (C++) parsed JSON. This method is preferable because it allows the developer to use the full power of `simdjson` (with the same parsing speed as the upstream), while still avoiding the overhead of constructing a full JavaScript object and focusing on lazily constructing only important pieces of the parsed object. Issue #5 has a very detailed explanation of this problem.
- **type**: (jsonString: string) => LazyParsedJson
- **observation**: You can only access the parsed object (since it is a C++ external object) through the function `valueForKeyPath`, which is similar to the [`NSObject valueForKeyPath`](https://docs.microsoft.com/en-us/dotnet/api/foundation.nsobject.valueforkeypath?view=xamarin-ios-sdk-12)

where:

`type JSONDataType`: is any of `{ string, number, object, array, boolean, null }`

```TS
interface LazyParsedJSON {
    valueForKeyPath: (keyPath: string) => JSONDataType
}
```

