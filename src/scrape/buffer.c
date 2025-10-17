#include "buffer.h"
#include <assert.h>
#include <scrape/url.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define T	    url
#define BUFINITSIZE 256

void
Buffer_init (struct chrbuf *buf, size_t len)
{
	assert (len > 0);
	buf->ptr = (char *)malloc (sizeof (char) * len);
	buf->len = len;
	buf->indx = 0;
	buf->ptr[buf->indx] = '\0';
}

void
Buffer_cleanup (struct chrbuf *buf)
{
	free (buf->ptr);
	buf->len = 0;
	buf->indx = 0;
}

void
Buffer_insert_char (struct chrbuf *buf, char inpt)
{
	if (buf->indx >= buf->len - 1) // need error check
		buf->ptr = realloc (buf->ptr,
				    sizeof (char) * (buf->len + BUFINITSIZE));
	buf->ptr[buf->indx++] = inpt;
	buf->ptr[buf->indx] = '\0';
}

void
Buffer_clear (struct chrbuf *buf)
{
	buf->indx = 0;
	buf->ptr[buf->indx] = '\0';
}

char *
Buffer_flush (struct chrbuf *buf)
{
	char *retrn;
	retrn = (char *)malloc (sizeof (*retrn) * buf->indx + 1);
	strcpy (retrn, buf->ptr);
	Buffer_clear (buf);
	return retrn;
}

char *
Buffer_find (struct chrbuf *buf, char c)
{
	return strchr (buf->ptr, c);
}
