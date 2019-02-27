const simdjsonAddon = require('./build/Release/simdjson.node');

console.log('addon',simdjsonAddon);
console.log(simdjsonAddon.hello());

module.exports = simdjsonAddon;