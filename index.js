const simdjson_ = require('./build/Release/simdjson.node');
if (simdjson.hasAVX2()) {
    const simdjson = simdjson_;
    module.exports = simdjson;
} else {
    // If the user doesn't have AVX2, we use the default JSON
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
}
