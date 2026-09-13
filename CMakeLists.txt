cmake_minimum_required(VERSION 3.19)

option(REX_OPTION_INI "Enables ini config support for REX." OFF)
option(REX_OPTION_JSON "Enables json config support for REX." OFF)
option(REX_OPTION_TOML "Enables toml config support for REX." OFF)
option(SKSE_SUPPORT_XBYAK "Enables trampoline support for Xbyak." OFF)
option(SKSE_SUPPORT_PATCH_SAFETY "Validate Trampoline::write_branch patch sites land on instruction boundaries before writing (vendors hde64); logs and still writes on failure, never blocks." ON)
option(ENABLE_SKYRIM_SE "Enable support for Skyrim SE in the dynamic runtime feature." ON)
option(ENABLE_SKYRIM_AE "Enable support for Skyrim AE in the dynamic runtime feature." ON)
option(ENABLE_SKYRIM_VR "Enable support for Skyrim VR in the dynamic runtime feature." ON)
option(BUILD_TESTS "Enable building of the unit tests." ON)
message("Options:")
message("\tEnable Xbyak: ${SKSE_SUPPORT_XBYAK}")
message("\tEnable Patch Safety Checks: ${SKSE_SUPPORT_PATCH_SAFETY}")
message("\tEnable Skyrim SE: ${ENABLE_SKYRIM_SE}")
message("\tEnable Skyrim AE: ${ENABLE_SKYRIM_AE}")
message("\tEnable Skyrim VR: ${ENABLE_SKYRIM_VR}")
message("\tBuild Tests: ${BUILD_TESTS}")

if(NOT ENABLE_SKYRIM_SE AND NOT ENABLE_SKYRIM_AE AND NOT ENABLE_SKYRIM_VR)
	message(FATAL_ERROR "At least one Skyrim runtime must be supported by the CommonLibSSE build.")
endif()

project(
	CommonLibSSE
	LANGUAGES CXX
	VERSION 8.0.1
)

include(CheckIPOSupported)
include(GNUInstallDirs)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
	message(FATAL_ERROR "in-source builds are not allowed")
endif()

find_package(spdlog CONFIG REQUIRED)
find_path(RAPIDCSV_INCLUDE_DIRS "rapidcsv.h")
find_package(directxtk CONFIG REQUIRED)

# Prefer a published prebuilt binary over a ~16-min source compile (clean release tag,
# in CI or with COMMONLIB_PREBUILT / COMMONLIB_PREBUILT_DIR) — see cmake/Prebuilt.cmake.
# Runs inside the consumer's add_subdirectory build, so the IMPORTED target points at the
# bundle's local paths — no install/export and none of the relocatability that find_package
# would require. Falls through to the source build on anything unsafe.
include(cmake/Prebuilt.cmake)
commonlib_resolve_prebuilt(COMMONLIB_PREBUILT_RESOLVED)
if(COMMONLIB_PREBUILT_RESOLVED)
	message(STATUS "CommonLibSSE: linking prebuilt binary from ${COMMONLIB_PREBUILT_RESOLVED}")
	add_library("${PROJECT_NAME}" STATIC IMPORTED GLOBAL)
	# Pin the lib to Release and map the other release-like configs onto it. Point Debug at a
	# non-existent sentinel rather than nothing: a multi-config generator validates every config
	# at generate time, so an empty Debug map fails the whole configure — the sentinel keeps
	# generate happy while making a Debug *build* fail loudly with a self-documenting name (the
	# Release-only bundle can't serve Debug; build it from source).
	set_target_properties(
		"${PROJECT_NAME}" PROPERTIES
		IMPORTED_CONFIGURATIONS "RELEASE;DEBUG"
		IMPORTED_LOCATION_RELEASE "${COMMONLIB_PREBUILT_RESOLVED}/lib/CommonLibSSE.lib"
		IMPORTED_LOCATION_DEBUG "${COMMONLIB_PREBUILT_RESOLVED}/lib/CommonLibSSE-debug-build-from-source.lib"
		MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release
		MAP_IMPORTED_CONFIG_MINSIZEREL Release
	)
	add_library("${PROJECT_NAME}::${PROJECT_NAME}" ALIAS "${PROJECT_NAME}")

	target_compile_features("${PROJECT_NAME}" INTERFACE cxx_std_23)
	target_include_directories(
		"${PROJECT_NAME}" INTERFACE
		"${COMMONLIB_PREBUILT_RESOLVED}/include"
		"${COMMONLIB_PREBUILT_RESOLVED}/extern/openvr/headers"
	)
	# Skyrim runtime set is layout-critical and required by the resolver, so define it
	# unconditionally to match the lib.
	target_compile_definitions(
		"${PROJECT_NAME}" INTERFACE
		WINVER=0x0601
		_WIN32_WINNT=0x0601
		ENABLE_SKYRIM_SE=1
		ENABLE_SKYRIM_AE=1
		ENABLE_SKYRIM_VR=1
		HAS_SKYRIM_MULTI_TARGETING=1
	)
	# The lib bakes every REX config + xbyak, but they're additive — expose only the ones the
	# consumer opted into, so it gets exactly the API (and headers) it asked for.
	foreach(_opt REX_OPTION_INI REX_OPTION_JSON REX_OPTION_TOML SKSE_SUPPORT_XBYAK)
		if(${_opt})
			target_compile_definitions("${PROJECT_NAME}" INTERFACE ${_opt}=1)
		endif()
	endforeach()
	if(MSVC)
		target_compile_options(
			"${PROJECT_NAME}" INTERFACE
			/Zc:preprocessor
			/wd4005 /wd4061 /wd4068 /wd4200 /wd4201 /wd4265 /wd4266 /wd4371
			/wd4514 /wd4582 /wd4583 /wd4623 /wd4625 /wd4626 /wd4702 /wd4710
			/wd4711 /wd4820 /wd4996 /wd5026 /wd5027 /wd5045 /wd5053 /wd5204 /wd5220
		)
	endif()
	target_link_libraries(
		"${PROJECT_NAME}" INTERFACE
		spdlog::spdlog
		Microsoft::DirectXTK
		advapi32.lib
		bcrypt.lib
		D3D11.lib
		d3dcompiler.lib
		dbghelp.lib
		DXGI.lib
		ole32.lib
		version.lib
		"${COMMONLIB_PREBUILT_RESOLVED}/lib/openvr_api.lib"
	)
	include(cmake/CommonLibSSE.cmake)  # add_commonlibsse_plugin() helper for consumers
	return()
