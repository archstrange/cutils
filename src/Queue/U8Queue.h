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
#ifndef CUTILS_U8Queue_H
#define CUTILS_U8Queue_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// U8Queue: a cycled queue type.
typedef struct _ADT_U8Queue_ *U8Queue;

/// Create a new U8Queue object.
U8Queue U8Queue_new();

/// Create a new U8Queue object with size @capacity.
U8Queue U8Queue_newWithCapacity(size_t capacity);

U8Queue U8Queue_clone(U8Queue self);

void U8Queue_copy(U8Queue self, U8Queue src);

/// Free @self.
void U8Queue_free(U8Queue self);

/// Check if @self is empty.
bool U8Queue_empty(U8Queue self);

/// Check if @self is full.
bool U8Queue_full(U8Queue self);

/// Get the current number of elements in queue @self.
size_t U8Queue_length(U8Queue self);

/// Get the @index'th element in queue @self.
///
/// Index started from head(indexed by 0) and should less then
/// @self's length, otherwise returned value is undefined.
uint8_t U8Queue_get(U8Queue self, size_t index);

/// Set the @index'th element.
///
/// If @index is not less then @self's length, nothing
/// will be done.
void U8Queue_set(U8Queue self, size_t index, uint8_t value);

/// Pop head element.
/// Returned value is undefined if @self is empty.
uint8_t U8Queue_popHead(U8Queue self);

/// Pop tail element.
/// Returned value is undefined if @self is empty.
uint8_t U8Queue_popTail(U8Queue self);

/// Push @value to head of @self.
void U8Queue_pushHead(U8Queue self, uint8_t value);

/// Push @value to tail of @self.
void U8Queue_pushTail(U8Queue self, uint8_t value);

#endif
