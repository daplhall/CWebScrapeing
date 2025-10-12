set(CMAKE_C_FLAGS $ENV{SCRAPE_C_FLAGS})


add_executable(scraper
    main.c
    scrape/htmldata.c
    scrape/scraper.c
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


###### cpp testing
add_executable(main_cpp
    main.cpp
    scrape/htmldata.c
    scrape/scraper.c
    scrape/xmlhelpers.c
)

target_include_directories(main_cpp
    PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
)

target_link_libraries(main_cpp
    PRIVATE
    robots
    CURL::libcurl
    LibXml2::LibXml2
)