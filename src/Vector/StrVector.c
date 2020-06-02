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

// This file is generated from Vector.c.ohce by ohce.
#include "StrVector.h"

#include <string.h>

struct _ADT_StrVector {
	size_t capacity, length;
	Str *data;
};

static inline void StrVector_realloc(StrVector self, size_t new_capacity);
static inline void StrVector_init(StrVector self, size_t capacity);
static inline void StrVector_final(StrVector self);

static inline void T_sign(Str *dst, Str src)
{
	Str_free(*dst);
	*dst = src;
}

StrVector StrVector_new()
{
	return StrVector_newWithCapacity(1);
}

StrVector StrVector_newWithCapacity(size_t capacity)
{
	StrVector self = malloc(sizeof(*self));
	StrVector_init(self, capacity);
	return self;
}

StrVector StrVector_newFromArray(Str const *array, size_t length)
{
	StrVector self = StrVector_newWithCapacity(length);
	for (size_t i = 0; i < length; i++) {
		self->data[i] = Str_clone(array[i]);
	}
	self->length = length;
	return self;
}

StrVector StrVector_clone(StrVector src)
{
	if (src == NULL) return StrVector_new();
	return StrVector_newFromArray(src->data, src->length);
}

void StrVector_copy(StrVector self, StrVector src)
{
	if (self == src) return;
	StrVector_copyArray(self, src->data, src->length);
}

void StrVector_copyArray(StrVector self, Str const *array, size_t n)
{
	StrVector_final(self);
	StrVector_init(self, n);
	for (size_t i = 0; i < n; i++) {
		self->data[i] = Str_clone(array[i]);
	}
	self->length = n;
}

void StrVector_copySub(StrVector self, StrVector src, size_t start, size_t n)
{
	if (self != src && start < src->length) {
		n = start + n < src->length ? n : src->length - start;
		StrVector_copyArray(self, src->data + start, n);
	}
}

void StrVector_free(StrVector self)
{
	if (self) {
		StrVector_final(self);
		free(self);
	}
}

int StrVector_cmp(StrVector self, StrVector right)
{
	if (self == right)
		return 0;

	int ret;
	size_t len = self->length;
	if (self->length < right->length) {
		ret = -1;
	} else if (self->length == right->length) {
		ret = 0;
	} else {
		len = right->length;
		ret = 1;
	}

	int cmp;
	for (size_t i = 0; i < len; i++) {
		cmp = Str_cmp(self->data[i], right->data[i]);
		if (cmp != 0)
			return cmp;
	}
	return ret;
}

bool StrVector_equal(StrVector self, StrVector right)
{
	if (self == right)
		return true;

	if (self->length != right->length)
		return false;

	for (size_t i = 0; i < self->length; i++) {
		if (
		!Str_equal(self->data[i], right->data[i])
		)
			return false;
	}
	return true;
}

uint32_t StrVector_hash(StrVector self)
{
	uint32_t hash = 0;
	for (size_t i = 0, n = self->length / 4; i < n; i++) {
		uint32_t hash_step = 0;
		size_t index = i << 2;
		for (size_t j = 0; j < 4; j++) {
			hash_step = (hash_step << 6)
				    + Str_hash(self->data[index + j]);
		}
		hash ^= hash_step;
	}
	uint32_t hash_step = 0;
	for (size_t i = self->length - (self->length % 4); i < self->length; i++) {
		hash_step = (hash_step << 6) + Str_hash(self->data[i]);
	}
	hash ^= hash_step;
	return hash;
}

size_t StrVector_dump(StrVector self, Str *buffer)
{
	return StrVector_dumpn(self, buffer, self->length);
}

size_t StrVector_dumpn(StrVector self, Str *buffer, size_t n)
{
	n = self->length < n ? self->length : n;
	memcpy(buffer, self->data, sizeof(Str) * n);
	return n;
}

bool StrVector_empty(StrVector self)
{
	return self->length == 0;
}

size_t StrVector_getLength(StrVector self)
{
	return self->length;
}

void StrVector_setLength(StrVector self, size_t length)
{
	if (length > self->capacity) {
		StrVector_realloc(self, length);
	}
	if (length > self->length) {
		for (size_t i = self->length; i < length; i++) {
			self->data[i] = Str_new();
		}
	}
	else {
		for (size_t i = length; i < self->length; i++) {
			Str_free(self->data[i]);
		}
	}
	self->length = length;
}

