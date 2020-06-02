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

// This file is generated from Queue.h.ohce by ohce.
#ifndef CUTILS_StrQueue_H
#define CUTILS_StrQueue_H
#include "../Vector/Str.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// StrQueue: a cycled queue type.
typedef struct _ADT_StrQueue_ *StrQueue;

/// Create a new StrQueue object.
StrQueue StrQueue_new();

/// Create a new StrQueue object with size @capacity.
StrQueue StrQueue_newWithCapacity(size_t capacity);

StrQueue StrQueue_clone(StrQueue self);

void StrQueue_copy(StrQueue self, StrQueue src);

/// Free @self.
void StrQueue_free(StrQueue self);

/// Check if @self is empty.
bool StrQueue_empty(StrQueue self);

/// Check if @self is full.
bool StrQueue_full(StrQueue self);

/// Get the current number of elements in queue @self.
size_t StrQueue_length(StrQueue self);

/// Get the @index'th element in queue @self.
///
/// Index started from head(indexed by 0) and should less then
/// @self's length, otherwise returned value is undefined.
Str StrQueue_get(StrQueue self, size_t index);

/// Set the @index'th element.
///
/// If @index is not less then @self's length, nothing
/// will be done.
/// Generic method `set`.
#define StrQueue_set(self, index, value) \
_Generic(value, \
	 Str: __StrQueue_set_use_assign, \
	 default: __StrQueue_set_use_copy \
) (self, index, value)

void __StrQueue_set_use_assign(StrQueue self, size_t index, Str value);
void __StrQueue_set_use_copy(StrQueue self, size_t index, Str *value);

/// Pop head element.
/// Returned value is undefined if @self is empty.
Str StrQueue_popHead(StrQueue self);

/// Pop tail element.
/// Returned value is undefined if @self is empty.
Str StrQueue_popTail(StrQueue self);

/// Push @value to head of @self.
/// Generic method `pushHead`.
#define StrQueue_pushHead(self, value) \
_Generic(value, \
	 Str: __StrQueue_pushHead_use_assign, \
	 default: __StrQueue_pushHead_use_clone \
) (self, value)

void __StrQueue_pushHead_use_assign(StrQueue self, Str value);
void __StrQueue_pushHead_use_clone(StrQueue self, Str *value);

/// Push @value to tail of @self.
/// Generic method `pushTail`.
#define StrQueue_pushTail(self, value) \
_Generic(value, \
	 Str: __StrQueue_pushTail_use_assign, \
	 default: __StrQueue_pushTail_use_clone \
) (self, value)

void __StrQueue_pushTail_use_assign(StrQueue self, Str value);
void __StrQueue_pushTail_use_clone(StrQueue self, Str *value);

#endif
