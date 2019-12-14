#include "base64.h"
#include <string.h>
#include <stdbool.h>

// 3-byte group --> 4 base64 chars
// ---------------|---------------|---------------
// 1 2 3 4 5 6 7 8|1 2 3 4 5 6 7 8|1 2 3 4 5 6 7 8
//            |           |           |
// -----------|-----------|-----------|-----------
// 1 2 3 4 5 6|1 2 3 4 5 6|1 2 3 4 5 6|1 2 3 4 5 6
static const uint8_t base64[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				  "abcdefghijklmnopqrstuvwxyz"
				  "0123456789+/=";

int base64_enc(Str in, Str out, const char *replace)
{
	if (in == NULL || out == NULL)
		return 1;

	uint8_t table[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			    "abcdefghijklmnopqrstuvwxyz"
			    "0123456789+/=";
	bool padding = false;
	switch (CStr_len(replace)) {
	case 3:
		padding = true;
		table[64] = replace[2];
	case 2:
		table[63] = replace[1];
	case 1:
		table[62] = replace[0];
	case 0:
		break;
	default:
		return 2; // bad replace!
	}

	Str_clear(out);
	size_t inlen = Str_getLength(in);
	const uint8_t *buf = Str_data(in);
	for (size_t i = 0, n = inlen / 3; i < n; i += 1, buf += 3) {
		Str_push(out, table[buf[0] >> 2]);
		Str_push(out, table[((buf[0] & 3) << 4) | (buf[1] >> 4)]);
		Str_push(out, table[((buf[1] & 15) << 2) | (buf[2] >> 6)]);
		Str_push(out, table[buf[2] & 0x3f]);
	}
	switch (inlen % 3) {
	case 1:
		Str_push(out, table[buf[0] >> 2]);
		Str_push(out, table[(buf[0] & 3) << 4]);
		if (padding) {
			Str_push(out, table[64]);
			Str_push(out, table[64]);
		}
		break;
	case 2:
		Str_push(out, table[buf[0] >> 2]);
		Str_push(out, table[((buf[0] & 3) << 4) | (buf[1] >> 4)]);
		Str_push(out, table[(buf[1] & 15) << 2]);
		if (padding) {
			Str_push(out, table[64]);
		}
		break;
	default:
		break;
	}
	return 0;
}

int base64_dec(Str in, Str out, const char *replace)
{
	if (in == NULL || out == NULL)
		return 1;

	int8_t table[128] = {
		// 16 bytes per row.
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
		52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1,
		-1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
		15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,
		-1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
		41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1,
	}; // -1 means invalid code.
	bool padding = false;
	uint8_t pad;
	switch (CStr_len(replace)) {
	case 3:
		padding = true;
		pad = replace[2];
	case 2:
		table['/'] = -1;
		table[replace[1]] = 63;
	case 1:
		table['+'] = -1;
		table[replace[0]] = 62;
	case 0:
		break;
	default:
		return 2; // bad replace!
	}
	
	Str_clear(out);
	size_t inlen = Str_getLength(in);
	const uint8_t *buf = Str_data(in);
	if (padding) { // two pad chars at most.
		if (inlen != 0 && buf[inlen - 1] == pad)
			inlen -= 1;
		if (inlen != 0 && buf[inlen - 1] == pad)
			inlen -= 1;
	}
	uint8_t g1, g2, g3, g4;
	for (size_t i = 0, n = inlen / 4; i < n; i += 1, buf += 4) {
		g1 = table[buf[0]];
		g2 = table[buf[1]];
		g3 = table[buf[2]];
		g4 = table[buf[3]];
		if (g1 == -1 || g2 == -1 || g3 == -1 || g4 == -1)
			return -1; // invalid input buffer.
		Str_push(out, (g1 << 2) | (g2 >> 4));
		Str_push(out, ((g2 & 0xf) << 4) | (g3 >> 2));
		Str_push(out, (g3 << 6) | g4);
	}
	switch (inlen % 4) { // 2 or 3 valid.
	case 2:
		g1 = table[buf[0]];
		g2 = table[buf[1]];
		if (g1 == -1 || g2 == -1)
			return -1; // invalid input buffer.
		Str_push(out, (g1 << 2) | (g2 >> 4));
		break;
	case 3:
		g1 = table[buf[0]];
		g2 = table[buf[1]];
		g3 = table[buf[2]];
		if (g1 == -1 || g2 == -1 || g3 == -1)
			return -1; // invalid input buffer.
		Str_push(out, (g1 << 2) | (g2 >> 4));
		Str_push(out, ((g2 & 0xf) << 4) | (g3 >> 2));
		break;
	default:
		return -1;
	}
	return 0;
}

