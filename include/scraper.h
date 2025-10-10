#ifndef SCRAPER_SCRAPING_H
#define SCRAPER_SCRAPING_H
#ifdef __cplusplus
extern C
{
#endif
#include <tidybuffio.h>
	int Scrape_html (const char *website, TidyBuffer *data);
#ifdef __cplusplus
}
#endif
#endif // SCRAPER_SCRAPING_H
