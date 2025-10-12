#ifndef HTML_SCRAPING_H
#define HTML_SCRAPING_H
#ifdef __cplusplus
extern "C" {
#else
#endif

#include <stddef.h>
#define T HtmlData

struct T {
	char *data; // should be null terminated
	size_t size;
};
void HtmlData_init (struct T *inpt);
void HtmlData_cleanup (struct T *html);

#undef T

#ifdef __cplusplus
}
#endif
#endif // HTML_SCRAPING_H
