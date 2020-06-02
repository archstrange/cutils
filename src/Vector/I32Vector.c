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
#include "I32Vector.h"

#include <string.h>

struct _ADT_I32Vector {
	size_t capacity, length;
	int32_t *data;
};

static inline void I32Vector_realloc(I32Vector self, size_t new_capacity);
static inline void I32Vector_init(I32Vector self, size_t capacity);
static inline void I32Vector_final(I32Vector self);


I32Vector I32Vector_new()
{
	return I32Vector_newWithCapacity(1);
}

I32Vector I32Vector_newWithCapacity(size_t capacity)
{
	I32Vector self = malloc(sizeof(*self));
	I32Vector_init(self, capacity);
	return self;
}

I32Vector I32Vector_newFromArray(int32_t const *array, size_t length)
{
	I32Vector self = I32Vector_newWithCapacity(length);
	memcpy(self->data, array, sizeof(int32_t) * length);
	self->length = length;
	return self;
}

I32Vector I32Vector_clone(I32Vector src)
{
	if (src == NULL) return I32Vector_new();
	return I32Vector_newFromArray(src->data, src->length);
}

void I32Vector_copy(I32Vector self, I32Vector src)
{
	if (self == src) return;
	I32Vector_copyArray(self, src->data, src->length);
}

void I32Vector_copyArray(I32Vector self, int32_t const *array, size_t n)
{
	I32Vector_final(self);
	I32Vector_init(self, n);
	memcpy(self->data, array, sizeof(int32_t) * n);
	self->length = n;
}

void I32Vector_copySub(I32Vector self, I32Vector src, size_t start, size_t n)
{
	if (self != src && start < src->length) {
		n = start + n < src->length ? n : src->length - start;
		I32Vector_copyArray(self, src->data + start, n);
	}
}

void I32Vector_free(I32Vector self)
{
	if (self) {
		I32Vector_final(self);
		free(self);
	}
}

int I32Vector_cmp(I32Vector self, I32Vector right)
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

bool I32Vector_equal(I32Vector self, I32Vector right)
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

uint32_t I32Vector_hash(I32Vector self)
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

size_t I32Vector_dump(I32Vector self, int32_t *buffer)
{
	return I32Vector_dumpn(self, buffer, self->length);
}

size_t I32Vector_dumpn(I32Vector self, int32_t *buffer, size_t n)
{
	n = self->length < n ? self->length : n;
	memcpy(buffer, self->data, sizeof(int32_t) * n);
	return n;
}

bool I32Vector_empty(I32Vector self)
{
	return self->length == 0;
}

size_t I32Vector_getLength(I32Vector self)
{
	return self->length;
}


void I32Vector_clear(I32Vector self)
{
	self->length = 0;
}

void I32Vector_eraseTail(I32Vector self, size_t count)
{
	count = count > self->length ? self->length : count;
	self->length -= count;
}

size_t I32Vector_getCapacity(I32Vector self)
{
	return self->capacity;
}

void I32Vector_setCapacity(I32Vector self, size_t capacity)
{
	capacity = capacity == 0 ? 1 : capacity;
	if (self->capacity == capacity) return;
	I32Vector_realloc(self, capacity);
}

void I32Vector_shrink(I32Vector self)
{
	I32Vector_setCapacity(self, self->length);
}

void I32Vector_set(I32Vector self, size_t index, int32_t value)
{
	self->data[index] = value;
}

int32_t I32Vector_get(I32Vector self, size_t index)
{
	return self->data[index];
}

#define Vector_preInsert(self, index) \
	if (index >= self->length) \
		return self->length; \
	if (self->length >= self->capacity) { \
		I32Vector_realloc(self, self->capacity * 2); \
	} \
	size_t i = self->length; \
	while (i > index) { \
		self->data[i] = self->data[i - 1]; \
		i -= 1; \
	} \
	self->length += 1

size_t I32Vector_insert(I32Vector self, size_t index, int32_t value)
{
	Vector_preInsert(self, index);
	self->data[i] = value;
	return self->length;
}

int32_t *I32Vector_data(I32Vector self)
{
	return self->data;
}

size_t I32Vector_push(I32Vector self, int32_t value)
{
	if (self->length >= self->capacity) {
		I32Vector_realloc(self, self->capacity * 2);
	}
	self->data[self->length] = value;
	self->length += 1;
	return self->length;
}

int32_t I32Vector_pop(I32Vector self)
{
	if (self->length > 0) 
		self->length -= 1;
	return self->data[self->length];
}

size_t I32Vector_append(I32Vector self, I32Vector src)
{
	return I32Vector_appendArray(self, src->data, src->length);
}

size_t I32Vector_appendArray(I32Vector self, const int32_t *a, size_t count)
{
	if (a == NULL || count == 0) {
		return self->length;
	}
	if (self->length + count > self->capacity) {
		I32Vector_realloc(self, self->capacity + count);
	}
	memcpy(self->data + self->length, a, sizeof(int32_t) * count);
	self->length += count;
	return self->length;
}

static inline void I32Vector_realloc(I32Vector self, size_t new_capacity)
{
	int32_t *tmp = calloc(new_capacity, sizeof(int32_t));
	if (self->length > new_capacity) {
		self->length = new_capacity;
	}
	memcpy(tmp, self->data, sizeof(int32_t) * self->length);
	free(self->data);
	self->data = tmp;
	self->capacity = new_capacity;
}

static inline void I32Vector_init(I32Vector self, size_t capacity)
{
	self->capacity = capacity == 0 ? 1 : capacity;
	self->length = 0;
	self->data = calloc(self->capacity, sizeof(int32_t));
}

static inline void I32Vector_final(I32Vector self)
{
	free(self->data);
	self->length = self->capacity = 0;
}

