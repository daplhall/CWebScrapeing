add_library(scrape
    htmldata.c
    scraper.c
    xmlhelpers.c
)

target_link_libraries(scrape
    PUBLIC
    CURL::libcurl
    LibXml2::LibXml2
    robotstxt
)

target_include_directories(scrape
    PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
)

add_library(
    robotstxt
    robotstxt.cpp
)

target_link_libraries(robotstxt
    PRIVATE
    robots
    scrape
)