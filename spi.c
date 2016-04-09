#include <stdint.h>
#include "stm32f042.h"
void initSPI()
{
    // Turn on the clock for the SPI interface
    RCC_APB2ENR |= BIT12;
    // Turn on PORT A
	RCC_AHBENR |= BIT17;
    // Configure the pins
    // SPI1 MOSI is on pin 13 (PA7) AF0.  This is labelled A6 on the Nucleo board
    GPIOA_MODER |= BIT15;
    GPIOA_MODER &= ~BIT14;
    GPIOA_AFRL &= ~(BIT31+BIT30+BIT29+BIT28);
    // Start with zero in the control registers.
    SPI1_CR1 = SPI1_CR2 = 0;
    SPI1_CR1 |= BIT0; // set CPHA to ensure MOSI is low when idle  
    SPI1_CR1 |= BIT2; // select master mode
    SPI1_CR1 |= (3 << 3); // select divider of 16.  48MHz/16 = 3MHz.  3 bits per WS2812 bit so: 1 Million WSbits/second : Within range of  1.53MHz to 540kHz    
    SPI1_CR1 |= BIT8+BIT9; // select software slave management and drive SSI high (not relevant in TI mode and not output to pins)
    SPI1_CR2 |= (7 << 8); // select 8 bit data transfer size   
    SPI1_CR1 |= BIT6; // enable SPI1
    
}
void writeSPI(uint8_t *Data,unsigned Count)
{   
    while(Count--)
    {
        SPI1_DR = (uint8_t)(*Data);        
        Data++;        
        while ( (SPI1_SR & (BIT12+BIT11))==(BIT12+BIT11)); // wait if FIFO full or greater        
    }    
}
