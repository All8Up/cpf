In order to build at the moment, you need to drop the source for the following in this folder:
gmock-1.7.0
rapidjson-1.1.0
SDL2-2.0.5
spdlog (latest version)

Run CMake the first time, then turn on the four related values:
EXTERN_INLINE_GMOCK
EXTERN_INLINE_RAPIDJSON
EXTERN_INLINE_SDL2
EXTERN_INLINE_SPDLOG

Rerun CMake and assuming all is well, things should work.
