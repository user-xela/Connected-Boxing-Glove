/*
 * uart1/src/uart1_gets.c
 * caracters string receiving
 * author 
 */

#include <uart1/include/uart1.h>

uInt8_t uart1_gets(uInt8_t *str_buf, uInt8_t buf_limit, uInt8_t echo)
{
    static uInt8_t i = 0;
    uInt8_t tmp;

    do {
        if (!uart1_getc(&tmp, echo))
            goto fail_nopayload; 
        
        if (i >= buf_limit) {
            str_buf[i-1] = '\0';
            i = 0;
            goto fail_limitbuffer;
        } 
        
        str_buf[i++] = tmp;                               
    } while (tmp != '\r');
    
    str_buf[--i] = '\0';
    i = 0;
    return TRUE;
fail_nopayload:    
fail_limitbuffer:
    return FALSE;    
}
