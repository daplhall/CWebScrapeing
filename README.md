# (WIP) A simple webscraper for C
![#f03c15](https://placehold.co/15x15/f03c15/f03c15.png) The project is currently WIP, and as such the README and program is not finished.  

The goal of this project is just to write a scraper in C for the enjoyment.
# Prerequisites
The program needs `libcurl`, `libxml2` and googles `Robotstxt`

# Program steps
1. Scraping
2. Proccesing
3. Transfer

# interface
ADT: Scraper
ADT: HtmlData // just a data structure

Scrape_html
callback_html
find_in_html(xmlXpathQuery);

HtmlData_create()
HtmlData_free()
HtmlData_get() -> string html
HtmlData_set(string html)


scraper_html->proccess_html->search_html

# CLangd

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1