void StrVector_clear(StrVector self)
{
	for (size_t i = 0; i < self->length; i++) {
		Str_free(self->data[i]);
	}
	self->length = 0;
}

void StrVector_eraseTail(StrVector self, size_t count)
{
	count = count > self->length ? self->length : count;
	for (size_t i = self->length - count; i < self->length; i++) {
		Str_free(self->data[i]);
	}
	self->length -= count;
}

size_t StrVector_getCapacity(StrVector self)
{
	return self->capacity;
}

void StrVector_setCapacity(StrVector self, size_t capacity)
{
	capacity = capacity == 0 ? 1 : capacity;
	if (self->capacity == capacity) return;
	StrVector_realloc(self, capacity);
}

void StrVector_shrink(StrVector self)
{
	StrVector_setCapacity(self, self->length);
}

void __StrVector_set_use_assign(StrVector self, size_t index, Str value)
{
	T_sign(self->data + index, value);
}

void __StrVector_set_use_copy(StrVector self, size_t index, Str *value)
{
	Str_copy(self->data[index], *value);
}

Str StrVector_get(StrVector self, size_t index)
{
	return self->data[index];
}

#define Vector_preInsert(self, index) \
	if (index >= self->length) \
		return self->length; \
	if (self->length >= self->capacity) { \
		StrVector_realloc(self, self->capacity * 2); \
	} \
	size_t i = self->length; \
	while (i > index) { \
		self->data[i] = self->data[i - 1]; \
		i -= 1; \
	} \
	self->length += 1

size_t __StrVector_insert_use_clone(StrVector self, size_t index, Str *value)
{
	Vector_preInsert(self, index);
	self->data[i] = Str_clone(*value);
	return self->length;
}

size_t __StrVector_insert_use_assign(StrVector self, size_t index, Str value)
{
	Vector_preInsert(self, index);
	self->data[i] = value;
	return self->length;
}

Str *StrVector_data(StrVector self)
{
	return self->data;
}

size_t __StrVector_push_use_clone(StrVector self, Str *value)
{
	if (self->length >= self->capacity) {
		StrVector_realloc(self, self->capacity * 2);
	}
	self->data[self->length] = Str_clone(*value);
	self->length += 1;
	return self->length;
}

size_t __StrVector_push_use_assign(StrVector self, Str value)
{
	if (self->length >= self->capacity) {
		StrVector_realloc(self, self->capacity * 2);
	}
	self->data[self->length] = value;
	self->length += 1;
	return self->length;
}

Str StrVector_pop(StrVector self)
{
	if (self->length > 0) 
		self->length -= 1;
	return self->data[self->length];
}

size_t StrVector_append(StrVector self, StrVector src)
{
	return StrVector_appendArray(self, src->data, src->length);
}

size_t StrVector_appendArray(StrVector self, const Str *a, size_t count)
{
	if (a == NULL || count == 0) {
		return self->length;
	}
	if (self->length + count > self->capacity) {
		StrVector_realloc(self, self->capacity + count);
	}
	for (size_t i = 0; i < count; i++) {
		self->data[self->length + i] = Str_clone(a[i]);
	}
	self->length += count;
	return self->length;
}

static inline void StrVector_realloc(StrVector self, size_t new_capacity)
{
	Str *tmp = calloc(new_capacity, sizeof(Str));
	if (self->length > new_capacity) {
		for (size_t i = new_capacity; i < self->length; i++) {
			Str_free(self->data[i]);
		}
		self->length = new_capacity;
	}
	memcpy(tmp, self->data, sizeof(Str) * self->length);
	free(self->data);
	self->data = tmp;
	self->capacity = new_capacity;
}

static inline void StrVector_init(StrVector self, size_t capacity)
{
	self->capacity = capacity == 0 ? 1 : capacity;
	self->length = 0;
	self->data = calloc(self->capacity, sizeof(Str));
}

static inline void StrVector_final(StrVector self)
{
	for (size_t i = 0; i < self->length; i++) {
		Str_free(self->data[i]);
	}
	free(self->data);
	self->length = self->capacity = 0;
}

