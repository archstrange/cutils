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

