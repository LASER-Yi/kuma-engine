project(Launch)

search_files()

add_executable(${PROJECT_NAME} ${found_sources} ${found_headers})

target_include_directories(${PROJECT_NAME} PUBLIC ${found_header_dirs})

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
