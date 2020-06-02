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
#include "U16Vector.h"

#include <string.h>

struct _ADT_U16Vector {
	size_t capacity, length;
	uint16_t *data;
};

static inline void U16Vector_realloc(U16Vector self, size_t new_capacity);
static inline void U16Vector_init(U16Vector self, size_t capacity);
static inline void U16Vector_final(U16Vector self);


U16Vector U16Vector_new()
{
	return U16Vector_newWithCapacity(1);
}

U16Vector U16Vector_newWithCapacity(size_t capacity)
{
	U16Vector self = malloc(sizeof(*self));
	U16Vector_init(self, capacity);
	return self;
}

U16Vector U16Vector_newFromArray(uint16_t const *array, size_t length)
{
	U16Vector self = U16Vector_newWithCapacity(length);
	memcpy(self->data, array, sizeof(uint16_t) * length);
	self->length = length;
	return self;
}

U16Vector U16Vector_clone(U16Vector src)
{
	if (src == NULL) return U16Vector_new();
	return U16Vector_newFromArray(src->data, src->length);
}

void U16Vector_copy(U16Vector self, U16Vector src)
{
	if (self == src) return;
	U16Vector_copyArray(self, src->data, src->length);
}

void U16Vector_copyArray(U16Vector self, uint16_t const *array, size_t n)
{
	U16Vector_final(self);
	U16Vector_init(self, n);
	memcpy(self->data, array, sizeof(uint16_t) * n);
	self->length = n;
}

void U16Vector_copySub(U16Vector self, U16Vector src, size_t start, size_t n)
{
	if (self != src && start < src->length) {
		n = start + n < src->length ? n : src->length - start;
		U16Vector_copyArray(self, src->data + start, n);
	}
}

void U16Vector_free(U16Vector self)
{
	if (self) {
		U16Vector_final(self);
		free(self);
	}
}

int U16Vector_cmp(U16Vector self, U16Vector right)
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

bool U16Vector_equal(U16Vector self, U16Vector right)
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

uint32_t U16Vector_hash(U16Vector self)
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

size_t U16Vector_dump(U16Vector self, uint16_t *buffer)
{
	return U16Vector_dumpn(self, buffer, self->length);
}

size_t U16Vector_dumpn(U16Vector self, uint16_t *buffer, size_t n)
{
	n = self->length < n ? self->length : n;
	memcpy(buffer, self->data, sizeof(uint16_t) * n);
	return n;
}

bool U16Vector_empty(U16Vector self)
{
	return self->length == 0;
}

size_t U16Vector_getLength(U16Vector self)
{
	return self->length;
}


void U16Vector_clear(U16Vector self)
{
	self->length = 0;
}

void U16Vector_eraseTail(U16Vector self, size_t count)
{
	count = count > self->length ? self->length : count;
	self->length -= count;
}

size_t U16Vector_getCapacity(U16Vector self)
{
	return self->capacity;
}

void U16Vector_setCapacity(U16Vector self, size_t capacity)
{
	capacity = capacity == 0 ? 1 : capacity;
	if (self->capacity == capacity) return;
	U16Vector_realloc(self, capacity);
}

void U16Vector_shrink(U16Vector self)
{
	U16Vector_setCapacity(self, self->length);
}

void U16Vector_set(U16Vector self, size_t index, uint16_t value)
{
	self->data[index] = value;
}

uint16_t U16Vector_get(U16Vector self, size_t index)
{
	return self->data[index];
}

#define Vector_preInsert(self, index) \
	if (index >= self->length) \
		return self->length; \
	if (self->length >= self->capacity) { \
		U16Vector_realloc(self, self->capacity * 2); \
	} \
	size_t i = self->length; \
	while (i > index) { \
		self->data[i] = self->data[i - 1]; \
		i -= 1; \
	} \
	self->length += 1

size_t U16Vector_insert(U16Vector self, size_t index, uint16_t value)
{
	Vector_preInsert(self, index);
	self->data[i] = value;
	return self->length;
}

uint16_t *U16Vector_data(U16Vector self)
{
	return self->data;
}

size_t U16Vector_push(U16Vector self, uint16_t value)
{
	if (self->length >= self->capacity) {
		U16Vector_realloc(self, self->capacity * 2);
	}
	self->data[self->length] = value;
	self->length += 1;
	return self->length;
}

uint16_t U16Vector_pop(U16Vector self)
{
	if (self->length > 0) 
		self->length -= 1;
	return self->data[self->length];
}

size_t U16Vector_append(U16Vector self, U16Vector src)
{
	return U16Vector_appendArray(self, src->data, src->length);
}

size_t U16Vector_appendArray(U16Vector self, const uint16_t *a, size_t count)
{
	if (a == NULL || count == 0) {
		return self->length;
	}
	if (self->length + count > self->capacity) {
		U16Vector_realloc(self, self->capacity + count);
	}
	memcpy(self->data + self->length, a, sizeof(uint16_t) * count);
	self->length += count;
	return self->length;
}

static inline void U16Vector_realloc(U16Vector self, size_t new_capacity)
{
	uint16_t *tmp = calloc(new_capacity, sizeof(uint16_t));
	if (self->length > new_capacity) {
		self->length = new_capacity;
	}
	memcpy(tmp, self->data, sizeof(uint16_t) * self->length);
	free(self->data);
	self->data = tmp;
	self->capacity = new_capacity;
}

static inline void U16Vector_init(U16Vector self, size_t capacity)
{
	self->capacity = capacity == 0 ? 1 : capacity;
	self->length = 0;
	self->data = calloc(self->capacity, sizeof(uint16_t));
}

static inline void U16Vector_final(U16Vector self)
{
	free(self->data);
	self->length = self->capacity = 0;
}

