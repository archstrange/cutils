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
#include "I64Queue.h"
#include <string.h>

struct _ADT_I64Queue_ {
	size_t c; // capacity
	size_t h, t; // head, tail
	int64_t *data;
};

// Careful: `-1 % 7 == -1` is true.
// Careful: `(0u - 1u) % 7u != 6` maybe true.
#define DECRE(i, m) ((((m) + (i)) - 1) % (m))
#define INCRE(i, m) (((i) + 1) % (m))
#define LENGTH(h, t, c) ((((c) + (t)) - (h)) % (c))
#define FULL(h, t, c) (LENGTH(h, t, c) + 1 == (c))
#define EMPTY(h, t) ((h) == (t))

static void I64Queue_resize(I64Queue self);
static inline void I64Queue_freeInternal(I64Queue self);
static inline void I64Queue_newInternal(I64Queue self, size_t c);
static inline void I64Queue_copyData(int64_t *data, I64Queue src);

I64Queue I64Queue_new()
{
	return I64Queue_newWithCapacity(1);
}

I64Queue I64Queue_newWithCapacity(size_t capacity)
{
	I64Queue self = malloc(sizeof(*self));
	I64Queue_newInternal(self, capacity);
	return self;
}

void I64Queue_free(I64Queue self)
{
	if (self != NULL) {
		I64Queue_freeInternal(self);
		free(self);
	}
}

I64Queue I64Queue_clone(I64Queue src)
{
	size_t len = LENGTH(src->h, src->t, src->c);
	I64Queue self = I64Queue_newWithCapacity(len);
	I64Queue_copyData(self->data, src);
	self->t = len;
	return self;
}

void I64Queue_copy(I64Queue self, I64Queue src)
{
	if (self == src)
		return;

	size_t len = LENGTH(src->h, src->t, src->c);
	I64Queue_freeInternal(self);
	I64Queue_newInternal(self, len);
	I64Queue_copyData(self->data, src);
	self->t = len;
}

bool I64Queue_empty(I64Queue self)
{
	return EMPTY(self->h, self->t);
}

bool I64Queue_full(I64Queue self)
{
	return FULL(self->h, self->t, self->c);
}

size_t I64Queue_length(I64Queue self)
{
	return LENGTH(self->h, self->t, self->c);
}

int64_t I64Queue_get(I64Queue self, size_t index)
{
	int64_t v;
	if (index >= LENGTH(self->h, self->t, self->c))
		return v;
	return self->data[(self->h + index) % self->c];
}

void I64Queue_set(I64Queue self, size_t index, int64_t value)
{
	if (index >= LENGTH(self->h, self->t, self->c))
		return;
	self->data[(self->h + index) % self->c] = value;
}

int64_t I64Queue_popHead(I64Queue self)
{
	int64_t v;
	if (!EMPTY(self->h, self->t)) {
		v = self->data[self->h];
		self->h = INCRE(self->h, self->c);
	}
	return v;
}

int64_t I64Queue_popTail(I64Queue self)
{
	int64_t v;
	if (!EMPTY(self->h, self->t)) {
		self->t = DECRE(self->t, self->c);
		v = self->data[self->t];
	}
	return v;
}

void I64Queue_pushHead(I64Queue self, int64_t value)
{
	if (FULL(self->h, self->t, self->c)) {
		I64Queue_resize(self);
	}
	DECRE(self->h, self->c);
	self->data[self->h] = value;
}

void I64Queue_pushTail(I64Queue self, int64_t value)
{
	if (FULL(self->h, self->t, self->c)) {
		I64Queue_resize(self);
	}
	self->data[self->t] = value;
	INCRE(self->t, self->c);
}

static void I64Queue_resize(I64Queue self)
{
	size_t nc = 2 * self->c, j = 0;
	int64_t *tmp = calloc(nc, sizeof(int64_t));
	for (size_t i = self->h; i != self->t; i = INCRE(i, self->c), j++) {
		tmp[j] = self->data[i];
	}
	free(self->data);
	self->data = tmp;
	self->h = 0;
	self->t = j;
	self->c = nc;
}

static inline void I64Queue_freeInternal(I64Queue self)
{
	free(self->data);
}

static inline void I64Queue_newInternal(I64Queue self, size_t c)
{
	self->c = c == 0 ? 1 : c;
	self->h = self->t = 0;
	self->data = calloc(c, sizeof(int64_t));
}

static inline void I64Queue_copyData(int64_t *data, I64Queue src)
{
	for (size_t i = src->h, j = 0; i != src->t; i = INCRE(i, src->c), j++) {
		data[j] = src->data[i];
	}
}

