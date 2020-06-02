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
#ifndef CUTILS_I64Queue_H
#define CUTILS_I64Queue_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// I64Queue: a cycled queue type.
typedef struct _ADT_I64Queue_ *I64Queue;

/// Create a new I64Queue object.
I64Queue I64Queue_new();

/// Create a new I64Queue object with size @capacity.
I64Queue I64Queue_newWithCapacity(size_t capacity);

I64Queue I64Queue_clone(I64Queue self);

void I64Queue_copy(I64Queue self, I64Queue src);

/// Free @self.
void I64Queue_free(I64Queue self);

/// Check if @self is empty.
bool I64Queue_empty(I64Queue self);

/// Check if @self is full.
bool I64Queue_full(I64Queue self);

/// Get the current number of elements in queue @self.
size_t I64Queue_length(I64Queue self);

/// Get the @index'th element in queue @self.
///
/// Index started from head(indexed by 0) and should less then
/// @self's length, otherwise returned value is undefined.
int64_t I64Queue_get(I64Queue self, size_t index);

/// Set the @index'th element.
///
/// If @index is not less then @self's length, nothing
/// will be done.
void I64Queue_set(I64Queue self, size_t index, int64_t value);

/// Pop head element.
/// Returned value is undefined if @self is empty.
int64_t I64Queue_popHead(I64Queue self);

/// Pop tail element.
/// Returned value is undefined if @self is empty.
int64_t I64Queue_popTail(I64Queue self);

/// Push @value to head of @self.
void I64Queue_pushHead(I64Queue self, int64_t value);

/// Push @value to tail of @self.
void I64Queue_pushTail(I64Queue self, int64_t value);

#endif
