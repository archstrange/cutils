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

#ifndef CUTILS_ENDIAN_H
#define CUTILS_ENDIAN_H
#include <stdint.h>

/// Byte-order swapper
///	endian_swap(void *block, size_t size);
///
/// Endianness convert:
///	void endian_ltoh(void *block, size_t size);
///	void endian_btoh(void *block, size_t size);
///	void endian_htol(void *block, size_t size);
///	void endian_htob(void *block, size_t size);
///
/// Host endianness check:
///	bool endian_host_islittle();
///	bool endian_host_isbig();
///
/// each one swap bytes between little(l) or big(b) endianess
/// with host(h) endianess

/// Swap bytes pointed by @block.
static inline void endian_swap(void *block, size_t size)
{
	unsigned char *bytes = block;
	size_t mid = size / 2;
	size -= 1;
	for (size_t i = 0; i < mid; i++) {
		unsigned char tmp = bytes[i];
		size_t j = size - i;
		bytes[i] = bytes[j];
		bytes[j] = tmp;
	}
}

static inline void __endian_nop__(void *block, size_t size) {}

#ifdef __BYTE_ORDER__
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__

#define endian_host_islittle() (!0)
#define endian_host_isbig() (!1)
#define endian_ltoh __endian_nop__
#define endian_btoh endian_swap
#define endian_htol __endian_nop__
#define endian_htob endian_swap

#else

#define endian_host_islittle() (!1)
#define endian_host_isbig() (!0)
#define endian_ltoh endian_swap
#define endian_btoh __endian_nop__
#define endian_htol endian_swap
#define endian_htob __endian_nop__

#endif
#endif

#endif
