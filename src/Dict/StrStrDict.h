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

// This file is generated from Dict.h.ohce by ohce.
#ifndef CUTILS_DICT_StrStrDict_H
#define CUTILS_DICT_StrStrDict_H
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Str.h"

typedef struct cutils_StrStrDict_ *StrStrDict;

StrStrDict StrStrDict_new();

StrStrDict StrStrDict_newWithSize(size_t size);

StrStrDict StrStrDict_clone(StrStrDict src);

void StrStrDict_copy(StrStrDict self, StrStrDict src);

void StrStrDict_free(StrStrDict self);

size_t StrStrDict_getLength(StrStrDict self);

void StrStrDict_setSize(StrStrDict self, size_t size);

#define StrStrDict_insert(self, key, value) \
_Generic(value, \
	 Str: __StrStrDict_insert_use_assign, \
	 default: __StrStrDict_insert_use_clone \
) (self, key, value)

void __StrStrDict_insert_use_clone(StrStrDict self, Str key, Str *value);
void __StrStrDict_insert_use_assign(StrStrDict self, Str key, Str value);

bool StrStrDict_find(StrStrDict self, Str key, Str *value);

bool StrStrDict_delete(StrStrDict self, Str key);



#endif
