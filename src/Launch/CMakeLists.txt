project(Launch)

search_files()

add_executable(${PROJECT_NAME} ${found_sources} ${found_headers})

target_include_directories(${PROJECT_NAME} PUBLIC ${found_header_dirs})

set(LINK_LIBRARIES Runtime)

if (APPLE)
search_library(APPKIT_LIB AppKit)

target_include_directories(${PROJECT_NAME} PRIVATE "${APPKIT_LIB}/Headers")

list(APPEND LINK_LIBRARIES ${APPKIT_LIB})
endif()

if (MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC ${LINK_LIBRARIES})
