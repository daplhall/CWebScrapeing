
#ifndef MYCALLBACKS_H
#define MYCALLBACKS_H
#ifdef __cplusplus
extern "C" {
#endif
#include <libxml/xpath.h>
void Scraper_xmlGetProp (xmlXPathContextPtr context,
			 xmlChar *PathEvalExpression, xmlChar *property,
			 char **out);
void Scraper_xmlGetContent (xmlXPathContextPtr context,
			    xmlChar *PathEvalExpression, char **out);
#ifdef __cplusplus
}
#endif
#endif // MYCALLBACKS_H
