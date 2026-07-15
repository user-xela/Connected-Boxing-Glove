/* 
 * uart2/src/uart2_putc.c
 * one byte payload sending
 * author 
 */

#include <uart2/include/uart2.h>

void uart2_putc(uInt8_t payload)
{
	while(uart2_tx_busy());
  	TX2REG = payload;   
}
