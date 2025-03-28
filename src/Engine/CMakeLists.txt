project(Engine)

include(CompileTarget)
include(PlatformMacros)

add_library(${PROJECT_NAME} ${TARGET_SOURCES} ${TARGET_HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${TARGET_HEADERS_DIR})

target_include_directories(${PROJECT_NAME} INTERFACE ${GLFW_INCLUDE_DIR})
