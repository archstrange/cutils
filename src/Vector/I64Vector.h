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
#ifndef ADT_TEMPLATE_I64Vector_H
#define ADT_TEMPLATE_I64Vector_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// I64Vector: Vector of int64_t, generated from `Vector.[ch].ohce`.
typedef struct _ADT_I64Vector *I64Vector;

/// Lifetime function: create a new I64Vector object.
I64Vector I64Vector_new();

/// Lifetime function: create a new I64Vector object with @capacity.
I64Vector I64Vector_newWithCapacity(size_t capacity);

/// Lifetime function: create a new I64Vector object from @array.
I64Vector I64Vector_newFromArray(const int64_t *array, size_t length);

/// Lifetime function: clone the whole @src object.
I64Vector I64Vector_clone(I64Vector src);

/// Lifetime function: copy the whole @src object to @self.
void I64Vector_copy(I64Vector self, I64Vector src);

/// Copy the first @n elements of @src to @self.
void I64Vector_copyArray(I64Vector self, const int64_t *array, size_t n);

/// Copy @n elements of @src started at @start to @self.
///
/// If @start is greater than @self's length or @self and @src
/// are the same object, nothing will be done.
///
/// If @src has not enough elements from @start, `I64Vector_copySub`
/// will stop after it copyed the last element.
void I64Vector_copySub(I64Vector self, I64Vector src, size_t start, size_t n);

/// Lifetime function: free @self object.
void I64Vector_free(I64Vector self);


/// Compare two I64Vectors.
int I64Vector_cmp(I64Vector self, I64Vector right);

/// Check equality.
bool I64Vector_equal(I64Vector self, I64Vector right);

/// Hash this object.
uint32_t I64Vector_hash(I64Vector self);

/// Dump all elements to @buffer. @buffer must hold enough space
/// to store all elements.
/// Note: conten of @buffer will be overwrited, if int64_t holds
/// dynamic memorys then only pointers are dumped.
///
/// Return: count of elements dumped.
size_t I64Vector_dump(I64Vector self, int64_t *buffer);

/// Same as `I64Vector_dump`, but the first @n elements only.
size_t I64Vector_dumpn(I64Vector self, int64_t *buffer, size_t n);

/// Check if @self if empty.
bool I64Vector_empty(I64Vector self);

/// Get length of @self.
size_t I64Vector_getLength(I64Vector self);


/// Clear all elements.
void I64Vector_clear(I64Vector self);

/// Try to erase the last elements of @self as much(@count) as it can.
void I64Vector_eraseTail(I64Vector self, size_t count);

/// Get capacity of @self.
size_t I64Vector_getCapacity(I64Vector self);

/// Tell I64Vector to preallocate enough memory. I64Vector's length
/// may be changed. Normally I64Vector will handle its memory
/// automatically, so call this if you want I64Vector to use specific size
/// of memory.
///
/// I64Vector always handle memory automatically, so capacity maybe changed
/// if you remove or add elements to @self.
void I64Vector_setCapacity(I64Vector self, size_t capacity);

/// Set capacity to its length.
void I64Vector_shrink(I64Vector self);

/// Same meanding as `self[index] = value`.
/// @index must be less than length of @self.
void I64Vector_set(I64Vector self, size_t index, int64_t value);

/// Same meanding as `self[index]`.
/// @index must be less than length of @self.
int64_t I64Vector_get(I64Vector self, size_t index);

/// Insert @value to `self[index]`, all elements after will be
/// moved backward.
/// @index should be less than length of @self, otherwise
/// nothing will be done.
///
/// Return length after this call.
size_t I64Vector_insert(I64Vector self, size_t index, int64_t value);

/// Get internal buffer.
///
/// This is unsafe, be aware what you are doing.
int64_t *I64Vector_data(I64Vector self);

/// Push @value to the back of @self.
size_t I64Vector_push(I64Vector self, int64_t value);

/// Pop out the last element. If no elements left, the returned
/// value is undefined.
int64_t I64Vector_pop(I64Vector self);

/// Append @src to @self.
size_t I64Vector_append(I64Vector self, I64Vector src);

/// Append a int64_t array to @self.
size_t I64Vector_appendArray(I64Vector self, const int64_t *a, size_t count);

#endif
