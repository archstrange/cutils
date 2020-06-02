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
#include "U8Queue.h"
#include <string.h>

struct _ADT_U8Queue_ {
	size_t c; // capacity
	size_t h, t; // head, tail
	uint8_t *data;
};

// Careful: `-1 % 7 == -1` is true.
// Careful: `(0u - 1u) % 7u != 6` maybe true.
#define DECRE(i, m) ((((m) + (i)) - 1) % (m))
#define INCRE(i, m) (((i) + 1) % (m))
#define LENGTH(h, t, c) ((((c) + (t)) - (h)) % (c))
#define FULL(h, t, c) (LENGTH(h, t, c) + 1 == (c))
#define EMPTY(h, t) ((h) == (t))

static void U8Queue_resize(U8Queue self);
static inline void U8Queue_freeInternal(U8Queue self);
static inline void U8Queue_newInternal(U8Queue self, size_t c);
static inline void U8Queue_copyData(uint8_t *data, U8Queue src);

U8Queue U8Queue_new()
{
	return U8Queue_newWithCapacity(1);
}

U8Queue U8Queue_newWithCapacity(size_t capacity)
{
	U8Queue self = malloc(sizeof(*self));
	U8Queue_newInternal(self, capacity);
	return self;
}

void U8Queue_free(U8Queue self)
{
	if (self != NULL) {
		U8Queue_freeInternal(self);
		free(self);
	}
}

U8Queue U8Queue_clone(U8Queue src)
{
	size_t len = LENGTH(src->h, src->t, src->c);
	U8Queue self = U8Queue_newWithCapacity(len);
	U8Queue_copyData(self->data, src);
	self->t = len;
	return self;
}

void U8Queue_copy(U8Queue self, U8Queue src)
{
	if (self == src)
		return;

	size_t len = LENGTH(src->h, src->t, src->c);
	U8Queue_freeInternal(self);
	U8Queue_newInternal(self, len);
	U8Queue_copyData(self->data, src);
	self->t = len;
}

bool U8Queue_empty(U8Queue self)
{
	return EMPTY(self->h, self->t);
}

bool U8Queue_full(U8Queue self)
{
	return FULL(self->h, self->t, self->c);
}

size_t U8Queue_length(U8Queue self)
{
	return LENGTH(self->h, self->t, self->c);
}

uint8_t U8Queue_get(U8Queue self, size_t index)
{
	uint8_t v;
	if (index >= LENGTH(self->h, self->t, self->c))
		return v;
	return self->data[(self->h + index) % self->c];
}

void U8Queue_set(U8Queue self, size_t index, uint8_t value)
{
	if (index >= LENGTH(self->h, self->t, self->c))
		return;
	self->data[(self->h + index) % self->c] = value;
}

uint8_t U8Queue_popHead(U8Queue self)
{
	uint8_t v;
	if (!EMPTY(self->h, self->t)) {
		v = self->data[self->h];
		self->h = INCRE(self->h, self->c);
	}
	return v;
}

uint8_t U8Queue_popTail(U8Queue self)
{
	uint8_t v;
	if (!EMPTY(self->h, self->t)) {
		self->t = DECRE(self->t, self->c);
		v = self->data[self->t];
	}
	return v;
}

void U8Queue_pushHead(U8Queue self, uint8_t value)
{
	if (FULL(self->h, self->t, self->c)) {
		U8Queue_resize(self);
	}
	DECRE(self->h, self->c);
	self->data[self->h] = value;
}

void U8Queue_pushTail(U8Queue self, uint8_t value)
{
	if (FULL(self->h, self->t, self->c)) {
		U8Queue_resize(self);
	}
	self->data[self->t] = value;
	INCRE(self->t, self->c);
}

static void U8Queue_resize(U8Queue self)
{
	size_t nc = 2 * self->c, j = 0;
	uint8_t *tmp = calloc(nc, sizeof(uint8_t));
	for (size_t i = self->h; i != self->t; i = INCRE(i, self->c), j++) {
		tmp[j] = self->data[i];
	}
	free(self->data);
	self->data = tmp;
	self->h = 0;
	self->t = j;
	self->c = nc;
}

static inline void U8Queue_freeInternal(U8Queue self)
{
	free(self->data);
}

static inline void U8Queue_newInternal(U8Queue self, size_t c)
{
	self->c = c == 0 ? 1 : c;
	self->h = self->t = 0;
	self->data = calloc(c, sizeof(uint8_t));
}

static inline void U8Queue_copyData(uint8_t *data, U8Queue src)
{
	for (size_t i = src->h, j = 0; i != src->t; i = INCRE(i, src->c), j++) {
		data[j] = src->data[i];
	}
}

