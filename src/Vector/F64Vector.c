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
#include "F64Vector.h"

#include <string.h>

struct _ADT_F64Vector {
	size_t capacity, length;
	double *data;
};

static inline void F64Vector_realloc(F64Vector self, size_t new_capacity);
static inline void F64Vector_init(F64Vector self, size_t capacity);
static inline void F64Vector_final(F64Vector self);


F64Vector F64Vector_new()
{
	return F64Vector_newWithCapacity(1);
}

F64Vector F64Vector_newWithCapacity(size_t capacity)
{
	F64Vector self = malloc(sizeof(*self));
	F64Vector_init(self, capacity);
	return self;
}

F64Vector F64Vector_newFromArray(double const *array, size_t length)
{
	F64Vector self = F64Vector_newWithCapacity(length);
	memcpy(self->data, array, sizeof(double) * length);
	self->length = length;
	return self;
}

F64Vector F64Vector_clone(F64Vector src)
{
	if (src == NULL) return F64Vector_new();
	return F64Vector_newFromArray(src->data, src->length);
}

void F64Vector_copy(F64Vector self, F64Vector src)
{
	if (self == src) return;
	F64Vector_copyArray(self, src->data, src->length);
}

void F64Vector_copyArray(F64Vector self, double const *array, size_t n)
{
	F64Vector_final(self);
	F64Vector_init(self, n);
	memcpy(self->data, array, sizeof(double) * n);
	self->length = n;
}

void F64Vector_copySub(F64Vector self, F64Vector src, size_t start, size_t n)
{
	if (self != src && start < src->length) {
		n = start + n < src->length ? n : src->length - start;
		F64Vector_copyArray(self, src->data + start, n);
	}
}

void F64Vector_free(F64Vector self)
{
	if (self) {
		F64Vector_final(self);
		free(self);
	}
}

int F64Vector_cmp(F64Vector self, F64Vector right)
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

bool F64Vector_equal(F64Vector self, F64Vector right)
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

uint32_t F64Vector_hash(F64Vector self)
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

size_t F64Vector_dump(F64Vector self, double *buffer)
{
	return F64Vector_dumpn(self, buffer, self->length);
}

size_t F64Vector_dumpn(F64Vector self, double *buffer, size_t n)
{
	n = self->length < n ? self->length : n;
	memcpy(buffer, self->data, sizeof(double) * n);
	return n;
}

bool F64Vector_empty(F64Vector self)
{
	return self->length == 0;
}

size_t F64Vector_getLength(F64Vector self)
{
	return self->length;
}


void F64Vector_clear(F64Vector self)
{
	self->length = 0;
}

void F64Vector_eraseTail(F64Vector self, size_t count)
{
	count = count > self->length ? self->length : count;
	self->length -= count;
}

size_t F64Vector_getCapacity(F64Vector self)
{
	return self->capacity;
}

void F64Vector_setCapacity(F64Vector self, size_t capacity)
{
	capacity = capacity == 0 ? 1 : capacity;
	if (self->capacity == capacity) return;
	F64Vector_realloc(self, capacity);
}

void F64Vector_shrink(F64Vector self)
{
	F64Vector_setCapacity(self, self->length);
}

void F64Vector_set(F64Vector self, size_t index, double value)
{
	self->data[index] = value;
}

double F64Vector_get(F64Vector self, size_t index)
{
	return self->data[index];
}

#define Vector_preInsert(self, index) \
	if (index >= self->length) \
		return self->length; \
	if (self->length >= self->capacity) { \
		F64Vector_realloc(self, self->capacity * 2); \
	} \
	size_t i = self->length; \
	while (i > index) { \
		self->data[i] = self->data[i - 1]; \
		i -= 1; \
	} \
	self->length += 1

size_t F64Vector_insert(F64Vector self, size_t index, double value)
{
	Vector_preInsert(self, index);
	self->data[i] = value;
	return self->length;
}

double *F64Vector_data(F64Vector self)
{
	return self->data;
}

size_t F64Vector_push(F64Vector self, double value)
{
	if (self->length >= self->capacity) {
		F64Vector_realloc(self, self->capacity * 2);
	}
	self->data[self->length] = value;
	self->length += 1;
	return self->length;
}

double F64Vector_pop(F64Vector self)
{
	if (self->length > 0) 
		self->length -= 1;
	return self->data[self->length];
}

size_t F64Vector_append(F64Vector self, F64Vector src)
{
	return F64Vector_appendArray(self, src->data, src->length);
}

size_t F64Vector_appendArray(F64Vector self, const double *a, size_t count)
{
	if (a == NULL || count == 0) {
		return self->length;
	}
	if (self->length + count > self->capacity) {
		F64Vector_realloc(self, self->capacity + count);
	}
	memcpy(self->data + self->length, a, sizeof(double) * count);
	self->length += count;
	return self->length;
}

static inline void F64Vector_realloc(F64Vector self, size_t new_capacity)
{
	double *tmp = calloc(new_capacity, sizeof(double));
	if (self->length > new_capacity) {
		self->length = new_capacity;
	}
	memcpy(tmp, self->data, sizeof(double) * self->length);
	free(self->data);
	self->data = tmp;
	self->capacity = new_capacity;
}

static inline void F64Vector_init(F64Vector self, size_t capacity)
{
	self->capacity = capacity == 0 ? 1 : capacity;
	self->length = 0;
	self->data = calloc(self->capacity, sizeof(double));
}

static inline void F64Vector_final(F64Vector self)
{
	free(self->data);
	self->length = self->capacity = 0;
}

