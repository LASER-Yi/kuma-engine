function(search_files)

if (DEFINED ARGV0)
    set(EXPORT_PREFIX ${ARGV0})
endif()

if (DEFINED ARGV1)
    set(TARGET_PWD ${ARGV1})
else()
    set(TARGET_PWD ".")
endif()

set(TARGET_SOURCES_DIR "${TARGET_PWD}/Private")
set(TARGET_HEADERS_DIR "${TARGET_PWD}/Public")

file(GLOB_RECURSE TARGET_SOURCES
    "${TARGET_SOURCES_DIR}/*.cpp" "${TARGET_SOURCES_DIR}/*.mm")

file(GLOB_RECURSE TARGET_HEADERS
    "${TARGET_HEADERS_DIR}/*.h" "${TARGET_SOURCES_DIR}/*.h")

if (DEFINED EXPORT_PREFIX)
    set(${EXPORT_PREFIX}_found_headers ${TARGET_HEADERS} PARENT_SCOPE)
    set(${EXPORT_PREFIX}_found_sources ${TARGET_SOURCES} PARENT_SCOPE)
    set(${EXPORT_PREFIX}_found_header_dirs ${TARGET_HEADERS_DIR} PARENT_SCOPE)
    set(${EXPORT_PREFIX}_found_source_dirs ${TARGET_SOURCES_DIR} PARENT_SCOPE)
else()
    set(found_headers ${TARGET_HEADERS} PARENT_SCOPE)
    set(found_sources ${TARGET_SOURCES} PARENT_SCOPE)
    set(found_header_dirs ${TARGET_HEADERS_DIR} PARENT_SCOPE)
    set(found_source_dirs ${TARGET_SOURCES_DIR} PARENT_SCOPE)
endif()
endfunction()


function(search_files_simple)

if (DEFINED ARGV0)
    set(EXPORT_PREFIX ${ARGV0})
endif()

if (DEFINED ARGV1)
    set(TARGET_PWD ${ARGV1})
else()
    set(TARGET_PWD ".")
endif()

file(GLOB_RECURSE TARGET_FILES
        "${TARGET_PWD}/*.cpp"
        "${TARGET_PWD}/*.h"
        "${TARGET_PWD}/*.mm"
    )

if (DEFINED EXPORT_PREFIX)
    set(${EXPORT_PREFIX}_found_sources ${TARGET_FILES} PARENT_SCOPE)
    set(${EXPORT_PREFIX}_found_dirs ${TARGET_PWD} PARENT_SCOPE)
else()
    set(found_sources ${TARGET_FILES} PARENT_SCOPE)
    set(found_dirs ${TARGET_PWD} PARENT_SCOPE)
endif()
endfunction()
