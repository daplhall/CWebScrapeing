#include "scrape/url.h"
#include "buffer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFINITSIZE 256
#define T	    url_T

enum state_T {
	SCHEME,
	AUTHORITY_OPTIONAL,
	PATH,
	QUERY,
	FRAGMENT,
	PARSE_AUTHORITY,
	PORT,
	END
};

struct finite_machine_T {
	enum state_T state;
	enum state_T next_state;
};

static enum state_T
schema_handler (char const inpt, struct chrbuf *buf, struct T *out)
{
	if (inpt == ':') {
		out->scheme = Buffer_flush (buf);
		return AUTHORITY_OPTIONAL;
	}
	Buffer_insert_char (buf, inpt);
	return SCHEME;
}

static enum state_T
authority_optional_handler (char const inpt, struct chrbuf *buf)
{
	if (Buffer_find (buf, '/') != NULL) {
		Buffer_clear (buf);
		return PARSE_AUTHORITY;
	} else if (inpt == '/') {
		Buffer_insert_char (buf, inpt);
		return AUTHORITY_OPTIONAL;
	} else {
		Buffer_clear (buf);
		return PATH;
	}
}

static enum state_T
path_handler (char const inpt, struct chrbuf *buf, struct T *out)
{
	if (inpt == '?') {
		out->path = Buffer_flush (buf);
		return QUERY; // i can skip this step and just save here
	} else if (inpt == '#') {
		out->path = Buffer_flush (buf);
		return FRAGMENT;
	} else if (inpt == '\0') {
		out->path = Buffer_flush (buf);
		return END;
	} else {
		Buffer_insert_char (buf, inpt);
		return PATH;
	}
}

static enum state_T
query_handler (char const inpt, struct chrbuf *buf, struct T *out)
{
	if (inpt == '#') {
		out->query = Buffer_flush (buf);
		return FRAGMENT;
	} else if (inpt == '\0') {
		out->query = Buffer_flush (buf);
		return END;
	} else {
		Buffer_insert_char (buf, inpt);
		return QUERY;
	}
}

static enum state_T
fragment_handler (char const inpt, struct chrbuf *buf, struct T *out)
{
	if (inpt == '\0') {
		out->fragment = Buffer_flush (buf);
		return END;
	} else {
		Buffer_insert_char (buf, inpt);
		return FRAGMENT;
	}
}

static enum state_T
parse_authority_handler (char const inpt, struct chrbuf *buf, struct T *out)
{
	if (inpt == '@') {
		out->userinfo = Buffer_flush (buf);
		return PARSE_AUTHORITY;
	} else if (inpt == ':') { // The setup of this means that
				  // username:password doesn't work
		out->host = Buffer_flush (buf);
		return PORT;
	} else if (inpt == '/') {
		out->host = Buffer_flush (buf);
		return PATH;
	} else {
		Buffer_insert_char (buf, inpt);
		return PARSE_AUTHORITY;
	}
}

static enum state_T
port_handler (char const inpt, struct chrbuf *buf, struct T *out)
{
	if ((isdigit (inpt))) {
		Buffer_insert_char (buf, inpt);
		return PORT;
	} else {
		out->port = Buffer_flush (buf);
		return PATH;
	}
}

void
Url_parse (char const *url, struct T *out)
{
	struct chrbuf buf;
	struct finite_machine_T machine = {
		.state = SCHEME,
		.next_state = SCHEME,
	};
	char const *c = url;
	Buffer_init (&buf, BUFINITSIZE);
	while (machine.state != END) {
		switch (machine.state) {
		case SCHEME:
			machine.next_state = schema_handler (*c, &buf, out);
			break;
		case AUTHORITY_OPTIONAL:
			machine.next_state
			    = authority_optional_handler (*c, &buf);
			break;
		case PATH:
			machine.next_state = path_handler (*c, &buf, out);
			break;
		case QUERY:
			machine.next_state = query_handler (*c, &buf, out);
			break;
		case FRAGMENT:
			machine.next_state = fragment_handler (*c, &buf, out);
			break;
		case PARSE_AUTHORITY:
			machine.next_state
			    = parse_authority_handler (*c, &buf, out);
			break;
		case PORT:
			machine.next_state = port_handler (*c, &buf, out);
			break;
		case END:
			break;
		}
		machine.state = machine.next_state;
		if (*c++ == '\0')
			break;
	}
	Buffer_cleanup (&buf);
}

void
Url_cleanup (struct T *url)
{
	free (url->scheme);
	free (url->userinfo);
	free (url->host);
	free (url->port);
	free (url->path);
	free (url->query);
	free (url->fragment);
}

void
Url_init (struct T *url)
{
	url->scheme = NULL;
	url->userinfo = NULL;
	url->host = NULL;
	url->port = NULL;
	url->path = NULL;
	url->query = NULL;
	url->fragment = NULL;
}
void
Url_print (struct T *url)
{
	if (url->scheme)
		printf ("scheme: %s\n", url->scheme);
	if (url->userinfo)
		printf ("userinfo: %s\n", url->userinfo);
	if (url->host)
		printf ("host: %s\n", url->host);
	if (url->port)
		printf ("port: %s\n", url->port);
	if (url->path)
		printf ("path: %s\n", url->path);
	if (url->query)
		printf ("query: %s\n", url->query);
	if (url->fragment)
		printf ("fragment: %s\n", url->fragment);
}
