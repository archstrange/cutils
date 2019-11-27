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

#include "LS.h"
#include "utf-8.h"
#include "Vector/U32Vector.h"

static U32Vector codepoints(const uint8_t *u, size_t len);
static inline LS LS_new(bool is_utf8, bool is_interact);
static bool LS_eatLine(LS self);
static void LS_update(LS self);
static bool LS_checkPosition(LS self, size_t pos);

struct _LexerSource_ {
	bool utf8, interact;
	union {
		Str ss; // str mode or line for interact mode
		U32Vector us; // utf-8 str mode or line for utf-8 interact mode
	};
	FILE *fs; // interact mode
	size_t index, row, column;
	int c;
	int e; // error
};

LS LS_newStrSource(Str s, bool is_utf8)
{
	LS self = LS_new(is_utf8, false);

	if (is_utf8) {
		self->us = codepoints(Str_data(s), Str_getLength(s));
	} else {
		self->ss = Str_clone(s);
	}

	LS_update(self);
	return self;
}

LS LS_newCStrSource(const char *s, bool is_utf8)
{
	LS self = LS_new(is_utf8, false);

	if (is_utf8) {
		self->us = codepoints(s, CStr_len(s));
	} else {
		self->ss = Str_newFromArray(s, CStr_len(s));
	}

	LS_update(self);
	return self;
}

LS LS_newFileSource(FILE *fp, bool is_utf8, bool is_interact)
{
	if (!is_interact) {
		Str s = Str_new();
		Str_readFile(s, fp);
		LS self = LS_newStrSource(s, is_utf8);
		Str_free(s);
		return self;
	}

	LS self = LS_new(is_utf8, true);

	self->fs = fp;
	if (is_utf8) {
		self->us = U32Vector_new();
	} else {
		self->ss = Str_new();
	}

	LS_update(self);
	return self;
}

void LS_free(LS self)
{
	if (self != NULL) {
		if (self->utf8)
			U32Vector_free(self->us);
		else
			Str_free(self->ss);
		free(self);
	}
}

int LS_char(LS self)
{
	return self->c;
}

void LS_position(LS self, size_t *index, size_t *row, size_t *column)
{
	if (index) *index = self->index;
	if (row) *row = self->row;
	if (column) *column = self->column;
}

bool LS_next(LS self)
{
	if (self->c < 0)
		return false;

	self->index += 1;
	LS_update(self);
	return self->c >= 0;
}

int LS_peek(LS self, int64_t pos)
{
	if (pos < 0 && (-pos) > self->index)
		return LS_BAD_POS;

	size_t index = self->index + pos;
	if (!LS_checkPosition(self, index))
		return LS_BAD_POS;
	if (self->utf8) {
		return U32Vector_get(self->us, index);
	} else {
		return Str_get(self->ss, index);
	}
}

static bool LS_eatLine(LS self)
{
	bool ret = true;
	U32Vector uline = NULL;
	Str line = Str_new();
	if (Str_readLine(line, self->fs) == 0) {
		self->e = LS_EOS;
		ret = false;
		goto readdone;
	}

	if (self->utf8) {
		uline = codepoints(Str_data(line), Str_getLength(line));
		if (uline == NULL) {
			self->e = LS_BAD_SOURCE;
			ret = false;
			goto cvtdone;
		}
		U32Vector_append(self->us, uline);
		U32Vector_push(self->us, '\n');
	} else {
		Str_append(self->ss, line);
		Str_push(self->ss, '\n');
	}


cvtdone:
	U32Vector_free(uline);

readdone:
	Str_free(line);
	return ret;
}

static void LS_update(LS self)
{
	if (self->c < 0)
		return;

	if (!LS_checkPosition(self, self->index)) {
		self->c = self->e;
		return;
	}

	if (self->utf8) {
		self->c = U32Vector_get(self->us, self->index);
	} else {
		self->c = Str_get(self->ss, self->index);
	}

	if (self->c == '\n') {
		self->row += 1;
		self->column = 0;
	} else {
		self->column += 1;
	}
}

static inline LS LS_new(bool is_utf8, bool is_interact)
{
	LS self = malloc(sizeof(*self));
	self->utf8 = is_utf8;
	self->interact = is_interact;
	self->index = self->c = self->e = 0;
	self->row = 1;
	self->column = 0;
	return self;
}

static bool LS_checkPosition(LS self, size_t pos)
{
	size_t len = self->utf8 ?
		U32Vector_getLength(self->us) :
		Str_getLength(self->ss);

	if (self->interact) {
		while (pos >= len) {
			if (!LS_eatLine(self)) return false;
		}
		return true;
	}
	if (pos < len) {
		return true;
	}
	self->e = LS_BAD_POS;
	return false;
}

static U32Vector codepoints(const uint8_t *u, size_t len)
{
	U32Vector cps = U32Vector_new();
	for (size_t i = 0; i < len;) {
		uint32_t cp;
		size_t n = utf8_codepoint_s(u, len - i, &cp);
		if (n == 0) {
			U32Vector_free(cps);
			return NULL;
		}
		U32Vector_push(cps, cp);
		i += n;
	}
	return cps;
}

