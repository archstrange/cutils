#ifndef CUTILS_XO_H
#define CUTILS_XO_H
#include "Str.h"
#include "Vector/StrVector.h"

enum xo_entry_type {
	/// short option: -<char>
	XO_ENTRY_SHORT = (1 << 1),
	/// long option: --<chars>
	XO_ENTRY_LONG = (1 << 2),
	/// require arg for this option
	XO_ENTRY_ARG = (1 << 3),

	/// option met in args-list
	XO_ENTRY_MET = (1 << 0),
};

struct xo_entry {
	/// BITs flags of `enum xo_entry_type`
	int type;
	/// short option name
	char s;
	/// long option name
	const char *l;
	/// arg of this option, filled by xo
	Str arg;
	/// help message of this option
	const char *help;
};

/// read the command line(argc, argv) to fill @entries and @args.
///
/// the type of last entry of @entries must be 0, which tells xo
/// it's the last entry. @args must be a StrVector object(not NULL).
///
/// if an option is met, then it's entry type will be flaged with
/// XO_ENTRY_MET bit.
///
/// arg of an option(if it needs and is followd by one) will be
/// put to entry's arg field.
///
/// other args will be put to @args as the order they are in @argv.
///
/// @argc must be the len of @argv, and @argv[0] will be ignored
/// since it's the program's name.
///
/// Return: TODO
///   0: success
///   1: bad short option
///   -1: bad option in @argv
///   positive: something wrong about arguments
///   negative: other error
int xo(int argc, const char *argv[], struct xo_entry entries[], StrVector args);

/// free all arg Str objects in @entries.
static inline void xo_free_args(struct xo_entry *entries);


static inline void xo_free_args(struct xo_entry *entries)
{
	while (entries->type != 0) {
		if (entries->arg != NULL) {
			Str_free(entries->arg);
			entries->arg = NULL;
		}
		entries += 1;
	}
}

#endif

