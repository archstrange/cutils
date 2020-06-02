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
#ifndef CUTILS_I16Queue_H
#define CUTILS_I16Queue_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// I16Queue: a cycled queue type.
typedef struct _ADT_I16Queue_ *I16Queue;

/// Create a new I16Queue object.
I16Queue I16Queue_new();

/// Create a new I16Queue object with size @capacity.
I16Queue I16Queue_newWithCapacity(size_t capacity);

I16Queue I16Queue_clone(I16Queue self);

void I16Queue_copy(I16Queue self, I16Queue src);

/// Free @self.
void I16Queue_free(I16Queue self);

/// Check if @self is empty.
bool I16Queue_empty(I16Queue self);

/// Check if @self is full.
bool I16Queue_full(I16Queue self);

/// Get the current number of elements in queue @self.
size_t I16Queue_length(I16Queue self);

/// Get the @index'th element in queue @self.
///
/// Index started from head(indexed by 0) and should less then
/// @self's length, otherwise returned value is undefined.
int16_t I16Queue_get(I16Queue self, size_t index);

/// Set the @index'th element.
///
/// If @index is not less then @self's length, nothing
/// will be done.
void I16Queue_set(I16Queue self, size_t index, int16_t value);

/// Pop head element.
/// Returned value is undefined if @self is empty.
int16_t I16Queue_popHead(I16Queue self);

/// Pop tail element.
/// Returned value is undefined if @self is empty.
int16_t I16Queue_popTail(I16Queue self);

/// Push @value to head of @self.
void I16Queue_pushHead(I16Queue self, int16_t value);

/// Push @value to tail of @self.
void I16Queue_pushTail(I16Queue self, int16_t value);

#endif
