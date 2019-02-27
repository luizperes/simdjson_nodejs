const simdjsonAddon = require('./build/Release/simdjson.node');

console.log('addon',simdjsonAddon);
if (simdjsonAddon.isValid("{ \"firstName\": \"John\", \"lastName\": \"Smith\" }")) {
    console.log("valid");
} else {
    console.log("not valid");
}

module.exports = simdjsonAddon;