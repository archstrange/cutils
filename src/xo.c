#include "xo.h"
#include "cprint.h"
#include "Dict/StrU32Dict.h"

struct xo {
	int argc;
	const char **argv;
	struct xo_entry *entries;
	StrVector args;

	// usage: table[opt] = entry_index
	// entry index start from 1
	uint32_t s_table[128];
	StrU32Dict l_table;
};

static int xo_fill_tables(struct xo *self);
static int xo_fill_entries(struct xo *self);
static uint32_t xo_opt2index(struct xo *self, const char *opt);

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
		.l_table = StrU32Dict_new()
	};
	StrVector_clear(args);
	ret = xo_fill_tables(&self);
	if (ret != 0) goto done;
	ret = xo_fill_entries(&self);

done:
	StrU32Dict_free(self.l_table);
	return ret;
}

static int xo_fill_tables(struct xo *self)
{
	uint32_t i = 1;
	int ret = 0;
	struct xo_entry *e = self->entries;
	Str key = Str_new();
	while (e->type != 0) {
		if (e->type & XO_ENTRY_SHORT) {
			if ((unsigned char)e->s < 127) {
				self->s_table[e->s] = i;
			} else {
				ret = 1;
				break;
			}
		}
		if (e->type & XO_ENTRY_LONG) {
			Str_copyArray(key, e->l, CStr_len(e->l));
			StrU32Dict_insert(self->l_table, key, i);
		}
		i += 1;
	}

	Str_free(key);
	return ret;
}

// @opt: "-...."
static uint32_t xo_opt2index(struct xo *self, const char *opt)
{
	uint32_t index = 0;
	Str key = Str_new();
	size_t len = CStr_len(opt);
	if (len > 2 && opt[1] == '-') { // "--..."
		Str_copyArray(key, opt + 2, len - 2);
		if (!StrU32Dict_find(self->l_table, key, &index)) index = 0;
	} else if ((unsigned char)opt[1] < 127){
		index = self->s_table[opt[1]];
	}

	Str_free(key);
	return index;
}

static int xo_fill_entries(struct xo *self)
{
	int i = 1;
	uint32_t index = 0;
	struct xo_entry *entry;
	for (; i < self->argc; i++) {
		if (self->argv[i][0] != '-' || self->argv[i][1] == 0) {
			StrVector_push(self->args, Str_newFromCStr(self->argv[i]));
			continue;
		}

		index = xo_opt2index(self, self->argv[i]);
		if (index == 0) goto badOption;
		entry = &self->entries[index - 1];
		entry->type |= XO_ENTRY_MET;

		if (!(entry->type & XO_ENTRY_ARG))
			continue;

		i += 1;
		if (i >= self->argc)
			break;

		if (entry->arg == NULL)
			entry->arg = Str_newFromCStr(self->argv[i]);
		else
			Str_copyArray(entry->arg, self->argv[1], CStr_len(self->argv[i]));
	}
	return 0;

badOption:
	fprintf(stderr,
		"\t" SGR(FG_RED, "%s") "is not a valid option!\n",
		self->argv[i]);
	return -1;
}

