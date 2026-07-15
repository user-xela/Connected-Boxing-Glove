/* 
 * uart1/src/uart1_putc.c
 * one byte payload sending
 * author 
 */

#include <uart1/include/uart1.h>

void uart1_putc(uInt8_t payload)
{
	while(!TXSTA1bits.TRMT);
  	TX1REG = payload;   
}
