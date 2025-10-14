#ifndef SCRAPER_URL_H
#define SCRAPER_URL_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#define T url
struct T {
	char *scheme;
	char *userinfo;
	char *host;
	char *port;
	char *path;
	char *query;
	char *fragment;
};

void Url_init (char const *url, struct T *init);
void Url_cleanup (struct T *url);

#undef T
#ifdef __cplusplus
}
#endif
#endif // SCRAPER_URL_T
