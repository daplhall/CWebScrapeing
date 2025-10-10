#include "scraper.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define NULLTERMBYTE 1

size_t
memory_callback (void *ptr, size_t size, size_t nmemb, void *userdata)
{
	size_t data_size = size * nmemb;
	HtmlData *data = (HtmlData *)userdata;
	char *html;

	html = (char *)malloc (data_size + NULLTERMBYTE);
	html[data_size] = '\0';
	memcpy (html, (char *)ptr, data_size);
	HtmlData_set (*data, html);
	return data_size;
}

int
Scrape_html (const char *website, HtmlData *data)
{
	CURL *handle;
	if ((handle = curl_easy_init ())) {
		CURLcode err;
		curl_easy_setopt (handle, CURLOPT_NOSIGNAL, 1L);
		curl_easy_setopt (handle, CURLOPT_WRITEFUNCTION,
				  memory_callback);
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
