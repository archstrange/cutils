#ifndef CUTILS_ENDIAN_H
#define CUTILS_ENDIAN_H

/// Bytes endian swapper
///
/// functions:
///	void endian_ltoh(void *block, int size);
///	void endian_btoh(void *block, int size);
///	void endian_htol(void *block, int size);
///	void endian_htob(void *block, int size);
///
/// each one swap bytes between little(l) or big(b) endianess
/// with host(h) endianess

static inline void __endian_byteswap__(void *block, int size)
{
	unsigned char *bytes = block;
	int mid = size / 2;
	size -= 1;
	for (int i = 0; i < mid; i++) {
		unsigned char tmp = bytes[i];
		int j = size - i;
		bytes[i] = bytes[j];
		bytes[j] = tmp;
	}
}

static inline void __endian_nop__(void *block, int size) {}

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__

#define endian_ltoh __endian_nop__
#define endian_btoh __endian_byteswap__
#define endian_htol __endian_nop__
#define endian_htob __endian_byteswap__

#else

#define endian_ltoh __endian_byteswap__
#define endian_btoh __endian_nop__
#define endian_htol __endian_byteswap__
#define endian_htob __endian_nop__

#endif

#endif
