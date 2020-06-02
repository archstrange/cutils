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
#ifndef ADT_TEMPLATE_U32Vector_H
#define ADT_TEMPLATE_U32Vector_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// U32Vector: Vector of uint32_t, generated from `Vector.[ch].ohce`.
typedef struct _ADT_U32Vector *U32Vector;

/// Lifetime function: create a new U32Vector object.
U32Vector U32Vector_new();

/// Lifetime function: create a new U32Vector object with @capacity.
U32Vector U32Vector_newWithCapacity(size_t capacity);

/// Lifetime function: create a new U32Vector object from @array.
U32Vector U32Vector_newFromArray(const uint32_t *array, size_t length);

/// Lifetime function: clone the whole @src object.
U32Vector U32Vector_clone(U32Vector src);

/// Lifetime function: copy the whole @src object to @self.
void U32Vector_copy(U32Vector self, U32Vector src);

/// Copy the first @n elements of @src to @self.
void U32Vector_copyArray(U32Vector self, const uint32_t *array, size_t n);

/// Copy @n elements of @src started at @start to @self.
///
/// If @start is greater than @self's length or @self and @src
/// are the same object, nothing will be done.
///
/// If @src has not enough elements from @start, `U32Vector_copySub`
/// will stop after it copyed the last element.
void U32Vector_copySub(U32Vector self, U32Vector src, size_t start, size_t n);

/// Lifetime function: free @self object.
void U32Vector_free(U32Vector self);


/// Compare two U32Vectors.
int U32Vector_cmp(U32Vector self, U32Vector right);

/// Check equality.
bool U32Vector_equal(U32Vector self, U32Vector right);

/// Hash this object.
uint32_t U32Vector_hash(U32Vector self);

/// Dump all elements to @buffer. @buffer must hold enough space
/// to store all elements.
/// Note: conten of @buffer will be overwrited, if uint32_t holds
/// dynamic memorys then only pointers are dumped.
///
/// Return: count of elements dumped.
size_t U32Vector_dump(U32Vector self, uint32_t *buffer);

/// Same as `U32Vector_dump`, but the first @n elements only.
size_t U32Vector_dumpn(U32Vector self, uint32_t *buffer, size_t n);

/// Check if @self if empty.
bool U32Vector_empty(U32Vector self);

/// Get length of @self.
size_t U32Vector_getLength(U32Vector self);


/// Clear all elements.
void U32Vector_clear(U32Vector self);

/// Try to erase the last elements of @self as much(@count) as it can.
void U32Vector_eraseTail(U32Vector self, size_t count);

/// Get capacity of @self.
size_t U32Vector_getCapacity(U32Vector self);

/// Tell U32Vector to preallocate enough memory. U32Vector's length
/// may be changed. Normally U32Vector will handle its memory
/// automatically, so call this if you want U32Vector to use specific size
/// of memory.
///
/// U32Vector always handle memory automatically, so capacity maybe changed
/// if you remove or add elements to @self.
void U32Vector_setCapacity(U32Vector self, size_t capacity);

/// Set capacity to its length.
void U32Vector_shrink(U32Vector self);

/// Same meanding as `self[index] = value`.
/// @index must be less than length of @self.
void U32Vector_set(U32Vector self, size_t index, uint32_t value);

/// Same meanding as `self[index]`.
/// @index must be less than length of @self.
uint32_t U32Vector_get(U32Vector self, size_t index);

/// Insert @value to `self[index]`, all elements after will be
/// moved backward.
/// @index should be less than length of @self, otherwise
/// nothing will be done.
///
/// Return length after this call.
size_t U32Vector_insert(U32Vector self, size_t index, uint32_t value);

/// Get internal buffer.
///
/// This is unsafe, be aware what you are doing.
uint32_t *U32Vector_data(U32Vector self);

/// Push @value to the back of @self.
size_t U32Vector_push(U32Vector self, uint32_t value);

/// Pop out the last element. If no elements left, the returned
/// value is undefined.
uint32_t U32Vector_pop(U32Vector self);

/// Append @src to @self.
size_t U32Vector_append(U32Vector self, U32Vector src);

/// Append a uint32_t array to @self.
size_t U32Vector_appendArray(U32Vector self, const uint32_t *a, size_t count);

#endif
