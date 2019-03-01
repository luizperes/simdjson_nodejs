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
suite.add('apache_builds.json#simdjson', function() {
    simdjson.isValid(apache_builds);
  })
  .add('apache_builds.json#JSON', function() {
    json.isValid(apache_builds);
  })
  .add('canada.json#simdjson', function() {
    simdjson.isValid(canada);
  })
  .add('canada.json#JSON', function() {
    json.isValid(canada);
  })
  .add('citm_catalog.json#simdjson', function() {
    simdjson.isValid(citm_catalog);
  })
  .add('citm_catalog.json#JSON', function() {
    json.isValid(citm_catalog);
  })
  .add('github_events.json#simdjson', function() {
    simdjson.isValid(github_events);
  })
  .add('github_events.json#JSON', function() {
    json.isValid(github_events);
  })
  .add('gsoc-2018.json#simdjson', function() {
    simdjson.isValid(gsoc_2018);
  })
  .add('gsoc-2018.json#JSON', function() {
    json.isValid(gsoc_2018);
  })
  .add('instruments.json#simdjson', function() {
    simdjson.isValid(instruments);
  })
  .add('instruments.json#JSON', function() {
    json.isValid(instruments);
  })
  .add('marine-ik.json#simdjson', function() {
    simdjson.isValid(marine_ik);
  })
  .add('marine-ik.json#JSON', function() {
    json.isValid(marine_ik);
  })
  .add('mesh.json#simdjson', function() {
    simdjson.isValid(mesh);
  })
  .add('mesh.json#JSON', function() {
    json.isValid(mesh);
  })
  .add('mesh.pretty.json#simdjson', function() {
    simdjson.isValid(mesh_pretty);
  })
  .add('mesh.pretty.json#JSON', function() {
    json.isValid(mesh_pretty);
  })
  .add('numbers.json#simdjson', function() {
    simdjson.isValid(numbers);
  })
  .add('numbers.json#JSON', function() {
    json.isValid(numbers);
  })
  .add('random.json#simdjson', function() {
    simdjson.isValid(random);
  })
  .add('random.json#JSON', function() {
    json.isValid(random);
  })
  .add('twitter.json#simdjson', function() {
    simdjson.isValid(twitter);
  })
  .add('twitter.json#JSON', function() {
    json.isValid(twitter);
  })
  .add('twitterescaped.json#simdjson', function() {
    simdjson.isValid(twitterescaped);
  })
  .add('twitterescaped.json#JSON', function() {
    json.isValid(twitterescaped);
  })
  .add('update-center.json#simdjson', function() {
    simdjson.isValid(update_center);
  })
  .add('update-center.json#JSON', function() {
    json.isValid(update_center);
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

