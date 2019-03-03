{
  "targets": [
    {
      "target_name": "simdjson",
      "default_configuration": "Release",
      "cflags": ["-O3", "-std=c99"],
      "cflags_cc": ["-O3", "-std=c++17"],
      "sources": [
        "simdjson/nonavx2.cpp"
      ],
      'include_dirs': ["<!@(node -p \"require('nan').include\")"]
    }
  ],
  "conditions": [
    [
      "target_arch in \"x64 x86_64\"",
      {
        "targets": [
          {
            "target_name": "simdjson-avx2",
            "default_configuration": "Release",
            "cflags!": [ "-fno-exceptions" ],
            "cflags_cc!": ["-O3", "-fno-exceptions", "-std=gnu++0x", "-std=gnu++1y", "-mavx2", "-mavx", "-mbmi", "-mpclmul"],
            "cflags_cc+": ["-O3", "-march=native", "-std=c++17", "-mavx2", "-mavx", "-mbmi", "-mpclmul"],
            "sources": ["simdjson/src/simdjson.cpp", "simdjson/bindings.cpp"],
            "xcode_settings": {
              "GCC_ENABLE_SSE42_EXTENSIONS": "YES",
              "CLANG_X86_VECTOR_INSTRUCTIONS": "avx2",
              "OTHER_CFLAGS": ["-mavx2", "-mavx", "-mbmi", "-mpclmul"],
            },
            "msvs_settings": {
              "VCCLCompilerTool": {
                "AdditionalOptions": ["/arch:AVX2", "/mavx2", "/mavx", "/mbmi", "/mpclmul"]
              }
            },
            "include_dirs": ["<!@(node -p \"require('nan').include\")"]
          }
        ]
      }
    ]
  ]
}