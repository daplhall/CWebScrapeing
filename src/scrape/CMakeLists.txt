add_library(scrape
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
####### Robotstxt (CPP)
add_library(robotstxt
    robotstxt.cpp
)

target_include_directories(robotstxt
    PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
)

target_link_libraries(robotstxt
    PRIVATE
    robots
    scrape
)