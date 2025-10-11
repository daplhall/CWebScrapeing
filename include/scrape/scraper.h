#ifndef SCRAPER_SCRAPING_H
#define SCRAPER_SCRAPING_H
#ifdef __cplusplus
extern C
{
#endif
#include "htmldata.h"
#include <libxml/xpath.h>
	typedef void (*Scrape_callback) (xmlXPathContextPtr context);

	struct Scrape_expr_data {
		xmlXPathObjectPtr *exprs;
		size_t size;
		xmlDoc *doc;
		xmlXPathContextPtr context;
	};

	void Scrape_expr_data_init (struct Scrape_expr_data * inpt,
				    size_t nexpr);
	void Scrape_expr_data_cleanup (struct Scrape_expr_data * inpt);
	int Scrape_html (const char *site, struct HtmlData *data);
	int Scrape_eval_expr (struct HtmlData * rawhtml, char const *exprs[],
			      size_t nexpr, struct Scrape_expr_data *out);
	int Scrape_website (char const *site, char const *expr[], size_t nexpr,
			    struct Scrape_expr_data *out);
	int Scrape_proccess (char const *website, char const *expr[],
			     Scrape_callback callbacks[], size_t nexpr);

#ifdef __cplusplus
}
#endif
#endif // SCRAPER_SCRAPING_H
