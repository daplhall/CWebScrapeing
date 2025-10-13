cmake_minimum_required(VERSION 4.1.2)

project(libcurl_exercise
    LANGUAGES
    C
    CXX
)

enable_testing()
include(dependencies.cmake)
add_subdirectory(src)
if(TESTING_ENABLED OR PROJECT_IS_TOP_LEVEL)
    add_subdirectory(tests)
endif()