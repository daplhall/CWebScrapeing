#include "scraper.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <tidy.h>

#define NULLTERMBYTE 1

size_t
callback_tidy (void *ptr, size_t size, size_t nmemb, void *userdata)
{
	size_t ndata = size * nmemb;
	TidyBuffer *data = (TidyBuffer *)userdata;
	tidyBufAppend (data, ptr, ndata);
	return ndata;
}

int
Scrape_html (const char *website, TidyBuffer *data)
{
	CURL *handle;
	if ((handle = curl_easy_init ())) {
		CURLcode err;
		curl_easy_setopt (handle, CURLOPT_NOSIGNAL, 1L);
		curl_easy_setopt (handle, CURLOPT_WRITEFUNCTION, callback_tidy);
		curl_easy_setopt (handle, CURLOPT_WRITEDATA, (void *)data);
		curl_easy_setopt (handle, CURLOPT_URL, website);
		if ((err = curl_easy_perform (handle)) != CURLE_OK) {
			fprintf (stderr, "error: %s \n",
				 curl_easy_strerror (err));
			return 0;
		}
		curl_easy_cleanup (handle);
	}
	return 1;
}
