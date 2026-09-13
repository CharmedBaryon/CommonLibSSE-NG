cmake_minimum_required(VERSION 3.21)

project(
	CommonLibSSEConsumerTest
	LANGUAGES CXX
	VERSION 1.0.0
)

# This test project validates that CommonLib works correctly when used as a dependency
# It specifically tests that STATIC_ASSERT_SIZE macros compile when consuming CommonLib

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add CommonLib as a subdirectory dependency (simulates real-world usage)
set(BUILD_TESTS OFF CACHE BOOL "Disable CommonLib tests in consumer" FORCE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/.. CommonLibSSE EXCLUDE_FROM_ALL)

# Create a simple test executable that uses CommonLib headers
add_executable(
	ConsumerTest
	test.cpp
)

target_link_libraries(
	ConsumerTest
	PRIVATE
	CommonLibSSE::CommonLibSSE
)

# Use CommonLib's precompiled header (critical for RTTI macros, stl namespace, etc.)
target_precompile_headers(
	ConsumerTest
	PRIVATE
		<SKSE/SKSE.h>
		<RE/Skyrim.h>
)

# Enable testing
enable_testing()
add_test(
	NAME ConsumerCompileTest
	COMMAND ConsumerTest
)
