#include "scrape/xmlhelpers.h"

char *
Scraper_xmlGetProp (xmlXPathContextPtr context, xmlChar *PathEvalExpression,
		    xmlChar *property)
{
	xmlNodePtr node;
	xmlXPathObjectPtr subexpr;
	char *out;
	// url
	subexpr = xmlXPathEvalExpression (PathEvalExpression, context);
	node = subexpr->nodesetval->nodeTab[0];
	out = (char *)xmlGetProp (node, property);
	xmlXPathFreeObject (subexpr);
	return out;
}

char *
Scraper_xmlGetContent (xmlXPathContextPtr context, xmlChar *PathEvalExpression)
{
	xmlNodePtr node;
	xmlXPathObjectPtr subexpr;
	char *out;

	subexpr = xmlXPathEvalExpression (PathEvalExpression, context);
	node = subexpr->nodesetval->nodeTab[0];
	out = (char *)xmlNodeGetContent (node);
	xmlXPathFreeObject (subexpr);
	return out;
}
