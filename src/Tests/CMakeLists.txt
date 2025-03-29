project(Tests)

set(TARGET_CASES_DIR "Cases")

file(GLOB_RECURSE TARGET_SOURCES
    "${TARGET_CASES_DIR}/*.cpp")

enable_testing()

add_executable(${PROJECT_NAME} ${TARGET_SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC
    Runtime
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
