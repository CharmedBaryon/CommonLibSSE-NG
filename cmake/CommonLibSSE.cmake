function(commonlibsse_parse_version VERSION)
    string(REGEX MATCHALL "^([0-9]+)(\.([0-9]+)(\.([0-9]+)(\.([0-9]+))?)?)?$" version_match "${VERSION}")
    unset(COMMONLIBSSE_VERSION_MAJOR PARENT_SCOPE)
    unset(COMMONLIBSSE_VERSION_MINOR PARENT_SCOPE)
    unset(COMMONLIBSSE_VERSION_PATCH PARENT_SCOPE)
    unset(COMMONLIBSSE_VERSION_TWEAK PARENT_SCOPE)

    if("${version_match} " STREQUAL " ")
        set(COMMONLIBSSE_VERSION_MATCH FALSE PARENT_SCOPE)
        return()
    endif()

    if(CMAKE_MATCH_1)
        string(STRIP ${CMAKE_MATCH_1} CMAKE_MATCH1) # save stripped version since we're doing a regex check later
    endif()

    if(CMAKE_MATCH_3)
        string(STRIP ${CMAKE_MATCH_3} CMAKE_MATCH3)
    endif()

    if(CMAKE_MATCH_5)
        string(STRIP ${CMAKE_MATCH_5} CMAKE_MATCH5)
    endif()

    if(CMAKE_MATCH_7)
        string(STRIP ${CMAKE_MATCH_7} CMAKE_MATCH7)
    endif()

    set(COMMONLIBSSE_VERSION_MATCH TRUE PARENT_SCOPE)
    set(COMMONLIBSSE_VERSION_MAJOR "0" PARENT_SCOPE)
    set(COMMONLIBSSE_VERSION_MINOR "0" PARENT_SCOPE)
    set(COMMONLIBSSE_VERSION_PATCH "0" PARENT_SCOPE)
    set(COMMONLIBSSE_VERSION_TWEAK "0" PARENT_SCOPE)

    if(DEFINED CMAKE_MATCH1 AND CMAKE_MATCH1 MATCHES "^[0-9]+$")
        message("Setting major version to ${CMAKE_MATCH_0}")
        set(COMMONLIBSSE_VERSION_MAJOR "${CMAKE_MATCH_0}" PARENT_SCOPE)
    endif()

    if(DEFINED CMAKE_MATCH3 AND CMAKE_MATCH3 MATCHES "^[0-9]+$")
        message("Setting minor version to ${CMAKE_MATCH_0}")
        set(COMMONLIBSSE_VERSION_MINOR "${CMAKE_MATCH_0}" PARENT_SCOPE)
    endif()

    if(DEFINED CMAKE_MATCH5 AND CMAKE_MATCH5 MATCHES "^[0-9]+$")
        message("Setting patch version to ${CMAKE_MATCH_0}")
        set(COMMONLIBSSE_VERSION_PATCH "${CMAKE_MATCH_0}" PARENT_SCOPE)
    endif()

    if(DEFINED CMAKE_MATCH7 AND CMAKE_MATCH7 MATCHES "^[0-9]+$")
        message("Setting tweak version to ${CMAKE_MATCH_0}")
        set(COMMONLIBSSE_VERSION_TWEAK "${CMAKE_MATCH_0}" PARENT_SCOPE)
    endif()
endfunction()

