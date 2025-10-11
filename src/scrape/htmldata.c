#include "scrape/htmldata.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#define NULLTERMSIZE 1
#define T	     HtmlData

void
HtmlData_init (struct T *inpt)
{
	assert (inpt != NULL);
	inpt->data = (char *)malloc (1);
	*inpt->data = '\0';
	inpt->size = 0;
}

void
HtmlData_cleanup (struct T *html)
{
	assert ((html != NULL) && (html->data != NULL));
	free (html->data);
	html->size = 0;
}
