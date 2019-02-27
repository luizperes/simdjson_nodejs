const simdjsonAddon = require('./build/Release/simdjson.node');

console.log('addon',simdjsonAddon);
if (simdjsonAddon.isValid("{ \"firstName\": \"John\", \"lastName\": \"Smith\" }")) {
    console.log("valid");
} else {
    console.log("not valid");
}

console.log(simdjsonAddon.parse("{ \"firstName\": \"John\", \"lastName\": \"Smith\" }"));

module.exports = simdjsonAddon;