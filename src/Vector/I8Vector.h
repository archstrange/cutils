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
#ifndef ADT_TEMPLATE_I8Vector_H
#define ADT_TEMPLATE_I8Vector_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// I8Vector: Vector of int8_t, generated from `Vector.[ch].ohce`.
typedef struct _ADT_I8Vector *I8Vector;

/// Lifetime function: create a new I8Vector object.
I8Vector I8Vector_new();

/// Lifetime function: create a new I8Vector object with @capacity.
I8Vector I8Vector_newWithCapacity(size_t capacity);

/// Lifetime function: create a new I8Vector object from @array.
I8Vector I8Vector_newFromArray(const int8_t *array, size_t length);

/// Lifetime function: clone the whole @src object.
I8Vector I8Vector_clone(I8Vector src);

/// Lifetime function: copy the whole @src object to @self.
void I8Vector_copy(I8Vector self, I8Vector src);

/// Copy the first @n elements of @src to @self.
void I8Vector_copyArray(I8Vector self, const int8_t *array, size_t n);

/// Copy @n elements of @src started at @start to @self.
///
/// If @start is greater than @self's length or @self and @src
/// are the same object, nothing will be done.
///
/// If @src has not enough elements from @start, `I8Vector_copySub`
/// will stop after it copyed the last element.
void I8Vector_copySub(I8Vector self, I8Vector src, size_t start, size_t n);

/// Lifetime function: free @self object.
void I8Vector_free(I8Vector self);


/// Compare two I8Vectors.
int I8Vector_cmp(I8Vector self, I8Vector right);

/// Check equality.
bool I8Vector_equal(I8Vector self, I8Vector right);

/// Hash this object.
uint32_t I8Vector_hash(I8Vector self);

/// Dump all elements to @buffer. @buffer must hold enough space
/// to store all elements.
/// Note: conten of @buffer will be overwrited, if int8_t holds
/// dynamic memorys then only pointers are dumped.
///
/// Return: count of elements dumped.
size_t I8Vector_dump(I8Vector self, int8_t *buffer);

/// Same as `I8Vector_dump`, but the first @n elements only.
size_t I8Vector_dumpn(I8Vector self, int8_t *buffer, size_t n);

/// Check if @self if empty.
bool I8Vector_empty(I8Vector self);

/// Get length of @self.
size_t I8Vector_getLength(I8Vector self);


/// Clear all elements.
void I8Vector_clear(I8Vector self);

/// Try to erase the last elements of @self as much(@count) as it can.
void I8Vector_eraseTail(I8Vector self, size_t count);

/// Get capacity of @self.
size_t I8Vector_getCapacity(I8Vector self);

/// Tell I8Vector to preallocate enough memory. I8Vector's length
/// may be changed. Normally I8Vector will handle its memory
/// automatically, so call this if you want I8Vector to use specific size
/// of memory.
///
/// I8Vector always handle memory automatically, so capacity maybe changed
/// if you remove or add elements to @self.
void I8Vector_setCapacity(I8Vector self, size_t capacity);

/// Set capacity to its length.
void I8Vector_shrink(I8Vector self);

/// Same meanding as `self[index] = value`.
/// @index must be less than length of @self.
void I8Vector_set(I8Vector self, size_t index, int8_t value);

/// Same meanding as `self[index]`.
/// @index must be less than length of @self.
int8_t I8Vector_get(I8Vector self, size_t index);

/// Insert @value to `self[index]`, all elements after will be
/// moved backward.
/// @index should be less than length of @self, otherwise
/// nothing will be done.
///
/// Return length after this call.
size_t I8Vector_insert(I8Vector self, size_t index, int8_t value);

/// Get internal buffer.
///
/// This is unsafe, be aware what you are doing.
int8_t *I8Vector_data(I8Vector self);

/// Push @value to the back of @self.
size_t I8Vector_push(I8Vector self, int8_t value);

/// Pop out the last element. If no elements left, the returned
/// value is undefined.
int8_t I8Vector_pop(I8Vector self);

/// Append @src to @self.
size_t I8Vector_append(I8Vector self, I8Vector src);

/// Append a int8_t array to @self.
size_t I8Vector_appendArray(I8Vector self, const int8_t *a, size_t count);

#endif
