#include "foo/main.h"
#include <stdlib.h>

static int a = 1;

int
main (int argc, char *argv[])
{
	helloworld ();
	a = 52;
	return EXIT_SUCCESS;
}
