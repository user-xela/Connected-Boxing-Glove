/* 
 * uart2/src/uart2_puts.c
 * send caracters string
 * author 
 */

#include <uart2/include/uart2.h>

void uart2_puts(const uInt8_t *str)
{
    while (*str != '\0')
        uart2_putc(*str++);
}