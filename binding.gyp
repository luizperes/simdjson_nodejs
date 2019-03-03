{       
  "variables": {
    "avx": "",
    "avx2": "",
  },
  "targets": [
    {
      "target_name": "simdjson",
      'include_dirs': ["<!@(node -p \"require('nan').include\")"],
      "sources": ["simdjson/nonavx2.cpp"],
      "conditions": [
        ["OS=='mac'", {
          "sources": ["simdjson/src/simdjson.cpp", "simdjson/bindings.cpp"],
          "xcode_settings": {
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
            'CLANG_CXX_LIBRARY': 'libc++',
            'MACOSX_DEPLOYMENT_TARGET': '10.7',
            "OTHER_CFLAGS": [
              "-mavx2", "-mavx", "-mbmi", "-mpclmul"
            ]
          },
          "cflags_cc+": ["-march=native", "-std=c++17"],
          "conditions": [
            ["avx2 == 'true'", {
              "sources": ["simdjson/src/simdjson.cpp", "simdson/binding.cpp"],
              "xcode_settings": {
                "OTHER_CFLAGS": [
                  "-mavx2", "-mavx", "-mbmi", "-mpclmul"
                ]              
              }              
            }],
            ["avx == 'true'", {
              "sources": ["simdjson/src/simdjson.cpp", "simdson/binding.cpp"],
              "xcode_settings": {
                "OTHER_CFLAGS": [
                  "-mavx", "-mbmi", "-mpclmul"
                ]              
              }              
            }]
          ]
        }],
        ["OS=='linux'", {
          "cflags!": [ "-fno-exceptions" ],
          "cflags_cc!": [ "-fno-exceptions", "-std=gnu++0x", "-std=gnu++1y" ],
          "cflags_cc+": ["-march=native", "-std=c++17"],
          "conditions": [
            ["avx2 == 'true'", {
              "sources": ["simdjson/src/simdjson.cpp", "simdson/binding.cpp"],
              "cflags_cc": [ "-mavx2", "-mavx", "-mbmi", "-mpclmul" ],
            }],
            ["avx == 'true'", {
              "sources": ["simdjson/src/simdjson.cpp", "simdson/binding.cpp"],
              "cflags_cc": [ "-mavx", "-mbmi", "-mpclmul" ],
            }]
          ]
        }],
        ["OS=='win'", {
          "cflags_cc+": ["-march=native", "-std=c++17"],
          'msvs_settings': {
            'VCCLCompilerTool': { 'ExceptionHandling': 1 },
          },                    
          "conditions": [
            ["avx2 == 'true'", {
              "sources": ["simdjson/src/simdjson.cpp", "simdson/binding.cpp"],
              "cflags_cc": [ "-mavx2", "-mavx", "-mbmi", "-mpclmul" ],
            }],
            ["avx == 'true'", {
              "sources": ["simdjson/src/simdjson.cpp", "simdson/binding.cpp"],
              "cflags_cc": [ "-mavx", "-mbmi", "-mpclmul" ],
            }]
          ]
        }]
      ]
    }
  ]
}