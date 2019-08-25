#ifndef SAD_PS_H
#define SAD_PS_H
#include <stdint.h>
#include <stdio.h>
#include "Vector/Str.h"
#include "Vector/U32Vector.h"

/// Parser Source Object
/// PS has its own source string, so if you new a PS from string,
/// you can do whatever to that string which won't effect PS at all.
///
/// Example:
///
///	PS ps = PS_newFromCStr("parser source string", PS_SOURCE_ASCII);
///	for (int c; (c = PS_curChar(ps)) > 0; PS_next(ps)) {
///		printf("line %lu column %lu is %c\n",
///		       PS_curLine(ps),
///		       PS_curColumn(ps),
///		       c);
///	}
///	PS_free(ps);
///
/// If current char is new-line, curLine will be increased and curColumn
/// will be 0.
typedef struct _sad_ps_ *PS;

/// Special current chars
enum {
	PS_BAD_SOURCE = -3, /// wrong encoding
	PS_BAD_POS = -2,
	PS_END = -1, /// end of PS
};

/// PS encoding
enum {
	PS_SOURCE_ASCII = 0,
	PS_SOURCE_UTF8,
};

PS PS_newFromStr(Str src, int encoding);

PS PS_newFromCStr(const char *src, int encoding);

PS PS_newFromFILE(FILE *src, int encoding);

void PS_free(PS self);

/// Get current char index
size_t PS_curIndex(PS self);

/// Get current char
int PS_curChar(PS self);

/// Get current char's logic position -- line.
size_t PS_curLine(PS self);

/// Get current char's logic position -- column.
size_t PS_curColumn(PS self);

/// Goto next char
void PS_next(PS self);

/// Peek char at curIndex + offset.
/// PS_BAD_POS maybe returned.
int PS_peek(PS self, int offset);

/// Set user defined error code.
/// PS will init it with zero.
void PS_setErrorCode(PS self, int code);

/// Get user defined error code.
int PS_getErrorCode(PS self);

#endif

