#ifndef CUTILS_UTF_8_H
#define CUTILS_UTF_8_H
#include <stdint.h>
#include <stdbool.h>

/// Validate UTF-8 char, return number of bytes of first char
/// pointed by @u, 0 for invalid char.
int utf8_validate(const uint8_t *u);

/// Get code point of UTF-8 char pointed by @utf8.
/// Return UTF-8 char byte-length, 0 for invalid encoding.
int utf8_codepoint(const uint8_t *utf8, uint32_t *cp);

/// Validate UTF-8 code point.
bool utf8_cp_validate(uint32_t cp);

/// Get UTF-8 char from code point @cp.
/// Return number of bytes encoded, 0 for invalid code point.
int utf8_char(uint32_t cp, uint8_t u[5]);

#endif

