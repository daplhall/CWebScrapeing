# Prerequisites
The program needs `libcurl` and `tidy`

# Program steps
1. Scraping
2. Proccesing
3. Transfer

# interface
ADT: Scraper
ADT: HtmlData // just a data structure

Scraper_html(string "<webpage>", out : HtmlData*)
Scraper_create()
Scraper_free()

HtmlData_create()
HtmlData_free()
HtmlData_get() -> string html
HtmlData_set(string html)

# CLangd

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1