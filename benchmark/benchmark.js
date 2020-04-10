const Benchmark = require(`benchmark`);
const fs = require(`fs`);
const zlib = require(`zlib`);
const simdjson = require(`../index.js`);

const examplePath = `${__dirname}/../jsonexamples`;
const jsonExamples = {
  apache_builds: fs.readFileSync(`${examplePath}/apache_builds.json`, `utf-8`),
  canada: fs.readFileSync(`${examplePath}/canada.json`, `utf-8`),
  citm_catalog: fs.readFileSync(`${examplePath}/citm_catalog.json`, `utf-8`),
  github_events: fs.readFileSync(`${examplePath}/github_events.json`, `utf-8`),
  gsoc_2018: fs.readFileSync(`${examplePath}/gsoc-2018.json`, `utf-8`),
  instruments: fs.readFileSync(`${examplePath}/instruments.json`, `utf-8`),
  marine_ik: fs.readFileSync(`${examplePath}/marine_ik.json`, `utf-8`),
  mesh_pretty: fs.readFileSync(`${examplePath}/mesh.pretty.json`, `utf-8`),
  mesh: fs.readFileSync(`${examplePath}/mesh.json`, `utf-8`),
  numbers: fs.readFileSync(`${examplePath}/numbers.json`, `utf-8`),
  random: fs.readFileSync(`${examplePath}/random.json`, `utf-8`),
  // 190MB file, compressed to 21MB
  sf_citylots: zlib.gunzipSync(fs.readFileSync(`${examplePath}/sf_citylots.json.gz`)).toString(),
  twitter: fs.readFileSync(`${examplePath}/twitter.json`, `utf-8`),
  twitterescaped: fs.readFileSync(`${examplePath}/twitterescaped.json`, `utf-8`),
  update_center: fs.readFileSync(`${examplePath}/update-center.json`, `utf-8`),
}

const suite = new Benchmark.Suite();

for (const [fileName, jsonStr] of Object.entries(jsonExamples)) {
  suite.add(`${fileName}.json#simdjson`, function(){
    simdjson.lazyParse(jsonStr);
  })
  suite.add(`${fileName}.json#JSON`, function(){
    JSON.parse(jsonStr);
  })
}

suite
  .on(`cycle`, function(event) {
    console.log(`${event.target} => ${(event.target.times.period * 1000).toFixed(3)}ms`)
  })
  .on(`complete`, function() {
    const columns = [
      `filename`,
      `filesize (MB)`,
      `JSON.parse(ms)`,
      `simdjson.lazyParse (ms)`,
      `JSON.parse (GB/s)`,
      `simdjson.lazyParse (GB/s)`,
      `X faster`,
    ];

    console.log(``);
    console.log(`| ${columns.join(` | `)} |`);
    // filename is left aligned, numbers are right aligned
    console.log(`| ${columns.map(col => col === `filename` ? `:--` : `--:`).join(` | `)} |`)

    const benches = this.filter(() => true);
    for (var i = 0; i < benches.length; i+=2) {
      const fileName = benches[i].name.split(`#`)[0];
      const fileSize = Buffer.byteLength(jsonExamples[fileName.split(`.`)[0]]) / 1e6;
      const jsonParseMs = benches[i + 1].times.period * 1000;
      const simdLazyParseMs = benches[i].times.period * 1000;
      const jsonParseGbps = fileSize / jsonParseMs;
      const simdjsonLazyParseGbps = fileSize / simdLazyParseMs;
      const xFaster = jsonParseMs / simdLazyParseMs;
      const row = [
        fileName,
        fileSize.toFixed(2),
        jsonParseMs.toFixed(3),
        simdLazyParseMs.toFixed(3),
        jsonParseGbps.toFixed(2),
        simdjsonLazyParseGbps.toFixed(2),
        xFaster.toFixed(2),
      ];

      console.log(`| ${row.join(` | `)} |`);
    }
  })
  .run({async: false });

