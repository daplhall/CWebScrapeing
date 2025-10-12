add_executable(scraper
    main.c
    scrape/htmldata.c
    scrape/scraper.c
    stack.c
    scrape/xmlhelpers.c
)

target_link_libraries(scraper
    CURL::libcurl
    LibXml2::LibXml2
)

target_include_directories(scraper
    PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
)
