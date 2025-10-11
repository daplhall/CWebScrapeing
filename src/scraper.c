#include "scraper.h"
#include "htmldata.h"
#include <assert.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <libxml/HTMLparser.h>
#include <libxml/HTMLtree.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NULLTERMBYTE 1
#define SUCCESS	     1
#define FAILURE	     0

void
Scrape_expr_data_init (struct Scrape_expr_data *inpt, size_t nexpr)
{
	inpt->objects
	    = (xmlXPathObjectPtr *)malloc (sizeof (xmlXPathContextPtr) * nexpr);
	inpt->size = nexpr;
	inpt->context = NULL;
	inpt->doc = NULL;
}

void
Scrape_expr_data_cleanup (struct Scrape_expr_data *inpt)
{
	xmlXPathObjectPtr *ptr = inpt->objects;
	size_t nexpr = inpt->size;
	while (nexpr--)
		xmlXPathFreeObject (*ptr++);
	free (inpt->objects);
	if (inpt->context)
		xmlXPathFreeContext (inpt->context);
	inpt->size = 0;
}

static size_t
callback_html (void *ptr, size_t size, size_t nmemb, void *userdata)
{
	struct HtmlData *data = (struct HtmlData *)userdata;
	size_t req_size = size * nmemb;
	size_t newsize = data->size + req_size;
	char *new;

	if (!(new = (char *)realloc (data->data, newsize + 1))) {
		fprintf (stderr, "Not enough memory (realloc)\n");
		return 0;
	}
	data->data = new;
	memcpy (&data->data[data->size], (char *)ptr, req_size);
	data->size = newsize;
	data->data[data->size] = '\0';
	return req_size;
}

int
Scrape_html (const char *site, struct HtmlData *rawhtml)
{
	CURL *handle;
	if ((handle = curl_easy_init ())) {
		CURLcode err;
		curl_easy_setopt (handle, CURLOPT_NOSIGNAL, 1L);
		curl_easy_setopt (handle, CURLOPT_WRITEFUNCTION, callback_html);
		curl_easy_setopt (handle, CURLOPT_WRITEDATA, (void *)rawhtml);
		curl_easy_setopt (handle, CURLOPT_URL, site);
		if ((err = curl_easy_perform (handle)) != CURLE_OK) {
			fprintf (stderr, "error: %s \n",
				 curl_easy_strerror (err));
			curl_easy_cleanup (handle);
			return FAILURE;
		}
		curl_easy_cleanup (handle);
	}
	return SUCCESS;
}

int
Scrape_eval_expr (struct HtmlData *rawhtml, char const *exprs[], size_t nexpr,
		  struct Scrape_expr_data *out)
{
	xmlXPathObjectPtr *iter;
	char const **instr = exprs;

	assert (nexpr > 0);
	out->doc = htmlReadMemory (rawhtml->data, rawhtml->size, NULL, "utf-8",
				   HTML_PARSE_NOERROR);
	out->context = xmlXPathNewContext (out->doc);
	iter = out->objects;
	do {
		*iter++
		    = xmlXPathEvalExpression ((xmlChar *)*instr, out->context);
	} while (++instr < exprs + nexpr);

	return SUCCESS;
}

int
Scrape_website (char const *site, char const *expr[], size_t nexpr,
		struct Scrape_expr_data *out)
{
	struct HtmlData html;
	HtmlData_init (&html);
	if (!(Scrape_html (site, &html))) {
		fprintf (stderr, "error: Scraping the website failed\n");
		return FAILURE;
	}
	Scrape_eval_expr (&html, expr, nexpr, out);
	HtmlData_cleanup (&html);
	return SUCCESS;
}
