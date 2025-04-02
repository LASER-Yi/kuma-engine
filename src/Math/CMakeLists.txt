project(Math)

search_files()

add_library(${PROJECT_NAME} ${found_sources} ${found_headers})

target_include_directories(${PROJECT_NAME} PUBLIC ${found_header_dirs})
target_include_directories(${PROJECT_NAME} PRIVATE ${found_source_dirs})
