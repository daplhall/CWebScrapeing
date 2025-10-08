add_library(foo
    main.c
)

target_compile_options(foo
    PRIVATE
    -g3
    -O0
)
