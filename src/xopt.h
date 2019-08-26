// cutils: my c utils library
// Copyright (C) 2019  Qijian Zhang <arch.strange@foxmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef CUTILS_XOPT_H
#define CUTILS_XOPT_H

typedef struct xopt *Xopt;

enum XOPT_FLAG {
	SHORT_OPT_WITH_ARG,
	SHORT_OPT_WITH_ARG_OPTIONAL,
	SHORT_OPT_WITHOUT_ARG,
	LONG_OPT_WITH_ARG,
	LONG_OPT_WITH_ARG_OPTIONAL,
	LONG_OPT_WITHOUT_ARG,
	SHORT_LONG_OPT_WITH_ARG,
	SHORT_LONG_OPT_WITH_ARG_OPTIONAL,
	SHORT_LONG_OPT_WITHOUT_ARG,
};

#define XOPT_SHORT 1
#define XOPT_LONG 2
#define XOPT_WITH_ARG 4
#define XOPT_WITHOUT_ARG 8

struct xoption {
	int id; /// id used to indetify this option, and must be positive
	int flags;
	char short_opt; /// short option name
	const char *long_opt; /// long option name
	const char *help; /// option's help message, this is optional
};

Xopt xopt_new(int argc, const char *argv[],
	      int opts_count, const struct xoption *opts);

void xopt_free(Xopt self);

/// Get next option.
/// The option's id is returned and there are some special id:
///     0: An isolated argument is met, which you can call $xopt_current_arg
///        to get it.
///    -1: Invalid option is met, you can call $xopt_current_opt to get it
///    -2: Job finished.
int xopt_get(Xopt self);

/// Return argument of option met by the last call of $xopt_get.
const char *xopt_current_arg(Xopt self);

/// Return option met by the last call of $xopt_get.
const char *xopt_current_opt(Xopt self);

#endif

