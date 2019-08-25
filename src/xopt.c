#include "xopt.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/// TODO
/// better design
/// help message
/// better opt syntax

struct xopt {
	int opts_count;
	const struct xoption *opts;
	int argc;
	const char **argv;
	int index;
	int short_index;
	bool in_short;
	const char *current_opt;
	char current_short_opt[2];
	const char *current_arg;
};

static int xopt_get_short(Xopt self);
static int xopt_get_long(Xopt self);
static int find_short(Xopt self, char s);
static int find_char(const char *str, char c);
static int find_long(Xopt self, const char *l, int n);

Xopt xopt_new(int argc, const char *argv[],
	      int opts_count, const struct xoption *opts)
{
	Xopt self = malloc(sizeof(*self));
	self->argc = argc;
	self->argv = argv;
	self->opts_count = opts_count;
	self->opts = opts;
	self->current_opt = self->current_arg = NULL;
	self->current_short_opt[0] = self->current_short_opt[1] = 0;
	self->index = 0;
	self->in_short = false;
	return self;
}

void xopt_free(Xopt self)
{
	free(self);
}

int xopt_get(Xopt self)
{
	if (self->in_short) {
		self->short_index += 1;
		if (self->argv[self->index][self->short_index] != 0) {
			return xopt_get_short(self);
		}
	}
	self->index += 1;
	self->in_short = false;
	if (self->index >= self->argc) {
		return -2;
	}
	if (self->argv[self->index][0] == '-') {
		if (self->argv[self->index][1] == '-') {
			return xopt_get_long(self);
		} else {
			self->in_short = true;
			self->short_index = 0;
			return xopt_get(self);
		}
	} else {
		self->current_arg = self->argv[self->index];
		return 0;
	}
}

const char *xopt_current_arg(Xopt self)
{
	return self->current_arg;
}

const char *xopt_current_opt(Xopt self)
{
	return self->current_opt;
}

///
/// Static functions
///

static int find_short(Xopt self, char s)
{
	for (int i = 0; i < self->opts_count; i++) {
		if (self->opts[i].flags & XOPT_SHORT) {
			if (self->opts[i].short_opt == s) {
				return i;
			}
		}
	}
	return -1;
}

static int xopt_get_short(Xopt self)
{
	int index = find_short(self, self->argv[self->index][self->short_index]);
	self->current_short_opt[0] = self->argv[self->index][self->short_index];
	self->current_opt = self->current_short_opt;
	if (index == -1) {
		return -1;
	} else {
		if ((self->opts[index].flags & XOPT_WITH_ARG)
		     && self->argv[self->index][self->short_index + 1] == 0
		     && self->index + 1 < self->argc
		     && self->argv[self->index + 1][0] != '-') {
			self->current_arg = self->argv[self->index + 1];
			self->in_short = false;
			self->index += 1;
		} else {
			self->current_arg = NULL;
		}
		return self->opts[index].id;
	}
}

static int find_char(const char *str, char c)
{
	for (int i = 0; str[i] != 0; i++) {
		if (str[i] == c) {
			return i;
		}
	}
	return -1;
}

static int find_long(Xopt self, const char *l, int n)
{
	for (int i = 0; i < self->opts_count; i++) {
		if (self->opts[i].flags & XOPT_LONG) {
			if (strncmp(l, self->opts[i].long_opt, n) == 0) {
				return i;
			}
		}
	}
	return -1;
}

static int xopt_get_long(Xopt self)
{
	int end = find_char(self->argv[self->index], '=');
	if (end == -1)
		end = find_char(self->argv[self->index], 0);
	int index = find_long(self, self->argv[self->index] + 2, end - 2);
	if (index == -1) {
		self->current_opt = self->argv[self->index];
		return -1;
	} else {
		self->current_opt = self->opts[index].long_opt;
		if (self->argv[self->index][end] == '='
		    && self->opts[index].flags & XOPT_WITH_ARG) {
			self->current_arg = self->argv[self->index] + end + 1;
		} else {
			self->current_arg = NULL;
		}
		return self->opts[index].id;
	}
}

