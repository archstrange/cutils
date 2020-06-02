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
#include "I64Vector.h"

#include <string.h>

struct _ADT_I64Vector {
	size_t capacity, length;
	int64_t *data;
};

static inline void I64Vector_realloc(I64Vector self, size_t new_capacity);
static inline void I64Vector_init(I64Vector self, size_t capacity);
static inline void I64Vector_final(I64Vector self);


I64Vector I64Vector_new()
{
	return I64Vector_newWithCapacity(1);
}

I64Vector I64Vector_newWithCapacity(size_t capacity)
{
	I64Vector self = malloc(sizeof(*self));
	I64Vector_init(self, capacity);
	return self;
}

I64Vector I64Vector_newFromArray(int64_t const *array, size_t length)
{
	I64Vector self = I64Vector_newWithCapacity(length);
	memcpy(self->data, array, sizeof(int64_t) * length);
	self->length = length;
	return self;
}

I64Vector I64Vector_clone(I64Vector src)
{
	if (src == NULL) return I64Vector_new();
	return I64Vector_newFromArray(src->data, src->length);
}

void I64Vector_copy(I64Vector self, I64Vector src)
{
	if (self == src) return;
	I64Vector_copyArray(self, src->data, src->length);
}

void I64Vector_copyArray(I64Vector self, int64_t const *array, size_t n)
{
	I64Vector_final(self);
	I64Vector_init(self, n);
	memcpy(self->data, array, sizeof(int64_t) * n);
	self->length = n;
}

void I64Vector_copySub(I64Vector self, I64Vector src, size_t start, size_t n)
{
	if (self != src && start < src->length) {
		n = start + n < src->length ? n : src->length - start;
		I64Vector_copyArray(self, src->data + start, n);
	}
}

void I64Vector_free(I64Vector self)
{
	if (self) {
		I64Vector_final(self);
		free(self);
	}
}

int I64Vector_cmp(I64Vector self, I64Vector right)
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
		cmp = self->data[i] - right->data[i];
		if (cmp != 0)
			return cmp;
	}
	return ret;
}

bool I64Vector_equal(I64Vector self, I64Vector right)
{
	if (self == right)
		return true;

	if (self->length != right->length)
		return false;

	for (size_t i = 0; i < self->length; i++) {
		if (
		self->data[i] != right->data[i]
		)
			return false;
	}
	return true;
}

uint32_t I64Vector_hash(I64Vector self)
{
	uint32_t hash = 0;
	for (size_t i = 0, n = self->length / 4; i < n; i++) {
		uint32_t hash_step = 0;
		size_t index = i << 2;
		for (size_t j = 0; j < 4; j++) {
			hash_step = (hash_step << 6) + self->data[index + j];
		}
		hash ^= hash_step;
	}
	uint32_t hash_step = 0;
	for (size_t i = self->length - (self->length % 4); i < self->length; i++) {
		hash_step = (hash_step << 6) + self->data[i];
	}
	hash ^= hash_step;
	return hash;
}

size_t I64Vector_dump(I64Vector self, int64_t *buffer)
{
	return I64Vector_dumpn(self, buffer, self->length);
}

size_t I64Vector_dumpn(I64Vector self, int64_t *buffer, size_t n)
{
	n = self->length < n ? self->length : n;
	memcpy(buffer, self->data, sizeof(int64_t) * n);
	return n;
}

bool I64Vector_empty(I64Vector self)
{
	return self->length == 0;
}

size_t I64Vector_getLength(I64Vector self)
{
	return self->length;
}


void I64Vector_clear(I64Vector self)
{
	self->length = 0;
}

void I64Vector_eraseTail(I64Vector self, size_t count)
{
	count = count > self->length ? self->length : count;
	self->length -= count;
}

size_t I64Vector_getCapacity(I64Vector self)
{
	return self->capacity;
}

void I64Vector_setCapacity(I64Vector self, size_t capacity)
{
	capacity = capacity == 0 ? 1 : capacity;
	if (self->capacity == capacity) return;
	I64Vector_realloc(self, capacity);
}

void I64Vector_shrink(I64Vector self)
{
	I64Vector_setCapacity(self, self->length);
}

void I64Vector_set(I64Vector self, size_t index, int64_t value)
{
	self->data[index] = value;
}

int64_t I64Vector_get(I64Vector self, size_t index)
{
	return self->data[index];
}

#define Vector_preInsert(self, index) \
	if (index >= self->length) \
		return self->length; \
	if (self->length >= self->capacity) { \
		I64Vector_realloc(self, self->capacity * 2); \
	} \
	size_t i = self->length; \
	while (i > index) { \
		self->data[i] = self->data[i - 1]; \
		i -= 1; \
	} \
	self->length += 1

size_t I64Vector_insert(I64Vector self, size_t index, int64_t value)
{
	Vector_preInsert(self, index);
	self->data[i] = value;
	return self->length;
}

int64_t *I64Vector_data(I64Vector self)
{
	return self->data;
}

size_t I64Vector_push(I64Vector self, int64_t value)
{
	if (self->length >= self->capacity) {
		I64Vector_realloc(self, self->capacity * 2);
	}
	self->data[self->length] = value;
	self->length += 1;
	return self->length;
}

int64_t I64Vector_pop(I64Vector self)
{
	if (self->length > 0) 
		self->length -= 1;
	return self->data[self->length];
}

size_t I64Vector_append(I64Vector self, I64Vector src)
{
	return I64Vector_appendArray(self, src->data, src->length);
}

size_t I64Vector_appendArray(I64Vector self, const int64_t *a, size_t count)
{
	if (a == NULL || count == 0) {
		return self->length;
	}
	if (self->length + count > self->capacity) {
		I64Vector_realloc(self, self->capacity + count);
	}
	memcpy(self->data + self->length, a, sizeof(int64_t) * count);
	self->length += count;
	return self->length;
}

static inline void I64Vector_realloc(I64Vector self, size_t new_capacity)
{
	int64_t *tmp = calloc(new_capacity, sizeof(int64_t));
	if (self->length > new_capacity) {
		self->length = new_capacity;
	}
	memcpy(tmp, self->data, sizeof(int64_t) * self->length);
	free(self->data);
	self->data = tmp;
	self->capacity = new_capacity;
}

static inline void I64Vector_init(I64Vector self, size_t capacity)
{
	self->capacity = capacity == 0 ? 1 : capacity;
	self->length = 0;
	self->data = calloc(self->capacity, sizeof(int64_t));
}

static inline void I64Vector_final(I64Vector self)
{
	free(self->data);
	self->length = self->capacity = 0;
}

