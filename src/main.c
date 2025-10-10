#include "scraper.h"
#include <curl/curl.h>
#include <libxml/HTMLparser.h>
#include <stdbool.h>
#include <stdlib.h>

int
main (int argc, char *argv[])
{
	struct HtmlData htmlbuf;

	curl_global_init (CURL_GLOBAL_ALL);
	HtmlData_init (&htmlbuf);

	if (!(Scrape_html ("https://daplhall.github.io/about.html",
			   &htmlbuf))) {
		fprintf (stderr, "Scraping Failed!\n");
		return EXIT_FAILURE;
	}
	printf ("%s\n", htmlbuf.data);
	HtmlData_cleanup (&htmlbuf);
	curl_global_cleanup ();
	return EXIT_SUCCESS;
}
