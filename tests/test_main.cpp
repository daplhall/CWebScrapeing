#include <curl/curl.h>
#include <gtest/gtest.h>

int
main (int argc, char **argv)
{
	curl_global_init (CURL_GLOBAL_ALL);
	testing::InitGoogleTest (&argc, argv);
	curl_global_cleanup ();
	return RUN_ALL_TESTS ();
}