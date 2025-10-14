#include "fixtures/scrape.hpp"
#include "scrape/scraper.h"
#include <cstdio>
#include <fstream>
#include <gtest/gtest.h>

#define REFERENCEFILE ROOTPATH
/*
 * Ideally i would have my own website/page to scrape such that
 * everything would be static.
*/
TEST_F (scrapingcourse, html)
{
	FILE *file;
	int rc;

	file = fopen (testfile.c_str (), "w");
	fclose (file);
	if (!(rc = Scrape_html ("https://www.scrapingcourse.com/ecommerce/",
				instructions, ninstr)))
		FAIL ();
	std::ifstream scraped, reffile;
	scraped.open (testfile);
	reffile.open (ROOTPATH "/tests/referencefiles/scrapingcourse_ref.txt");
	for (std::string scrap, ref;
	     getline (scraped, scrap, '\n') && getline (reffile, ref, '\n');) {
	}
	scraped.close ();
	reffile.close ();
}