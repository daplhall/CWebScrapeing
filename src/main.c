#include "scrape/scraper.h"
#include "scrape/xmlhelpers.h"
#include <curl/curl.h>
#include <libxml/HTMLparser.h>
#include <libxml/HTMLtree.h>
#include <libxml/xpath.h>
#include <scrape/robotstxt.h>
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
	struct Scrape_instr instructions[]
	    = { { .expr = "//li[contains(@class, 'product')]",
		  .callback = fetch_callback } };
	size_t nexpr = sizeof (instructions) / sizeof (instructions[0]);
	curl_global_init (CURL_GLOBAL_ALL);
	Scrape_proccess ("https://www.scrapingcourse.com/ecommerce/",
			 instructions, nexpr);

	struct HtmlData dump;
	HtmlData_init (&dump);
	Scrape_html ("webpage/robots.txt", &dump);
	printf ("%s", dump.data);
	int a = Scrape_allowed (dump.data, "some_scraper",
				"API or webpage to strip");
	printf ("Allowed? %d\n", a);
	HtmlData_cleanup (&dump);
	curl_global_cleanup ();
	return EXIT_SUCCESS;
}
