cmake_minimum_required(VERSION 3.21)

project(
        CommonLibSSESamplePlugin
        VERSION 1.0.0
        DESCRIPTION "A sample SKSE plugin built with CommonLibSSE."
        LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CommonLibSSE CONFIG REQUIRED)

add_commonlibsse_plugin(${PROJECT_NAME} SOURCES Main.cpp)
