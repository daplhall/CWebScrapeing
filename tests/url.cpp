#include "fixtures/url.hpp"
#include "scrape/url.h"
#include <gtest/gtest.h>
#include <string>

TEST_F (url1, playground)
{
	struct url_T data;
	Url_init (&data);
	Url_parse (website.c_str (), &data);

	expect_webdata (data.scheme, "https");
	expect_webdata (data.host, "web.page.com");
	expect_webdata (data.path, "dicechanics/api.html");
	expect_webdata (data.fragment, "dicechanics.pool");

	Url_cleanup (&data);
}

TEST_F (url2, playground)
{
	struct url_T data;
	Url_init (&data);
	Url_parse (website.c_str (), &data);

	expect_webdata (data.scheme, "file");
	expect_webdata (
	    data.path,
	    "home/user/Documents/folder/folder2/a.b.c.s.d/index.html");

	Url_cleanup (&data);
}

TEST_F (url3, playground)
{
	struct url_T data;
	Url_init (&data);
	Url_parse (website.c_str (), &data);
	expect_webdata (data.scheme, "https");
	expect_webdata (data.userinfo, "password");
	expect_webdata (data.host, "webpage.com");
	expect_webdata (data.port, "2424");
	expect_webdata (data.path, "dicechanics/api.html");
	expect_webdata (data.fragment, "dicechanics.pool");
	Url_cleanup (&data);
}