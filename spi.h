// spi.h
// Low level spi functions for the STM32F042 Nucleo board.
// Note: There are two SPI channels SPI1 and SPI2
// This particular module is intended for use with the WS2812B smart LED's and 
// so does NOT represent standard SPI


// WS2812B: notes:
// To output a logic '0' a high pulse of 0.4us followed by a low pulse of 0.85us is required
// To output a logic '1' a high pulse of 0.85us followed by a low pulse of 0.4us is required
// All timings are +/- 150ns
// A reset pulse (low for > 50us) is required after each 24 bit transmission.
// Will attempt to output pulses using the SPI interface.  To achieve the desired mark/space
// ratio, the SPI will be operated faster than the WS2812B so that several (3) SPI pulses 
// amount to 1 WS2812B logic interval.  Output bits will be formatted as follows:
// 
// WS2812B '0' : SPI 100
// WS2812B '1' : SPI 110
// This implies that 1 SPI bit should last approx 0.4uS (+/- 150ns)
// SPI clock is based on PCLK/2 so, at 48MHz this gives a base clock speed of 24MHz
// Applying a divisor of 8 gives 3MHz or a period of 0.333us which is within the 
// tolerance of the WS2812B.  
#include <stdint.h>
void initSPI();
void writeSPI(uint8_t *Data,unsigned Count);
