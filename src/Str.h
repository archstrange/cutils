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

#ifndef CUTILS_STR_H
#define CUTILS_STR_H
#include "Vector/Str.h"
#include <stdio.h>

static inline size_t CStr_len(const char *cstr)
{
	if (cstr == NULL)
		return 0;

	const char *s = cstr;
	while (*s != 0)
		s += 1;
	return s - cstr;
}

static inline Str Str_newFromCStr(const char *cstr)
{
	return Str_newFromArray(cstr, CStr_len(cstr));
}

/// Make @self C-style string so that we can use Str_data()
/// as a C string.
static inline void Str_asCStr(Str self)
{
	Str_push(self, 0);
	Str_pop(self);
}

static inline char *CStr_new(size_t len)
{
	return calloc(len + 1, 1);
}

static inline char *CStr_newFromStr(Str src)
{
	size_t len = Str_getLength(src);
	char *self = malloc(len + 1);
	Str_dump(src, self);
	self[len] = 0;
	return self;
}

/// Create a local(at stack) C-string @name.
#define CStr_localFromStr(name, str) \
	char name[Str_getLength(str) + 1]; \
	Str_dump(str, name); \
	name[Str_getLength(str)] = 0

/// Print Str @self to @out
static inline size_t Str_print(Str self, FILE *out)
{
	return fwrite(Str_data(self), 1, Str_getLength(self), out);
}

/// Same as @Str_print but appended a newline.
static inline size_t Str_echo(Str self, FILE *out)
{
	Str_appendArray(self, "\n", 2);
	size_t s = Str_print(self, out);
	Str_pop(self);
	Str_pop(self);
	return s;
}

static inline size_t Str_readFile(Str self, FILE *fp)
{
	int c;
	Str_clear(self);
	while ((c = getc(fp)) != EOF) {
		Str_push(self, c);
	}
	return Str_getLength(self);
}

static inline size_t Str_readLine(Str self, FILE *fp)
{
	int c;
	Str_clear(self);
	while ((c = getc(fp)) != EOF && c != '\n') {
		Str_push(self, c);
	}
	return Str_getLength(self);
}

#endif
