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
#ifndef CUTILS_F32Queue_H
#define CUTILS_F32Queue_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// F32Queue: a cycled queue type.
typedef struct _ADT_F32Queue_ *F32Queue;

/// Create a new F32Queue object.
F32Queue F32Queue_new();

/// Create a new F32Queue object with size @capacity.
F32Queue F32Queue_newWithCapacity(size_t capacity);

F32Queue F32Queue_clone(F32Queue self);

void F32Queue_copy(F32Queue self, F32Queue src);

/// Free @self.
void F32Queue_free(F32Queue self);

/// Check if @self is empty.
bool F32Queue_empty(F32Queue self);

/// Check if @self is full.
bool F32Queue_full(F32Queue self);

/// Get the current number of elements in queue @self.
size_t F32Queue_length(F32Queue self);

/// Get the @index'th element in queue @self.
///
/// Index started from head(indexed by 0) and should less then
/// @self's length, otherwise returned value is undefined.
float F32Queue_get(F32Queue self, size_t index);

/// Set the @index'th element.
///
/// If @index is not less then @self's length, nothing
/// will be done.
void F32Queue_set(F32Queue self, size_t index, float value);

/// Pop head element.
/// Returned value is undefined if @self is empty.
float F32Queue_popHead(F32Queue self);

/// Pop tail element.
/// Returned value is undefined if @self is empty.
float F32Queue_popTail(F32Queue self);

/// Push @value to head of @self.
void F32Queue_pushHead(F32Queue self, float value);

/// Push @value to tail of @self.
void F32Queue_pushTail(F32Queue self, float value);

#endif
