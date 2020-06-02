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
#include "I8Queue.h"
#include <string.h>

struct _ADT_I8Queue_ {
	size_t c; // capacity
	size_t h, t; // head, tail
	int8_t *data;
};

// Careful: `-1 % 7 == -1` is true.
// Careful: `(0u - 1u) % 7u != 6` maybe true.
#define DECRE(i, m) ((((m) + (i)) - 1) % (m))
#define INCRE(i, m) (((i) + 1) % (m))
#define LENGTH(h, t, c) ((((c) + (t)) - (h)) % (c))
#define FULL(h, t, c) (LENGTH(h, t, c) + 1 == (c))
#define EMPTY(h, t) ((h) == (t))

static void I8Queue_resize(I8Queue self);
static inline void I8Queue_freeInternal(I8Queue self);
static inline void I8Queue_newInternal(I8Queue self, size_t c);
static inline void I8Queue_copyData(int8_t *data, I8Queue src);

I8Queue I8Queue_new()
{
	return I8Queue_newWithCapacity(1);
}

I8Queue I8Queue_newWithCapacity(size_t capacity)
{
	I8Queue self = malloc(sizeof(*self));
	I8Queue_newInternal(self, capacity);
	return self;
}

void I8Queue_free(I8Queue self)
{
	if (self != NULL) {
		I8Queue_freeInternal(self);
		free(self);
	}
}

I8Queue I8Queue_clone(I8Queue src)
{
	size_t len = LENGTH(src->h, src->t, src->c);
	I8Queue self = I8Queue_newWithCapacity(len);
	I8Queue_copyData(self->data, src);
	self->t = len;
	return self;
}

void I8Queue_copy(I8Queue self, I8Queue src)
{
	if (self == src)
		return;

	size_t len = LENGTH(src->h, src->t, src->c);
	I8Queue_freeInternal(self);
	I8Queue_newInternal(self, len);
	I8Queue_copyData(self->data, src);
	self->t = len;
}

bool I8Queue_empty(I8Queue self)
{
	return EMPTY(self->h, self->t);
}

bool I8Queue_full(I8Queue self)
{
	return FULL(self->h, self->t, self->c);
}

size_t I8Queue_length(I8Queue self)
{
	return LENGTH(self->h, self->t, self->c);
}

int8_t I8Queue_get(I8Queue self, size_t index)
{
	int8_t v;
	if (index >= LENGTH(self->h, self->t, self->c))
		return v;
	return self->data[(self->h + index) % self->c];
}

void I8Queue_set(I8Queue self, size_t index, int8_t value)
{
	if (index >= LENGTH(self->h, self->t, self->c))
		return;
	self->data[(self->h + index) % self->c] = value;
}

int8_t I8Queue_popHead(I8Queue self)
{
	int8_t v;
	if (!EMPTY(self->h, self->t)) {
		v = self->data[self->h];
		self->h = INCRE(self->h, self->c);
	}
	return v;
}

int8_t I8Queue_popTail(I8Queue self)
{
	int8_t v;
	if (!EMPTY(self->h, self->t)) {
		self->t = DECRE(self->t, self->c);
		v = self->data[self->t];
	}
	return v;
}

void I8Queue_pushHead(I8Queue self, int8_t value)
{
	if (FULL(self->h, self->t, self->c)) {
		I8Queue_resize(self);
	}
	DECRE(self->h, self->c);
	self->data[self->h] = value;
}

void I8Queue_pushTail(I8Queue self, int8_t value)
{
	if (FULL(self->h, self->t, self->c)) {
		I8Queue_resize(self);
	}
	self->data[self->t] = value;
	INCRE(self->t, self->c);
}

static void I8Queue_resize(I8Queue self)
{
	size_t nc = 2 * self->c, j = 0;
	int8_t *tmp = calloc(nc, sizeof(int8_t));
	for (size_t i = self->h; i != self->t; i = INCRE(i, self->c), j++) {
		tmp[j] = self->data[i];
	}
	free(self->data);
	self->data = tmp;
	self->h = 0;
	self->t = j;
	self->c = nc;
}

static inline void I8Queue_freeInternal(I8Queue self)
{
	free(self->data);
}

static inline void I8Queue_newInternal(I8Queue self, size_t c)
{
	self->c = c == 0 ? 1 : c;
	self->h = self->t = 0;
	self->data = calloc(c, sizeof(int8_t));
}

static inline void I8Queue_copyData(int8_t *data, I8Queue src)
{
	for (size_t i = src->h, j = 0; i != src->t; i = INCRE(i, src->c), j++) {
		data[j] = src->data[i];
	}
}

