{
    "targets": [{
        "target_name": "simdjson",
        "default_configuration": "Release",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions", "-std=gnu++0x", "-std=gnu++1y" ],
        "cflags_cc+": ["-march=native", "-std=c++17"],
         "sources": [
            "simdjson/main.cpp",
            "simdjson/bindings.cpp",
            "simdjson/src/simdjson.cpp"
        ],
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")"
        ],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }]
}
