#include "scrape/htmldata.h"
#include "scrape/scraper.h"
#include <curl/easy.h>
#include <iostream>
#include <robots.h>

int
main ()
{
	googlebot::RobotsMatcher matcher;
	struct HtmlData html;
	struct Scrape_instr data;

	std::cout << "Hello world" << std::endl;
	return 0;
}