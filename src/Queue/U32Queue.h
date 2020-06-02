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
#ifndef CUTILS_U32Queue_H
#define CUTILS_U32Queue_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// U32Queue: a cycled queue type.
typedef struct _ADT_U32Queue_ *U32Queue;

/// Create a new U32Queue object.
U32Queue U32Queue_new();

/// Create a new U32Queue object with size @capacity.
U32Queue U32Queue_newWithCapacity(size_t capacity);

U32Queue U32Queue_clone(U32Queue self);

void U32Queue_copy(U32Queue self, U32Queue src);

/// Free @self.
void U32Queue_free(U32Queue self);

/// Check if @self is empty.
bool U32Queue_empty(U32Queue self);

/// Check if @self is full.
bool U32Queue_full(U32Queue self);

/// Get the current number of elements in queue @self.
size_t U32Queue_length(U32Queue self);

/// Get the @index'th element in queue @self.
///
/// Index started from head(indexed by 0) and should less then
/// @self's length, otherwise returned value is undefined.
uint32_t U32Queue_get(U32Queue self, size_t index);

/// Set the @index'th element.
///
/// If @index is not less then @self's length, nothing
/// will be done.
void U32Queue_set(U32Queue self, size_t index, uint32_t value);

/// Pop head element.
/// Returned value is undefined if @self is empty.
uint32_t U32Queue_popHead(U32Queue self);

/// Pop tail element.
/// Returned value is undefined if @self is empty.
uint32_t U32Queue_popTail(U32Queue self);

/// Push @value to head of @self.
void U32Queue_pushHead(U32Queue self, uint32_t value);

/// Push @value to tail of @self.
void U32Queue_pushTail(U32Queue self, uint32_t value);

#endif
