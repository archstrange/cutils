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
#ifndef ADT_TEMPLATE_I32Vector_H
#define ADT_TEMPLATE_I32Vector_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// I32Vector: Vector of int32_t, generated from `Vector.[ch].ohce`.
typedef struct _ADT_I32Vector *I32Vector;

/// Lifetime function: create a new I32Vector object.
I32Vector I32Vector_new();

/// Lifetime function: create a new I32Vector object with @capacity.
I32Vector I32Vector_newWithCapacity(size_t capacity);

/// Lifetime function: create a new I32Vector object from @array.
I32Vector I32Vector_newFromArray(const int32_t *array, size_t length);

/// Lifetime function: clone the whole @src object.
I32Vector I32Vector_clone(I32Vector src);

/// Lifetime function: copy the whole @src object to @self.
void I32Vector_copy(I32Vector self, I32Vector src);

/// Copy the first @n elements of @src to @self.
void I32Vector_copyArray(I32Vector self, const int32_t *array, size_t n);

/// Copy @n elements of @src started at @start to @self.
///
/// If @start is greater than @self's length or @self and @src
/// are the same object, nothing will be done.
///
/// If @src has not enough elements from @start, `I32Vector_copySub`
/// will stop after it copyed the last element.
void I32Vector_copySub(I32Vector self, I32Vector src, size_t start, size_t n);

/// Lifetime function: free @self object.
void I32Vector_free(I32Vector self);


/// Compare two I32Vectors.
int I32Vector_cmp(I32Vector self, I32Vector right);

/// Check equality.
bool I32Vector_equal(I32Vector self, I32Vector right);

/// Hash this object.
uint32_t I32Vector_hash(I32Vector self);

/// Dump all elements to @buffer. @buffer must hold enough space
/// to store all elements.
/// Note: conten of @buffer will be overwrited, if int32_t holds
/// dynamic memorys then only pointers are dumped.
///
/// Return: count of elements dumped.
size_t I32Vector_dump(I32Vector self, int32_t *buffer);

/// Same as `I32Vector_dump`, but the first @n elements only.
size_t I32Vector_dumpn(I32Vector self, int32_t *buffer, size_t n);

/// Check if @self if empty.
bool I32Vector_empty(I32Vector self);

/// Get length of @self.
size_t I32Vector_getLength(I32Vector self);


/// Clear all elements.
void I32Vector_clear(I32Vector self);

/// Try to erase the last elements of @self as much(@count) as it can.
void I32Vector_eraseTail(I32Vector self, size_t count);

/// Get capacity of @self.
size_t I32Vector_getCapacity(I32Vector self);

/// Tell I32Vector to preallocate enough memory. I32Vector's length
/// may be changed. Normally I32Vector will handle its memory
/// automatically, so call this if you want I32Vector to use specific size
/// of memory.
///
/// I32Vector always handle memory automatically, so capacity maybe changed
/// if you remove or add elements to @self.
void I32Vector_setCapacity(I32Vector self, size_t capacity);

/// Set capacity to its length.
void I32Vector_shrink(I32Vector self);

/// Same meanding as `self[index] = value`.
/// @index must be less than length of @self.
void I32Vector_set(I32Vector self, size_t index, int32_t value);

/// Same meanding as `self[index]`.
/// @index must be less than length of @self.
int32_t I32Vector_get(I32Vector self, size_t index);

/// Insert @value to `self[index]`, all elements after will be
/// moved backward.
/// @index should be less than length of @self, otherwise
/// nothing will be done.
///
/// Return length after this call.
size_t I32Vector_insert(I32Vector self, size_t index, int32_t value);

/// Get internal buffer.
///
/// This is unsafe, be aware what you are doing.
int32_t *I32Vector_data(I32Vector self);

/// Push @value to the back of @self.
size_t I32Vector_push(I32Vector self, int32_t value);

/// Pop out the last element. If no elements left, the returned
/// value is undefined.
int32_t I32Vector_pop(I32Vector self);

/// Append @src to @self.
size_t I32Vector_append(I32Vector self, I32Vector src);

/// Append a int32_t array to @self.
size_t I32Vector_appendArray(I32Vector self, const int32_t *a, size_t count);

#endif
