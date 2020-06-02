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
#ifndef CUTILS_F64Queue_H
#define CUTILS_F64Queue_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// F64Queue: a cycled queue type.
typedef struct _ADT_F64Queue_ *F64Queue;

/// Create a new F64Queue object.
F64Queue F64Queue_new();

/// Create a new F64Queue object with size @capacity.
F64Queue F64Queue_newWithCapacity(size_t capacity);

F64Queue F64Queue_clone(F64Queue self);

void F64Queue_copy(F64Queue self, F64Queue src);

/// Free @self.
void F64Queue_free(F64Queue self);

/// Check if @self is empty.
bool F64Queue_empty(F64Queue self);

/// Check if @self is full.
bool F64Queue_full(F64Queue self);

/// Get the current number of elements in queue @self.
size_t F64Queue_length(F64Queue self);

/// Get the @index'th element in queue @self.
///
/// Index started from head(indexed by 0) and should less then
/// @self's length, otherwise returned value is undefined.
double F64Queue_get(F64Queue self, size_t index);

/// Set the @index'th element.
///
/// If @index is not less then @self's length, nothing
/// will be done.
void F64Queue_set(F64Queue self, size_t index, double value);

/// Pop head element.
/// Returned value is undefined if @self is empty.
double F64Queue_popHead(F64Queue self);

/// Pop tail element.
/// Returned value is undefined if @self is empty.
double F64Queue_popTail(F64Queue self);

/// Push @value to head of @self.
void F64Queue_pushHead(F64Queue self, double value);

/// Push @value to tail of @self.
void F64Queue_pushTail(F64Queue self, double value);

#endif
