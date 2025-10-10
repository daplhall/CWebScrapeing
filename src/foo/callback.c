#include "foo/callback.h"
#include <errno.h>
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
	return data_size;
}

int
write_html (const struct html_data *data, const char *fname)
{
	FILE *file;
	if (!(file = fopen (fname, "w"))) {
		fprintf (stderr, "error: file %s couldn't open, errno %d\n",
			 fname, errno);
		return 0;
	} else {
		fputs (data->html, file);
	}

	fclose (file);
	return 1;
}
