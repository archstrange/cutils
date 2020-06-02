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
#ifndef CUTILS_U64Queue_H
#define CUTILS_U64Queue_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// U64Queue: a cycled queue type.
typedef struct _ADT_U64Queue_ *U64Queue;

/// Create a new U64Queue object.
U64Queue U64Queue_new();

/// Create a new U64Queue object with size @capacity.
U64Queue U64Queue_newWithCapacity(size_t capacity);

U64Queue U64Queue_clone(U64Queue self);

void U64Queue_copy(U64Queue self, U64Queue src);

/// Free @self.
void U64Queue_free(U64Queue self);

/// Check if @self is empty.
bool U64Queue_empty(U64Queue self);

/// Check if @self is full.
bool U64Queue_full(U64Queue self);

/// Get the current number of elements in queue @self.
size_t U64Queue_length(U64Queue self);

/// Get the @index'th element in queue @self.
///
/// Index started from head(indexed by 0) and should less then
/// @self's length, otherwise returned value is undefined.
uint64_t U64Queue_get(U64Queue self, size_t index);

/// Set the @index'th element.
///
/// If @index is not less then @self's length, nothing
/// will be done.
void U64Queue_set(U64Queue self, size_t index, uint64_t value);

/// Pop head element.
/// Returned value is undefined if @self is empty.
uint64_t U64Queue_popHead(U64Queue self);

/// Pop tail element.
/// Returned value is undefined if @self is empty.
uint64_t U64Queue_popTail(U64Queue self);

/// Push @value to head of @self.
void U64Queue_pushHead(U64Queue self, uint64_t value);

/// Push @value to tail of @self.
void U64Queue_pushTail(U64Queue self, uint64_t value);

#endif
