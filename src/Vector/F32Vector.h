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
#ifndef ADT_TEMPLATE_F32Vector_H
#define ADT_TEMPLATE_F32Vector_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// F32Vector: Vector of float, generated from `Vector.[ch].ohce`.
typedef struct _ADT_F32Vector *F32Vector;

/// Lifetime function: create a new F32Vector object.
F32Vector F32Vector_new();

/// Lifetime function: create a new F32Vector object with @capacity.
F32Vector F32Vector_newWithCapacity(size_t capacity);

/// Lifetime function: create a new F32Vector object from @array.
F32Vector F32Vector_newFromArray(const float *array, size_t length);

/// Lifetime function: clone the whole @src object.
F32Vector F32Vector_clone(F32Vector src);

/// Lifetime function: copy the whole @src object to @self.
void F32Vector_copy(F32Vector self, F32Vector src);

/// Copy the first @n elements of @src to @self.
void F32Vector_copyArray(F32Vector self, const float *array, size_t n);

/// Copy @n elements of @src started at @start to @self.
///
/// If @start is greater than @self's length or @self and @src
/// are the same object, nothing will be done.
///
/// If @src has not enough elements from @start, `F32Vector_copySub`
/// will stop after it copyed the last element.
void F32Vector_copySub(F32Vector self, F32Vector src, size_t start, size_t n);

/// Lifetime function: free @self object.
void F32Vector_free(F32Vector self);


/// Compare two F32Vectors.
int F32Vector_cmp(F32Vector self, F32Vector right);

/// Check equality.
bool F32Vector_equal(F32Vector self, F32Vector right);

/// Hash this object.
uint32_t F32Vector_hash(F32Vector self);

/// Dump all elements to @buffer. @buffer must hold enough space
/// to store all elements.
/// Note: conten of @buffer will be overwrited, if float holds
/// dynamic memorys then only pointers are dumped.
///
/// Return: count of elements dumped.
size_t F32Vector_dump(F32Vector self, float *buffer);

/// Same as `F32Vector_dump`, but the first @n elements only.
size_t F32Vector_dumpn(F32Vector self, float *buffer, size_t n);

/// Check if @self if empty.
bool F32Vector_empty(F32Vector self);

/// Get length of @self.
size_t F32Vector_getLength(F32Vector self);


/// Clear all elements.
void F32Vector_clear(F32Vector self);

/// Try to erase the last elements of @self as much(@count) as it can.
void F32Vector_eraseTail(F32Vector self, size_t count);

/// Get capacity of @self.
size_t F32Vector_getCapacity(F32Vector self);

/// Tell F32Vector to preallocate enough memory. F32Vector's length
/// may be changed. Normally F32Vector will handle its memory
/// automatically, so call this if you want F32Vector to use specific size
/// of memory.
///
/// F32Vector always handle memory automatically, so capacity maybe changed
/// if you remove or add elements to @self.
void F32Vector_setCapacity(F32Vector self, size_t capacity);

/// Set capacity to its length.
void F32Vector_shrink(F32Vector self);

/// Same meanding as `self[index] = value`.
/// @index must be less than length of @self.
void F32Vector_set(F32Vector self, size_t index, float value);

/// Same meanding as `self[index]`.
/// @index must be less than length of @self.
float F32Vector_get(F32Vector self, size_t index);

/// Insert @value to `self[index]`, all elements after will be
/// moved backward.
/// @index should be less than length of @self, otherwise
/// nothing will be done.
///
/// Return length after this call.
size_t F32Vector_insert(F32Vector self, size_t index, float value);

/// Get internal buffer.
///
/// This is unsafe, be aware what you are doing.
float *F32Vector_data(F32Vector self);

/// Push @value to the back of @self.
size_t F32Vector_push(F32Vector self, float value);

/// Pop out the last element. If no elements left, the returned
/// value is undefined.
float F32Vector_pop(F32Vector self);

/// Append @src to @self.
size_t F32Vector_append(F32Vector self, F32Vector src);

/// Append a float array to @self.
size_t F32Vector_appendArray(F32Vector self, const float *a, size_t count);

#endif
