add_executable(scraper
    main.c
    htmldata.c
    scraper.c
)


target_link_libraries(scraper
    curl
)

target_include_directories(scraper
    PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
)