#include "scraping_course.h"
#include "scraper.h"
#include "stack.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define FAILURE 0
#define SUCCESS 1

static void
fetch_data (struct Scrape_expr_data *object, Stack out)
{
	xmlXPathObjectPtr test = *object->objects; // tmp
	xmlXPathObjectPtr evalexpr;
	xmlXPathContextPtr context = object->context;
	xmlNodePtr datanode = test->nodesetval->nodeTab[0];
	xmlNodePtr node;
	char *url;

	xmlXPathSetContextNode (datanode, context);
	evalexpr = xmlXPathEvalExpression ((xmlChar *)".//a", context);
	node = evalexpr->nodesetval->nodeTab[0];
	url = (char *)xmlGetProp (node, (xmlChar *)"href");
	printf ("%s\n", url);
	free (url);
	xmlXPathFreeObject (evalexpr);
}

int
ecommernce (void)
{
	Stack stack;
	struct Scrape_expr_data expr_objects;
	char const *expr[] = { "//li[contains(@class, 'product')]" };
	size_t nexpr = sizeof (expr) / sizeof (expr[0]);
	stack = Stack_create ();

	Scrape_expr_data_init (&expr_objects, nexpr);
	if (!(Scrape_website ("https://www.scrapingcourse.com/ecommerce/", expr,
			      nexpr, &expr_objects))) {
		fprintf (stderr, "error: Scrape_website failed\n");
		Scrape_expr_data_cleanup (&expr_objects);
		return FAILURE;
	}
	fetch_data (&expr_objects, stack);

	Stack_free (stack);
	Scrape_expr_data_cleanup (&expr_objects);
	return SUCCESS;
}
