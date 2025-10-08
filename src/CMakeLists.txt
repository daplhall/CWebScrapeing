add_executable(start
    main.c
)

target_include_directories(start
    PRIVATE
    ../include
)

target_link_libraries(start
    foo
)

target_compile_options(start
    PRIVATE
    -g3
    -O0
)

add_subdirectory(foo)