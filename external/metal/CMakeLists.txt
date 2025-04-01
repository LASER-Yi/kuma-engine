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

# Metal cpp library (linker)
target_link_libraries(Metal
        "-framework Metal"
        "-framework Foundation"
        "-framework QuartzCore"
        )
