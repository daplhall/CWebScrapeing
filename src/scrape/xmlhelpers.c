#include "scrape/xmlhelpers.h"

void
Scraper_xmlGetProp (xmlXPathContextPtr context, xmlChar *PathEvalExpression,
		    xmlChar *property, char **out)
{
	xmlNodePtr node;
	xmlXPathObjectPtr subexpr;
	// url
	subexpr = xmlXPathEvalExpression (PathEvalExpression, context);
	node = subexpr->nodesetval->nodeTab[0];
	*out = (char *)xmlGetProp (node, property);
	xmlXPathFreeObject (subexpr);
}

void
Scraper_xmlGetContent (xmlXPathContextPtr context, xmlChar *PathEvalExpression,
		       char **out)
{
	xmlNodePtr node;
	xmlXPathObjectPtr subexpr;

	subexpr = xmlXPathEvalExpression (PathEvalExpression, context);
	node = subexpr->nodesetval->nodeTab[0];
	*out = (char *)xmlNodeGetContent (node);
	xmlXPathFreeObject (subexpr);
}
