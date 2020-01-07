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

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#include "../src/xo.h"
#include "../src/codec/utf8.h"
#include "../src/Str.h"
#include "../src/fs/Path.h"
#include "../src/codec/base64.h"

void test_xo(int argc, const char *argv[])
{/*{{{*/
	struct xo_entry options[] = {
		{ .type = XO_ENTRY_SHORT, .s = 'a' },
		{ .type = XO_ENTRY_SHORT, .s = 'b' },
		{ .type = XO_ENTRY_SHORT, .s = 'c' },

		{ .type = XO_ENTRY_SHORT | XO_ENTRY_ARG, .s = 'A' },
		{ .type = XO_ENTRY_SHORT | XO_ENTRY_ARG, .s = 'B' },
		{ .type = XO_ENTRY_SHORT | XO_ENTRY_ARG, .s = 'C' },

		{ .type = XO_ENTRY_LONG, .l = "aaa" },
		{ .type = XO_ENTRY_LONG, .l = "bbb" },
		{ .type = XO_ENTRY_LONG, .l = "ccc" },

		{ .type = XO_ENTRY_LONG | XO_ENTRY_ARG, .l = "AAA" },
		{ .type = XO_ENTRY_LONG | XO_ENTRY_ARG, .l = "BBB" },
		{ .type = XO_ENTRY_LONG | XO_ENTRY_ARG, .l = "CCC" },

		{ .type = XO_ENTRY_SHORT | XO_ENTRY_LONG, .s = 'x', .l = "xxx"},
		{ .type = XO_ENTRY_SHORT | XO_ENTRY_LONG, .s = 'y', .l = "yyy"},
		{ .type = XO_ENTRY_SHORT | XO_ENTRY_LONG, .s = 'z', .l = "zzz"},

		{ .type = XO_ENTRY_SHORT | XO_ENTRY_LONG | XO_ENTRY_ARG,
			.s = 'X', .l = "XXX"
		},
		{ .type = XO_ENTRY_SHORT | XO_ENTRY_LONG | XO_ENTRY_ARG,
			.s = 'Y', .l = "YYY"
		},
		{ .type = XO_ENTRY_SHORT | XO_ENTRY_LONG | XO_ENTRY_ARG,
			.s = 'Z', .l = "ZZZ"
		},
		{ .type = 0 },
	};
	StrVector args = StrVector_new();

	if (xo(argc, argv, options, args) != 0) exit(1);

	printf("Test xo:\n");
	struct xo_entry *e = options;
	while (e->type != 0) {
		if (e->type & XO_ENTRY_MET) {
			fputs("\tmet: ", stdout);
			if (e->type & XO_ENTRY_SHORT) printf("-%c ", e->s);
			if (e->type & XO_ENTRY_LONG) printf("--%s ", e->l);
			if (e->type & XO_ENTRY_ARG) Str_print(e->arg, stdout);
			putc('\n', stdout);
		}
		e += 1;
	}

	size_t args_n = StrVector_getLength(args);
	if (args_n != 0) {
		puts("has args:");
		for (size_t i = 0; i < args_n; i++) {
			fputs("\t", stdout);
			Str_echo(StrVector_get(args, i), stdout);
		}
	}

	StrVector_free(args);
	xo_free_args(options);
}/*}}}*/

void test_fs_path()
{/*{{{*/
#define originPath "/home/qijian/../qijian/bench/c/cutils/././src/../"
#define refinedPath "/home/qijian/bench/c/cutils"
	Str ps = Str_newFromCStr(originPath);
	Path p = Path_new(ps);
	Path_refine(p);
	Path_getStr(p, ps);

	assert(Path_isAbs(p));
	assert(CStr_len(refinedPath) == Str_getLength(ps));
	assert(strncmp(refinedPath, Str_data(ps), Str_getLength(ps)) == 0);

	Str_free(ps);
	Path_free(p);
}/*}}}*/

void test_Str()
{/*{{{*/
#define HASH(cstr, len) \
	Str_copyArray(str, cstr, len); \
	hash = Str_hash(str); \
	printf("Str '" cstr "' hash: %x, mod 7: %u\n", hash, hash % 7)

	Str str = Str_new();
	uint32_t hash;
	HASH("hello", 5);
	HASH("hallo", 5);

	HASH("qijian", 6);
	HASH("Qijian", 6);

	HASH("qijian zhang", 12);
	HASH("Qijian Zhang", 12);

	HASH("a very long string but only first char different!", 49);
	HASH("A very long string but only first char different!", 49);
}/*}}}*/

void test_codec_base64()
{/*{{{*/
	Str in = Str_newFromCStr("Qijian Zhang 张奇建");
	Str out = Str_new();
	Str back = Str_new();
	assert(base64_enc(in, out, NULL) == 0);
	assert(base64_dec(out, back, NULL) == 0);
	assert(Str_equal(back, in));

	assert(base64_enc(in, out, "&,") == 0);
	assert(base64_dec(out, back, "&,") == 0);
	assert(Str_equal(back, in));
}/*}}}*/

void test_codec_utf8()
{/*{{{*/
	uint8_t *yes = "✅";
	uint32_t yes_cp = 0x2705;
	uint8_t *no = "❌";
	uint32_t no_cp = 0x274C;
	uint32_t cp;
	uint8_t u[5];

	assert(utf8_codepoint(yes, &cp) == strlen(yes));
	assert(cp == yes_cp);
	utf8_char(cp, u);
	assert(strcmp(u, yes) == 0);
	assert(utf8_codepoint(no, &cp) == strlen(no));
	assert(cp == no_cp);
	utf8_char(cp, u);
	assert(strcmp(u, no) == 0);

	Str in = Str_newFromCStr("Qijian Zhang 张奇建");
	U32Vector out = U32Vector_new();
	Str back = Str_new();
	assert(utf8_dec(in, out) == 0);
	assert(utf8_enc(out, back) == 0);
	assert(Str_equal(back, in));
}/*}}}*/

int main(int argc, const char *argv[])
{
	test_fs_path();
	test_Str();
	test_codec_base64();
	test_codec_utf8();

	return 0;
}

