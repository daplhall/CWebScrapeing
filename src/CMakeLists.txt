add_executable(scraper
    main.c
    htmldata.c
    scraper.c
    scraping_course.c
    stack.c
)


target_link_libraries(scraper
    CURL::libcurl
    LibXml2::LibXml2
)

target_include_directories(scraper
    PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
)