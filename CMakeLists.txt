cmake_minimum_required(VERSION 3.19)

option(SKSE_SUPPORT_XBYAK "Enables trampoline support for Xbyak." OFF)
option(ENABLE_SKYRIM_SE "Enable support for Skyrim SE in the dynamic runtime feature." ON)
option(ENABLE_SKYRIM_AE "Enable support for Skyrim AE in the dynamic runtime feature." ON)
option(ENABLE_SKYRIM_VR "Enable support for Skyrim VR in the dynamic runtime feature." ON)
option(BUILD_TESTS "Enable building of the unit tests." ON)
message("Options:")
message("\tEnable Xbyak: ${SKSE_SUPPORT_XBYAK}")
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
	VERSION 3.6.0
)

include(CheckIPOSupported)
include(GNUInstallDirs)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
	message(FATAL_ERROR "in-source builds are not allowed")
endif()

find_package(spdlog CONFIG REQUIRED)
find_path(RAPIDCSV_INCLUDE_DIRS "rapidcsv.h")
find_package(directxtk CONFIG REQUIRED)

include(cmake/sourcelist.cmake)
include(cmake/testlist.cmake)

source_group(
	TREE "${CMAKE_CURRENT_SOURCE_DIR}"
	FILES ${SOURCES}
)

check_ipo_supported(RESULT USE_IPO OUTPUT IPO_OUTPUT)

if(USE_IPO)
	set(CMAKE_INTERPROCEDURAL_OPTIMIZATION "$<$<CONFIG:RELEASE>:ON>")
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
	"$<$<BOOL:${SKSE_SUPPORT_XBYAK}>:SKSE_SUPPORT_XBYAK=1>"
	"$<$<BOOL:${ENABLE_SKYRIM_SE}>:ENABLE_SKYRIM_SE=1>"
	"$<$<BOOL:${ENABLE_SKYRIM_AE}>:ENABLE_SKYRIM_AE=1>"
	"$<$<BOOL:${ENABLE_SKYRIM_VR}>:ENABLE_SKYRIM_VR=1>"
	HAS_SKYRIM_MULTI_TARGETING=1
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

		# disable warnings
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

target_compile_definitions(
	"${PROJECT_NAME}"
	PUBLIC
)

target_link_libraries(
	"${PROJECT_NAME}"
	PUBLIC
	spdlog::spdlog
	Microsoft::DirectXTK
	Advapi32.lib
	D3D11.lib
	d3dcompiler.lib
	Dbghelp.lib
	DXGI.lib
	Ole32.lib
	Version.lib
)

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

	target_precompile_headers(
		"${PROJECT_NAME}Tests"
		PRIVATE
		include/SKSE/Impl/PCH.h
	)

	file(COPY
		tests/REL/version-1-4-15-0.csv
		tests/REL/version-1-5-97-0.bin
		tests/REL/versionlib-1-6-353-0.bin
		DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/Data/SKSE/Plugins/"
	)

	catch_discover_tests("${PROJECT_NAME}Tests")
	add_test(NAME "${PROJECT_NAME}Tests" COMMAND "${PROJECT_NAME}Tests")
endif()
