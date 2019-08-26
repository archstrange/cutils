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

#ifndef SAD_PS_H
#define SAD_PS_H
#include <stdint.h>
#include <stdio.h>
#include "Vector/Str.h"
#include "Vector/U32Vector.h"

/// Parser Source Object
/// PS has its own source string, so if you new a PS from string,
/// you can do whatever to that string which won't effect PS at all.
///
/// Example:
///
///	PS ps = PS_newFromCStr("parser source string", PS_SOURCE_ASCII);
///	for (int c; (c = PS_curChar(ps)) > 0; PS_next(ps)) {
///		printf("line %lu column %lu is %c\n",
///		       PS_curLine(ps),
///		       PS_curColumn(ps),
///		       c);
///	}
///	PS_free(ps);
///
/// If current char is new-line, curLine will be increased and curColumn
/// will be 0.
typedef struct _sad_ps_ *PS;

/// Special current chars
enum {
	PS_BAD_SOURCE = -3, /// wrong encoding
	PS_BAD_POS = -2,
	PS_END = -1, /// end of PS
};

/// PS encoding
enum {
	PS_SOURCE_ASCII = 0,
	PS_SOURCE_UTF8,
};

PS PS_newFromStr(Str src, int encoding);

PS PS_newFromCStr(const char *src, int encoding);

PS PS_newFromFILE(FILE *src, int encoding);

void PS_free(PS self);

/// Get current char index
size_t PS_curIndex(PS self);

/// Get current char
int PS_curChar(PS self);

/// Get current char's logic position -- line.
size_t PS_curLine(PS self);

/// Get current char's logic position -- column.
size_t PS_curColumn(PS self);

/// Goto next char
void PS_next(PS self);

/// Peek char at curIndex + offset.
/// PS_BAD_POS maybe returned.
int PS_peek(PS self, int offset);

/// Set user defined error code.
/// PS will init it with zero.
void PS_setErrorCode(PS self, int code);

/// Get user defined error code.
int PS_getErrorCode(PS self);

#endif

