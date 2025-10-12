#include "robots.h"
#include "scrape/htmldata.h"
#include <string>
#include <vector>

extern "C" int
Scrape (char *website, const char *user_agent)
{
	std::vector<std::string> usr = { user_agent };
	return 0;
}