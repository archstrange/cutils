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
#include "StrQueue.h"
#include <string.h>

struct _ADT_StrQueue_ {
	size_t c; // capacity
	size_t h, t; // head, tail
	Str *data;
};

// Careful: `-1 % 7 == -1` is true.
// Careful: `(0u - 1u) % 7u != 6` maybe true.
#define DECRE(i, m) ((((m) + (i)) - 1) % (m))
#define INCRE(i, m) (((i) + 1) % (m))
#define LENGTH(h, t, c) ((((c) + (t)) - (h)) % (c))
#define FULL(h, t, c) (LENGTH(h, t, c) + 1 == (c))
#define EMPTY(h, t) ((h) == (t))

static void StrQueue_resize(StrQueue self);
static inline void StrQueue_freeInternal(StrQueue self);
static inline void StrQueue_newInternal(StrQueue self, size_t c);
static inline void StrQueue_copyData(Str *data, StrQueue src);

StrQueue StrQueue_new()
{
	return StrQueue_newWithCapacity(1);
}

StrQueue StrQueue_newWithCapacity(size_t capacity)
{
	StrQueue self = malloc(sizeof(*self));
	StrQueue_newInternal(self, capacity);
	return self;
}

void StrQueue_free(StrQueue self)
{
	if (self != NULL) {
		StrQueue_freeInternal(self);
		free(self);
	}
}

StrQueue StrQueue_clone(StrQueue src)
{
	size_t len = LENGTH(src->h, src->t, src->c);
	StrQueue self = StrQueue_newWithCapacity(len);
	StrQueue_copyData(self->data, src);
	self->t = len;
	return self;
}

void StrQueue_copy(StrQueue self, StrQueue src)
{
	if (self == src)
		return;

	size_t len = LENGTH(src->h, src->t, src->c);
	StrQueue_freeInternal(self);
	StrQueue_newInternal(self, len);
	StrQueue_copyData(self->data, src);
	self->t = len;
}

bool StrQueue_empty(StrQueue self)
{
	return EMPTY(self->h, self->t);
}

bool StrQueue_full(StrQueue self)
{
	return FULL(self->h, self->t, self->c);
}

size_t StrQueue_length(StrQueue self)
{
	return LENGTH(self->h, self->t, self->c);
}

Str StrQueue_get(StrQueue self, size_t index)
{
	Str v;
	if (index >= LENGTH(self->h, self->t, self->c))
		return v;
	return self->data[(self->h + index) % self->c];
}

void __StrQueue_set_use_copy(StrQueue self, size_t index, Str *value)
{
	if (index >= LENGTH(self->h, self->t, self->c))
		return;
	Str_copy(self->data[(self->h + index) % self->c], *value);
}

void __StrQueue_set_use_assign(StrQueue self, size_t index, Str value)
{
	if (index >= LENGTH(self->h, self->t, self->c))
		return;
	Str_free(self->data[(self->h + index) % self->c]);
	self->data[(self->h + index) % self->c] = value;
}

Str StrQueue_popHead(StrQueue self)
{
	Str v;
	if (!EMPTY(self->h, self->t)) {
		v = self->data[self->h];
		self->h = INCRE(self->h, self->c);
	}
	return v;
}

Str StrQueue_popTail(StrQueue self)
{
	Str v;
	if (!EMPTY(self->h, self->t)) {
		self->t = DECRE(self->t, self->c);
		v = self->data[self->t];
	}
	return v;
}

void __StrQueue_pushHead_use_clone(StrQueue self, Str *value)
{
	if (FULL(self->h, self->t, self->c)) {
		StrQueue_resize(self);
	}
	DECRE(self->h, self->c);
	self->data[self->h] = Str_clone(*value);
}

void __StrQueue_pushHead_use_assign(StrQueue self, Str value)
{
	if (FULL(self->h, self->t, self->c)) {
		StrQueue_resize(self);
	}
	DECRE(self->h, self->c);
	self->data[self->h] = value;
}

void __StrQueue_pushTail_use_clone(StrQueue self, Str *value)
{
	if (FULL(self->h, self->t, self->c)) {
		StrQueue_resize(self);
	}
	self->data[self->t] = Str_clone(*value);
	INCRE(self->t, self->c);
}

void __StrQueue_pushTail_use_assign(StrQueue self, Str value)
{
	if (FULL(self->h, self->t, self->c)) {
		StrQueue_resize(self);
	}
	self->data[self->t] = value;
	INCRE(self->t, self->c);
}

static void StrQueue_resize(StrQueue self)
{
	size_t nc = 2 * self->c, j = 0;
	Str *tmp = calloc(nc, sizeof(Str));
	for (size_t i = self->h; i != self->t; i = INCRE(i, self->c), j++) {
		tmp[j] = self->data[i];
	}
	free(self->data);
	self->data = tmp;
	self->h = 0;
	self->t = j;
	self->c = nc;
}

static inline void StrQueue_freeInternal(StrQueue self)
{
	for (size_t i = self->h; i != self->t; i = INCRE(i, self->c)) {
		Str_free(self->data[i]);
	}
	free(self->data);
}

static inline void StrQueue_newInternal(StrQueue self, size_t c)
{
	self->c = c == 0 ? 1 : c;
	self->h = self->t = 0;
	self->data = calloc(c, sizeof(Str));
}

static inline void StrQueue_copyData(Str *data, StrQueue src)
{
	for (size_t i = src->h, j = 0; i != src->t; i = INCRE(i, src->c), j++) {
		data[j] = Str_clone(src->data[i]);
	}
}

