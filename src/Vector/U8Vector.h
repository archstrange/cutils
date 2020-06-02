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
#ifndef ADT_TEMPLATE_U8Vector_H
#define ADT_TEMPLATE_U8Vector_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// U8Vector: Vector of uint8_t, generated from `Vector.[ch].ohce`.
typedef struct _ADT_U8Vector *U8Vector;

/// Lifetime function: create a new U8Vector object.
U8Vector U8Vector_new();

/// Lifetime function: create a new U8Vector object with @capacity.
U8Vector U8Vector_newWithCapacity(size_t capacity);

/// Lifetime function: create a new U8Vector object from @array.
U8Vector U8Vector_newFromArray(const uint8_t *array, size_t length);

/// Lifetime function: clone the whole @src object.
U8Vector U8Vector_clone(U8Vector src);

/// Lifetime function: copy the whole @src object to @self.
void U8Vector_copy(U8Vector self, U8Vector src);

/// Copy the first @n elements of @src to @self.
void U8Vector_copyArray(U8Vector self, const uint8_t *array, size_t n);

/// Copy @n elements of @src started at @start to @self.
///
/// If @start is greater than @self's length or @self and @src
/// are the same object, nothing will be done.
///
/// If @src has not enough elements from @start, `U8Vector_copySub`
/// will stop after it copyed the last element.
void U8Vector_copySub(U8Vector self, U8Vector src, size_t start, size_t n);

/// Lifetime function: free @self object.
void U8Vector_free(U8Vector self);


/// Compare two U8Vectors.
int U8Vector_cmp(U8Vector self, U8Vector right);

/// Check equality.
bool U8Vector_equal(U8Vector self, U8Vector right);

/// Hash this object.
uint32_t U8Vector_hash(U8Vector self);

/// Dump all elements to @buffer. @buffer must hold enough space
/// to store all elements.
/// Note: conten of @buffer will be overwrited, if uint8_t holds
/// dynamic memorys then only pointers are dumped.
///
/// Return: count of elements dumped.
size_t U8Vector_dump(U8Vector self, uint8_t *buffer);

/// Same as `U8Vector_dump`, but the first @n elements only.
size_t U8Vector_dumpn(U8Vector self, uint8_t *buffer, size_t n);

/// Check if @self if empty.
bool U8Vector_empty(U8Vector self);

/// Get length of @self.
size_t U8Vector_getLength(U8Vector self);


/// Clear all elements.
void U8Vector_clear(U8Vector self);

/// Try to erase the last elements of @self as much(@count) as it can.
void U8Vector_eraseTail(U8Vector self, size_t count);

/// Get capacity of @self.
size_t U8Vector_getCapacity(U8Vector self);

/// Tell U8Vector to preallocate enough memory. U8Vector's length
/// may be changed. Normally U8Vector will handle its memory
/// automatically, so call this if you want U8Vector to use specific size
/// of memory.
///
/// U8Vector always handle memory automatically, so capacity maybe changed
/// if you remove or add elements to @self.
void U8Vector_setCapacity(U8Vector self, size_t capacity);

/// Set capacity to its length.
void U8Vector_shrink(U8Vector self);

/// Same meanding as `self[index] = value`.
/// @index must be less than length of @self.
void U8Vector_set(U8Vector self, size_t index, uint8_t value);

/// Same meanding as `self[index]`.
/// @index must be less than length of @self.
uint8_t U8Vector_get(U8Vector self, size_t index);

/// Insert @value to `self[index]`, all elements after will be
/// moved backward.
/// @index should be less than length of @self, otherwise
/// nothing will be done.
///
/// Return length after this call.
size_t U8Vector_insert(U8Vector self, size_t index, uint8_t value);

/// Get internal buffer.
///
/// This is unsafe, be aware what you are doing.
uint8_t *U8Vector_data(U8Vector self);

/// Push @value to the back of @self.
size_t U8Vector_push(U8Vector self, uint8_t value);

/// Pop out the last element. If no elements left, the returned
/// value is undefined.
uint8_t U8Vector_pop(U8Vector self);

/// Append @src to @self.
size_t U8Vector_append(U8Vector self, U8Vector src);

/// Append a uint8_t array to @self.
size_t U8Vector_appendArray(U8Vector self, const uint8_t *a, size_t count);

#endif
