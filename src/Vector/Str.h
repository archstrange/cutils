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
#ifndef ADT_TEMPLATE_Str_H
#define ADT_TEMPLATE_Str_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// Str: Vector of uint8_t, generated from `Vector.[ch].ohce`.
typedef struct _ADT_Str *Str;

/// Lifetime function: create a new Str object.
Str Str_new();

/// Lifetime function: create a new Str object with @capacity.
Str Str_newWithCapacity(size_t capacity);

/// Lifetime function: create a new Str object from @array.
Str Str_newFromArray(const uint8_t *array, size_t length);

/// Lifetime function: clone the whole @src object.
Str Str_clone(Str src);

/// Lifetime function: copy the whole @src object to @self.
void Str_copy(Str self, Str src);

/// Copy the first @n elements of @src to @self.
void Str_copyArray(Str self, const uint8_t *array, size_t n);

/// Copy @n elements of @src started at @start to @self.
///
/// If @start is greater than @self's length or @self and @src
/// are the same object, nothing will be done.
///
/// If @src has not enough elements from @start, `Str_copySub`
/// will stop after it copyed the last element.
void Str_copySub(Str self, Str src, size_t start, size_t n);

/// Lifetime function: free @self object.
void Str_free(Str self);


/// Compare two Strs.
int Str_cmp(Str self, Str right);

/// Check equality.
bool Str_equal(Str self, Str right);

/// Hash this object.
uint32_t Str_hash(Str self);

/// Dump all elements to @buffer. @buffer must hold enough space
/// to store all elements.
/// Note: conten of @buffer will be overwrited, if uint8_t holds
/// dynamic memorys then only pointers are dumped.
///
/// Return: count of elements dumped.
size_t Str_dump(Str self, uint8_t *buffer);

/// Same as `Str_dump`, but the first @n elements only.
size_t Str_dumpn(Str self, uint8_t *buffer, size_t n);

/// Check if @self if empty.
bool Str_empty(Str self);

/// Get length of @self.
size_t Str_getLength(Str self);


/// Clear all elements.
void Str_clear(Str self);

/// Try to erase the last elements of @self as much(@count) as it can.
void Str_eraseTail(Str self, size_t count);

/// Get capacity of @self.
size_t Str_getCapacity(Str self);

/// Tell Str to preallocate enough memory. Str's length
/// may be changed. Normally Str will handle its memory
/// automatically, so call this if you want Str to use specific size
/// of memory.
///
/// Str always handle memory automatically, so capacity maybe changed
/// if you remove or add elements to @self.
void Str_setCapacity(Str self, size_t capacity);

/// Set capacity to its length.
void Str_shrink(Str self);

/// Same meanding as `self[index] = value`.
/// @index must be less than length of @self.
void Str_set(Str self, size_t index, uint8_t value);

/// Same meanding as `self[index]`.
/// @index must be less than length of @self.
uint8_t Str_get(Str self, size_t index);

/// Insert @value to `self[index]`, all elements after will be
/// moved backward.
/// @index should be less than length of @self, otherwise
/// nothing will be done.
///
/// Return length after this call.
size_t Str_insert(Str self, size_t index, uint8_t value);

/// Get internal buffer.
///
/// This is unsafe, be aware what you are doing.
uint8_t *Str_data(Str self);

/// Push @value to the back of @self.
size_t Str_push(Str self, uint8_t value);

/// Pop out the last element. If no elements left, the returned
/// value is undefined.
uint8_t Str_pop(Str self);

/// Append @src to @self.
size_t Str_append(Str self, Str src);

/// Append a uint8_t array to @self.
size_t Str_appendArray(Str self, const uint8_t *a, size_t count);

#endif
