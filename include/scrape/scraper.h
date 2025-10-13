#ifndef SCRAPER_SCRAPING_H
#define SCRAPER_SCRAPING_H
#ifdef __cplusplus
extern "C" {
#endif
#include "htmldata.h"
#include <libxml/xpath.h>
typedef void (*Scrape_callback) (xmlXPathContextPtr context);

struct Scrape_instr {
	const char *expr;
	Scrape_callback callback;
};

int Scrape_html (char const *url, struct Scrape_instr instr[static 1],
		 size_t ninstr);
#ifdef __cplusplus
}
#endif
#endif // SCRAPER_SCRAPING_H
