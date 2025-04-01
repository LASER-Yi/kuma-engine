
function(search_library lib_var lib_name)
    set(LIBRARY_CACHE_VAR ${lib_var}_VAR)
    find_library(${LIBRARY_CACHE_VAR} ${lib_name})

    if (NOT ${lib_var}_VAR)
        message(FATAL_ERROR "Cannot found ${lib_name} library")
    else()
        message(STATUS "Using ${lib_name} library from ${${LIBRARY_CACHE_VAR}}")
    endif()

    set(${lib_var} ${${LIBRARY_CACHE_VAR}} PARENT_SCOPE)
endfunction()
