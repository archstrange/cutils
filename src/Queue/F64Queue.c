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
#include "F64Queue.h"
#include <string.h>

struct _ADT_F64Queue_ {
	size_t c; // capacity
	size_t h, t; // head, tail
	double *data;
};

// Careful: `-1 % 7 == -1` is true.
// Careful: `(0u - 1u) % 7u != 6` maybe true.
#define DECRE(i, m) ((((m) + (i)) - 1) % (m))
#define INCRE(i, m) (((i) + 1) % (m))
#define LENGTH(h, t, c) ((((c) + (t)) - (h)) % (c))
#define FULL(h, t, c) (LENGTH(h, t, c) + 1 == (c))
#define EMPTY(h, t) ((h) == (t))

static void F64Queue_resize(F64Queue self);
static inline void F64Queue_freeInternal(F64Queue self);
static inline void F64Queue_newInternal(F64Queue self, size_t c);
static inline void F64Queue_copyData(double *data, F64Queue src);

F64Queue F64Queue_new()
{
	return F64Queue_newWithCapacity(1);
}

F64Queue F64Queue_newWithCapacity(size_t capacity)
{
	F64Queue self = malloc(sizeof(*self));
	F64Queue_newInternal(self, capacity);
	return self;
}

void F64Queue_free(F64Queue self)
{
	if (self != NULL) {
		F64Queue_freeInternal(self);
		free(self);
	}
}

F64Queue F64Queue_clone(F64Queue src)
{
	size_t len = LENGTH(src->h, src->t, src->c);
	F64Queue self = F64Queue_newWithCapacity(len);
	F64Queue_copyData(self->data, src);
	self->t = len;
	return self;
}

void F64Queue_copy(F64Queue self, F64Queue src)
{
	if (self == src)
		return;

	size_t len = LENGTH(src->h, src->t, src->c);
	F64Queue_freeInternal(self);
	F64Queue_newInternal(self, len);
	F64Queue_copyData(self->data, src);
	self->t = len;
}

bool F64Queue_empty(F64Queue self)
{
	return EMPTY(self->h, self->t);
}

bool F64Queue_full(F64Queue self)
{
	return FULL(self->h, self->t, self->c);
}

size_t F64Queue_length(F64Queue self)
{
	return LENGTH(self->h, self->t, self->c);
}

double F64Queue_get(F64Queue self, size_t index)
{
	double v;
	if (index >= LENGTH(self->h, self->t, self->c))
		return v;
	return self->data[(self->h + index) % self->c];
}

void F64Queue_set(F64Queue self, size_t index, double value)
{
	if (index >= LENGTH(self->h, self->t, self->c))
		return;
	self->data[(self->h + index) % self->c] = value;
}

double F64Queue_popHead(F64Queue self)
{
	double v;
	if (!EMPTY(self->h, self->t)) {
		v = self->data[self->h];
		self->h = INCRE(self->h, self->c);
	}
	return v;
}

double F64Queue_popTail(F64Queue self)
{
	double v;
	if (!EMPTY(self->h, self->t)) {
		self->t = DECRE(self->t, self->c);
		v = self->data[self->t];
	}
	return v;
}

void F64Queue_pushHead(F64Queue self, double value)
{
	if (FULL(self->h, self->t, self->c)) {
		F64Queue_resize(self);
	}
	DECRE(self->h, self->c);
	self->data[self->h] = value;
}

void F64Queue_pushTail(F64Queue self, double value)
{
	if (FULL(self->h, self->t, self->c)) {
		F64Queue_resize(self);
	}
	self->data[self->t] = value;
	INCRE(self->t, self->c);
}

static void F64Queue_resize(F64Queue self)
{
	size_t nc = 2 * self->c, j = 0;
	double *tmp = calloc(nc, sizeof(double));
	for (size_t i = self->h; i != self->t; i = INCRE(i, self->c), j++) {
		tmp[j] = self->data[i];
	}
	free(self->data);
	self->data = tmp;
	self->h = 0;
	self->t = j;
	self->c = nc;
}

static inline void F64Queue_freeInternal(F64Queue self)
{
	free(self->data);
}

static inline void F64Queue_newInternal(F64Queue self, size_t c)
{
	self->c = c == 0 ? 1 : c;
	self->h = self->t = 0;
	self->data = calloc(c, sizeof(double));
}

static inline void F64Queue_copyData(double *data, F64Queue src)
{
	for (size_t i = src->h, j = 0; i != src->t; i = INCRE(i, src->c), j++) {
		data[j] = src->data[i];
	}
}

