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
#include "Str.h"

#include <string.h>

struct _ADT_Str {
	size_t capacity, length;
	uint8_t *data;
};

static inline void Str_realloc(Str self, size_t new_capacity);
static inline void Str_init(Str self, size_t capacity);
static inline void Str_final(Str self);


Str Str_new()
{
	return Str_newWithCapacity(1);
}

Str Str_newWithCapacity(size_t capacity)
{
	Str self = malloc(sizeof(*self));
	Str_init(self, capacity);
	return self;
}

Str Str_newFromArray(uint8_t const *array, size_t length)
{
	Str self = Str_newWithCapacity(length);
	memcpy(self->data, array, sizeof(uint8_t) * length);
	self->length = length;
	return self;
}

Str Str_clone(Str src)
{
	if (src == NULL) return Str_new();
	return Str_newFromArray(src->data, src->length);
}

void Str_copy(Str self, Str src)
{
	if (self == src) return;
	Str_copyArray(self, src->data, src->length);
}

void Str_copyArray(Str self, uint8_t const *array, size_t n)
{
	Str_final(self);
	Str_init(self, n);
	memcpy(self->data, array, sizeof(uint8_t) * n);
	self->length = n;
}

void Str_copySub(Str self, Str src, size_t start, size_t n)
{
	if (self != src && start < src->length) {
		n = start + n < src->length ? n : src->length - start;
		Str_copyArray(self, src->data + start, n);
	}
}

void Str_free(Str self)
{
	if (self) {
		Str_final(self);
		free(self);
	}
}

int Str_cmp(Str self, Str right)
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

bool Str_equal(Str self, Str right)
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

uint32_t Str_hash(Str self)
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

size_t Str_dump(Str self, uint8_t *buffer)
{
	return Str_dumpn(self, buffer, self->length);
}

size_t Str_dumpn(Str self, uint8_t *buffer, size_t n)
{
	n = self->length < n ? self->length : n;
	memcpy(buffer, self->data, sizeof(uint8_t) * n);
	return n;
}

bool Str_empty(Str self)
{
	return self->length == 0;
}

size_t Str_getLength(Str self)
{
	return self->length;
}


void Str_clear(Str self)
{
	self->length = 0;
}

void Str_eraseTail(Str self, size_t count)
{
	count = count > self->length ? self->length : count;
	self->length -= count;
}

size_t Str_getCapacity(Str self)
{
	return self->capacity;
}

void Str_setCapacity(Str self, size_t capacity)
{
	capacity = capacity == 0 ? 1 : capacity;
	if (self->capacity == capacity) return;
	Str_realloc(self, capacity);
}

void Str_shrink(Str self)
{
	Str_setCapacity(self, self->length);
}

void Str_set(Str self, size_t index, uint8_t value)
{
	self->data[index] = value;
}

uint8_t Str_get(Str self, size_t index)
{
	return self->data[index];
}

#define Vector_preInsert(self, index) \
	if (index >= self->length) \
		return self->length; \
	if (self->length >= self->capacity) { \
		Str_realloc(self, self->capacity * 2); \
	} \
	size_t i = self->length; \
	while (i > index) { \
		self->data[i] = self->data[i - 1]; \
		i -= 1; \
	} \
	self->length += 1

size_t Str_insert(Str self, size_t index, uint8_t value)
{
	Vector_preInsert(self, index);
	self->data[i] = value;
	return self->length;
}

uint8_t *Str_data(Str self)
{
	return self->data;
}

size_t Str_push(Str self, uint8_t value)
{
	if (self->length >= self->capacity) {
		Str_realloc(self, self->capacity * 2);
	}
	self->data[self->length] = value;
	self->length += 1;
	return self->length;
}

uint8_t Str_pop(Str self)
{
	if (self->length > 0) 
		self->length -= 1;
	return self->data[self->length];
}

size_t Str_append(Str self, Str src)
{
	return Str_appendArray(self, src->data, src->length);
}

size_t Str_appendArray(Str self, const uint8_t *a, size_t count)
{
	if (a == NULL || count == 0) {
		return self->length;
	}
	if (self->length + count > self->capacity) {
		Str_realloc(self, self->capacity + count);
	}
	memcpy(self->data + self->length, a, sizeof(uint8_t) * count);
	self->length += count;
	return self->length;
}

static inline void Str_realloc(Str self, size_t new_capacity)
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

static inline void Str_init(Str self, size_t capacity)
{
	self->capacity = capacity == 0 ? 1 : capacity;
	self->length = 0;
	self->data = calloc(self->capacity, sizeof(uint8_t));
}

static inline void Str_final(Str self)
{
	free(self->data);
	self->length = self->capacity = 0;
}

