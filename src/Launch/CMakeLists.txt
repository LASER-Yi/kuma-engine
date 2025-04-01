project(Launch)

include(CompileTarget)
include(PlatformMacros)

add_executable(${PROJECT_NAME} ${TARGET_SOURCES} ${TARGET_HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${TARGET_HEADERS_DIR})

set(LINK_LIBRARIES Runtime)

if (APPLE)
list(APPEND LINK_LIBRARIES "-framework AppKit")
endif()

if (MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC ${LINK_LIBRARIES})
