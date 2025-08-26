cmake_minimum_required(VERSION 3.15)

project(libcx LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE libcxSources CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

add_library(libcx STATIC ${libcxSources})

target_include_directories(libcx
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(libcx PRIVATE -nostdlib++)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(libcx PRIVATE 
        -Wall 
        -Wextra 
        -Werror 
        -pedantic
        -fno-exceptions
        -fno-rtti
    )
elseif (MSVC)
    target_compile_options(libcx PRIVATE 
        /W4 
        /WX
        /EHs
        /GR-
    )
endif()

include(FetchContent)
FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.6.0
)

FetchContent_MakeAvailable(catch2)

set(libcxTestsSources
    tests/arena.cpp
    tests/alloc.cpp
    tests/mem.cpp
    tests/array_list.cpp
)

add_executable(libcxTests ${libcxTestsSources})
target_link_libraries(libcxTests PRIVATE
    libcx
    Catch2::Catch2WithMain
)

target_precompile_headers(libcxTests PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/pch.h
)

include(CTest)
include(Catch)
catch_discover_tests(libcxTests)
