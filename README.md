# simdjson_nodejs
> Node.js bindings for [simdjson](https://github.com/lemire/simdjson), a gigabytes-per-second JSON parser, possibly the fastest JSON parser at the moment. *simdjson* works on popular platforms such as OS X, Linux, and Windows and the Node.js bindings up-to-date have only been tested on OS X.

## Installation
The installation can be done in one step with `npm`:

`npm install simdjson`

## Usage

##### Check if a JSON string is valid:
```Javascript
const simdjson = require('simdjson');

const jsonString = ...
const valid = simdjson.isValid(jsonString); // true
```

##### Parsing a JSON string
```Javascript
const simdjson = require('simdjson');

const jsonString = ...
const parsedJSON = simdjson.parse(jsonString); // parsed JSON object
```

## Benchmarks

Requirements: git, npm, node, a linux-like system, a recent compiler (GCC,clang)

To benchmark directly from the project:

```
git clone https://github.com/luizperes/simdjson_nodejs.git
cd simdjson_nodejs
npm install
cd benchmark
node benchmark
```


|      filename     |   default JSON |    simdjson     |
| :---------------: | :------------: | :-------------: |
| apache_builds.json | 0.0007187123801716652 | 0.00013120465355748363 |
| canada.json | 0.023433125946428573 | 0.004240565511370573 |
| citm_catalog.json | 0.012581310435294117 | 0.00862821200096525 |
| github_events.json | 0.000606156420195201 | 0.0003024769703496055 |
| gsoc-2018.json | 0.017244597679166664 | 0.003557362459253248 |
| instruments.json | 0.0009677125544015644 | 0.0002326451132910277 |
| marine-ik.json | 0.023001695748538015 | 0.0062001457338820305 |
| mesh.json | 0.0051030897583148535 | 0.0014432593387370893 |
| mesh.pretty.json | 0.0070244677156250015 | 0.002700871435166786 |
| numbers.json | 0.001020789959175084 | 0.00026952393988960194 |
| random.json | 0.008408114811428573 | 0.003142749020011699 |
| twitter.json | 0.006392268774964838 | 0.002995028150702426 |
| twitterescaped.json | 0.002938425365325077 | 0.0008673295529352932 |
| update-center.json | 0.007703586972358122 | 0.002606976810584796 |

### Ops/sec

```Text
apache_builds.json#simdjson x 7,622 ops/sec ±0.58% (89 runs sampled) => 0.00013120465355748363
apache_builds.json#JSON x 1,391 ops/sec ±1.13% (90 runs sampled) => 0.0007187123801716652
canada.json#simdjson x 236 ops/sec ±0.55% (84 runs sampled) => 0.004240565511370573
canada.json#JSON x 42.67 ops/sec ±1.31% (56 runs sampled) => 0.023433125946428573
citm_catalog.json#simdjson x 116 ops/sec ±0.57% (74 runs sampled) => 0.00862821200096525
citm_catalog.json#JSON x 79.48 ops/sec ±1.87% (68 runs sampled) => 0.012581310435294117
github_events.json#simdjson x 3,306 ops/sec ±0.43% (95 runs sampled) => 0.0003024769703496055
github_events.json#JSON x 1,650 ops/sec ±1.23% (92 runs sampled) => 0.000606156420195201
gsoc-2018.json#simdjson x 281 ops/sec ±0.59% (88 runs sampled) => 0.003557362459253248
gsoc-2018.json#JSON x 57.99 ops/sec ±2.26% (60 runs sampled) => 0.017244597679166664
instruments.json#simdjson x 4,298 ops/sec ±0.56% (95 runs sampled) => 0.0002326451132910277
instruments.json#JSON x 1,033 ops/sec ±1.79% (88 runs sampled) => 0.0009677125544015644
marine-ik.json#simdjson x 161 ops/sec ±0.59% (81 runs sampled) => 0.0062001457338820305
marine-ik.json#JSON x 43.48 ops/sec ±1.29% (57 runs sampled) => 0.023001695748538015
mesh.json#simdjson x 693 ops/sec ±0.64% (91 runs sampled) => 0.0014432593387370893
mesh.json#JSON x 196 ops/sec ±1.21% (82 runs sampled) => 0.0051030897583148535
mesh.pretty.json#simdjson x 370 ops/sec ±0.81% (84 runs sampled) => 0.002700871435166786
mesh.pretty.json#JSON x 142 ops/sec ±1.33% (80 runs sampled) => 0.0070244677156250015
numbers.json#simdjson x 3,710 ops/sec ±0.52% (92 runs sampled) => 0.00026952393988960194
numbers.json#JSON x 980 ops/sec ±1.49% (88 runs sampled) => 0.001020789959175084
random.json#simdjson x 318 ops/sec ±0.50% (88 runs sampled) => 0.003142749020011699
random.json#JSON x 119 ops/sec ±2.29% (75 runs sampled) => 0.008408114811428573
twitter.json#simdjson x 334 ops/sec ±0.47% (87 runs sampled) => 0.002995028150702426
twitter.json#JSON x 156 ops/sec ±1.49% (79 runs sampled) => 0.006392268774964838
twitterescaped.json#simdjson x 1,153 ops/sec ±0.52% (93 runs sampled) => 0.0008673295529352932
twitterescaped.json#JSON x 340 ops/sec ±1.63% (85 runs sampled) => 0.002938425365325077
update-center.json#simdjson x 384 ops/sec ±0.57% (90 runs sampled) => 0.002606976810584796
update-center.json#JSON x 130 ops/sec ±2.30% (73 runs sampled) => 0.007703586972358122
```

You may run the benchmarks by running the commands:
  - `cd /path/to/simdjson_nodejs/benchmark`
  - `node benchmark.js`

###### Observation:
Please refer to the the original repository benchmarks for more information about the performance of *simdjson* [https://github.com/lemire/simdjson](https://github.com/lemire/simdjson).

### AVX2

*simdjson* will choose the default JS `JSON` library in case that your machine does not have AVX2 support. Therefore, it is required AVX2 support in order to use all of its powers. You may want to check whether your OS/processor supports it:

- OS X: `sysctl -a | grep machdep.cpu.leaf7_features`
- Linux: `grep avx2 /proc/cpuinfo`
