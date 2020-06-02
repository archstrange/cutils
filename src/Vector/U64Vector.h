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

// This file is generated from Vector.h.ohce by ohce.
#ifndef ADT_TEMPLATE_U64Vector_H
#define ADT_TEMPLATE_U64Vector_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// U64Vector: Vector of uint64_t, generated from `Vector.[ch].ohce`.
typedef struct _ADT_U64Vector *U64Vector;

/// Lifetime function: create a new U64Vector object.
U64Vector U64Vector_new();

/// Lifetime function: create a new U64Vector object with @capacity.
U64Vector U64Vector_newWithCapacity(size_t capacity);

/// Lifetime function: create a new U64Vector object from @array.
U64Vector U64Vector_newFromArray(const uint64_t *array, size_t length);

/// Lifetime function: clone the whole @src object.
U64Vector U64Vector_clone(U64Vector src);

/// Lifetime function: copy the whole @src object to @self.
void U64Vector_copy(U64Vector self, U64Vector src);

/// Copy the first @n elements of @src to @self.
void U64Vector_copyArray(U64Vector self, const uint64_t *array, size_t n);

/// Copy @n elements of @src started at @start to @self.
///
/// If @start is greater than @self's length or @self and @src
/// are the same object, nothing will be done.
///
/// If @src has not enough elements from @start, `U64Vector_copySub`
/// will stop after it copyed the last element.
void U64Vector_copySub(U64Vector self, U64Vector src, size_t start, size_t n);

/// Lifetime function: free @self object.
void U64Vector_free(U64Vector self);


/// Compare two U64Vectors.
int U64Vector_cmp(U64Vector self, U64Vector right);

/// Check equality.
bool U64Vector_equal(U64Vector self, U64Vector right);

/// Hash this object.
uint32_t U64Vector_hash(U64Vector self);

/// Dump all elements to @buffer. @buffer must hold enough space
/// to store all elements.
/// Note: conten of @buffer will be overwrited, if uint64_t holds
/// dynamic memorys then only pointers are dumped.
///
/// Return: count of elements dumped.
size_t U64Vector_dump(U64Vector self, uint64_t *buffer);

/// Same as `U64Vector_dump`, but the first @n elements only.
size_t U64Vector_dumpn(U64Vector self, uint64_t *buffer, size_t n);

/// Check if @self if empty.
bool U64Vector_empty(U64Vector self);

/// Get length of @self.
size_t U64Vector_getLength(U64Vector self);


/// Clear all elements.
void U64Vector_clear(U64Vector self);

/// Try to erase the last elements of @self as much(@count) as it can.
void U64Vector_eraseTail(U64Vector self, size_t count);

/// Get capacity of @self.
size_t U64Vector_getCapacity(U64Vector self);

/// Tell U64Vector to preallocate enough memory. U64Vector's length
/// may be changed. Normally U64Vector will handle its memory
/// automatically, so call this if you want U64Vector to use specific size
/// of memory.
///
/// U64Vector always handle memory automatically, so capacity maybe changed
/// if you remove or add elements to @self.
void U64Vector_setCapacity(U64Vector self, size_t capacity);

/// Set capacity to its length.
void U64Vector_shrink(U64Vector self);

/// Same meanding as `self[index] = value`.
/// @index must be less than length of @self.
void U64Vector_set(U64Vector self, size_t index, uint64_t value);

/// Same meanding as `self[index]`.
/// @index must be less than length of @self.
uint64_t U64Vector_get(U64Vector self, size_t index);

/// Insert @value to `self[index]`, all elements after will be
/// moved backward.
/// @index should be less than length of @self, otherwise
/// nothing will be done.
///
/// Return length after this call.
size_t U64Vector_insert(U64Vector self, size_t index, uint64_t value);

/// Get internal buffer.
///
/// This is unsafe, be aware what you are doing.
uint64_t *U64Vector_data(U64Vector self);

/// Push @value to the back of @self.
size_t U64Vector_push(U64Vector self, uint64_t value);

/// Pop out the last element. If no elements left, the returned
/// value is undefined.
uint64_t U64Vector_pop(U64Vector self);

/// Append @src to @self.
size_t U64Vector_append(U64Vector self, U64Vector src);

/// Append a uint64_t array to @self.
size_t U64Vector_appendArray(U64Vector self, const uint64_t *a, size_t count);

#endif
