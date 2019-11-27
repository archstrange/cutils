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

#ifndef CUTILS_LS_H
#define CUTILS_LS_H
#include "Str.h"
#include <stdio.h>
#include <stdbool.h>

enum {
	LS_BAD_SOURCE = -3, /// Bad source format
	LS_BAD_POS = -2, /// Bad position
	LS_EOS = -1, /// Eod Of Source
};

typedef struct _LexerSource_ *LS;

LS LS_newStrSource(Str s, bool is_utf8);

LS LS_newCStrSource(const char *s, bool is_utf8);

LS LS_newFileSource(FILE *fp, bool is_utf8, bool is_interact);

void LS_free(LS self);

int LS_char(LS self);

void LS_position(LS self, size_t *index, size_t *row, size_t *column);

bool LS_next(LS self);

int LS_peek(LS self, int64_t pos);

#endif

