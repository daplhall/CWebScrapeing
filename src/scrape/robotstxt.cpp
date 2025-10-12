#include "robots.h"
#include <string>
#include <vector>

extern "C" int
Scrape_allowed (char const *robot_txt, char const *user_agent, char const *url)
{
	std::vector<std::string> const usr = { user_agent };
	googlebot::RobotsMatcher matcher;
	return matcher.AllowedByRobots (robot_txt, &usr, url);
}