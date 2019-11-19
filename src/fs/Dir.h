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

