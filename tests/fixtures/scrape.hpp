#ifndef SCRAPE_FIXTURE_H
#define SCRAPE_FIXTURE_H
#include "scrape/scraper.h"
#include "scrape/xmlhelpers.h"
#include <cstdio>
#include <cstdlib>
#include <gtest/gtest.h>
#include <string.h>
// TESTPATH is defined by CMake
#define FILEPATH TESTPATH

class scrapingcourse : public ::testing::Test
{
      protected:
	struct Scrape_instr *instructions;
	size_t ninstr = 1;
	inline static std::string const testfile
	    = FILEPATH "/scrapingcourse.txt";
	void
	SetUp ()
	{
		instructions = new struct Scrape_instr[ninstr];
		instructions->expr = "//li[contains(@class, 'product')]";
		instructions->callback = fetch_callback;
	}

	void
	TearDown ()
	{
		delete[] instructions;
	}
	static void
	fetch_callback (xmlXPathContextPtr context)
	{
		FILE *file;
		char *url, *img, *name, *price;
		// url
		Scraper_xmlGetProp (context, (xmlChar *)".//a",
				    (xmlChar *)"href", &url);
		// Img
		Scraper_xmlGetProp (context, (xmlChar *)".//a/img",
				    (xmlChar *)"src", &img);
		// name
		Scraper_xmlGetContent (context, (xmlChar *)".//a/h2", &name);
		// price
		Scraper_xmlGetContent (context, (xmlChar *)".//a/span", &price);
		// Clean up
		file = fopen (testfile.c_str (), "a");

		fputs (url, file);
		fprintf (file, "%s\n", url);
		fprintf (file, "\t%s\n", img);
		fprintf (file, "\t%s\n", name);
		fprintf (file, "\t%s\n", price);

		fclose (file);

		free (url);
		free (img);
		free (name);
		free (price);
	}
};

#endif