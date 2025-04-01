cmake_minimum_required(VERSION 3.20)

project(kuma-engine
    VERSION 0.1.0
    LANGUAGES CXX OBJCXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")


# Avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP in CMake 3.24:
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
  cmake_policy(SET CMP0135 NEW)
endif()

list(APPEND CMAKE_MODULE_PATH 
    "${CMAKE_CURRENT_SOURCE_DIR}/CMake"
    "${CMAKE_CURRENT_SOURCE_DIR}/CMake/modules"
    )

include(Common)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# BEGIN - Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/52204f78f94d7512df1f0f3bea1d47437a2c3a58.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
# END - Google Test

# add subdirectories
add_subdirectory(external)
add_subdirectory(src)
