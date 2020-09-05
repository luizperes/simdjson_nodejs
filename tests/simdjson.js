const fs = require(`fs`);
const assert = require(`assert`);
const simdjson = require(`../index`);

const examplesPath = `${__dirname}/../jsonexamples`;
const jsonExamples = {
  demo: fs.readFileSync(`${examplesPath}/small/demo.json`, `utf-8`),
  canada: fs.readFileSync(`${examplesPath}/canada.json`, `utf-8`),
  apache_builds: fs.readFileSync(`${examplesPath}/apache_builds.json`, `utf-8`),
};

describe(`simdjson`, function () {
  context(`isValid`, function () {
    it(`returns true for valid json strings`, function () {
      assert.equal(simdjson.isValid(jsonExamples.canada), true);
      assert.equal(simdjson.isValid(jsonExamples.apache_builds), true);
    });

    it(`returns false for valid json strings`, function () {
      assert.equal(simdjson.isValid(`@#$`), false);
      assert.equal(simdjson.isValid(`{"hello"}`), false);
      assert.equal(simdjson.isValid(`{hello: "world"}`), false);
      assert.equal(simdjson.isValid(`[1,2, {"hello: "world"}`), false);
    });
  });

  context(`parse`, function () {
    it(`parses into valid js object`, function () {
      assert.deepStrictEqual(simdjson.parse(jsonExamples.demo), {
        Image: {
          Width: 800,
          Height: 600,
          Title: `View from 15th Floor`,
          Thumbnail: {
            Url: `http://www.example.com/image/481989943`,
            Height: 125,
            Width: 100,
          },
          Animated: false,
          IDs: [116, 943, 234, 38793],
        },
      });
    });

    it(`throws error for invalid json str`, function () {
      assert.throws(
        () => simdjson.parse(jsonExamples.demo + `#$`),
        new Error(`The JSON document has an improper structure: missing or superfluous commas, braces, missing keys, etc.`)
      );
    });
  });

  context(`lazyParse`, function () {
    it(`returns value from keyPath`, function () {
      const jsonTape = simdjson.lazyParse(jsonExamples.apache_builds);
      assert.equal(
        jsonTape.valueForKeyPath(`jobs[400].name`),
        `Lucene-Solr-Clover-4.x`
      );
    });

    it(`throws error for invalid keyPath`, function () {
      const jsonTape = simdjson.lazyParse(jsonExamples.canada);
      assert.throws(
        () => jsonTape.valueForKeyPath(`foo.bar.yolo`),
        new Error(`The JSON field referenced does not exist in this object.`)
      );
    });

    it(`empty keyPath returns full value`, function () {
      const jsonTape = simdjson.lazyParse(jsonExamples.demo);
      assert.deepStrictEqual(jsonTape.valueForKeyPath(``), {
        Image: {
          Width: 800,
          Height: 600,
          Title: `View from 15th Floor`,
          Thumbnail: {
            Url: `http://www.example.com/image/481989943`,
            Height: 125,
            Width: 100,
          },
          Animated: false,
          IDs: [116, 943, 234, 38793],
        },
      });
    });
  });
});
