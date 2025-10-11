#include "scrape/scraper.h"
#include "scrape/xmlhelpers.h"
#include <curl/curl.h>
#include <libxml/HTMLparser.h>
#include <libxml/HTMLtree.h>
#include <libxml/xpath.h>
#include <stdbool.h>
#include <stdlib.h>

void
fetch_callback (xmlXPathContextPtr context)
{
	char *url, *img, *name, *price;
	// url
	url = Scraper_xmlGetProp (context, (xmlChar *)".//a",
				  (xmlChar *)"href");
	// Img
	img = Scraper_xmlGetProp (context, (xmlChar *)".//a/img",
				  (xmlChar *)"src");
	// name
	name = Scraper_xmlGetContent (context, (xmlChar *)".//a/h2");
	// price
	price = Scraper_xmlGetContent (context, (xmlChar *)".//a/span");
	// Clean up
	printf ("%s\n", url);
	printf ("\t%s\n", img);
	printf ("\t%s\n", name);
	printf ("\t%s\n", price);
	free (url);
	free (img);
	free (name);
	free (price);
}

int
main (int argc, char *argv[])
{
	char const *expr[] = { "//li[contains(@class, 'product')]" };
	size_t nexpr = sizeof (expr) / sizeof (expr[0]);
	curl_global_init (CURL_GLOBAL_ALL);
	Scrape_proccess ("https://www.scrapingcourse.com/ecommerce/", expr,
			 nexpr, fetch_callback);
	curl_global_cleanup ();
	return EXIT_SUCCESS;
}
