#include "foo/main.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/typecheck-gcc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NULLTERMBYTE 1

struct html_data {
	char *html;
	size_t size;
};

size_t memory_callback (void *ptr, size_t size, size_t nmemb, void *userdata);

int
main (int argc, char *argv[])
{

	CURL *handle;
	struct html_data data;

	curl_global_init (CURL_GLOBAL_ALL);
	if ((handle = curl_easy_init ())) {
		CURLcode res;
		// V| avoids race cond, i need to beable to hande SIGPIPE
		curl_easy_setopt (handle, CURLOPT_NOSIGNAL, 1L);
		curl_easy_setopt (handle, CURLOPT_WRITEFUNCTION,
				  memory_callback);
		curl_easy_setopt (handle, CURLOPT_WRITEDATA, (void *)&data);
		curl_easy_setopt (handle, CURLOPT_URL, "https://example.com");

		if ((res = curl_easy_perform (handle)) != CURLE_OK) {
			fprintf (stderr, "error: %s \n",
				 curl_easy_strerror (res));
		} else {
			printf ("data packet size: %lu\n"
				"HTML:%s\n",
				data.size, data.html);
		}
	}
	return EXIT_SUCCESS;
}

size_t
memory_callback (void *ptr, size_t size, size_t nmemb, void *userdata)
{
	size_t data_size = size * nmemb;
	struct html_data *data = (struct html_data *)userdata;
	char *html;

	html = (char *)malloc (data_size + NULLTERMBYTE);
	memcpy (html, (char *)ptr, data_size);
	data->html = html;
	data->size = data_size;

	return data_size;
}
