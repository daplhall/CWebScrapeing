#include "scrape/url.h"
#include <curl/curl.h>
#include <scrape/robotstxt.h>
#include <stdbool.h>

int
main (int argc, char *argv[])
{
	struct url_T data;
	/*
	char const url[] = "file:///home/danielph/Documents/programming/repos/"
			   "daplhall.github.io/index.html";
   */
	char const url[]
	    = "https://password@daplhall.github.io:2424/dicechanics/"
	      "api.html#dicechanics.pool";
	Url_init (&data);
	Url_parse (url, &data);
	Url_print (&data);
	Url_cleanup (&data);
}
