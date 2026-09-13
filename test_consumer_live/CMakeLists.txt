cmake_minimum_required(VERSION 3.21)

project(
	CommonLibSSELiveVerify
	LANGUAGES CXX
	VERSION 1.0.0
)

# NOT part of CI (see README.md) -- builds a real SKSE plugin, meant to be
# deployed to a real game install and run against a real running Skyrim
# process. CI has no game to launch, so this only runs locally/manually.

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# flat (SE+AE) by default; -DLIVE_VERIFY_VR=ON builds the VR-only variant instead.
option(LIVE_VERIFY_VR "Build the VR-only variant instead of flat SE/AE" OFF)
if(LIVE_VERIFY_VR)
	set(ENABLE_SKYRIM_SE OFF CACHE BOOL " " FORCE)
	set(ENABLE_SKYRIM_AE OFF CACHE BOOL " " FORCE)
	set(ENABLE_SKYRIM_VR ON CACHE BOOL " " FORCE)
else()
	set(ENABLE_SKYRIM_SE ON CACHE BOOL " " FORCE)
	set(ENABLE_SKYRIM_AE ON CACHE BOOL " " FORCE)
	set(ENABLE_SKYRIM_VR OFF CACHE BOOL " " FORCE)
endif()
set(BUILD_TESTS OFF CACHE BOOL "Disable CommonLib tests in consumer" FORCE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/.. CommonLibSSE EXCLUDE_FROM_ALL)
get_target_property(COMMONLIB_SRC_DIR CommonLibSSE SOURCE_DIR)
include(${COMMONLIB_SRC_DIR}/cmake/CommonLibSSE.cmake)

add_commonlibsse_plugin(${PROJECT_NAME}
	AUTHOR "CommonLibVR"
	SOURCES src/plugin.cpp
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_compile_definitions(${PROJECT_NAME} PRIVATE WIN32_LEAN_AND_MEAN NOMINMAX UNICODE _UNICODE)
target_precompile_headers(${PROJECT_NAME} PRIVATE include/PCH.h)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