endif()

include(cmake/sourcelist.cmake)
include(cmake/testlist.cmake)

if(SKSE_SUPPORT_PATCH_SAFETY)
	# hde64 has no vcpkg port -- vendor MinHook's 3-file instruction-length decoder directly.
	# LANGUAGE C (set below) needs an explicit enable_language(C), or Ninja-based
	# generators fail at generate time (the VS generator tolerates the omission).
	enable_language(C)
	include(FetchContent)
	FetchContent_Declare(
		hde64
		GIT_REPOSITORY https://github.com/TsudaKageyu/minhook.git
		GIT_TAG v1.3.4
		GIT_SHALLOW TRUE
		# Populate source only -- MinHook's own root CMakeLists.txt would otherwise add
		# its full hooking library as a subdirectory/target, which we don't want.
		SOURCE_SUBDIR src/hde
	)
	FetchContent_MakeAvailable(hde64)
endif()

source_group(
	TREE "${CMAKE_CURRENT_SOURCE_DIR}"
	FILES ${SOURCES}
)

# IPO/LTCG substantially slows Release compile+link (MSVC's LTCG especially) for a
# correctness-only CI matrix that ships no artifact. Off by default there
# (-DCOMMONLIB_ENABLE_IPO=OFF); the real prebuilt/release builds keep it on.
option(COMMONLIB_ENABLE_IPO "Enable interprocedural (link-time) optimization for Release builds" ON)

if(COMMONLIB_ENABLE_IPO)
	check_ipo_supported(RESULT USE_IPO OUTPUT IPO_OUTPUT)
	if(USE_IPO)
		set(CMAKE_INTERPROCEDURAL_OPTIMIZATION "$<$<CONFIG:RELEASE>:ON>")
	endif()
endif()

add_library(
	"${PROJECT_NAME}"
	STATIC
	${SOURCES}
	.clang-format
	CommonLibSSE.natvis
)

add_library("${PROJECT_NAME}::${PROJECT_NAME}" ALIAS "${PROJECT_NAME}")

