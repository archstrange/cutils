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

#include "../src/xopt.h"
#include "../src/utf-8.h"
#include "../src/Str.h"
#include "../src/fs/Path.h"

void test_xopt(int argc, const char *argv[])
{/*{{{*/
	struct xoption opts[] = {
		{ .id = 1, .flags = XOPT_SHORT | XOPT_LONG | XOPT_WITHOUT_ARG, .short_opt = 't', .long_opt = "top", .help = NULL },
		{ .id = 2, .flags = XOPT_SHORT | XOPT_LONG | XOPT_WITHOUT_ARG, .short_opt = 'l', .long_opt = "left", .help = NULL },
		{ .id = 3, .flags = XOPT_SHORT | XOPT_LONG | XOPT_WITHOUT_ARG, .short_opt = 'b', .long_opt = "buttom", .help = NULL },
		{ .id = 4, .flags = XOPT_SHORT | XOPT_LONG | XOPT_WITHOUT_ARG, .short_opt = 'r', .long_opt = "right", .help = NULL },
		{ .id = 5, .flags = XOPT_SHORT | XOPT_LONG | XOPT_WITH_ARG, .short_opt = 'n', .long_opt = "north", .help = NULL },
		{ .id = 6, .flags = XOPT_SHORT | XOPT_LONG | XOPT_WITH_ARG, .short_opt = 'w', .long_opt = "weast", .help = NULL },
		{ .id = 7, .flags = XOPT_SHORT | XOPT_LONG | XOPT_WITH_ARG, .short_opt = 's', .long_opt = "south", .help = NULL },
		{ .id = 8, .flags = XOPT_SHORT | XOPT_LONG | XOPT_WITH_ARG, .short_opt = 'e', .long_opt = "east", .help = NULL },
	};
	Xopt xopt = xopt_new(argc, argv, 8, opts);

	int id;
	while ((id = xopt_get(xopt)) != -2) {
		switch (id) {
		case 1: case 2: case 3: case 4:
			printf("get option -%c | --%s\n", opts[id - 1].short_opt, opts[id - 1].long_opt);
			break;
		case 5: case 6: case 7: case 8:
			printf("get option -%c | --%s ", opts[id - 1].short_opt, opts[id - 1].long_opt);
			const char *arg = xopt_current_arg(xopt);
			if (arg != NULL) printf("with argument %s\n", arg);
			else printf("without argument\n");
			break;
		case 0:
			printf("get argument %s\n", xopt_current_arg(xopt));
			break;
		case -1:
			printf("get a invalid option %s\n", xopt_current_opt(xopt));
			break;
		}
	}
	printf("parse opt finished!\n");

	xopt_free(xopt);
}/*}}}*/

void test_utf8()
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
{
#define HASH(cstr, len) \
	Str_copyArray(str, cstr, len); \
	printf("Str '" cstr "' hash: %x\n", Str_hash(str))

	Str str = Str_new();
	HASH("hello", 5);
	HASH("hallo", 5);

	HASH("qijian", 6);
	HASH("Qijian", 6);

	HASH("qijian zhang", 12);
	HASH("Qijian Zhang", 12);

	HASH("a very long string but only first char different!", 49);
	HASH("A very long string but only first char different!", 49);
}

int main(int argc, const char *argv[])
{
	test_utf8();
	test_fs_path();
	test_Str();

	return 0;
}

