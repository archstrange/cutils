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
#ifndef ADT_TEMPLATE_F64Vector_H
#define ADT_TEMPLATE_F64Vector_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// F64Vector: Vector of double, generated from `Vector.[ch].ohce`.
typedef struct _ADT_F64Vector *F64Vector;

/// Lifetime function: create a new F64Vector object.
F64Vector F64Vector_new();

/// Lifetime function: create a new F64Vector object with @capacity.
F64Vector F64Vector_newWithCapacity(size_t capacity);

/// Lifetime function: create a new F64Vector object from @array.
F64Vector F64Vector_newFromArray(const double *array, size_t length);

/// Lifetime function: clone the whole @src object.
F64Vector F64Vector_clone(F64Vector src);

/// Lifetime function: copy the whole @src object to @self.
void F64Vector_copy(F64Vector self, F64Vector src);

/// Copy the first @n elements of @src to @self.
void F64Vector_copyArray(F64Vector self, const double *array, size_t n);

/// Copy @n elements of @src started at @start to @self.
///
/// If @start is greater than @self's length or @self and @src
/// are the same object, nothing will be done.
///
/// If @src has not enough elements from @start, `F64Vector_copySub`
/// will stop after it copyed the last element.
void F64Vector_copySub(F64Vector self, F64Vector src, size_t start, size_t n);

/// Lifetime function: free @self object.
void F64Vector_free(F64Vector self);


/// Compare two F64Vectors.
int F64Vector_cmp(F64Vector self, F64Vector right);

/// Check equality.
bool F64Vector_equal(F64Vector self, F64Vector right);

/// Hash this object.
uint32_t F64Vector_hash(F64Vector self);

/// Dump all elements to @buffer. @buffer must hold enough space
/// to store all elements.
/// Note: conten of @buffer will be overwrited, if double holds
/// dynamic memorys then only pointers are dumped.
///
/// Return: count of elements dumped.
size_t F64Vector_dump(F64Vector self, double *buffer);

/// Same as `F64Vector_dump`, but the first @n elements only.
size_t F64Vector_dumpn(F64Vector self, double *buffer, size_t n);

/// Check if @self if empty.
bool F64Vector_empty(F64Vector self);

/// Get length of @self.
size_t F64Vector_getLength(F64Vector self);


/// Clear all elements.
void F64Vector_clear(F64Vector self);

/// Try to erase the last elements of @self as much(@count) as it can.
void F64Vector_eraseTail(F64Vector self, size_t count);

/// Get capacity of @self.
size_t F64Vector_getCapacity(F64Vector self);

/// Tell F64Vector to preallocate enough memory. F64Vector's length
/// may be changed. Normally F64Vector will handle its memory
/// automatically, so call this if you want F64Vector to use specific size
/// of memory.
///
/// F64Vector always handle memory automatically, so capacity maybe changed
/// if you remove or add elements to @self.
void F64Vector_setCapacity(F64Vector self, size_t capacity);

/// Set capacity to its length.
void F64Vector_shrink(F64Vector self);

/// Same meanding as `self[index] = value`.
/// @index must be less than length of @self.
void F64Vector_set(F64Vector self, size_t index, double value);

/// Same meanding as `self[index]`.
/// @index must be less than length of @self.
double F64Vector_get(F64Vector self, size_t index);

/// Insert @value to `self[index]`, all elements after will be
/// moved backward.
/// @index should be less than length of @self, otherwise
/// nothing will be done.
///
/// Return length after this call.
size_t F64Vector_insert(F64Vector self, size_t index, double value);

/// Get internal buffer.
///
/// This is unsafe, be aware what you are doing.
double *F64Vector_data(F64Vector self);

/// Push @value to the back of @self.
size_t F64Vector_push(F64Vector self, double value);

/// Pop out the last element. If no elements left, the returned
/// value is undefined.
double F64Vector_pop(F64Vector self);

/// Append @src to @self.
size_t F64Vector_append(F64Vector self, F64Vector src);

/// Append a double array to @self.
size_t F64Vector_appendArray(F64Vector self, const double *a, size_t count);

#endif
