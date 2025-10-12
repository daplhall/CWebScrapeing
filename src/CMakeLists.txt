set(CMAKE_C_FLAGS "${SCRAPE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${SCRAPE_CXX_FLAGS}")
add_executable(webscraper
    main.c
)


target_link_libraries(webscraper
    PRIVATE
    scrape
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

add_subdirectory(scrape)