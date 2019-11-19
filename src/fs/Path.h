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

#ifndef CUTILS_FS_PATH_H
#define CUTILS_FS_PATH_H
#include <stdbool.h>
#include "../Str.h"

typedef struct Path *Path;

enum {
	PATH_FILE_TYPE_UNKNOWN = 0,
	PATH_FILE_TYPE_FILE,
	PATH_FILE_TYPE_DIR,
	PATH_FILE_TYPE_SYM_LINK,
};

/// Create a new Path object from Str @source.
///
/// If @source is NULL or empty, a current working path
/// will be returned(same as `Path_newCurrentWorkPath`.
Path Path_new(Str source);

/// Create a new Path object with current process work directory.
Path Path_newCurrentWorkPath();

Path Path_clone(Path src);

/// Copy the content of @src to @self.
void Path_copy(Path self, Path src);

void Path_free(Path self);

/// Check if @self is absolute path.
bool Path_isAbs(Path self);

/// Convert @self to absolute path if @self is relative path,
/// and take @current as current working directory.
///
/// @current may be NULL or relative. If it's that so,
/// the real current working directory will be used:
/// `<cwd>/current/self`
///
/// If @self is absolute path already, nothing will be done.
void Path_convertToAbs(Path self, Path current);

/// Like shell `cd` command.
void Path_cd(Path self, Path p);

/// Append @filename to @self, @filename must be a single
/// file name(contains no '/' chars).
void Path_append(Path self, Str filename);

/// Try to remove '.' and '..' nodes from @self.
void Path_refine(Path self);

/// Get the string path of @self, so you can use @str
/// to open a DIR of FILE.
void Path_getStr(Path self, Str str);

#endif

