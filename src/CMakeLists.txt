add_executable(start
    main.c
)

target_include_directories(start
    PRIVATE
    "${PROJECT_SOURCE_DIR}/include"
)

target_link_libraries(start
    foo
)

add_subdirectory(foo)