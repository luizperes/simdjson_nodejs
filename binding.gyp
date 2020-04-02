{
  "targets": [
    {
      "target_name": "simdjson",
      "default_configuration": "Release",
      "cflags!": ["-fno-exceptions"],
      "cflags_cc!": ["-O3", "-fno-exceptions", "-std=gnu++0x", "-std=gnu++1y"],
      "cflags_cc+": ["-O3", "-std=c++17"],
      "sources": [
        "simdjson/main.cpp",
        "simdjson/src/simdjson.cpp",
        "simdjson/bindings.cpp"
      ],
      "xcode_settings": {
        "OTHER_CFLAGS": ["-std=c++17"],
      },
      "msvs_settings": {
        "VCCLCompilerTool": {
          "AdditionalOptions": ["/std:c++17"]
        }
      },
      "include_dirs": ["<!@(node -p \"require('node-addon-api').include\")"],
      "defines": ["NAPI_DISABLE_CPP_EXCEPTIONS"]
    }
  ]
}
