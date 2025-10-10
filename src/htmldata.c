#include "htmldata.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NULLTERMSIZE 1
#define T	     HtmlData

struct T {
	char *data; // should be null terminated
	size_t len;
};

struct T *
HtmlData_create (void)
{
	struct T *new;
	if (!(new = malloc (sizeof (*new)))) {
		fprintf (stderr, "error: HtmlData could not be allocated\n");
		return NULL;
	}
	new->data = 0;
	new->len = 0;
	return new;
}

void
HtmlData_destroy (struct T *html)
{
	assert ((html != NULL) && "Null pointer sent to");
	free (html->data);
	free (html);
}

char *
HtmlData_get (struct T *html)
{
	assert ((html->data != NULL)
		&& "You are attempting to fetch html that doesn't exist");
	return html->data;
}

/*
 * Transfers ownership of inpt to HtmlData
 */
void
HtmlData_set (struct T *html, char *inpt)
{
	html->data = inpt;
	html->len = strlen (inpt) + NULLTERMSIZE;
}
