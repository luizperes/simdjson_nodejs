# simdjson_nodejs
[![tests](https://github.com/luizperes/simdjson_nodejs/workflows/tests/badge.svg?branch=master)](https://github.com/luizperes/simdjson_nodejs/actions)
[![npm](https://img.shields.io/npm/v/simdjson.svg)](https://www.npmjs.com/package/simdjson)
[![npm](https://img.shields.io/npm/dm/simdjson.svg)](https://www.npmjs.com/package/simdjson)
[![npm](https://img.shields.io/npm/l/simdjson.svg)](https://github.com/luizperes/simdjson_nodejs/blob/master/LICENCE)

> Node.js bindings for [simdjson](https://github.com/lemire/simdjson), a gigabytes-per-second JSON parser, possibly the fastest JSON parser at the moment. *simdjson* as well as *simdjson_nodejs* work on popular platforms such as OS X, Linux, and Windows.

## Installation
The installation can be done in one step with `npm`:

`npm install simdjson`

## Usage

##### API Documentation
See [index.d.ts](index.d.ts) for available `simdjson` binding functions and their input/output types.

##### Check if a JSON string is valid:
```Javascript
const simdjson = require('simdjson');

const jsonString = "{ \"answer\": 42 }";
const valid = simdjson.isValid(jsonString); // true
```

##### Parsing a JSON string (lazily)
_Obs.: Please see that the overhead of converting a C++ object to a JS object might make the parsing time in the NodeJS slower for the simdjson. Therefore, parsing it lazily is preferrable. For more information check issue #5._
```Javascript
const simdjson = require('simdjson');

const jsonString = "{   \
  \"foo\": {            \
    \"bar\": [ 0, 42 ]  \
  }                     \
}";
const JSONbuffer = simdjson.lazyParse(jsonString); // external (C++) parsed JSON object
console.log(JSONbuffer.valueForKeyPath("foo.bar[1]")); // 42
```

##### Parsing a JSON string
_Obs.: Parsing a JSON lazily is preferrable._
```Javascript
const simdjson = require('simdjson');

const jsonString = "{   \
  \"foo\": {            \
    \"bar\": [ 0, 42 ]  \
  }                     \
}";
const parsedJSON = simdjson.parse(jsonString); // parsed JSON object
```

## Benchmarks

Requirements: git, npm, node, a linux-like system, a recent compiler (GCC,clang)

To benchmark directly from the project:

```
git clone https://github.com/luizperes/simdjson_nodejs.git
cd simdjson_nodejs
npm install
npm run benchmark
```

| filename | filesize (MB) | JSON.parse(ms) | simdjson.lazyParse (ms) | JSON.parse (GB/s) | simdjson.lazyParse (GB/s) | X faster |
| :-- | --: | --: | --: | --: | --: | --: |
| apache_builds.json | 0.13 | 0.303 | 0.158 | 0.42 | 0.80 | 1.91 |
| canada.json | 2.25 | 14.332 | 7.584 | 0.16 | 0.30 | 1.89 |
| citm_catalog.json | 1.73 | 5.387 | 5.768 | 0.32 | 0.30 | 0.93 |
| github_events.json | 0.07 | 0.192 | 0.091 | 0.34 | 0.71 | 2.10 |
| gsoc_2018.json | 3.33 | 5.420 | 3.839 | 0.61 | 0.87 | 1.41 |
| instruments.json | 0.22 | 0.673 | 0.619 | 0.33 | 0.36 | 1.09 |
| marine_ik.json | 2.98 | 13.169 | 6.397 | 0.23 | 0.47 | 2.06 |
| mesh_pretty.json | 1.58 | 5.704 | 3.043 | 0.28 | 0.52 | 1.87 |
| mesh.json | 0.72 | 2.856 | 1.404 | 0.25 | 0.52 | 2.03 |
| numbers.json | 0.15 | 0.643 | 0.280 | 0.23 | 0.54 | 2.30 |
| random.json | 0.51 | 1.914 | 2.447 | 0.27 | 0.21 | 0.78 |
| sf_citylots.json | 189.78 | 1492.166 | 709.692 | 0.13 | 0.27 | 2.10 |
| twitter.json | 0.63 | 1.621 | 2.112 | 0.39 | 0.30 | 0.77 |
| twitterescaped.json | 0.56 | 1.924 | 0.959 | 0.29 | 0.59 | 2.01 |
| update_center.json | 0.53 | 2.803 | 2.715 | 0.19 | 0.20 | 1.03 |

Results from a 2018 MacBook Pro with 2.3GHz Intel Core i9.

### Ops/sec

```text
apache_builds.json#simdjson x 6,844 ops/sec ±1.61% (90 runs sampled) => 0.146ms
apache_builds.json#JSON x 3,274 ops/sec ±1.83% (90 runs sampled) => 0.305ms
canada.json#simdjson x 183 ops/sec ±7.69% (72 runs sampled) => 5.475ms
canada.json#JSON x 71.87 ops/sec ±0.92% (74 runs sampled) => 13.914ms
citm_catalog.json#simdjson x 155 ops/sec ±2.95% (72 runs sampled) => 6.470ms
citm_catalog.json#JSON x 207 ops/sec ±59.63% (90 runs sampled) => 4.820ms
github_events.json#simdjson x 11,783 ops/sec ±1.80% (90 runs sampled) => 0.085ms
github_events.json#JSON x 120 ops/sec ±192.65% (92 runs sampled) => 8.310ms
gsoc_2018.json#simdjson x 307 ops/sec ±1.81% (79 runs sampled) => 3.255ms
gsoc_2018.json#JSON x 166 ops/sec ±47.75% (81 runs sampled) => 6.029ms
instruments.json#simdjson x 3,691 ops/sec ±2.06% (87 runs sampled) => 0.271ms
instruments.json#JSON x 2,155 ops/sec ±0.83% (93 runs sampled) => 0.464ms
marine_ik.json#simdjson x 140 ops/sec ±3.08% (73 runs sampled) => 7.133ms
marine_ik.json#JSON x 51.20 ops/sec ±60.81% (76 runs sampled) => 19.533ms
mesh_pretty.json#simdjson x 504 ops/sec ±1.93% (87 runs sampled) => 1.985ms
mesh_pretty.json#JSON x 251 ops/sec ±1.02% (85 runs sampled) => 3.987ms
mesh.json#simdjson x 733 ops/sec ±0.99% (92 runs sampled) => 1.363ms
mesh.json#JSON x 349 ops/sec ±0.64% (89 runs sampled) => 2.869ms
numbers.json#simdjson x 4,099 ops/sec ±1.10% (94 runs sampled) => 0.244ms
numbers.json#JSON x 1,372 ops/sec ±38.74% (95 runs sampled) => 0.729ms
random.json#simdjson x 504 ops/sec ±0.97% (91 runs sampled) => 1.983ms
random.json#JSON x 538 ops/sec ±0.93% (91 runs sampled) => 1.859ms
sf_citylots.json#simdjson x 1.76 ops/sec ±4.02% (9 runs sampled) => 569.580ms
sf_citylots.json#JSON x 0.53 ops/sec ±20.38% (6 runs sampled) => 1880.563ms
twitter.json#simdjson x 478 ops/sec ±0.68% (89 runs sampled) => 2.093ms
twitter.json#JSON x 612 ops/sec ±0.90% (91 runs sampled) => 1.633ms
twitterescaped.json#simdjson x 1,203 ops/sec ±1.80% (88 runs sampled) => 0.831ms
twitterescaped.json#JSON x 488 ops/sec ±2.33% (82 runs sampled) => 2.051ms
update_center.json#simdjson x 469 ops/sec ±3.43% (85 runs sampled) => 2.132ms
update_center.json#JSON x 293 ops/sec ±12.87% (57 runs sampled) => 3.410ms
```

###### Observation:
Please refer to the the original repository benchmarks for more information about the performance of *simdjson* [https://github.com/lemire/simdjson](https://github.com/lemire/simdjson).

