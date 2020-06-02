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
#include "I32Queue.h"
#include <string.h>

struct _ADT_I32Queue_ {
	size_t c; // capacity
	size_t h, t; // head, tail
	int32_t *data;
};

// Careful: `-1 % 7 == -1` is true.
// Careful: `(0u - 1u) % 7u != 6` maybe true.
#define DECRE(i, m) ((((m) + (i)) - 1) % (m))
#define INCRE(i, m) (((i) + 1) % (m))
#define LENGTH(h, t, c) ((((c) + (t)) - (h)) % (c))
#define FULL(h, t, c) (LENGTH(h, t, c) + 1 == (c))
#define EMPTY(h, t) ((h) == (t))

static void I32Queue_resize(I32Queue self);
static inline void I32Queue_freeInternal(I32Queue self);
static inline void I32Queue_newInternal(I32Queue self, size_t c);
static inline void I32Queue_copyData(int32_t *data, I32Queue src);

I32Queue I32Queue_new()
{
	return I32Queue_newWithCapacity(1);
}

I32Queue I32Queue_newWithCapacity(size_t capacity)
{
	I32Queue self = malloc(sizeof(*self));
	I32Queue_newInternal(self, capacity);
	return self;
}

void I32Queue_free(I32Queue self)
{
	if (self != NULL) {
		I32Queue_freeInternal(self);
		free(self);
	}
}

I32Queue I32Queue_clone(I32Queue src)
{
	size_t len = LENGTH(src->h, src->t, src->c);
	I32Queue self = I32Queue_newWithCapacity(len);
	I32Queue_copyData(self->data, src);
	self->t = len;
	return self;
}

void I32Queue_copy(I32Queue self, I32Queue src)
{
	if (self == src)
		return;

	size_t len = LENGTH(src->h, src->t, src->c);
	I32Queue_freeInternal(self);
	I32Queue_newInternal(self, len);
	I32Queue_copyData(self->data, src);
	self->t = len;
}

bool I32Queue_empty(I32Queue self)
{
	return EMPTY(self->h, self->t);
}

bool I32Queue_full(I32Queue self)
{
	return FULL(self->h, self->t, self->c);
}

size_t I32Queue_length(I32Queue self)
{
	return LENGTH(self->h, self->t, self->c);
}

int32_t I32Queue_get(I32Queue self, size_t index)
{
	int32_t v;
	if (index >= LENGTH(self->h, self->t, self->c))
		return v;
	return self->data[(self->h + index) % self->c];
}

void I32Queue_set(I32Queue self, size_t index, int32_t value)
{
	if (index >= LENGTH(self->h, self->t, self->c))
		return;
	self->data[(self->h + index) % self->c] = value;
}

int32_t I32Queue_popHead(I32Queue self)
{
	int32_t v;
	if (!EMPTY(self->h, self->t)) {
		v = self->data[self->h];
		self->h = INCRE(self->h, self->c);
	}
	return v;
}

int32_t I32Queue_popTail(I32Queue self)
{
	int32_t v;
	if (!EMPTY(self->h, self->t)) {
		self->t = DECRE(self->t, self->c);
		v = self->data[self->t];
	}
	return v;
}

void I32Queue_pushHead(I32Queue self, int32_t value)
{
	if (FULL(self->h, self->t, self->c)) {
		I32Queue_resize(self);
	}
	DECRE(self->h, self->c);
	self->data[self->h] = value;
}

void I32Queue_pushTail(I32Queue self, int32_t value)
{
	if (FULL(self->h, self->t, self->c)) {
		I32Queue_resize(self);
	}
	self->data[self->t] = value;
	INCRE(self->t, self->c);
}

static void I32Queue_resize(I32Queue self)
{
	size_t nc = 2 * self->c, j = 0;
	int32_t *tmp = calloc(nc, sizeof(int32_t));
	for (size_t i = self->h; i != self->t; i = INCRE(i, self->c), j++) {
		tmp[j] = self->data[i];
	}
	free(self->data);
	self->data = tmp;
	self->h = 0;
	self->t = j;
	self->c = nc;
}

static inline void I32Queue_freeInternal(I32Queue self)
{
	free(self->data);
}

static inline void I32Queue_newInternal(I32Queue self, size_t c)
{
	self->c = c == 0 ? 1 : c;
	self->h = self->t = 0;
	self->data = calloc(c, sizeof(int32_t));
}

static inline void I32Queue_copyData(int32_t *data, I32Queue src)
{
	for (size_t i = src->h, j = 0; i != src->t; i = INCRE(i, src->c), j++) {
		data[j] = src->data[i];
	}
}

