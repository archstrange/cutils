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
#ifndef CUTILS_I8Queue_H
#define CUTILS_I8Queue_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// I8Queue: a cycled queue type.
typedef struct _ADT_I8Queue_ *I8Queue;

/// Create a new I8Queue object.
I8Queue I8Queue_new();

/// Create a new I8Queue object with size @capacity.
I8Queue I8Queue_newWithCapacity(size_t capacity);

I8Queue I8Queue_clone(I8Queue self);

void I8Queue_copy(I8Queue self, I8Queue src);

/// Free @self.
void I8Queue_free(I8Queue self);

/// Check if @self is empty.
bool I8Queue_empty(I8Queue self);

/// Check if @self is full.
bool I8Queue_full(I8Queue self);

/// Get the current number of elements in queue @self.
size_t I8Queue_length(I8Queue self);

/// Get the @index'th element in queue @self.
///
/// Index started from head(indexed by 0) and should less then
/// @self's length, otherwise returned value is undefined.
int8_t I8Queue_get(I8Queue self, size_t index);

/// Set the @index'th element.
///
/// If @index is not less then @self's length, nothing
/// will be done.
void I8Queue_set(I8Queue self, size_t index, int8_t value);

/// Pop head element.
/// Returned value is undefined if @self is empty.
int8_t I8Queue_popHead(I8Queue self);

/// Pop tail element.
/// Returned value is undefined if @self is empty.
int8_t I8Queue_popTail(I8Queue self);

/// Push @value to head of @self.
void I8Queue_pushHead(I8Queue self, int8_t value);

/// Push @value to tail of @self.
void I8Queue_pushTail(I8Queue self, int8_t value);

#endif
