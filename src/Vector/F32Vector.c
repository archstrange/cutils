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
#include "F32Vector.h"

#include <string.h>

struct _ADT_F32Vector {
	size_t capacity, length;
	float *data;
};

static inline void F32Vector_realloc(F32Vector self, size_t new_capacity);
static inline void F32Vector_init(F32Vector self, size_t capacity);
static inline void F32Vector_final(F32Vector self);


F32Vector F32Vector_new()
{
	return F32Vector_newWithCapacity(1);
}

F32Vector F32Vector_newWithCapacity(size_t capacity)
{
	F32Vector self = malloc(sizeof(*self));
	F32Vector_init(self, capacity);
	return self;
}

F32Vector F32Vector_newFromArray(float const *array, size_t length)
{
	F32Vector self = F32Vector_newWithCapacity(length);
	memcpy(self->data, array, sizeof(float) * length);
	self->length = length;
	return self;
}

F32Vector F32Vector_clone(F32Vector src)
{
	if (src == NULL) return F32Vector_new();
	return F32Vector_newFromArray(src->data, src->length);
}

void F32Vector_copy(F32Vector self, F32Vector src)
{
	if (self == src) return;
	F32Vector_copyArray(self, src->data, src->length);
}

void F32Vector_copyArray(F32Vector self, float const *array, size_t n)
{
	F32Vector_final(self);
	F32Vector_init(self, n);
	memcpy(self->data, array, sizeof(float) * n);
	self->length = n;
}

void F32Vector_copySub(F32Vector self, F32Vector src, size_t start, size_t n)
{
	if (self != src && start < src->length) {
		n = start + n < src->length ? n : src->length - start;
		F32Vector_copyArray(self, src->data + start, n);
	}
}

void F32Vector_free(F32Vector self)
{
	if (self) {
		F32Vector_final(self);
		free(self);
	}
}

int F32Vector_cmp(F32Vector self, F32Vector right)
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

bool F32Vector_equal(F32Vector self, F32Vector right)
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

uint32_t F32Vector_hash(F32Vector self)
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

size_t F32Vector_dump(F32Vector self, float *buffer)
{
	return F32Vector_dumpn(self, buffer, self->length);
}

size_t F32Vector_dumpn(F32Vector self, float *buffer, size_t n)
{
	n = self->length < n ? self->length : n;
	memcpy(buffer, self->data, sizeof(float) * n);
	return n;
}

bool F32Vector_empty(F32Vector self)
{
	return self->length == 0;
}

size_t F32Vector_getLength(F32Vector self)
{
	return self->length;
}


void F32Vector_clear(F32Vector self)
{
	self->length = 0;
}

void F32Vector_eraseTail(F32Vector self, size_t count)
{
	count = count > self->length ? self->length : count;
	self->length -= count;
}

size_t F32Vector_getCapacity(F32Vector self)
{
	return self->capacity;
}

void F32Vector_setCapacity(F32Vector self, size_t capacity)
{
	capacity = capacity == 0 ? 1 : capacity;
	if (self->capacity == capacity) return;
	F32Vector_realloc(self, capacity);
}

void F32Vector_shrink(F32Vector self)
{
	F32Vector_setCapacity(self, self->length);
}

void F32Vector_set(F32Vector self, size_t index, float value)
{
	self->data[index] = value;
}

float F32Vector_get(F32Vector self, size_t index)
{
	return self->data[index];
}

#define Vector_preInsert(self, index) \
	if (index >= self->length) \
		return self->length; \
	if (self->length >= self->capacity) { \
		F32Vector_realloc(self, self->capacity * 2); \
	} \
	size_t i = self->length; \
	while (i > index) { \
		self->data[i] = self->data[i - 1]; \
		i -= 1; \
	} \
	self->length += 1

size_t F32Vector_insert(F32Vector self, size_t index, float value)
{
	Vector_preInsert(self, index);
	self->data[i] = value;
	return self->length;
}

float *F32Vector_data(F32Vector self)
{
	return self->data;
}

size_t F32Vector_push(F32Vector self, float value)
{
	if (self->length >= self->capacity) {
		F32Vector_realloc(self, self->capacity * 2);
	}
	self->data[self->length] = value;
	self->length += 1;
	return self->length;
}

float F32Vector_pop(F32Vector self)
{
	if (self->length > 0) 
		self->length -= 1;
	return self->data[self->length];
}

size_t F32Vector_append(F32Vector self, F32Vector src)
{
	return F32Vector_appendArray(self, src->data, src->length);
}

size_t F32Vector_appendArray(F32Vector self, const float *a, size_t count)
{
	if (a == NULL || count == 0) {
		return self->length;
	}
	if (self->length + count > self->capacity) {
		F32Vector_realloc(self, self->capacity + count);
	}
	memcpy(self->data + self->length, a, sizeof(float) * count);
	self->length += count;
	return self->length;
}

static inline void F32Vector_realloc(F32Vector self, size_t new_capacity)
{
	float *tmp = calloc(new_capacity, sizeof(float));
	if (self->length > new_capacity) {
		self->length = new_capacity;
	}
	memcpy(tmp, self->data, sizeof(float) * self->length);
	free(self->data);
	self->data = tmp;
	self->capacity = new_capacity;
}

static inline void F32Vector_init(F32Vector self, size_t capacity)
{
	self->capacity = capacity == 0 ? 1 : capacity;
	self->length = 0;
	self->data = calloc(self->capacity, sizeof(float));
}

static inline void F32Vector_final(F32Vector self)
{
	free(self->data);
	self->length = self->capacity = 0;
}

