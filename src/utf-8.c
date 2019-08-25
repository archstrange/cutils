#include "utf-8.h"

/// UTF8-octets = *( UTF8-char )
/// UTF8-char   = UTF8-1 / UTF8-2 / UTF8-3 / UTF8-4
///
/// UTF8-1      = %x00-7F
///
/// UTF8-2      = %xC2-DF UTF8-tail
///
/// UTF8-3      = %xE0 %xA0-BF UTF8-tail /
///               %xE1-EC 2( UTF8-tail ) /
///               %xED %x80-9F UTF8-tail /
///               %xEE-EF 2( UTF8-tail )
///
/// UTF8-4      = %xF0 %x90-BF 2( UTF8-tail ) /
///               %xF1-F3 3( UTF8-tail ) /
///               %xF4 %x80-8F 2( UTF8-tail )
///
/// UTF8-tail   = %x80-BF

#define IN_RANGE(c, min, max) ((c) >= (min) && (c) <= (max))
#define IS_TAIL(c) IN_RANGE(c, 0x80, 0xBF)

const static uint8_t OCT_HEAD[256] = {
	// 00-7F: 0YYY YYYY, 7F
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	// 80-C1: invalid
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0,
	// C2-DF: 110Y YYYx, 1F
	      2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	// E0
	31,
	// E1-EC
	   32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
	// ED
	   33,
	// EE-EF
	   32, 32,
	// F0
	41,
	// F1-F3
	   42, 42, 42,
	// F4
	               43,
};

int utf8_validate(const uint8_t *u)
{
	switch (OCT_HEAD[u[0]]) {
	case 1:
		return 1;
	case 2:
		if (IS_TAIL(u[1]))
			return 2;
		break;
	case 31:
		if (IN_RANGE(u[1], 0xA0, 0xBF) && IS_TAIL(u[2]))
			return 3;
		break;
	case 32:
		if (IS_TAIL(u[1]) && IS_TAIL(u[2]))
			return 3;
		break;
	case 33:
		if (IN_RANGE(u[1], 0x80, 0x9F) && IS_TAIL(u[2]))
			return 3;
		break;
	case 41:
		if (IN_RANGE(u[1], 0x90, 0xBF) && IS_TAIL(u[2]) && IS_TAIL(u[3]))
			return 4;
		break;
	case 42:
		if (IS_TAIL(u[1]) && IS_TAIL(u[2]) && IS_TAIL(u[3]))
			return 4;
		break;
	case 43:
		if (IN_RANGE(u[1], 0x80, 0x8F) && IS_TAIL(u[2]) && IS_TAIL(u[3]))
			return 4;
		break;
	default:
		break;
	}
	return 0;
}

int utf8_codepoint(const uint8_t *u, uint32_t *cp)
{
	switch (OCT_HEAD[u[0]]) {
	case 1:
		goto OCT1;
	case 2:
		if (IS_TAIL(u[1]))
			goto OCT2;
		break;
	case 31:
		if (IN_RANGE(u[1], 0xA0, 0xBF) && IS_TAIL(u[2]))
			goto OCT3;
		break;
	case 32:
		if (IS_TAIL(u[1]) && IS_TAIL(u[2]))
			goto OCT3;
		break;
	case 33:
		if (IN_RANGE(u[1], 0x80, 0x9F) && IS_TAIL(u[2]))
			goto OCT3;
		break;
	case 41:
		if (IN_RANGE(u[1], 0x90, 0xBF) && IS_TAIL(u[2]) && IS_TAIL(u[3]))
			goto OCT4;
		break;
	case 42:
		if (IS_TAIL(u[1]) && IS_TAIL(u[2]) && IS_TAIL(u[3]))
			goto OCT4;
		break;
	case 43:
		if (IN_RANGE(u[1], 0x80, 0x8F) && IS_TAIL(u[2]) && IS_TAIL(u[3]))
			goto OCT4;
		break;
	default:
		break;
	}
OCT0:
	return 0;
OCT1:
	*cp = u[0];
	return 1;
OCT2:
	*cp = (u[0] & 0x1F) << 6;
	*cp += u[1] & 0x3F;
	return 2;
OCT3:
	*cp = (u[0] & 0x0F) << 12;
	*cp += (u[1] & 0x3F) << 6;
	*cp += u[2] & 0x3F;
	return 3;
OCT4:
	*cp = (u[0] & 0x07) << 18;
	*cp = (u[1] & 0x3F) << 12;
	*cp += (u[2] & 0x3F) << 6;
	*cp += u[3] & 0x3F;
	return 4;
}

int utf8_char(uint32_t cp, uint8_t u[5])
{
	if (!(cp >> 7u)) {
		u[1] = 0;
		u[0] = cp;
		return 1;
	} else if (!(cp >> 11u)) {
		u[2] = 0;
		u[1] = 0x80u | (0x3Fu & cp);
		u[0] = 0xC0u | (cp >> 6u);
		return 2;
	} else if (!(cp >> 16)) {
		u[3] = 0;
		u[2] = 0x80u | (0x3Fu & cp);
		u[1] = 0x80u | (0x3Fu & (cp >> 6));
		u[0] = 0xE0u | (cp >> 12);
		return 3;
	} else if (!(cp >> 21u)) {
		u[4] = 0;
		u[3] = 0x80u | (0x3Fu & cp);
		u[2] = 0x80u | (0x3Fu & (cp >> 6));
		u[1] = 0x80u | (0x3Fu & (cp >> 12));
		u[0] = 0xF0u | (cp >> 18);
		return 4;
	}
	return 0;
}

bool utf8_cp_validate(uint32_t cp)
{
	return !(cp >> 21u);
}

