In order to build at the moment, you need to drop the source for the following in this folder:
gmock-1.7.0
rapidjson-1.1.0
SDL2-2.0.5
spdlog (latest version)
cereal-1.2.2

Run CMake the first time, then turn on the related values:
EXTERN_INLINE_GMOCK
EXTERN_INLINE_RAPIDJSON
EXTERN_INLINE_SDL2
EXTERN_INLINE_SPDLOG
EXTERN_INLINE_CEREAL

Rerun CMake and assuming all is well, things should work.


NOTES:
	Probably going to do away with spdlog and use glog or something less cumbersome and annoying.  It may be fast
	but the purpose is to also not be an intrusive pain.
