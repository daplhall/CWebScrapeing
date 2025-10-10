#include "scraper.h"
#include "htmldata.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define NULLTERMBYTE 1

size_t
callback_html (void *ptr, size_t size, size_t nmemb, struct HtmlData *userdata)
{
	struct HtmlData *data = (struct HtmlData *)userdata;
	size_t req_size = size * nmemb;
	size_t newsize = data->size + req_size;
	char *new;

	if (!(new = (char *)realloc (data->data, newsize + 1))) {
		fprintf (stderr, "Not enough memory (realloc)\n");
		return 0;
	}
	data->data = new;
	memcpy (&data->data[data->size], (char *)ptr, req_size);
	data->size = newsize;
	data->data[data->size] = '\0';
	return req_size;
}

int
Scrape_html (const char *website, struct HtmlData *data)
{
	CURL *handle;
	if ((handle = curl_easy_init ())) {
		CURLcode err;
		curl_easy_setopt (handle, CURLOPT_NOSIGNAL, 1L);
		curl_easy_setopt (handle, CURLOPT_WRITEFUNCTION, callback_html);
		curl_easy_setopt (handle, CURLOPT_WRITEDATA, (void *)data);
		curl_easy_setopt (handle, CURLOPT_URL, website);
		if ((err = curl_easy_perform (handle)) != CURLE_OK) {
			fprintf (stderr, "error: %s \n",
				 curl_easy_strerror (err));
			curl_easy_cleanup (handle);
			return 0;
		}
		curl_easy_cleanup (handle);
	}
	return 1;
}
