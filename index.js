const simdjsonAddon = require('./build/Release/simdjson.node');

console.log('addon', simdjsonAddon);

module.exports = simdjsonAddon;