#pragma once
#include <stddef.h>

struct html_data {
	char *html;
	size_t size;
};

size_t memory_callback (void *ptr, size_t size, size_t nmemb, void *userdata);
int write_html (const struct html_data *data, const char *fname);
