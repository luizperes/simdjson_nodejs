# simdjson_nodejs
> Node.js bindings for [simdjson](https://github.com/lemire/simdjson), a gigabytes-per-second JSON parser, possibly the fastest JSON parser at the moment. *simdjson* works on popular platforms such as OS X, Linux, and Windows and the Node.js bindings up-to-date have only been tested on OS X.

## Benchmarks
Please refer to the the original repository benchmarks for more information about the performance of *simdjson* [https://github.com/lemire/simdjson](https://github.com/lemire/simdjson).

## Installation
The installation can be done in one step with `npm`:

`npm install simdjson`

### AVX2

*simdjson* requires AVX2 support to function. Check to see if your OS/processor supports it:

- OS X: `sysctl -a | grep machdep.cpu.leaf7_features`
- Linux: `grep avx2 /proc/cpuinfo`

## Usage

##### Check if a JSON string is valid:
```Javascript
const simdjson = require('simdjson');

const jsonString = ...
const valid = simdjson.isValid(jsonString) // true
```

##### Parsing a JSON string
```Javascript
const simdjson = require('simdjson');

const jsonString = ...
const parsedJSON = simdjson.parse(jsonString) // parsed JSON object
```

Example of parsed JSON:
```JSON
{
    "type": "search_results",
    "count": 2,
    "results": [
        {"username": "bob"},
        {"username": "tod"}
    ],
    "error": {
        "message": "All good captain"
    }
}
```
