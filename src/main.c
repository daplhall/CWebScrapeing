#include "scraper.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/typecheck-gcc.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int
write_html (const HtmlData data, const char *fname)
{
	FILE *file;
	if (!(file = fopen (fname, "w"))) {
		fprintf (stderr, "error: file %s couldn't open, errno %d\n",
			 fname, errno);
		return 0;
	} else {
		fputs (HtmlData_get (data), file);
	}

	fclose (file);
	return 1;
}
int
main (int argc, char *argv[])
{
	curl_global_init (CURL_GLOBAL_ALL);
	HtmlData html;
	html = HtmlData_create ();
	Scrape_html ("https://example.com", &html);
	write_html (html, "example.html");
	HtmlData_destroy (html);
	curl_global_cleanup ();
	return EXIT_SUCCESS;
}
