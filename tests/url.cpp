#include "scrape/url.h"
#include <gtest/gtest.h>

TEST (url, playground)
{
	struct url data;
	char const *url = "i dont matter atm :D";
	Url_init (url, &data);
	FAIL ();
}