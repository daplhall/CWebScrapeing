#include "foo/callback.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/typecheck-gcc.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main (int argc, char *argv[])
{

	CURL *handle;
	struct html_data data;

	curl_global_init (CURL_GLOBAL_ALL);
	if ((handle = curl_easy_init ())) {
		CURLcode res;
		// V| avoids race cond, i need to beable to handle SIGPIPE
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
