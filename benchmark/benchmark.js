const Benchmark = require('benchmark');
const suite = new Benchmark.Suite;
const fs = require('fs');
const json = require('./is_valid');
const simdjson = require('../index.js');

const apache_builds = fs.readFileSync('../jsonexamples/apache_builds.json', 'utf-8');
const canada = fs.readFileSync('../jsonexamples/canada.json', 'utf-8');
const citm_catalog = fs.readFileSync('../jsonexamples/citm_catalog.json', 'utf-8');
const github_events = fs.readFileSync('../jsonexamples/github_events.json', 'utf-8');
const gsoc_2018 = fs.readFileSync('../jsonexamples/gsoc-2018.json', 'utf-8');
const instruments = fs.readFileSync('../jsonexamples/instruments.json', 'utf-8');
const marine_ik = fs.readFileSync('../jsonexamples/marine_ik.json', 'utf-8');
const mesh = fs.readFileSync('../jsonexamples/mesh.json', 'utf-8');
const mesh_pretty = fs.readFileSync('../jsonexamples/mesh.pretty.json', 'utf-8');
const numbers = fs.readFileSync('../jsonexamples/numbers.json', 'utf-8');
const random = fs.readFileSync('../jsonexamples/random.json', 'utf-8');
const twitter = fs.readFileSync('../jsonexamples/twitter.json', 'utf-8');
const twitterescaped = fs.readFileSync('../jsonexamples/twitterescaped.json', 'utf-8');
const update_center = fs.readFileSync('../jsonexamples/update-center.json', 'utf-8');

// Generate very big JSON at runtime or else there would be a file > 300mb
const RANDOM_STRING = 'abcdefghijklmnopqrstuvwxCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-=_+[]{}\\|;:\'",<.>/?`~';
const stringLength = Math.pow(2, 10);
const bigString = new Array(stringLength).fill(RANDOM_STRING).join('');
const arrayLength = Math.pow(2, 7);
const bigArray = new Array(arrayLength).fill(bigString);
let index = 0;
const objectSize = Math.pow(2, 2);
const bigObject = new Array(objectSize).fill(undefined).reduce((accumulator) => {
  accumulator[index] = bigArray;
  index++;
  return accumulator;
}, {});
const big_nonsense = JSON.stringify(bigObject);

suite
  .add('apache_builds.json#simdjson', function() {
    simdjson.parse(apache_builds);
  })
  .add('apache_builds.json#JSON', function() {
    JSON.parse(apache_builds);
  })
  .add('canada.json#simdjson', function() {
    simdjson.parse(canada);
  })
  .add('canada.json#JSON', function() {
    JSON.parse(canada);
  })
  .add('citm_catalog.json#simdjson', function() {
    simdjson.parse(citm_catalog);
  })
  .add('citm_catalog.json#JSON', function() {
    JSON.parse(citm_catalog);
  })
  .add('github_events.json#simdjson', function() {
    simdjson.parse(github_events);
  })
  .add('github_events.json#JSON', function() {
    JSON.parse(github_events);
  })
  .add('gsoc-2018.json#simdjson', function() {
    simdjson.parse(gsoc_2018);
  })
  .add('gsoc-2018.json#JSON', function() {
    JSON.parse(gsoc_2018);
  })
  .add('instruments.json#simdjson', function() {
    simdjson.parse(instruments);
  })
  .add('instruments.json#JSON', function() {
    JSON.parse(instruments);
  })
  .add('marine-ik.json#simdjson', function() {
    simdjson.parse(marine_ik);
  })
  .add('marine-ik.json#JSON', function() {
    JSON.parse(marine_ik);
  })
  .add('mesh.json#simdjson', function() {
    simdjson.parse(mesh);
  })
  .add('mesh.json#JSON', function() {
    JSON.parse(mesh);
  })
  .add('mesh.pretty.json#simdjson', function() {
    simdjson.parse(mesh_pretty);
  })
  .add('mesh.pretty.json#JSON', function() {
    JSON.parse(mesh_pretty);
  })
  .add('numbers.json#simdjson', function() {
    simdjson.parse(numbers);
  })
  .add('numbers.json#JSON', function() {
    JSON.parse(numbers);
  })
  .add('random.json#simdjson', function() {
    simdjson.parse(random);
  })
  .add('random.json#JSON', function() {
    JSON.parse(random);
  })
  .add('twitter.json#simdjson', function() {
    simdjson.parse(twitter);
  })
  .add('twitter.json#JSON', function() {
    JSON.parse(twitter);
  })
  .add('twitterescaped.json#simdjson', function() {
    simdjson.parse(twitterescaped);
  })
  .add('twitterescaped.json#JSON', function() {
    JSON.parse(twitterescaped);
  })
  .add('update-center.json#simdjson', function() {
    simdjson.parse(update_center);
  })
  .add('update-center.json#JSON', function() {
    JSON.parse(update_center);
  })
  .add('big_nonsense.json#simdjson', function() {
    simdjson.parse(big_nonsense);
  })
  .add('big_nonsense.json#JSON', function() {
    JSON.parse(big_nonsense);
  })
  .on('cycle', function(event) {
    console.log(String(event.target) + " => " + String(event.target.times.period)) + " secs";
  })
  .on('complete', function() {
    console.log("|      filename     |   JSON file    |   simdjson file |");
    console.log("| :---------------: | :------------: | :-------------: |");
    const benches = this.filter(() => true);
    for (var i = 0; i < benches.length; i+=2) {
      var str = '| ';
      str +=  String(benches[i + 1].name.split('#')[0]) + '.json';
      str += ' | ';
      str +=  String(benches[i + 1].times.period);
      str += ' | ';
      str +=  String(benches[i].times.period);
      str += ' |';
      console.log(str);
    }
  })
  .run({ 'async': false });

