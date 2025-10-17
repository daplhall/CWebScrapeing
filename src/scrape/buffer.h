#ifndef INTERNAL_SCRAPE_BUFFER_H
#define INTERNAL_SCRAPE_BUFFER_H

#include <stddef.h>
struct chrbuf {
	char *ptr;
	size_t indx;
	size_t len;
};

void Buffer_init (struct chrbuf *buf, size_t len);
void Buffer_cleanup (struct chrbuf *buf);
void Buffer_insert_char (struct chrbuf *buf, char inpt);
void Buffer_clear (struct chrbuf *buf);
char *Buffer_flush (struct chrbuf *buf);
char *Buffer_find (struct chrbuf *buf, char c);

#endif // INTERNAL_SCRAPE_BUFFER_H