function(target_commonlibsse_properties TARGET)
    # EXCLUDE_FROM_ALL and SOURCES are supported here to simplify passing arguments from add_commonlibsse_plugin.
    set(options OPTIONAL USE_ADDRESS_LIBRARY USE_SIGNATURE_SCANNING STRUCT_DEPENDENT EXCLUDE_FROM_ALL)
    set(oneValueArgs NAME AUTHOR EMAIL VERSION MINIMUM_SKSE_VERSION)
    set(multiValueArgs COMPATIBLE_RUNTIMES SOURCES)
    cmake_parse_arguments(PARSE_ARGV 1 ADD_COMMONLIBSSE_PLUGIN "${options}" "${oneValueArgs}"
        "${multiValueArgs}")

    set(commonlibsse_plugin_file "${CMAKE_CURRENT_BINARY_DIR}/__${TARGET}Plugin.cpp")

    # Set the plugin name.
    set(commonlibsse_plugin_name "${TARGET}")

    if(DEFINED ADD_COMMONLIBSSE_PLUGIN_NAME)
        set(commonlibsse_plugin_name "${ADD_COMMONLIBSSE_PLUGIN_NAME}")
    endif()

    # Setup version number of the plugin.
    set(commonlibsse_plugin_version "${PROJECT_VERSION}")

    if(DEFINED ADD_COMMONLIBSSE_PLUGIN_VERSION)
        set(commonlibsse_plugin_version "${ADD_COMMONLIBSSE_PLUGIN_VERSION}")
    endif()

    message("Parsing commonlibsse_plugin_version ${commonlibsse_plugin_version}")
    commonlibsse_parse_version("${commonlibsse_plugin_version}")

    if(NOT DEFINED COMMONLIBSSE_VERSION_MAJOR)
        message(FATAL_ERROR "Unable to parse plugin version number ${commonlibsse_plugin_version}.")
    endif()

    set(commonlibsse_plugin_version "REL::Version{ ${COMMONLIBSSE_VERSION_MAJOR}, ${COMMONLIBSSE_VERSION_MINOR}, ${COMMONLIBSSE_VERSION_PATCH}, ${COMMONLIBSSE_VERSION_TWEAK} }")

    # Handle minimum SKSE version constraints.
    if(NOT DEFINED ADD_COMMONLIBSSE_PLUGIN_MINIMUM_SKSE_VERSION)
        set(ADD_COMMONLIBSSE_PLUGIN_MINIMUM_SKSE_VERSION 0)
    endif()

    message("Parsing ADD_COMMONLIBSSE_PLUGIN_MINIMUM_SKSE_VERSION ${ADD_COMMONLIBSSE_PLUGIN_MINIMUM_SKSE_VERSION}")
    commonlibsse_parse_version("${ADD_COMMONLIBSSE_PLUGIN_MINIMUM_SKSE_VERSION}")

    if(NOT COMMONLIBSSE_VERSION_MATCH)
        message(FATAL_ERROR "Unable to parse SKSE minimum SKSE version number "
            "${ADD_COMMONLIBSSE_PLUGIN_MINIMUM_SKSE_VERSION}.")
    endif()

    set(commonlibsse_min_skse_version "REL::Version{ ${COMMONLIBSSE_VERSION_MAJOR}, ${COMMONLIBSSE_VERSION_MINOR}, ${COMMONLIBSSE_VERSION_PATCH}, ${COMMONLIBSSE_VERSION_TWEAK} }")

    # Setup compatibility configuration.
    if(NOT ADD_COMMONLIBSSE_PLUGIN_STRUCT_DEPENDENT)
        set(commonlibsse_plugin_struct_compatibility "SKSE::StructCompatibility::Independent")
    else()
        set(commonlibsse_plugin_struct_compatibility "SKSE::StructCompatibility::Dependent")
    endif()

    if(NOT ADD_COMMONLIBSSE_PLUGIN_USE_SIGNATURE_SCANNING AND NOT DEFINED ADD_COMMONLIBSSE_PLUGIN_COMPATIBLE_RUNTIMES)
        set(ADD_COMMONLIBSSE_PLUGIN_USE_ADDRESS_LIBRARY TRUE)
    endif()

    if(ADD_COMMONLIBSSE_PLUGIN_USE_ADDRESS_LIBRARY OR ADD_COMMONLIBSSE_PLUGIN_USE_SIGNATURE_SCANNING)
        if(DEFINED ADD_COMMONLIBSSE_PLUGIN_COMPATIBLE_RUNTIMES)
            message(FATAL_ERROR "COMPATIBLE_RUNTIMES option should not be used with USE_ADDRESS_LIBRARY or "
                "USE_SIGNATURE_SCANNING")
        endif()

        if(NOT ADD_COMMONLIBSSE_PLUGIN_USE_ADDRESS_LIBRARY)
            set(commonlibsse_plugin_compatibility "VersionIndependence::SignatureScanning")
        else()
            set(commonlibsse_plugin_compatibility "SKSE::VersionIndependence::AddressLibrary")
        endif()
    else()
        list(LENGTH ${ADD_COMMONLIBSSE_PLUGIN_COMPATIBLE_RUNTIMES} commonlibsse_plugin_compatibility_count)

        if(commonlibsse_plugin_compatibility_count GREATER 16)
            message(FATAL_ERROR "No more than 16 version numbers can be provided for COMPATIBLE_RUNTIMES.")
        endif()

        foreach(SKYRIM_VERSION ${ADD_COMMONLIBSSE_PLUGIN_COMPATIBLE_RUNTIMES})
            if(DEFINED commonlibsse_plugin_compatibility)
                set(commonlibsse_plugin_compatibility "${commonlibsse_plugin_compatibility}, ")
            endif()

            commonlibsse_parse_version("${SKYRIM_VERSION}")

            if(NOT COMMONLIBSSE_VERSION_MATCH)
                message(FATAL_ERROR "Unable to parse Skyrim runtime version number ${SKYRIM_VERSION}.")
            endif()

            set(commonlibsse_plugin_compatibility "${commonlibsse_plugin_compatibility}REL::Version{ ${COMMONLIBSSE_VERSION_MAJOR}, ${COMMONLIBSSE_VERSION_MINOR}, ${COMMONLIBSSE_VERSION_PATCH}, ${COMMONLIBSSE_VERSION_TWEAK} }")
        endforeach()

        set(commonlibsse_plugin_compatibility "{ ${commonlibsse_plugin_compatibility} }")
    endif()

    file(WRITE "${commonlibsse_plugin_file}"
        "#include \"REL/Relocation.h\"\n"
        "#include \"SKSE/SKSE.h\"\n"
        "\n"
        "SKSEPluginInfo(\n"
        "    .Version = ${commonlibsse_plugin_version},\n"
        "    .Name = \"${commonlibsse_plugin_name}\"sv,\n"
        "    .Author = \"${ADD_COMMONLIBSSE_PLUGIN_AUTHOR}\"sv,\n"
        "    .SupportEmail = \"${ADD_COMMONLIBSSE_PLUGIN_EMAIL}\"sv,\n"
        "    .StructCompatibility = ${commonlibsse_plugin_struct_compatibility},\n"
        "    .RuntimeCompatibility = ${commonlibsse_plugin_compatibility},\n"
        "    .MinimumSKSEVersion = ${commonlibsse_min_skse_version}\n"
        ")\n")

    target_sources("${TARGET}" PRIVATE "${commonlibsse_plugin_file}")
    target_compile_definitions("${TARGET}" PRIVATE __CMAKE_COMMONLIBSSE_PLUGIN=1)
    target_link_libraries("${TARGET}" PUBLIC CommonLibSSE::CommonLibSSE)
    target_include_directories("${TARGET}" PUBLIC CommonLibSSE_INCLUDE_DIRS)
endfunction()

function(add_commonlibsse_plugin TARGET)
    set(options OPTIONAL USE_ADDRESS_LIBRARY USE_SIGNATURE_SCANNING STRUCT_DEPENDENT EXCLUDE_FROM_ALL)
    set(oneValueArgs NAME AUTHOR EMAIL VERSION MINIMUM_SKSE_VERSION)
    set(multiValueArgs COMPATIBLE_RUNTIMES SOURCES)
    cmake_parse_arguments(PARSE_ARGV 1 ADD_COMMONLIBSSE_PLUGIN "${options}" "${oneValueArgs}"
        "${multiValueArgs}")

    add_library("${TARGET}" SHARED $<$<BOOL:${ADD_COMMONLIBSSE_PLUGIN_EXCLUDE_FROM_ALL}>:EXCLUDE_FROM_ALL>
        ${ADD_COMMONLIBSSE_PLUGIN_SOURCES})
    target_commonlibsse_properties("${TARGET}" ${ARGN})
endfunction()