target_compile_definitions(
	"${PROJECT_NAME}"
	PUBLIC
	WINVER=0x0601 # windows 7, minimum supported version by skyrim special edition
	_WIN32_WINNT=0x0601
	"$<$<BOOL:${REX_OPTION_INI}>:REX_OPTION_INI=1>"
	"$<$<BOOL:${REX_OPTION_JSON}>:REX_OPTION_JSON=1>"
	"$<$<BOOL:${REX_OPTION_TOML}>:REX_OPTION_TOML=1>"
	"$<$<BOOL:${SKSE_SUPPORT_XBYAK}>:SKSE_SUPPORT_XBYAK=1>"
	"$<$<BOOL:${SKSE_SUPPORT_PATCH_SAFETY}>:SKSE_SUPPORT_PATCH_SAFETY=1>"
	"$<$<BOOL:${ENABLE_SKYRIM_SE}>:ENABLE_SKYRIM_SE=1>"
	"$<$<BOOL:${ENABLE_SKYRIM_AE}>:ENABLE_SKYRIM_AE=1>"
	"$<$<BOOL:${ENABLE_SKYRIM_VR}>:ENABLE_SKYRIM_VR=1>"
	"$<$<AND:$<BOOL:${ENABLE_SKYRIM_SE}>,$<BOOL:${ENABLE_SKYRIM_AE}>>:HAS_SKYRIM_MULTI_TARGETING=1>"
	"$<$<AND:$<BOOL:${ENABLE_SKYRIM_SE}>,$<BOOL:${ENABLE_SKYRIM_VR}>>:HAS_SKYRIM_MULTI_TARGETING=1>"
	"$<$<AND:$<BOOL:${ENABLE_SKYRIM_AE}>,$<BOOL:${ENABLE_SKYRIM_VR}>>:HAS_SKYRIM_MULTI_TARGETING=1>"
)

# PRIVATE: only REL::Module's embedded license notice reads this, so it stays out of the
# consumer-visible PUBLIC definitions above to avoid macro collisions.
target_compile_definitions(
	"${PROJECT_NAME}"
	PRIVATE
	"COMMONLIB_VERSION=\"${PROJECT_VERSION}\""
)

target_compile_features(
	"${PROJECT_NAME}"
	PUBLIC
	cxx_std_23
)

if(MSVC)
	target_compile_options(
		"${PROJECT_NAME}"
		PUBLIC

		# Enhanced debug information for optimized code (includes all type info in PDB for RE/debugging)
		"$<$<CONFIG:Debug>:/Zo>"

		# Standards conformance
		/Zc:preprocessor # Enable conforming preprocessor (required for STATIC_ASSERT_SIZE variadic macro)

		# disable warnings
		"$<$<CONFIG:Debug>:/wd4702>" # unreachable code: debug builds don't optimize away compile-time conditionals
		/wd4005 # macro redefinition
		/wd4061 # enumerator 'identifier' in switch of enum 'enumeration' is not explicitly handled by a case label
		/wd4068 # unknown pragma
		/wd4200 # nonstandard extension used : zero-sized array in struct/union
		/wd4201 # nonstandard extension used : nameless struct/union
		/wd4265 # 'type': class has virtual functions, but its non-trivial destructor is not virtual; instances of this class may not be destructed correctly
		/wd4266 # 'function' : no override available for virtual member function from base 'type'; function is hidden
		/wd4371 # 'classname': layout of class may have changed from a previous version of the compiler due to better packing of member 'member'
		/wd4514 # 'function' : unreferenced inline function has been removed
		/wd4582 # 'type': constructor is not implicitly called
		/wd4583 # 'type': destructor is not implicitly called
		/wd4623 # 'derived class' : default constructor was implicitly defined as deleted because a base class default constructor is inaccessible or deleted
		/wd4625 # 'derived class' : copy constructor was implicitly defined as deleted because a base class copy constructor is inaccessible or deleted
		/wd4626 # 'derived class' : assignment operator was implicitly defined as deleted because a base class assignment operator is inaccessible or deleted
		/wd4710 # 'function' : function not inlined
		/wd4711 # function 'function' selected for inline expansion
		/wd4820 # 'bytes' bytes padding added after construct 'member_name'
		/wd4996 # 'deprecated function': required due to Microsoft STL itself using its own deprecated functions
		/wd5026 # 'type': move constructor was implicitly defined as deleted
		/wd5027 # 'type': move assignment operator was implicitly defined as deleted
		/wd5045 # Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
		/wd5053 # support for 'explicit(<expr>)' in C++17 and earlier is a vendor extension
		/wd5204 # 'type-name': class has virtual functions, but its trivial destructor is not virtual; instances of objects derived from this class may not be destructed correctly
		/wd5220 # 'member': a non-static data member with a volatile qualified type no longer implies that compiler generated copy / move constructors and copy / move assignment operators are not trivial
	)
endif()

set(OPENVR_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern/openvr/headers)
set(OPENVR_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern/openvr/lib/win64)
target_include_directories(
	"${PROJECT_NAME}"
	PUBLIC
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
	"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
	"$<BUILD_INTERFACE:${OPENVR_INCLUDE_DIR}>"
)

target_include_directories(
	"${PROJECT_NAME}"
	PRIVATE
	${spdlog_INCLUDE_DIRS}
	${RAPIDCSV_INCLUDE_DIRS}
)

