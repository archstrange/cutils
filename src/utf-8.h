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

#ifndef CUTILS_UTF_8_H
#define CUTILS_UTF_8_H
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

/// Validate UTF-8 char, return number of bytes of first char
/// pointed by @u, 0 for invalid char.
int utf8_validate(const uint8_t *u);

int utf8_validate_s(const uint8_t *u, size_t len);

/// Get code point of UTF-8 char pointed by @utf8.
/// Return UTF-8 char byte-length, 0 for invalid encoding.
int utf8_codepoint(const uint8_t *u, uint32_t *cp);

int utf8_codepoint_s(const uint8_t *u, size_t len, uint32_t *cp);

/// Validate UTF-8 code point.
bool utf8_cp_validate(uint32_t cp);

/// Get UTF-8 char from code point @cp.
/// Return number of bytes encoded, 0 for invalid code point.
int utf8_char(uint32_t cp, uint8_t u[5]);

#endif

