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
#ifndef ADT_TEMPLATE_I16Vector_H
#define ADT_TEMPLATE_I16Vector_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// I16Vector: Vector of int16_t, generated from `Vector.[ch].ohce`.
typedef struct _ADT_I16Vector *I16Vector;

/// Lifetime function: create a new I16Vector object.
I16Vector I16Vector_new();

/// Lifetime function: create a new I16Vector object with @capacity.
I16Vector I16Vector_newWithCapacity(size_t capacity);

/// Lifetime function: create a new I16Vector object from @array.
I16Vector I16Vector_newFromArray(const int16_t *array, size_t length);

/// Lifetime function: clone the whole @src object.
I16Vector I16Vector_clone(I16Vector src);

/// Lifetime function: copy the whole @src object to @self.
void I16Vector_copy(I16Vector self, I16Vector src);

/// Copy the first @n elements of @src to @self.
void I16Vector_copyArray(I16Vector self, const int16_t *array, size_t n);

/// Copy @n elements of @src started at @start to @self.
///
/// If @start is greater than @self's length or @self and @src
/// are the same object, nothing will be done.
///
/// If @src has not enough elements from @start, `I16Vector_copySub`
/// will stop after it copyed the last element.
void I16Vector_copySub(I16Vector self, I16Vector src, size_t start, size_t n);

/// Lifetime function: free @self object.
void I16Vector_free(I16Vector self);


/// Compare two I16Vectors.
int I16Vector_cmp(I16Vector self, I16Vector right);

/// Check equality.
bool I16Vector_equal(I16Vector self, I16Vector right);

/// Hash this object.
uint32_t I16Vector_hash(I16Vector self);

/// Dump all elements to @buffer. @buffer must hold enough space
/// to store all elements.
/// Note: conten of @buffer will be overwrited, if int16_t holds
/// dynamic memorys then only pointers are dumped.
///
/// Return: count of elements dumped.
size_t I16Vector_dump(I16Vector self, int16_t *buffer);

/// Same as `I16Vector_dump`, but the first @n elements only.
size_t I16Vector_dumpn(I16Vector self, int16_t *buffer, size_t n);

/// Check if @self if empty.
bool I16Vector_empty(I16Vector self);

/// Get length of @self.
size_t I16Vector_getLength(I16Vector self);


/// Clear all elements.
void I16Vector_clear(I16Vector self);

/// Try to erase the last elements of @self as much(@count) as it can.
void I16Vector_eraseTail(I16Vector self, size_t count);

/// Get capacity of @self.
size_t I16Vector_getCapacity(I16Vector self);

/// Tell I16Vector to preallocate enough memory. I16Vector's length
/// may be changed. Normally I16Vector will handle its memory
/// automatically, so call this if you want I16Vector to use specific size
/// of memory.
///
/// I16Vector always handle memory automatically, so capacity maybe changed
/// if you remove or add elements to @self.
void I16Vector_setCapacity(I16Vector self, size_t capacity);

/// Set capacity to its length.
void I16Vector_shrink(I16Vector self);

/// Same meanding as `self[index] = value`.
/// @index must be less than length of @self.
void I16Vector_set(I16Vector self, size_t index, int16_t value);

/// Same meanding as `self[index]`.
/// @index must be less than length of @self.
int16_t I16Vector_get(I16Vector self, size_t index);

/// Insert @value to `self[index]`, all elements after will be
/// moved backward.
/// @index should be less than length of @self, otherwise
/// nothing will be done.
///
/// Return length after this call.
size_t I16Vector_insert(I16Vector self, size_t index, int16_t value);

/// Get internal buffer.
///
/// This is unsafe, be aware what you are doing.
int16_t *I16Vector_data(I16Vector self);

/// Push @value to the back of @self.
size_t I16Vector_push(I16Vector self, int16_t value);

/// Pop out the last element. If no elements left, the returned
/// value is undefined.
int16_t I16Vector_pop(I16Vector self);

/// Append @src to @self.
size_t I16Vector_append(I16Vector self, I16Vector src);

/// Append a int16_t array to @self.
size_t I16Vector_appendArray(I16Vector self, const int16_t *a, size_t count);

#endif
