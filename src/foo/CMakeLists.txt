add_library(foo
    callback.c
)

target_include_directories(foo
    PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
)