set(CMAKE_C_FLAGS "${SCRAPE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${SCRAPE_CXX_FLAGS}")

add_executable(tests
    test_main.cpp
    scrape.cpp
)

target_link_libraries(tests
    PRIVATE
    scrape
    GTest::gtest_main
)

set_target_properties(tests PROPERTIES CXX_STANDARD 17)
target_compile_definitions(tests PUBLIC TESTPATH="${CMAKE_CURRENT_BINARY_DIR}")
target_compile_definitions(tests PUBLIC ROOTPATH="${CMAKE_SOURCE_DIR}")

target_include_directories(tests
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/fixtures
)

