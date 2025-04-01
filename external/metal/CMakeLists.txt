# This ThirdParty library copied from https://github.com/LeeTeng2001/metal-cpp-cmake
# Header is available at https://developer.apple.com/metal/cpp

include(FetchContent)
FetchContent_Declare(Metal_CPP
        URL https://developer.apple.com/metal/cpp/files/metal-cpp_macOS15.2_iOS18.2.zip
        )
FetchContent_MakeAvailable(Metal_CPP)

# Library definition
add_library(Metal
        ${CMAKE_CURRENT_SOURCE_DIR}/definition.cpp
        )

# Metal cpp headers
target_include_directories(Metal PUBLIC
        "${metal_cpp_SOURCE_DIR}"
        )

find_library(METAL_LIB Metal)
find_library(FOUNDATION_LIB Foundation)
find_library(QUARTZ_CORE_LIB QuartzCore)

if (NOT METAL_LIB)
  message(FATAL_ERROR "Cannot found Metal library")
else()
  message(STATUS "Using Metal library from ${METAL_LIB}")
endif()

if (NOT FOUNDATION_LIB)
  message(FATAL_ERROR "Cannot found Foundation library")
else()
  message(STATUS "Using Foundation library from ${FOUNDATION_LIB}")
endif()

if (NOT QUARTZ_CORE_LIB)
  message(FATAL_ERROR "Cannot found QuartzCore library")
else()
  message(STATUS "Using QuartzCore library from ${QUARTZ_CORE_LIB}")
endif()

# Metal cpp library (linker)
target_link_libraries(Metal
        ${METAL_LIB}
        ${FOUNDATION_LIB}
        ${QUARTZ_CORE_LIB}
        )
