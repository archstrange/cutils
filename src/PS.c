#include "PS.h"
#include "utf-8.h"
#include <string.h>

struct _sad_ps_ {
	int encoding;
	union {
		Str asciiSrc;
		U32Vector utf8Src;
		void *src;
	};
	size_t curIndex, srcLength;
	int curChar;
	size_t curLine, curColumn;
	int errorCode;
};

static inline Str readfile(FILE *fp);

static inline PS PS_new(void *src, int encoding);
static inline PS PS_newUTF8(Str src);
static inline int32_t PS_sourceGet(PS self, size_t index);

/// Convert utf-8 string to code points.
/// Return NULL if format is error.
static U32Vector to_codepoints(Str str);

static void PS_nextASCII(PS self);
static void PS_nextUTF8(PS self);
static void PS_updateCurrent(PS self);

PS PS_newFromStr(Str src, int encoding)
{
	switch (encoding) {
	case PS_SOURCE_ASCII:
		return PS_new(Str_clone(src), encoding);
	case PS_SOURCE_UTF8:
		return PS_newUTF8(src);
	default:
		return NULL;
	}
}

PS PS_newFromCStr(const char *src, int encoding)
{
	switch (encoding) {
	case PS_SOURCE_ASCII:
		return PS_new(Str_newFromArray(src, strlen(src)),
			      PS_SOURCE_ASCII);
	case PS_SOURCE_UTF8: {
		Str ustr = Str_newFromArray(src, strlen(src));
		PS self = PS_newUTF8(ustr);
		Str_free(ustr);
		return self;
	}
	default:
		return NULL;
	}
}

PS PS_newFromFILE(FILE *src, int encoding)
{
	switch (encoding) {
	case PS_SOURCE_ASCII:
		return PS_new(readfile(src), PS_SOURCE_ASCII);
	case PS_SOURCE_UTF8: {
		Str ustr = readfile(src);
		PS self = PS_newUTF8(ustr);
		Str_free(ustr);
		return self;
	}
	default:
		return NULL;
	}
}

void PS_free(PS self)
{
	if (self != NULL) {
		switch (self->encoding) {
		case PS_SOURCE_ASCII:
			Str_free(self->asciiSrc);
			break;
		case PS_SOURCE_UTF8:
			U32Vector_free(self->utf8Src);
			break;
		}
		free(self);
	}
}

size_t PS_curIndex(PS self)
{
	return self->curIndex;
}

int PS_curChar(PS self)
{
	return self->curChar;
}

size_t PS_curLine(PS self)
{
	return self->curLine;
}

size_t PS_curColumn(PS self)
{
	return self->curColumn;
}

void PS_next(PS self)
{
	if (self->curIndex < self->srcLength) {
		self->curIndex += 1;
	}
	PS_updateCurrent(self);
}

int PS_peek(PS self, int offset)
{
	size_t index;
	if (offset >= 0) {
		index = offset + self->curIndex;
		if (index < self->srcLength) {
			return PS_sourceGet(self, index);
		}
	} else if ((size_t)(-offset) <= self->curIndex){
		return PS_sourceGet(self, self->curIndex - (size_t)(-offset));
	}
	return PS_BAD_POS;
}

void PS_setErrorCode(PS self, int code)
{
	self->errorCode = code;
}

int PS_getErrorCode(PS self)
{
	return self->errorCode;
}

static inline PS PS_new(void *src, int encoding)
{
	PS self = malloc(sizeof(*self));
	self->encoding = encoding;
	self->src = src;
	switch (self->encoding) {
	case PS_SOURCE_ASCII:
		self->srcLength = Str_getLength(self->asciiSrc);
		break;
	case PS_SOURCE_UTF8:
		self->srcLength = U32Vector_getLength(self->utf8Src);
		break;
	}
	self->curIndex = 0;
	self->curLine = 1;
	self->curColumn = 0;
	self->errorCode = 0;
	PS_updateCurrent(self);
	return self;
}

static inline PS PS_newUTF8(Str src)
{
	U32Vector cps = to_codepoints(src);
	if (cps == NULL) {
		return NULL;
	}
	return PS_new(cps, PS_SOURCE_UTF8);
}

static void PS_updateCurrent(PS self)
{
	switch (self->encoding) {
	case PS_SOURCE_ASCII:
		if (self->curIndex >= self->srcLength) {
			self->curChar = PS_END;
			return;
		}
		self->curChar = Str_get(self->asciiSrc, self->curIndex);
		break;
	case PS_SOURCE_UTF8:
		if (self->curIndex >= self->srcLength) {
			self->curChar = PS_END;
			return;
		}
		self->curChar = U32Vector_get(self->utf8Src, self->curIndex);
		break;
	default:
		self->curChar = PS_BAD_SOURCE;
		return;
	}
	if (self->curChar == '\n') {
		self->curLine += 1;
		self->curColumn = 0;
	} else {
		self->curColumn += 1;
	}
}

static inline int32_t PS_sourceGet(PS self, size_t index)
{
	switch (self->encoding) {
	case PS_SOURCE_ASCII:
		return Str_get(self->asciiSrc, index);
	case PS_SOURCE_UTF8:
		return U32Vector_get(self->utf8Src, index);
	default:
		return PS_BAD_SOURCE;
	}
}

static inline Str readfile(FILE *fp)
{
	int c;
	Str str = Str_newWithCapacity(0);
	while ((c = getc(fp)) != EOF) {
		Str_push(str, c);
	}
	return str;
}

static U32Vector to_codepoints(Str str)
{
	size_t str_len = Str_getLength(str);
	const uint8_t *str_ptr = Str_data(str);
	U32Vector cps = U32Vector_newWithCapacity(str_len / 4);
	uint32_t cp;
	for (size_t i = 0, len; i < str_len; i += len) {
		len = utf8_codepoint(str_ptr + i, &cp);
		if (len == 0) {
			U32Vector_free(cps);
			return NULL;
		}
		U32Vector_push(cps, cp);
	}
}

