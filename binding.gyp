{
    "targets": [{
        "target_name": "simdjson",
        "default_configuration": "Release",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions", "-std=gnu++0x", "-std=gnu++1y" ],
        "cflags_cc+": ["-march=native", "-std=c++17"],
         "sources": [
            "simdjson/main.cpp"
        ],
        'include_dirs': [
            "<!@(node -p \"require('nan').include\")"
        ]
    }]
}