if(SKSE_SUPPORT_PATCH_SAFETY)
	# hde64.h is only ever included from Trampoline.cpp -- the check never appears in a
	# public header, so PRIVATE keeps the vendored dependency off every downstream
	# consumer's include path.
	target_sources("${PROJECT_NAME}" PRIVATE "${hde64_SOURCE_DIR}/src/hde/hde64.c")
	target_include_directories("${PROJECT_NAME}" PRIVATE "${hde64_SOURCE_DIR}/src/hde")
	# VS doesn't reliably infer hde64.c's LANGUAGE without this (silent <None>, fails only
	# at link time); a vendored C file also can't use our C++ precompiled header, and /WX-
	# keeps its own warnings from becoming errors without touching the file itself.
	set_source_files_properties(
		"${hde64_SOURCE_DIR}/src/hde/hde64.c" PROPERTIES
		LANGUAGE C
		SKIP_PRECOMPILE_HEADERS ON
		COMPILE_OPTIONS "$<$<CXX_COMPILER_ID:MSVC>:/WX->"
	)
endif()

target_compile_definitions(
	"${PROJECT_NAME}"
	PUBLIC
)

target_link_libraries(
	"${PROJECT_NAME}"
	PUBLIC
	spdlog::spdlog
	Microsoft::DirectXTK
	advapi32.lib
	bcrypt.lib
	D3D11.lib
	d3dcompiler.lib
	dbghelp.lib
	DXGI.lib
	ole32.lib
	version.lib
	"$<$<BOOL:${ENABLE_SKYRIM_VR}>:${OPENVR_LIB_DIR}/openvr_api.lib>"
)

if(MSVC)
	target_link_options(
		"${PROJECT_NAME}"
		PUBLIC
		# Generate complete PDB with all type information for reverse engineering
		"$<$<CONFIG:Debug>:/DEBUG:FULL>"
	)
endif()

target_precompile_headers(
	"${PROJECT_NAME}"
	PRIVATE
	include/SKSE/Impl/PCH.h
)

install(
	TARGETS "${PROJECT_NAME}"
	EXPORT "${PROJECT_NAME}-targets"
)

install(
	EXPORT "${PROJECT_NAME}-targets"
	NAMESPACE "${PROJECT_NAME}::"
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)

configure_file(
	cmake/config.cmake.in
	"${PROJECT_NAME}Config.cmake"
	@ONLY
)

install(
	FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)

install(
	DIRECTORY
	"include/RE"
	"include/REL"
	"include/REX"
	"include/SKSE"
	DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

if(BUILD_TESTS)
	find_package(Catch2 CONFIG REQUIRED)
	include(CTest)
	include(Catch)

	add_executable(
		"${PROJECT_NAME}Tests"
		${TESTS}
	)

	target_include_directories(
		"${PROJECT_NAME}Tests"
		PUBLIC
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
	)

	target_include_directories(
		"${PROJECT_NAME}Tests"
		PRIVATE
		${Catch2_INCLUDE_DIRS}
		${spdlog_INCLUDE_DIRS}
		${RAPIDCSV_INCLUDE_DIRS}
	)

	target_compile_definitions(
		"${PROJECT_NAME}Tests"
		PUBLIC
		ENABLE_COMMONLIBSSE_TESTING=1
	)

	target_link_libraries(
		"${PROJECT_NAME}Tests"
		PRIVATE
		${PROJECT_NAME}
		Catch2::Catch2
	)

	if(MSVC)
		target_link_options(
			"${PROJECT_NAME}Tests"
			PRIVATE
			# Generate complete PDB with all type information for reverse engineering
			"$<$<CONFIG:Debug>:/DEBUG:FULL>"
		)
	endif()

	target_precompile_headers(
		"${PROJECT_NAME}Tests"
		PRIVATE
		include/SKSE/Impl/PCH.h
	)

	file(COPY
		tests/REL/input-queue.csv
		tests/REL/version-1-4-15-0.csv
		tests/REL/version-1-5-97-0.bin
		tests/REL/versionlib-1-6-353-0.bin
		tests/REL/versionlib-1-6-629-0.bin
		tests/REL/versionlib-1-6-1130-0.bin
		tests/REL/versionlib-1-6-1170-0.bin
		tests/REL/versionlib-1-6-1179-0.bin
		tests/REL/versionlib-1-7-99-0.bin
		tests/REL/version-invalid-format.bin
		DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/Data/SKSE/Plugins/"
	)

	catch_discover_tests("${PROJECT_NAME}Tests")
	add_test(NAME "${PROJECT_NAME}Tests" COMMAND "${PROJECT_NAME}Tests")
endif()
