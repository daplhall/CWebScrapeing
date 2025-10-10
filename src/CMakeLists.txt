add_executable(scraper
    main.c
)


target_link_libraries(scraper
    curl
    foo
)

add_subdirectory(foo)