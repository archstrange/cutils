#include "xo.h"
#include "cprint.h"
#include "Dict/StrU32Dict.h"

#define MSG_INV_OPT \
	"an invalid option"
#define MSG_MIS_ARG \
	"missing an argument"
#define MSG_WNG_POS \
	"at the wrong position, since it needs an argument right after it"

#define FILL_OPTARG(e, s) \
	if (e->arg == NULL) e->arg = Str_newFromCStr(s); \
	else Str_copyArray(e->arg, s, CStr_len(s))

struct xo {
	int argc;
	const char **argv;
	struct xo_entry *entries;
	StrVector args;

	// usage: table[opt] = entry_index
	// entry index start from 1
	uint32_t s_table[128];
	StrU32Dict l_table;

	int i; // current option index
};

static bool xo_fill_tables(struct xo *self);
static bool xo_fill_entries(struct xo *self);
static inline bool xo_read_option(struct xo *self);
static bool xo_met_long_option(struct xo *self);
static bool xo_met_short_option(struct xo *self);
static inline void xo_bad_long_option(struct xo *self, const char *msg);
static inline void xo_bad_short_option(struct xo *self, char name, const char *msg);

// build a short options table: s --> entry
// and a long options table: l --> entry
//
// for short: uint32_t s_table[128] --> index to @entries
// for long: a str-uint32_t Dict is good
int xo(int argc, const char *argv[], struct xo_entry entries[], StrVector args)
{
	int ret = 0;
	struct xo self = {
		.argc = argc,
		.argv = argv,
		.entries = entries,
		.args = args,
		.s_table = { 0 },
		.l_table = StrU32Dict_new(),
		.i = 1,
	};
	StrVector_clear(args);
	if (!xo_fill_tables(&self)) {
		ret = 1;
		goto done;
	}

	if (!xo_fill_entries(&self))
		ret = -1;

done:
	StrU32Dict_free(self.l_table);
	return ret;
}

static bool xo_fill_tables(struct xo *self)
{
	uint32_t i = 1;
	bool ret = true;
	struct xo_entry *e = self->entries;
	Str key = Str_new();
	while (e->type != 0) {
		if (e->type & XO_ENTRY_SHORT) {
			if ((unsigned char)e->s < 127) {
				self->s_table[e->s] = i;
			} else {
				ret = false;
				break;
			}
		}
		if (e->type & XO_ENTRY_LONG) {
			Str_copyArray(key, e->l, CStr_len(e->l));
			StrU32Dict_insert(self->l_table, key, i);
		}
		i += 1;
		e += 1;
	}

	Str_free(key);
	return ret;
}

static bool xo_fill_entries(struct xo *self)
{
	const char *opt;
	for (; self->i < self->argc; self->i++) {
		opt = self->argv[self->i];
		if (opt[0] != '-' || opt[1] == 0) {
			StrVector_push(self->args, Str_newFromCStr(opt));
		} else {
			if (!xo_read_option(self)) return false;
		}
	}
	return true;
}

static inline bool xo_read_option(struct xo *self)
{
	const char *opt = self->argv[self->i];
	if (opt[1] == '-' && opt[2] != 0) {
		return xo_met_long_option(self);
	} else {
		return xo_met_short_option(self);
	}
}

static bool xo_met_long_option(struct xo *self)
{
	bool ret = false;
	uint32_t index = 0;
	const char *msg = NULL;
	Str key = Str_newFromCStr(self->argv[self->i] + 2);
	if (!StrU32Dict_find(self->l_table, key, &index)) {
		msg = MSG_INV_OPT;
		goto error;
	}

	struct xo_entry *e = &self->entries[index - 1];
	e->type |= XO_ENTRY_MET;
	if (e->type & XO_ENTRY_ARG) {
		if (self->i + 1 >= self->argc) {
			msg = MSG_MIS_ARG;
			goto error;
		}
		self->i += 1;
		FILL_OPTARG(e, self->argv[self->i]);
	}
	ret = true;
error:
	if (msg != NULL) xo_bad_long_option(self, msg);
	Str_free(key);
	return ret;
}

static bool xo_met_short_option(struct xo *self)
{
	uint32_t index = 0;
	struct xo_entry *e;
	const char *opt = self->argv[self->i] + 1;

again:
	if ((unsigned char)*opt >= 127 || self->s_table[*opt] == 0) {
		xo_bad_short_option(self, *opt, MSG_INV_OPT);
		return false;
	}

	e = &self->entries[self->s_table[*opt] - 1];
	e->type |= XO_ENTRY_MET;

	if (e->type & XO_ENTRY_ARG) {
		if (opt[1] != 0) {
			xo_bad_short_option(self, *opt, MSG_WNG_POS);
			return false;
		}
		if (self->i + 1 >= self->argc) {
			xo_bad_short_option(self, *opt, MSG_MIS_ARG);
			return false;
		}
		self->i += 1;
		FILL_OPTARG(e, self->argv[self->i]);
		return true;
	}

	opt += 1;
	if (*opt != 0)
		goto again;
	return true;
}

static inline void xo_bad_long_option(struct xo *self, const char *msg)
{
	fprintf(stderr,
		SGR(FG_RED, "ERROR") ": option '"
		SGR(FG_RED, "%s") "' is %s\n",
		self->argv[self->i],
		msg);
}

static inline void xo_bad_short_option(struct xo *self, char name, const char *msg)
{
	fprintf(stderr,
		SGR(FG_RED, "ERROR") ": option '"
		SGR(FG_RED, "%c") "' in "
		SGR(UNDERLINE, "%s") " is %s\n",
		name,
		self->argv[self->i],
		msg);
}

