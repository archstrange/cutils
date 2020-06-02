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
#ifndef CUTILS_U16Queue_H
#define CUTILS_U16Queue_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// U16Queue: a cycled queue type.
typedef struct _ADT_U16Queue_ *U16Queue;

/// Create a new U16Queue object.
U16Queue U16Queue_new();

/// Create a new U16Queue object with size @capacity.
U16Queue U16Queue_newWithCapacity(size_t capacity);

U16Queue U16Queue_clone(U16Queue self);

void U16Queue_copy(U16Queue self, U16Queue src);

/// Free @self.
void U16Queue_free(U16Queue self);

/// Check if @self is empty.
bool U16Queue_empty(U16Queue self);

/// Check if @self is full.
bool U16Queue_full(U16Queue self);

/// Get the current number of elements in queue @self.
size_t U16Queue_length(U16Queue self);

/// Get the @index'th element in queue @self.
///
/// Index started from head(indexed by 0) and should less then
/// @self's length, otherwise returned value is undefined.
uint16_t U16Queue_get(U16Queue self, size_t index);

/// Set the @index'th element.
///
/// If @index is not less then @self's length, nothing
/// will be done.
void U16Queue_set(U16Queue self, size_t index, uint16_t value);

/// Pop head element.
/// Returned value is undefined if @self is empty.
uint16_t U16Queue_popHead(U16Queue self);

/// Pop tail element.
/// Returned value is undefined if @self is empty.
uint16_t U16Queue_popTail(U16Queue self);

/// Push @value to head of @self.
void U16Queue_pushHead(U16Queue self, uint16_t value);

/// Push @value to tail of @self.
void U16Queue_pushTail(U16Queue self, uint16_t value);

#endif
