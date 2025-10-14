#include "scrape/url.h"
#include <assert.h>
#include <scrape/url.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define T	    url
#define BUFINITSIZE 256

struct chrbuf {
	char *ptr;
	size_t indx;
	size_t len;
};

static void
Buffer_init (struct chrbuf *buf, size_t len)
{
	assert (len > 0);
	buf->ptr = (char *)malloc (sizeof (char) * len);
	buf->len = len;
	buf->indx = 0;
	buf->ptr[buf->indx] = '\0';
}

static void
Buffer_cleanup (struct chrbuf *buf)
{
	free (buf->ptr);
	buf->len = 0;
	buf->indx = 0;
}

static void
Buffer_insert_char (struct chrbuf *buf, char inpt)
{
	if (buf->indx >= buf->len - 1) // need error check
		buf->ptr = realloc (buf->ptr,
				    sizeof (char) * (buf->len + BUFINITSIZE));
	buf->ptr[buf->indx++] = inpt;
	buf->ptr[buf->indx] = '\0';
}

static void
Buffer_clear (struct chrbuf *buf)
{
	buf->indx = 0;
	buf->ptr[buf->indx] = '\0';
}

static char *
Buffer_flush (struct chrbuf *buf)
{
	char *retrn;
	retrn = (char *)malloc (sizeof (*retrn) * buf->indx + 1);
	strcpy (retrn, buf->ptr);
	Buffer_clear (buf);
	return retrn;
}

static void
parse_url (char const *url, struct T *retrn)
{
	struct chrbuf buf;
	Buffer_init (&buf, 1);
	Buffer_cleanup (&buf);
}

void
Url_init (char const *url, struct T *init)
{
	parse_url ("", init);
}

void
Url_cleanup (struct T *url)
{
	free (url->scheme);
	url->scheme = NULL;
	free (url->userinfo);
	url->userinfo = NULL;
	free (url->host);
	url->host = NULL;
	free (url->port);
	url->port = NULL;
	free (url->path);
	url->path = NULL;
	free (url->query);
	url->query = NULL;
	free (url->fragment);
	url->fragment = NULL;
}
