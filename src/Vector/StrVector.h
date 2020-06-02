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
#ifndef ADT_TEMPLATE_StrVector_H
#define ADT_TEMPLATE_StrVector_H
#include "Str.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// StrVector: Vector of Str, generated from `Vector.[ch].ohce`.
typedef struct _ADT_StrVector *StrVector;

/// Lifetime function: create a new StrVector object.
StrVector StrVector_new();

/// Lifetime function: create a new StrVector object with @capacity.
StrVector StrVector_newWithCapacity(size_t capacity);

/// Lifetime function: create a new StrVector object from @array.
StrVector StrVector_newFromArray(const Str *array, size_t length);

/// Lifetime function: clone the whole @src object.
StrVector StrVector_clone(StrVector src);

/// Lifetime function: copy the whole @src object to @self.
void StrVector_copy(StrVector self, StrVector src);

/// Copy the first @n elements of @src to @self.
void StrVector_copyArray(StrVector self, const Str *array, size_t n);

/// Copy @n elements of @src started at @start to @self.
///
/// If @start is greater than @self's length or @self and @src
/// are the same object, nothing will be done.
///
/// If @src has not enough elements from @start, `StrVector_copySub`
/// will stop after it copyed the last element.
void StrVector_copySub(StrVector self, StrVector src, size_t start, size_t n);

/// Lifetime function: free @self object.
void StrVector_free(StrVector self);


/// Compare two StrVectors.
int StrVector_cmp(StrVector self, StrVector right);

/// Check equality.
bool StrVector_equal(StrVector self, StrVector right);

/// Hash this object.
uint32_t StrVector_hash(StrVector self);

/// Dump all elements to @buffer. @buffer must hold enough space
/// to store all elements.
/// Note: conten of @buffer will be overwrited, if Str holds
/// dynamic memorys then only pointers are dumped.
///
/// Return: count of elements dumped.
size_t StrVector_dump(StrVector self, Str *buffer);

/// Same as `StrVector_dump`, but the first @n elements only.
size_t StrVector_dumpn(StrVector self, Str *buffer, size_t n);

/// Check if @self if empty.
bool StrVector_empty(StrVector self);

/// Get length of @self.
size_t StrVector_getLength(StrVector self);

/// Set length of @self.
void StrVector_setLength(StrVector self, size_t length);

/// Clear all elements.
void StrVector_clear(StrVector self);

/// Try to erase the last elements of @self as much(@count) as it can.
void StrVector_eraseTail(StrVector self, size_t count);

/// Get capacity of @self.
size_t StrVector_getCapacity(StrVector self);

/// Tell StrVector to preallocate enough memory. StrVector's length
/// may be changed. Normally StrVector will handle its memory
/// automatically, so call this if you want StrVector to use specific size
/// of memory.
///
/// StrVector always handle memory automatically, so capacity maybe changed
/// if you remove or add elements to @self.
void StrVector_setCapacity(StrVector self, size_t capacity);

/// Set capacity to its length.
void StrVector_shrink(StrVector self);

/// Same meanding as `self[index] = value`.
/// @index must be less than length of @self.
/// Generic element `set` method, pass `Str` to assign or `Str *`
/// to copy.
#define StrVector_set(self, index, value) \
_Generic(value, \
	 Str: __StrVector_set_use_assign, \
	 default: __StrVector_set_use_copy \
) (self, index, value)

void __StrVector_set_use_assign(StrVector self, size_t index, Str value);
void __StrVector_set_use_copy(StrVector self, size_t index, Str *value);

/// Same meanding as `self[index]`.
/// @index must be less than length of @self.
Str StrVector_get(StrVector self, size_t index);

/// Insert @value to `self[index]`, all elements after will be
/// moved backward.
/// @index should be less than length of @self, otherwise
/// nothing will be done.
///
/// Return length after this call.
/// Generic element `insert` method, pass `Str` to assign or `Str *`
/// to clone.
#define StrVector_insert(self, index, value) \
_Generic(value, \
	 Str: __StrVector_insert_use_assign, \
	 default: __StrVector_insert_use_clone \
) (self, index, value)

size_t __StrVector_insert_use_assign(StrVector self, size_t index, Str value);
size_t __StrVector_insert_use_clone(StrVector self, size_t index, Str *value);

/// Get internal buffer.
///
/// This is unsafe, be aware what you are doing.
Str *StrVector_data(StrVector self);

/// Push @value to the back of @self.
/// Generic element `push` method, pass `Str` to assign or `Str *`
/// to clone.
#define StrVector_push(self, value) \
_Generic(value, \
	 Str: __StrVector_push_use_assign, \
	 default: __StrVector_push_use_clone \
) (self, value)

size_t __StrVector_push_use_assign(StrVector self, Str value);
size_t __StrVector_push_use_clone(StrVector self, Str *value);

/// Pop out the last element. If no elements left, the returned
/// value is undefined.
/// Remember to free the returned object, since it's newed by
/// StrVector itself.
Str StrVector_pop(StrVector self);

/// Append @src to @self.
size_t StrVector_append(StrVector self, StrVector src);

/// Append a Str array to @self.
size_t StrVector_appendArray(StrVector self, const Str *a, size_t count);

#endif
