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
#ifndef CUTILS_DICT_StrU32Dict_H
#define CUTILS_DICT_StrU32Dict_H
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Str.h"

typedef struct cutils_StrU32Dict_ *StrU32Dict;

StrU32Dict StrU32Dict_new();

StrU32Dict StrU32Dict_newWithSize(size_t size);

StrU32Dict StrU32Dict_clone(StrU32Dict src);

void StrU32Dict_copy(StrU32Dict self, StrU32Dict src);

void StrU32Dict_free(StrU32Dict self);

size_t StrU32Dict_getLength(StrU32Dict self);

void StrU32Dict_setSize(StrU32Dict self, size_t size);

void StrU32Dict_insert(StrU32Dict self, Str key, uint32_t value);

bool StrU32Dict_find(StrU32Dict self, Str key, uint32_t *value);

bool StrU32Dict_delete(StrU32Dict self, Str key);



#endif
