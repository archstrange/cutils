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
#include "U8Vector.h"

#include <string.h>

struct _ADT_U8Vector {
	size_t capacity, length;
	uint8_t *data;
};

static inline void U8Vector_realloc(U8Vector self, size_t new_capacity);
static inline void U8Vector_init(U8Vector self, size_t capacity);
static inline void U8Vector_final(U8Vector self);


U8Vector U8Vector_new()
{
	return U8Vector_newWithCapacity(1);
}

U8Vector U8Vector_newWithCapacity(size_t capacity)
{
	U8Vector self = malloc(sizeof(*self));
	U8Vector_init(self, capacity);
	return self;
}

U8Vector U8Vector_newFromArray(uint8_t const *array, size_t length)
{
	U8Vector self = U8Vector_newWithCapacity(length);
	memcpy(self->data, array, sizeof(uint8_t) * length);
	self->length = length;
	return self;
}

U8Vector U8Vector_clone(U8Vector src)
{
	if (src == NULL) return U8Vector_new();
	return U8Vector_newFromArray(src->data, src->length);
}

void U8Vector_copy(U8Vector self, U8Vector src)
{
	if (self == src) return;
	U8Vector_copyArray(self, src->data, src->length);
}

void U8Vector_copyArray(U8Vector self, uint8_t const *array, size_t n)
{
	U8Vector_final(self);
	U8Vector_init(self, n);
	memcpy(self->data, array, sizeof(uint8_t) * n);
	self->length = n;
}

void U8Vector_copySub(U8Vector self, U8Vector src, size_t start, size_t n)
{
	if (self != src && start < src->length) {
		n = start + n < src->length ? n : src->length - start;
		U8Vector_copyArray(self, src->data + start, n);
	}
}

void U8Vector_free(U8Vector self)
{
	if (self) {
		U8Vector_final(self);
		free(self);
	}
}

int U8Vector_cmp(U8Vector self, U8Vector right)
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

bool U8Vector_equal(U8Vector self, U8Vector right)
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

uint32_t U8Vector_hash(U8Vector self)
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

size_t U8Vector_dump(U8Vector self, uint8_t *buffer)
{
	return U8Vector_dumpn(self, buffer, self->length);
}

size_t U8Vector_dumpn(U8Vector self, uint8_t *buffer, size_t n)
{
	n = self->length < n ? self->length : n;
	memcpy(buffer, self->data, sizeof(uint8_t) * n);
	return n;
}

bool U8Vector_empty(U8Vector self)
{
	return self->length == 0;
}

size_t U8Vector_getLength(U8Vector self)
{
	return self->length;
}


void U8Vector_clear(U8Vector self)
{
	self->length = 0;
}

void U8Vector_eraseTail(U8Vector self, size_t count)
{
	count = count > self->length ? self->length : count;
	self->length -= count;
}

size_t U8Vector_getCapacity(U8Vector self)
{
	return self->capacity;
}

void U8Vector_setCapacity(U8Vector self, size_t capacity)
{
	capacity = capacity == 0 ? 1 : capacity;
	if (self->capacity == capacity) return;
	U8Vector_realloc(self, capacity);
}

void U8Vector_shrink(U8Vector self)
{
	U8Vector_setCapacity(self, self->length);
}

void U8Vector_set(U8Vector self, size_t index, uint8_t value)
{
	self->data[index] = value;
}

uint8_t U8Vector_get(U8Vector self, size_t index)
{
	return self->data[index];
}

#define Vector_preInsert(self, index) \
	if (index >= self->length) \
		return self->length; \
	if (self->length >= self->capacity) { \
		U8Vector_realloc(self, self->capacity * 2); \
	} \
	size_t i = self->length; \
	while (i > index) { \
		self->data[i] = self->data[i - 1]; \
		i -= 1; \
	} \
	self->length += 1

size_t U8Vector_insert(U8Vector self, size_t index, uint8_t value)
{
	Vector_preInsert(self, index);
	self->data[i] = value;
	return self->length;
}

uint8_t *U8Vector_data(U8Vector self)
{
	return self->data;
}

size_t U8Vector_push(U8Vector self, uint8_t value)
{
	if (self->length >= self->capacity) {
		U8Vector_realloc(self, self->capacity * 2);
	}
	self->data[self->length] = value;
	self->length += 1;
	return self->length;
}

uint8_t U8Vector_pop(U8Vector self)
{
	if (self->length > 0) 
		self->length -= 1;
	return self->data[self->length];
}

size_t U8Vector_append(U8Vector self, U8Vector src)
{
	return U8Vector_appendArray(self, src->data, src->length);
}

size_t U8Vector_appendArray(U8Vector self, const uint8_t *a, size_t count)
{
	if (a == NULL || count == 0) {
		return self->length;
	}
	if (self->length + count > self->capacity) {
		U8Vector_realloc(self, self->capacity + count);
	}
	memcpy(self->data + self->length, a, sizeof(uint8_t) * count);
	self->length += count;
	return self->length;
}

static inline void U8Vector_realloc(U8Vector self, size_t new_capacity)
{
	uint8_t *tmp = calloc(new_capacity, sizeof(uint8_t));
	if (self->length > new_capacity) {
		self->length = new_capacity;
	}
	memcpy(tmp, self->data, sizeof(uint8_t) * self->length);
	free(self->data);
	self->data = tmp;
	self->capacity = new_capacity;
}

static inline void U8Vector_init(U8Vector self, size_t capacity)
{
	self->capacity = capacity == 0 ? 1 : capacity;
	self->length = 0;
	self->data = calloc(self->capacity, sizeof(uint8_t));
}

static inline void U8Vector_final(U8Vector self)
{
	free(self->data);
	self->length = self->capacity = 0;
}

