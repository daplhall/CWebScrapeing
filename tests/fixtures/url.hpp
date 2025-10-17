#ifndef SCRAPE_FIXTURE_H
#define SCRAPE_FIXTURE_H

#include <gtest/gtest.h>
#include <string>

class url : public ::testing ::Test
{
      protected:
	std::string website;
	static void
	expect_webdata (std::string incomming, std::string expected)
	{
		EXPECT_EQ (incomming, expected);
	}
};

class url1 : public ::url
{
      protected:
	void
	SetUp ()
	{
		website = "https://web.page.com/dicechanics/"
			  "api.html#dicechanics.pool\0";
	}
};

class url2 : public ::url
{
      protected:
	void
	SetUp ()
	{
		website = "file:///home/user/Documents/folder/folder2/"
			  "a.b.c.s.d/index.html\0";
	}
};

class url3 : public ::url
{
	void
	SetUp ()
	{
		website = "https://password@webpage.com:2424/dicechanics/"
			  "api.html#dicechanics.pool\0";
	}
};

#endif // SCRAPE_FIXTURE_H