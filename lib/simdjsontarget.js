const os = require('os');
const moduleExists = require('./moduleexists');

const nodePaths = {
  AVX2: '../build/Release/simdjson-avx2.node',
  PLAIN: '../build/Release/simdjson.node'
};

let path = nodePaths.PLAIN;
if (moduleExists(nodePaths.AVX2) && os.arch() === 'x64') {
  const simdjson = require(nodePaths.AVX2);
  if (simdjson && simdjson.hasAVX2()) {
    path = nodePaths.AVX2;
  }
}

if (path === nodePaths.PLAIN) {
  const simdjson = JSON;
  simdjson["isValid"] = (str) => {
    try {
      simdjson.parse(str);
    } catch (e) {
      return false;
    }
    return true;
  };
  module.exports = simdjson;
} else {
  module.exports = require(nodePaths.AVX2);
}

