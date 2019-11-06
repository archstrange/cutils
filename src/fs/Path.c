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
#include "../Vector/PtrVector.h"
#include <unistd.h>
#include <string.h>

struct Path {
	bool is_abs;
	PtrVector nodes;
};

static PtrVector construct_nodes(const char *path, size_t len);
static PtrVector clone_nodes(PtrVector nodes);
static inline void free_nodes(PtrVector nodes);

Path Path_new(Str source)
{
	size_t len = Str_getLength(source);
	if (source == NULL || len == 0) {
		return NULL;
	}

	Path self = malloc(sizeof(*self));
	self->is_abs = Str_get(source, 0) == '/';
	self->nodes = construct_nodes(Str_data(source), len);
	return self;
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
	self->nodes = clone_nodes(src->nodes);
	return self;
}

void Path_copy(Path self, Path src)
{
	free_nodes(self->nodes);
	self->nodes = clone_nodes(src->nodes);
	self->is_abs = src->is_abs;
}

void Path_mvmem(Path self, Path tmp)
{
	free_nodes(self->nodes);
	*self = *tmp;
	free(tmp);
}

void Path_free(Path self)
{
	if (self != NULL) {
		free_nodes(self->nodes);
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
	Path_mvmem(self, new);
}

void Path_cd(Path self, Path p)
{
	if (p->is_abs) {
		self->is_abs = true;
		free_nodes(self->nodes);
		self->nodes = clone_nodes(p->nodes);
	} else {
		PtrVector_append(self->nodes, p->nodes);
	}
}

void Path_refine(Path self)
{
#define IS_DOT(str) (Str_getLength(str) == 1 && Str_get(str, 0) == '.')
#define IS_DOTDOT(str) (Str_getLength(str) == 2 \
		&& Str_get(str, 0) == '.' \
		&& Str_get(str, 1) == '.')

	if (!self->is_abs)
		return;

	void **nodes = PtrVector_data(self->nodes);
	size_t len = PtrVector_getLength(self->nodes);
	if (len == 0)
		return;

	PtrVector newnodes = PtrVector_newWithCapacity(0);
	for (size_t i = 0; i < len; i++) {
		if (IS_DOT(nodes[i])) {
			Str_free(nodes[i]);
		} else if (IS_DOTDOT(nodes[i])) {
			Str_free(nodes[i]);
			if (PtrVector_getLength(newnodes) != 0) {
				Str_free(PtrVector_pop(newnodes));
			}
		} else {
			PtrVector_push(newnodes, nodes[i]);
		}
	}
	PtrVector_free(self->nodes);
	self->nodes = newnodes;
}

void Path_getStr(Path self, Str str)
{
	Str_clear(str);
	if (self->is_abs)
		Str_push(str, '/');

	size_t len = PtrVector_getLength(self->nodes);
	void **data = PtrVector_data(self->nodes);
	for (size_t i = 0; i < len; i++) {
		Str_append(str, data[i]);
		Str_push(str, '/');
	}
	Str_pop(str);
}

static PtrVector construct_nodes(const char *path, size_t len)
{
	PtrVector nodes = PtrVector_newWithCapacity(0);
	for (size_t i = 0; i < len; i++) {
		if (path[i] == '/') {
			continue;
		}
		size_t j = i + 1;
		while (j < len && path[j] != '/') {
			j += 1;
		}
		PtrVector_push(nodes, Str_newFromArray(&path[i], j - i));
		i = j;
	}
	return nodes;
}

static PtrVector clone_nodes(PtrVector nodes)
{
	size_t len = PtrVector_getLength(nodes);
	PtrVector new = PtrVector_newWithCapacity(len);
	void **data = PtrVector_data(nodes);
	void **new_data = PtrVector_data(new);
	for (size_t i = 0; i < len; i++) {
		new_data[i] = Str_clone(data[i]);
	}
	return new;
}

static inline void free_nodes(PtrVector nodes)
{
	if (nodes == NULL)
		return;
	size_t len = PtrVector_getLength(nodes);
	void **data = PtrVector_data(nodes);
	for (size_t i = 0; i < len; i++) {
		Str_free(data[i]);
	}
	PtrVector_free(nodes);
}

