set(CMAKE_C_FLAGS "${SCRAPE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${SCRAPE_CXX_FLAGS}")

add_executable(webscraper
    main.c
)

target_link_libraries(webscraper
    PRIVATE
    scrape
)

add_subdirectory(scrape)