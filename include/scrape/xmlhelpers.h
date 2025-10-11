
#ifndef MYCALLBACKS_H
#define MYCALLBACKS_H
#ifdef __cplusplus
extern "C" {
#endif
#include <libxml/xpath.h>
char *Scraper_xmlGetProp (xmlXPathContextPtr context,
			  xmlChar *PathEvalExpression, xmlChar *property);
char *Scraper_xmlGetContent (xmlXPathContextPtr context,
			     xmlChar *PathEvalExpression);
#ifdef __cplusplus
}
#endif
#endif // MYCALLBACKS_H
