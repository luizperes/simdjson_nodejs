# simdjson_nodejs
> Node.js bindings for [simdjson](https://github.com/lemire/simdjson), a gigabytes-per-second JSON parser, possibly the fastest JSON parser at the moment. *simdjson* as well as *simdjson_nodejs* work on popular platforms such as OS X, Linux, and Windows.

## Installation
The installation can be done in one step with `npm`:

`npm install simdjson`

## Usage

##### API Documentation
Please refer to the [API Documentation](https://github.com/luizperes/simdjson_nodejs/blob/master/Documentation.md) to have a better understanding of NodeJS bindings for `simdjson`.

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

| filename | filesize (MB) | JSON.parse (ms) | simdjson.parse (ms) | X faster |
| :------- | ------------: | --------------: | ------------------: | -------: |
| apache_builds.json | 0.13 | 0.305 | 0.146 | 2.09 |
| canada.json | 2.25 | 13.914 | 5.475 | 2.54 |
| citm_catalog.json | 1.73 | 4.820 | 6.470 | 0.74 |
| github_events.json | 0.07 | 8.310 | 0.085 | 97.91 |
| gsoc_2018.json | 3.33 | 6.029 | 3.255 | 1.85 |
| instruments.json | 0.22 | 0.464 | 0.271 | 1.71 |
| marine_ik.json | 2.98 | 19.533 | 7.133 | 2.74 |
| mesh_pretty.json | 1.58 | 3.987 | 1.985 | 2.01 |
| mesh.json | 0.72 | 2.869 | 1.363 | 2.10 |
| numbers.json | 0.15 | 0.729 | 0.244 | 2.99 |
| random.json | 0.51 | 1.859 | 1.983 | 0.94 |
| sf_citylots.json | 189.78 | 1880.563 | 569.580 | 3.30 |
| twitter.json | 0.63 | 1.633 | 2.093 | 0.78 |
| twitterescaped.json | 0.56 | 2.051 | 0.831 | 2.47 |
| update_center.json | 0.53 | 3.410 | 2.132 | 1.60 |

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

