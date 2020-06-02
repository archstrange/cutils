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
#ifndef ADT_TEMPLATE_U16Vector_H
#define ADT_TEMPLATE_U16Vector_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// U16Vector: Vector of uint16_t, generated from `Vector.[ch].ohce`.
typedef struct _ADT_U16Vector *U16Vector;

/// Lifetime function: create a new U16Vector object.
U16Vector U16Vector_new();

/// Lifetime function: create a new U16Vector object with @capacity.
U16Vector U16Vector_newWithCapacity(size_t capacity);

/// Lifetime function: create a new U16Vector object from @array.
U16Vector U16Vector_newFromArray(const uint16_t *array, size_t length);

/// Lifetime function: clone the whole @src object.
U16Vector U16Vector_clone(U16Vector src);

/// Lifetime function: copy the whole @src object to @self.
void U16Vector_copy(U16Vector self, U16Vector src);

/// Copy the first @n elements of @src to @self.
void U16Vector_copyArray(U16Vector self, const uint16_t *array, size_t n);

/// Copy @n elements of @src started at @start to @self.
///
/// If @start is greater than @self's length or @self and @src
/// are the same object, nothing will be done.
///
/// If @src has not enough elements from @start, `U16Vector_copySub`
/// will stop after it copyed the last element.
void U16Vector_copySub(U16Vector self, U16Vector src, size_t start, size_t n);

/// Lifetime function: free @self object.
void U16Vector_free(U16Vector self);


/// Compare two U16Vectors.
int U16Vector_cmp(U16Vector self, U16Vector right);

/// Check equality.
bool U16Vector_equal(U16Vector self, U16Vector right);

/// Hash this object.
uint32_t U16Vector_hash(U16Vector self);

/// Dump all elements to @buffer. @buffer must hold enough space
/// to store all elements.
/// Note: conten of @buffer will be overwrited, if uint16_t holds
/// dynamic memorys then only pointers are dumped.
///
/// Return: count of elements dumped.
size_t U16Vector_dump(U16Vector self, uint16_t *buffer);

/// Same as `U16Vector_dump`, but the first @n elements only.
size_t U16Vector_dumpn(U16Vector self, uint16_t *buffer, size_t n);

/// Check if @self if empty.
bool U16Vector_empty(U16Vector self);

/// Get length of @self.
size_t U16Vector_getLength(U16Vector self);


/// Clear all elements.
void U16Vector_clear(U16Vector self);

/// Try to erase the last elements of @self as much(@count) as it can.
void U16Vector_eraseTail(U16Vector self, size_t count);

/// Get capacity of @self.
size_t U16Vector_getCapacity(U16Vector self);

/// Tell U16Vector to preallocate enough memory. U16Vector's length
/// may be changed. Normally U16Vector will handle its memory
/// automatically, so call this if you want U16Vector to use specific size
/// of memory.
///
/// U16Vector always handle memory automatically, so capacity maybe changed
/// if you remove or add elements to @self.
void U16Vector_setCapacity(U16Vector self, size_t capacity);

/// Set capacity to its length.
void U16Vector_shrink(U16Vector self);

/// Same meanding as `self[index] = value`.
/// @index must be less than length of @self.
void U16Vector_set(U16Vector self, size_t index, uint16_t value);

/// Same meanding as `self[index]`.
/// @index must be less than length of @self.
uint16_t U16Vector_get(U16Vector self, size_t index);

/// Insert @value to `self[index]`, all elements after will be
/// moved backward.
/// @index should be less than length of @self, otherwise
/// nothing will be done.
///
/// Return length after this call.
size_t U16Vector_insert(U16Vector self, size_t index, uint16_t value);

/// Get internal buffer.
///
/// This is unsafe, be aware what you are doing.
uint16_t *U16Vector_data(U16Vector self);

/// Push @value to the back of @self.
size_t U16Vector_push(U16Vector self, uint16_t value);

/// Pop out the last element. If no elements left, the returned
/// value is undefined.
uint16_t U16Vector_pop(U16Vector self);

/// Append @src to @self.
size_t U16Vector_append(U16Vector self, U16Vector src);

/// Append a uint16_t array to @self.
size_t U16Vector_appendArray(U16Vector self, const uint16_t *a, size_t count);

#endif
