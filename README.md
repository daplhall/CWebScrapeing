# Prerequisites
The program needs `libcurl` and `tidy`

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