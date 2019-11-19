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

