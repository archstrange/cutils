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

#include "Path.h"
#include "../Vector/StrVector.h"
#include <unistd.h>
#include <string.h>

struct Path {
	bool is_abs;
	StrVector nodes;
};

static StrVector construct_nodes(const char *path, size_t len);

Path Path_new(Str source)
{
	size_t len = Str_getLength(source);
	if (source == NULL || len == 0) {
		return Path_newCurrentWorkPath();
	}

	Path self = malloc(sizeof(*self));
	self->is_abs = Str_get(source, 0) == '/';
	self->nodes = construct_nodes(Str_data(source), len);
	return self;
}

Path Path_newFromCStr(const char *source)
{
	Str s = Str_newFromArray(source, strlen(source));
	Path p = Path_new(s);
	Str_free(s);
	return p;
}

Path Path_newCurrentWorkPath()
{
	char *cwd = getcwd(NULL, 0);
	size_t len = strlen(cwd);

	Path self = malloc(sizeof(*self));
	self->is_abs = cwd[0] == '/';
	self->nodes = construct_nodes(cwd, len);
	free(cwd);
	return self;
}

Path Path_clone(Path src)
{
	Path self = malloc(sizeof(*self));
	self->is_abs = src->is_abs;
	self->nodes = StrVector_clone(src->nodes);
	return self;
}

void Path_copy(Path self, Path src)
{
	if (self == src)
		return;
	StrVector_copy(self->nodes, src->nodes);
	self->is_abs = src->is_abs;
}

void Path_free(Path self)
{
	if (self != NULL) {
		StrVector_free(self->nodes);
		free(self);
	}
}

bool Path_isAbs(Path self)
{
	return self->is_abs;
}

void Path_convertToAbs(Path self, Path current)
{
	if (self->is_abs)
		return;
	Path new = NULL;
	if (current == NULL) {
		new = Path_newCurrentWorkPath();
	} else if (current->is_abs) {
		new = Path_clone(current);
	} else {
		new = Path_newCurrentWorkPath();
		Path_cd(new, current);
	}
	Path_cd(new, self);
	StrVector_free(self->nodes);
	*self = *new;
	free(new);
}

void Path_cd(Path self, Path p)
{
	if (p->is_abs) {
		Path_copy(self, p);
	} else {
		StrVector_append(self->nodes, p->nodes);
	}
}

void Path_append(Path self, Str filename)
{
	StrVector_push(self->nodes, filename);
}

void Path_refine(Path self)
{
#define IS_DOT(str) (Str_getLength(str) == 1 && Str_get(str, 0) == '.')
#define IS_DOTDOT(str) (Str_getLength(str) == 2 \
		&& Str_get(str, 0) == '.' \
		&& Str_get(str, 1) == '.')

	if (!self->is_abs)
		return;

	Str *nodes = StrVector_data(self->nodes);
	size_t len = StrVector_getLength(self->nodes);
	if (len == 0)
		return;

	StrVector newnodes = StrVector_newWithCapacity(0);
	for (size_t i = 0; i < len; i++) {
		if (IS_DOTDOT(nodes[i])) {
			size_t nlen = StrVector_getLength(newnodes);
			if (nlen != 0) {
				StrVector_setLength(newnodes, nlen - 1);
			}
		} else if (!IS_DOT(nodes[i])){
			StrVector_push(newnodes, nodes[i]);
		}
	}
	StrVector_free(self->nodes);
	self->nodes = newnodes;
}

void Path_getStr(Path self, Str str)
{
	Str_clear(str);
	size_t len = StrVector_getLength(self->nodes);
	Str *data = StrVector_data(self->nodes);

	if (!self->is_abs)
		Str_push(str, '.');
	else if (len == 0)
		Str_push(str, '/');

	for (size_t i = 0; i < len; i++) {
		Str_push(str, '/');
		Str_append(str, data[i]);
	}
}

static StrVector construct_nodes(const char *path, size_t len)
{
	StrVector nodes = StrVector_newWithCapacity(0);
	for (size_t i = 0; i < len; i++) {
		if (path[i] == '/') {
			continue;
		}
		size_t j = i + 1;
		while (j < len && path[j] != '/') {
			j += 1;
		}
		StrVector_push(nodes, Str_newFromArray(&path[i], j - i));
		i = j;
	}
	return nodes;
}

