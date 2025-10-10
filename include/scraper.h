#ifndef SCRAPER_SCRAPING_H
#define SCRAPER_SCRAPING_H
#ifdef __cplusplus
extern C
{
#endif
#include "htmldata.h"
	int Scrape_html (const char *website, HtmlData *data);
#ifdef __cplusplus
}
#endif
#endif // SCRAPER_SCRAPING_H
