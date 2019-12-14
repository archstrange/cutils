#ifndef CUTILS_CODEC_BASE64_H
#define CUTILS_CODEC_BASE64_H
#include "../Str.h"
#include <stdint.h>

/// Base64 encoder.
///
/// Input: @in, sequence of bytes
/// Output: @out, receive encoded bytes that are all base64 chars.
///
/// Default base64 chars(0..63):
///     A..Za..z0..9+/
///
/// The last two chars diff from different base64 implements, which
/// you can pass @replace to tell @base64_enc.
///
/// @replace may be NULL or empty, and default base64 chars will be used,
/// otherwise it must be the following contents:
///   1. replace the last two chars and use <pad-char> for padding:
///	"<62nd-char><63rd-char><pad-char>"
///   2. replace the last two chars and no padding:
///	"<62nd-char><63rd-char>"
///   3. replace the 62nd char:
///	"<62nd-char>"
///
/// Return: 0 for success, non-zero for failure:
///     1: NULL pointer, @in and/or @out is/are NULL.
///     2: bad @replace.
int base64_enc(Str in, Str out, const char *replace);

/// Decoder of @base64_enc.
///
/// Return: 0 for success, non-zero for failure:
///     1: NULL pointer, @in and/or @out is/are NULL.
///     2: bad @replace.
///     -1: bad content of @in, and @out may not be cleaned.
int base64_dec(Str in, Str out, const char *replace);

#endif

