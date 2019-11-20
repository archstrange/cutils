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

#include "log.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Str.h"
#include "fs/Path.h"
#include "fs/Dir.h"

static bool makedir(Path path);

struct Logger {
	Str appname;
	Path path;
	FILE *file;
};

Logger Logger_new(const char *appname, const char *storage_path)
{
	if (appname == NULL || *appname == 0)
		return NULL;

	Logger self = calloc(1, sizeof(*self));
	self->appname = Str_newFromArray(appname, CStr_len(appname));
	if (storage_path == NULL || *storage_path == 0) { // use ~/.log/
		self->path = Path_newFromCStr(getenv("HOME"));
		Path_appendCStrName(self->path, ".log");
	} else { // use storage_path/
		self->path = Path_newFromCStr(storage_path);
	}

	if (makedir(self->path)) {
		Path_append(self->path, self->appname);
	} else {
		goto onError;
	}

	return self;
onError:
	Logger_free(self);
	return NULL;
}

void Logger_free(Logger self)
{
	if (self) {
		Str_free(self->appname);
		Path_free(self->path);
		fclose(self->file);
		free(self);
	}
}

static bool makedir(Path path)
{
	bool ret = true;
	Str ps = Str_new();
	Path_getStr(path, ps);
	CStr_localFromStr(dir, ps);
	if (mkdir(dir, S_IRWXU)) {
		if (errno != EEXIST) {
			ret = false;
		}
	}

	Str_free(ps);
	return ret;
}

