#include "scraper.h"
#include <curl/curl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <tidy.h>
#include <tidybuffio.h>

void
dumpNode (TidyDoc doc, TidyNode tnod, int indent)
{
	TidyNode child;
	TidyBuffer buf;
	tidyBufInit (&buf);
	for (child = tidyGetChild (tnod); child; child = tidyGetNext (child)) {
		ctmbstr name;
		if ((name = tidyNodeGetName (child))) {
		} else {
			/* if it does not have a name, then it's
			 * probably text, cdata, etc... */
			tidyNodeGetText (doc, child, &buf);
			printf ("%s\n", buf.bp ? (char *)buf.bp : "");
			tidyBufClear (&buf);
		}
		dumpNode (doc, child, indent + 4); /* recursive */
	}
	tidyBufFree (&buf);
}

int
main (int argc, char *argv[])
{
	curl_global_init (CURL_GLOBAL_ALL);
	TidyBuffer htmlbuf = { 0 }, tidy_errbuf = { 0 };
	TidyDoc tdoc;
	int err;

	tdoc = tidyCreate ();
	tidyOptSetBool (tdoc, TidyForceOutput, true);
	tidyBufInit (&htmlbuf);
	tidyBufInit (&tidy_errbuf);

	if (!(Scrape_html ("https://daplhall.github.io/about.html",
			   &htmlbuf))) {
		fprintf (stderr, "Scraping Failed!\n");
		return EXIT_FAILURE;
	}
	if ((err = tidyParseBuffer (tdoc, &htmlbuf)) >= 0) {
		if ((err = tidyCleanAndRepair (tdoc)) >= 0) {
			if ((tidyRunDiagnostics (tdoc)) >= 0) {
				dumpNode (tdoc, tidyGetRoot (tdoc), 0);
				fprintf (stderr, "%s\n", tidy_errbuf.bp);
			}
		}
	}

	// write_html (html, "example.html");
	tidyBufFree (&tidy_errbuf);
	tidyBufFree (&htmlbuf);
	tidyRelease (tdoc);
	curl_global_cleanup ();
	return EXIT_SUCCESS;
}
