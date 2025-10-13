#include "scrape/scraper.h"
#include <assert.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <libxml/HTMLparser.h>
#include <libxml/HTMLtree.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 1
#define FAILURE 0

struct webdump {
	char *data; // should be null terminated
	size_t size;
};

struct exprs {
	xmlXPathObjectPtr *exprs;
	size_t size;
	xmlDoc *doc;
	xmlXPathContextPtr context;
};

static void
webdump_init (struct webdump *inpt)
{
	assert (inpt != NULL);
	inpt->data = (char *)malloc (1);
	*inpt->data = '\0';
	inpt->size = 0;
}

static void
webdump_cleanup (struct webdump *html)
{
	assert ((html != NULL) && (html->data != NULL));
	free (html->data);
	html->size = 0;
}

static void
expr_init (struct exprs *inpt, size_t nexpr)
{
	inpt->exprs
	    = (xmlXPathObjectPtr *)malloc (sizeof (xmlXPathContextPtr) * nexpr);
	inpt->size = nexpr;
	inpt->context = NULL;
	inpt->doc = NULL;
}

static void
expr_cleanup (struct exprs *inpt)
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
	struct webdump *data = (struct webdump *)userdata;
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

static CURLcode
curl_dump (CURL *handle, char const *url, struct webdump *out)
{
	curl_easy_setopt (handle, CURLOPT_NOSIGNAL, 1L);
	curl_easy_setopt (handle, CURLOPT_WRITEFUNCTION, callback_txt);
	curl_easy_setopt (handle, CURLOPT_WRITEDATA, (void *)out);
	curl_easy_setopt (handle, CURLOPT_URL, url);
	return curl_easy_perform (handle);
}

static int
scrape (const char *url, struct webdump *out)
{
	CURL *handle;
	if ((handle = curl_easy_init ())) {
		CURLcode err;
		curl_easy_reset (handle);
		if ((err = curl_dump (handle, url, out)) != CURLE_OK) {
			fprintf (stderr, "error: %s \n",
				 curl_easy_strerror (err));
			curl_easy_cleanup (handle);
			return FAILURE;
		}
		curl_easy_cleanup (handle);
	}
	return SUCCESS;
}

static int
evaluate_instructions (struct webdump const *html,
		       struct Scrape_instr const instrs[static 1],
		       size_t ninstrs, struct exprs *nodes)
{
	xmlXPathObjectPtr *nodes_iter;

	assert (ninstrs > 0);
	nodes->doc = htmlReadMemory (html->data, html->size, NULL, "utf-8",
				     HTML_PARSE_NOERROR);
	nodes->context = xmlXPathNewContext (nodes->doc);
	nodes_iter = nodes->exprs + ninstrs;
	while (ninstrs)
		*--nodes_iter = xmlXPathEvalExpression (
		    (xmlChar *)instrs[--ninstrs].expr, nodes->context);
	return SUCCESS;
}

static int
get_html (char const *url, struct Scrape_instr instr[static 1], size_t ninstr,
	  struct exprs *nodes)
{
	struct webdump dump;
	webdump_init (&dump);
	if (!(scrape (url, &dump))) {
		fprintf (stderr, "error: Scraping the website failed\n");
		return FAILURE;
	}
	evaluate_instructions (&dump, instr, ninstr, nodes);
	webdump_cleanup (&dump);
	return SUCCESS;
}

static void
proccess_html (struct exprs *object, struct Scrape_instr instrs[static 1])
{
	size_t remaining = object->size;
	xmlXPathObjectPtr *iter = object->exprs;
	struct Scrape_instr *instrsptr = instrs;
	while (remaining--) {
		xmlXPathContextPtr context = object->context;
		xmlXPathObjectPtr scraped;
		Scrape_callback callback;
		scraped = *iter++;
		callback = (instrsptr++)->callback;
		for (int i = 0; i < scraped->nodesetval->nodeNr; ++i) {
			xmlNodePtr datanode = scraped->nodesetval->nodeTab[i];
			xmlXPathSetContextNode (datanode, context);
			callback (context);
		}
	}
}

int
Scrape_html (char const *url, struct Scrape_instr instr[static 1],
	     size_t ninstr)
{
	struct exprs expr_nodes;

	expr_init (&expr_nodes, ninstr);
	if (!(get_html (url, instr, ninstr, &expr_nodes))) {
		fprintf (stderr, "error: Scrape_website failed\n");
		expr_cleanup (&expr_nodes);
		return FAILURE;
	}
	proccess_html (&expr_nodes, instr);

	expr_cleanup (&expr_nodes);
	return SUCCESS;
}
