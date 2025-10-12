#include "scrape/scraper.h"
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
	inpt->exprs
	    = (xmlXPathObjectPtr *)malloc (sizeof (xmlXPathContextPtr) * nexpr);
	inpt->size = nexpr;
	inpt->context = NULL;
	inpt->doc = NULL;
}

void
Scrape_expr_data_cleanup (struct Scrape_expr_data *inpt)
{
	xmlXPathObjectPtr *ptr = inpt->exprs;
	size_t nexpr = inpt->size;
	while (nexpr--)
		xmlXPathFreeObject (*ptr++);
	free (inpt->exprs);
	if (inpt->context)
		xmlXPathFreeContext (inpt->context);
	inpt->size = 0;
}

static size_t
callback_txt (void *ptr, size_t size, size_t nmemb, void *userdata)
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
		curl_easy_setopt (handle, CURLOPT_WRITEFUNCTION, callback_txt);
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
Scrape_eval_expr (struct HtmlData *rawhtml, struct Scrape_instr exprs[],
		  size_t nexpr, struct Scrape_expr_data *out)
{
	xmlXPathObjectPtr *out_iter;
	struct Scrape_instr *instr = exprs;

	assert (nexpr > 0);
	out->doc = htmlReadMemory (rawhtml->data, rawhtml->size, NULL, "utf-8",
				   HTML_PARSE_NOERROR);
	out->context = xmlXPathNewContext (out->doc);
	out_iter = out->exprs;
	do {
		*out_iter++ = xmlXPathEvalExpression ((xmlChar *)instr->expr,
						      out->context);
	} while (++instr < exprs + nexpr);

	return SUCCESS;
}

int
Scrape_website (char const *site, struct Scrape_instr instr[], size_t nexpr,
		struct Scrape_expr_data *out)
{
	struct HtmlData html;
	HtmlData_init (&html);
	if (!(Scrape_html (site, &html))) {
		fprintf (stderr, "error: Scraping the website failed\n");
		return FAILURE;
	}
	Scrape_eval_expr (&html, instr, nexpr, out);
	HtmlData_cleanup (&html);
	return SUCCESS;
}

static void
fetch_data (struct Scrape_expr_data *object,
	    struct Scrape_instr instr[static 1])
{
	size_t remaining = object->size;
	xmlXPathObjectPtr *iter = object->exprs;
	struct Scrape_instr *instructiter = instr;
	while (remaining--) {
		xmlXPathContextPtr context = object->context;
		xmlXPathObjectPtr scraped;
		Scrape_callback callback;
		scraped = *iter++;
		callback = (instructiter++)->callback;
		for (int i = 0; i < scraped->nodesetval->nodeNr; ++i) {
			xmlNodePtr datanode = scraped->nodesetval->nodeTab[i];
			xmlXPathSetContextNode (datanode, context);
			callback (context);
		}
	}
}

int
Scrape_proccess (char const *website, struct Scrape_instr instr[], size_t nexpr)
{
	struct Scrape_expr_data expr_objects;

	Scrape_expr_data_init (&expr_objects, nexpr);
	if (!(Scrape_website (website, instr, nexpr, &expr_objects))) {
		fprintf (stderr, "error: Scrape_website failed\n");
		Scrape_expr_data_cleanup (&expr_objects);
		return FAILURE;
	}
	fetch_data (&expr_objects, instr);

	Scrape_expr_data_cleanup (&expr_objects);
	return SUCCESS;
}
