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

#ifndef CUTILS_FS_DIR_H
#define CUTILS_FS_DIR_H
#include <stdbool.h>
#include "../Vector/I32Vector.h"
#include "../Vector/StrVector.h"
#include "Path.h"

enum {
	DIRENTRY_TYPE_UNKNOWN = 0,
	DIRENTRY_TYPE_FILE,
	DIRENTRY_TYPE_DIR,
	DIRENTRY_TYPE_LINK,
};

typedef struct _Dir_ *Dir;

/// Open @dirpath, return the opened Dir object.
Dir Dir_open(Path dirpath);

/// Open current working dir.
static inline Dir Dir_openCurrent()
{
	Path c = Path_newCurrentWorkPath();
	Dir dir = Dir_open(c);
	Path_free(c);
	return dir;
}

/// Close @self and free all memory.
void Dir_close(Dir self);

/// Get all entries of @self.
///
/// @names is StrVector to hold all file names, @types is I32Vector
/// to hold all file types. One of them can be NULL if you don't
/// care about them.
void Dir_entries(Dir self, StrVector names, I32Vector types);

#endif

