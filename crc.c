#include "crc.h"

#define AD7768_CRC8_POLYNOMIAL_REPRESENTATION 0x07 /* x8 + x2 + x + 1 */

unsigned char AD7768_ComputeCRC8(unsigned long * pBuf, unsigned short bufSize)
{
	unsigned long i = 0;
	unsigned char crc = 0xFF;

	while (bufSize)
	{
		for (i = 0x800000; i != 0x000000; i >>= 1)
		{
			if (((crc & 0x80) != 0) != ((*pBuf & i) != 0)) /* MSB of CRC register XOR input Bit from Data */
			{
				crc <<= 1;
				crc ^= AD7768_CRC8_POLYNOMIAL_REPRESENTATION;
			}
			else
			{
				crc <<= 1;
			}
		}
		pBuf++;
		bufSize--;
	}
	return crc;
}
