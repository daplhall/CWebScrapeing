#ifndef WEBSITE_SPECIFICS_H
#define WEBSITE_SPECIFICS_H
#ifdef __cplusplus
extern C
{
#endif
	struct ecom_data {
		char *url;
		char *image;
		char *name;
		char *price;
	};

	int ecommernce (void);
#ifdef __cplusplus
}
#endif
#endif // WEBSITE_SPECIFICS_H
