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

// This file is generated from Queue.c.ohce by ohce.
#include "U64Queue.h"
#include <string.h>

struct _ADT_U64Queue_ {
	size_t c; // capacity
	size_t h, t; // head, tail
	uint64_t *data;
};

// Careful: `-1 % 7 == -1` is true.
// Careful: `(0u - 1u) % 7u != 6` maybe true.
#define DECRE(i, m) ((((m) + (i)) - 1) % (m))
#define INCRE(i, m) (((i) + 1) % (m))
#define LENGTH(h, t, c) ((((c) + (t)) - (h)) % (c))
#define FULL(h, t, c) (LENGTH(h, t, c) + 1 == (c))
#define EMPTY(h, t) ((h) == (t))

static void U64Queue_resize(U64Queue self);
static inline void U64Queue_freeInternal(U64Queue self);
static inline void U64Queue_newInternal(U64Queue self, size_t c);
static inline void U64Queue_copyData(uint64_t *data, U64Queue src);

U64Queue U64Queue_new()
{
	return U64Queue_newWithCapacity(1);
}

U64Queue U64Queue_newWithCapacity(size_t capacity)
{
	U64Queue self = malloc(sizeof(*self));
	U64Queue_newInternal(self, capacity);
	return self;
}

void U64Queue_free(U64Queue self)
{
	if (self != NULL) {
		U64Queue_freeInternal(self);
		free(self);
	}
}

U64Queue U64Queue_clone(U64Queue src)
{
	size_t len = LENGTH(src->h, src->t, src->c);
	U64Queue self = U64Queue_newWithCapacity(len);
	U64Queue_copyData(self->data, src);
	self->t = len;
	return self;
}

void U64Queue_copy(U64Queue self, U64Queue src)
{
	if (self == src)
		return;

	size_t len = LENGTH(src->h, src->t, src->c);
	U64Queue_freeInternal(self);
	U64Queue_newInternal(self, len);
	U64Queue_copyData(self->data, src);
	self->t = len;
}

bool U64Queue_empty(U64Queue self)
{
	return EMPTY(self->h, self->t);
}

bool U64Queue_full(U64Queue self)
{
	return FULL(self->h, self->t, self->c);
}

size_t U64Queue_length(U64Queue self)
{
	return LENGTH(self->h, self->t, self->c);
}

uint64_t U64Queue_get(U64Queue self, size_t index)
{
	uint64_t v;
	if (index >= LENGTH(self->h, self->t, self->c))
		return v;
	return self->data[(self->h + index) % self->c];
}

void U64Queue_set(U64Queue self, size_t index, uint64_t value)
{
	if (index >= LENGTH(self->h, self->t, self->c))
		return;
	self->data[(self->h + index) % self->c] = value;
}

uint64_t U64Queue_popHead(U64Queue self)
{
	uint64_t v;
	if (!EMPTY(self->h, self->t)) {
		v = self->data[self->h];
		self->h = INCRE(self->h, self->c);
	}
	return v;
}

uint64_t U64Queue_popTail(U64Queue self)
{
	uint64_t v;
	if (!EMPTY(self->h, self->t)) {
		self->t = DECRE(self->t, self->c);
		v = self->data[self->t];
	}
	return v;
}

void U64Queue_pushHead(U64Queue self, uint64_t value)
{
	if (FULL(self->h, self->t, self->c)) {
		U64Queue_resize(self);
	}
	DECRE(self->h, self->c);
	self->data[self->h] = value;
}

void U64Queue_pushTail(U64Queue self, uint64_t value)
{
	if (FULL(self->h, self->t, self->c)) {
		U64Queue_resize(self);
	}
	self->data[self->t] = value;
	INCRE(self->t, self->c);
}

static void U64Queue_resize(U64Queue self)
{
	size_t nc = 2 * self->c, j = 0;
	uint64_t *tmp = calloc(nc, sizeof(uint64_t));
	for (size_t i = self->h; i != self->t; i = INCRE(i, self->c), j++) {
		tmp[j] = self->data[i];
	}
	free(self->data);
	self->data = tmp;
	self->h = 0;
	self->t = j;
	self->c = nc;
}

static inline void U64Queue_freeInternal(U64Queue self)
{
	free(self->data);
}

static inline void U64Queue_newInternal(U64Queue self, size_t c)
{
	self->c = c == 0 ? 1 : c;
	self->h = self->t = 0;
	self->data = calloc(c, sizeof(uint64_t));
}

static inline void U64Queue_copyData(uint64_t *data, U64Queue src)
{
	for (size_t i = src->h, j = 0; i != src->t; i = INCRE(i, src->c), j++) {
		data[j] = src->data[i];
	}
}

