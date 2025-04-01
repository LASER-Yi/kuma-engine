project(Launch)

include(CompileTarget)
include(PlatformMacros)

add_executable(${PROJECT_NAME} ${TARGET_SOURCES} ${TARGET_HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${TARGET_HEADERS_DIR})

set(LINK_LIBRARIES Runtime)

if (APPLE)
find_library(APPKIT_LIB AppKit)

if (NOT APPKIT_LIB)
  message(FATAL_ERROR "Cannot found AppKit library")
else()
  message(STATUS "Using AppKit library from ${APPKIT_LIB}")
endif()

target_include_directories(${PROJECT_NAME} PRIVATE "${APPKIT_LIB}/Headers")

list(APPEND LINK_LIBRARIES ${APPKIT_LIB})
endif()

if (MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC ${LINK_LIBRARIES})
