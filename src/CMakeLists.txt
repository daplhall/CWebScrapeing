add_executable(scraper
    main.c
)

target_include_directories(scraper
    PRIVATE
    "${PROJECT_SOURCE_DIR}/include"
)

target_link_libraries(scraper
    curl
    foo
)

add_subdirectory(foo)