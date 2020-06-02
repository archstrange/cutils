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
#ifndef CUTILS_I32Queue_H
#define CUTILS_I32Queue_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// I32Queue: a cycled queue type.
typedef struct _ADT_I32Queue_ *I32Queue;

/// Create a new I32Queue object.
I32Queue I32Queue_new();

/// Create a new I32Queue object with size @capacity.
I32Queue I32Queue_newWithCapacity(size_t capacity);

I32Queue I32Queue_clone(I32Queue self);

void I32Queue_copy(I32Queue self, I32Queue src);

/// Free @self.
void I32Queue_free(I32Queue self);

/// Check if @self is empty.
bool I32Queue_empty(I32Queue self);

/// Check if @self is full.
bool I32Queue_full(I32Queue self);

/// Get the current number of elements in queue @self.
size_t I32Queue_length(I32Queue self);

/// Get the @index'th element in queue @self.
///
/// Index started from head(indexed by 0) and should less then
/// @self's length, otherwise returned value is undefined.
int32_t I32Queue_get(I32Queue self, size_t index);

/// Set the @index'th element.
///
/// If @index is not less then @self's length, nothing
/// will be done.
void I32Queue_set(I32Queue self, size_t index, int32_t value);

/// Pop head element.
/// Returned value is undefined if @self is empty.
int32_t I32Queue_popHead(I32Queue self);

/// Pop tail element.
/// Returned value is undefined if @self is empty.
int32_t I32Queue_popTail(I32Queue self);

/// Push @value to head of @self.
void I32Queue_pushHead(I32Queue self, int32_t value);

/// Push @value to tail of @self.
void I32Queue_pushTail(I32Queue self, int32_t value);

#endif
