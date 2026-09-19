cmake_minimum_required(VERSION 3.28)
project(Optimization_Library VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_TESTING "Build the test suite" ON)
add_library(Optimization_Library STATIC)
add_library(Optimization_Library::Optimization_Library ALIAS Optimization_Library)

target_include_directories(Optimization_Library
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/Optimization_Library>
        $<INSTALL_INTERFACE:include>
)

target_sources(Optimization_Library
    PUBLIC
        FILE_SET CXX_MODULES FILES
            include/Optimization_Library/Point.cppm
            include/Optimization_Library/Point/Point_Base.cppm
            include/Optimization_Library/Point/Operators_Base.cppm
            include/Optimization_Library/Point/Point_Operators.cppm
            include/Optimization_Library/Point/Point_Utils.cppm
            include/Optimization_Library/PointValue.cppm
            include/Optimization_Library/PointValue/PointValue_Base.cppm
            include/Optimization_Library/PointValue/PointValue_Utils.cppm
)

target_compile_features(Optimization_Library PUBLIC cxx_std_20)

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()