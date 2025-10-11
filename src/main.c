#include "scraping_course.h"
#include <curl/curl.h>
#include <libxml/HTMLparser.h>
#include <libxml/HTMLtree.h>
#include <libxml/xpath.h>
#include <stdbool.h>
#include <stdlib.h>

int
main (int argc, char *argv[])
{
	curl_global_init (CURL_GLOBAL_ALL);
	ecommernce ();
	curl_global_cleanup ();
	return EXIT_SUCCESS;
}
