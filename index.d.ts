// NOTE: please keep this in sync with exports defined in simdjsonnode::Init in simdjson/bindings.cpp file

declare module "simdjson" {
  /**
   * Checks whether or not a json string is valid.
   * It is a very fast operation, since it validates the json string in parallel using simd cpu instructions.
   * NOTE: isValid only validates the documents, but doesn't parse the document into strings, numbers, e.t.c
   */
  export function isValid(jsonStr: string): boolean;

  /**
   * Equivalent to native `JSON.parse` with a similar signature.
   * NOTE: This method is **NOT** preferable because there exists a lot of overhead in the conversion of C++ data into JS objects
   * (see `node-addon-api` package).
   *
   * If you require the full jsonStr -> js objects, use JSON.parse instead.
   */
  export function parse(jsonStr: string): any;

  export interface JSONTape {
    /**
     * Similar to [`NSObject valueForKeyPath`](https://docs.microsoft.com/en-us/dotnet/api/foundation.nsobject.valueforkeypath?view=xamarin-ios-sdk-12)
     * keyPath is a x.y or x[y] separated string in format e.g address.city.unit.0 or jobs[0].result.output
     * e.g address.city.house.0
     */
    valueForKeyPath(keyPath: string): any;
  }

  /**
   * Parses a json string and keeps an internal pointer to parsed json tape.
   * This method is preferable because it allows the developer to use the full power of `simdjson` (with the same > 2.5GB/s parsing speed as the upstream).
   * Since constructing the full Javascript object is perf intensive, we instead lazily parse a subset of the object based on a keyPath.
   * See [Issue #5](https://github.com/luizperes/simdjson_nodejs/issues/5) for a detailed explanation of the problem.
   */
  export function lazyParse(jsonString: string): JSONTape;
}
