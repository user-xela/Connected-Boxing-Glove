/* 
 * uart1/src/uart1_puts.c
 * send caracters string
 * author 
 */

#include <uart1/include/uart1.h>

void uart1_puts(const uInt8_t *str)
{
    while (*str != '\0')
        uart1_putc(*str++);
}
