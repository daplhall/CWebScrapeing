#ifndef SCRAPER_URL_H
#define SCRAPER_URL_H
#ifdef __cplusplus
extern "C" {
#endif

#define T url_T
struct T {
	char *scheme;
	char *userinfo;
	char *host;
	char *port;
	char *path;
	char *query;
	char *fragment;
};

void Url_parse (char const *url, struct T *out);
void Url_init (struct T *url);
void Url_print (struct T *url);
void Url_cleanup (struct T *url);

#undef T
#ifdef __cplusplus
}
#endif
#endif // SCRAPER_URL_T
