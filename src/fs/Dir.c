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

#include "Dir.h"
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

static inline int enttype2detype(int type);

struct _Dir_ {
	DIR *dp;
	Str path;
};

Dir Dir_open(Path dirpath)
{
	Dir self = malloc(sizeof(*self));
	self->path = Str_new();
	Path_getStr(dirpath, self->path);
	Str_push(self->path, 0);
	self->dp = opendir(Str_data(self->path));

	if (self->dp == NULL) {
		Dir_close(self);
		self = NULL;
	}

	return self;
}

void Dir_close(Dir self)
{
	Str_free(self->path);
	if (self->dp != NULL) closedir(self->dp);
	free(self);
}

void Dir_entries(Dir self, StrVector names, I32Vector types)
{
	StrVector_clear(names);
	I32Vector_clear(types);
	struct dirent *e = NULL;
	Str name = Str_new();
	rewinddir(self->dp);
	while ((e = readdir(self->dp)) != NULL) {
		Str_copyArray(name, e->d_name, strlen(e->d_name));
		StrVector_push(names, name);
		I32Vector_push(types, enttype2detype(e->d_type));
	}
	Str_free(name);
}

static inline int enttype2detype(int type)
{
	switch (type) {
	case DT_UNKNOWN:
		return DIRENTRY_TYPE_UNKNOWN;
	case DT_DIR:
		return DIRENTRY_TYPE_DIR;
	case DT_LNK:
		return DIRENTRY_TYPE_LINK;
	default:
		return DIRENTRY_TYPE_FILE;
	}
}

