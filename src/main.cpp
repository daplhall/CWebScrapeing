#include "scrape/htmldata.h"
#include "scrape/scraper.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include <iostream>
#include <robots.h>

int
main ()
{
	googlebot::RobotsMatcher matcher;
	struct HtmlData html;
	const std::vector<std::string> mem = { "Some Scraper", "hellooo" };
	bool allowed;
	HtmlData_init (&html);
	Scrape_html ("https://www.kelz0r.dk/robots.txt", &html);
	std::printf ("%s\n", html.data);
	allowed = matcher.AllowedByRobots (
	    html.data, &mem,
	    "https://www.kelz0r.dk/magic/banned/"); // 1: allowed 0: not
	std::cout << "am i allowed? " << allowed << std::endl;
	HtmlData_cleanup (&html);
	return 0;
}