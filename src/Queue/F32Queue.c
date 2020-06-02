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
#include "F32Queue.h"
#include <string.h>

struct _ADT_F32Queue_ {
	size_t c; // capacity
	size_t h, t; // head, tail
	float *data;
};

// Careful: `-1 % 7 == -1` is true.
// Careful: `(0u - 1u) % 7u != 6` maybe true.
#define DECRE(i, m) ((((m) + (i)) - 1) % (m))
#define INCRE(i, m) (((i) + 1) % (m))
#define LENGTH(h, t, c) ((((c) + (t)) - (h)) % (c))
#define FULL(h, t, c) (LENGTH(h, t, c) + 1 == (c))
#define EMPTY(h, t) ((h) == (t))

static void F32Queue_resize(F32Queue self);
static inline void F32Queue_freeInternal(F32Queue self);
static inline void F32Queue_newInternal(F32Queue self, size_t c);
static inline void F32Queue_copyData(float *data, F32Queue src);

F32Queue F32Queue_new()
{
	return F32Queue_newWithCapacity(1);
}

F32Queue F32Queue_newWithCapacity(size_t capacity)
{
	F32Queue self = malloc(sizeof(*self));
	F32Queue_newInternal(self, capacity);
	return self;
}

void F32Queue_free(F32Queue self)
{
	if (self != NULL) {
		F32Queue_freeInternal(self);
		free(self);
	}
}

F32Queue F32Queue_clone(F32Queue src)
{
	size_t len = LENGTH(src->h, src->t, src->c);
	F32Queue self = F32Queue_newWithCapacity(len);
	F32Queue_copyData(self->data, src);
	self->t = len;
	return self;
}

void F32Queue_copy(F32Queue self, F32Queue src)
{
	if (self == src)
		return;

	size_t len = LENGTH(src->h, src->t, src->c);
	F32Queue_freeInternal(self);
	F32Queue_newInternal(self, len);
	F32Queue_copyData(self->data, src);
	self->t = len;
}

bool F32Queue_empty(F32Queue self)
{
	return EMPTY(self->h, self->t);
}

bool F32Queue_full(F32Queue self)
{
	return FULL(self->h, self->t, self->c);
}

size_t F32Queue_length(F32Queue self)
{
	return LENGTH(self->h, self->t, self->c);
}

float F32Queue_get(F32Queue self, size_t index)
{
	float v;
	if (index >= LENGTH(self->h, self->t, self->c))
		return v;
	return self->data[(self->h + index) % self->c];
}

void F32Queue_set(F32Queue self, size_t index, float value)
{
	if (index >= LENGTH(self->h, self->t, self->c))
		return;
	self->data[(self->h + index) % self->c] = value;
}

float F32Queue_popHead(F32Queue self)
{
	float v;
	if (!EMPTY(self->h, self->t)) {
		v = self->data[self->h];
		self->h = INCRE(self->h, self->c);
	}
	return v;
}

float F32Queue_popTail(F32Queue self)
{
	float v;
	if (!EMPTY(self->h, self->t)) {
		self->t = DECRE(self->t, self->c);
		v = self->data[self->t];
	}
	return v;
}

void F32Queue_pushHead(F32Queue self, float value)
{
	if (FULL(self->h, self->t, self->c)) {
		F32Queue_resize(self);
	}
	DECRE(self->h, self->c);
	self->data[self->h] = value;
}

void F32Queue_pushTail(F32Queue self, float value)
{
	if (FULL(self->h, self->t, self->c)) {
		F32Queue_resize(self);
	}
	self->data[self->t] = value;
	INCRE(self->t, self->c);
}

static void F32Queue_resize(F32Queue self)
{
	size_t nc = 2 * self->c, j = 0;
	float *tmp = calloc(nc, sizeof(float));
	for (size_t i = self->h; i != self->t; i = INCRE(i, self->c), j++) {
		tmp[j] = self->data[i];
	}
	free(self->data);
	self->data = tmp;
	self->h = 0;
	self->t = j;
	self->c = nc;
}

static inline void F32Queue_freeInternal(F32Queue self)
{
	free(self->data);
}

static inline void F32Queue_newInternal(F32Queue self, size_t c)
{
	self->c = c == 0 ? 1 : c;
	self->h = self->t = 0;
	self->data = calloc(c, sizeof(float));
}

static inline void F32Queue_copyData(float *data, F32Queue src)
{
	for (size_t i = src->h, j = 0; i != src->t; i = INCRE(i, src->c), j++) {
		data[j] = src->data[i];
	}
}

