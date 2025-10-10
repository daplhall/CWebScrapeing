#pragma once
#include <stddef.h>

struct html_data {
	char *html;
	size_t size;
};

size_t memory_callback (void *ptr, size_t size, size_t nmemb, void *userdata);