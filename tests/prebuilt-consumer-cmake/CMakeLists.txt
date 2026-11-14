# Self-test for the CMake clean-tag auto-fetch: add_subdirectory the CommonLibSSE-NG repo
# with COMMONLIB_PREBUILT_DIR pointing at the just-assembled bundle, so the resolver in
# cmake/Prebuilt.cmake exposes CommonLibSSE as an IMPORTED target. add_commonlibsse_plugin
# then compiles a generated plugin TU against the prebuilt headers and links the prebuilt
# lib — proving the bundle is consumable with zero CommonLib recompile. Driven by
# prebuilt.yml; locally: configure with -DCOMMONLIB_PREBUILT_DIR=<extracted bundle>.
cmake_minimum_required(VERSION 3.19)
project(prebuilt_consumer_cmake LANGUAGES CXX)

# The repo root is two levels up; give add_subdirectory an explicit binary dir.
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../.." commonlib)

add_commonlibsse_plugin(prebuilt_consumer_cmake
	AUTHOR "CommonLibSSE-NG"
	NAME "prebuilt_consumer_cmake"
	VERSION 1.0.0)

# CommonLibSSE-NG headers are PCH-dependent; consumers force-include a PCH.
target_precompile_headers(prebuilt_consumer_cmake PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/pch.h")
