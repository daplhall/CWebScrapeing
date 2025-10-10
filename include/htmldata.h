#ifndef HTML_SCRAPING_H
#define HTML_SCRAPING_H
#ifdef __cplusplus
extern C
{
#endif

#define T HtmlData
	typedef struct T *T;
	T HtmlData_create (void);
	void HtmlData_destroy (T htmldata);
	char *HtmlData_get (T htmldata);
	void HtmlData_set (T html, char *inpt);
#undef T

#ifdef __cplusplus
}
#endif
#endif // HTML_SCRAPING_H
