#include "foo/callback.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NULLTERMBYTE 1

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
	uint i = 0;
	for (; i < 0xffffffaa; i++)
		;
	return data_size;
}
