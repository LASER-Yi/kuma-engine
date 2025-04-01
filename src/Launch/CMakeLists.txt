project(Launch)

search_files_simple(common Common)

if (APPLE)
    search_files_simple(platform Mac)
elseif(WIN32)
    search_files_simple(platform Windows)
else()
    message(FATAL_ERROR "Unsupported platform")
endif()


add_executable(${PROJECT_NAME} 
        ${common_found_sources} 
        ${platform_found_sources} 
    )

target_include_directories(${PROJECT_NAME} PUBLIC 
        ${common_found_dirs}
        ${platform_found_dirs}
    )

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
