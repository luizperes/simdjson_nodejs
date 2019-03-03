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
      "defines": [],
      "conditions": [
        ["OS=='mac'", {          
          "xcode_settings": {
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
            'CLANG_CXX_LIBRARY': 'libc++',
            'MACOSX_DEPLOYMENT_TARGET': '10.7',            
          },
          "conditions": [
            ["avx2 == 'true'", {
              "sources": ["simdjson/src/simdjson.cpp", "simdson/binding.cpp"],
              "xcode_settings": {
                "OTHER_CFLAGS": [
                  "-mavx2"
                ]              
              }              
            }],
            ["avx == 'true'", {
              "sources": ["simdjson/src/simdjson.cpp", "simdson/binding.cpp"],
              "xcode_settings": {
                "OTHER_CFLAGS": [
                  "-mavx"
                ]              
              }              
            }]
          ]
        }],
        ["OS=='linux'", {          
          'cflags!': [ '-fno-exceptions' ],
          'cflags_cc!': [ '-fno-exceptions' ],
          "conditions": [
            ["avx2 == 'true'", {
              "sources": ["simdjson/src/simdjson.cpp", "simdson/binding.cpp"],
              'cflags_cc': [ '-mavx2' ],
            }],
            ["avx == 'true'", {
              "sources": ["simdjson/src/simdjson.cpp", "simdson/binding.cpp"],
              'cflags_cc': [ '-mavx' ],
            }]
          ]
        }],
        ["OS=='win'", {
          'msvs_settings': {
            'VCCLCompilerTool': { 'ExceptionHandling': 1 },
          },                    
          "conditions": [
            ["avx2 == 'true'", {
              "sources": ["simdjson/src/simdjson.cpp", "simdson/binding.cpp"],
              'cflags_cc': [ '-mavx2' ],
            }],
            ["avx == 'true'", {
              "sources": ["simdjson/src/simdjson.cpp", "simdson/binding.cpp"],
              'cflags_cc': [ '-mavx' ],
            }]
          ]
        }]
      ]
    }
  ]
}