/*
 * uart1/src/uart1_getc.c
 * one byte payload receiving
 * author 
 */

#include <uart1/include/uart1.h>

#define UART1_XON   0x11
#define UART1_XOFF  0x13

/* one byte buffer */
//uInt8_t	uart1_rx_buffer;
//uInt8_t uart1_rx_ready;

/* circular buffer */
circ_buffer_t uart1_rx;

void uart1_isr_process (void)
{
    uInt8_t lost;
    
    if(PIR3bits.RC1IF) {
        /* one byte buffer */
//        uart1_rx_buffer = RC1REG;
//        uart1_rx_ready = TRUE;        
        
        /* circular buffer */
        if ( uart1_rx.nb_elt < UART1_CIRC_BUFF_SIZE ) {
            uart1_rx.buffer[uart1_rx.idx_write] = RC1REG;
            uart1_rx.nb_elt++;
            uart1_rx.idx_write++;
            
            if ( uart1_rx.idx_write >= UART1_CIRC_BUFF_SIZE )
                uart1_rx.idx_write = 0;        

            /* software flow control
             * Sending XOFF requires at least two characters time to transmit
             * current data transmit and XOFF
             *  */
            if ( uart1_rx.nb_elt == (UART1_CIRC_BUFF_SIZE - 4) ) {
                while(uart1_tx_busy());
                TX1REG = UART1_XOFF;
            }           
        } else {
            /* if receiver and/or transmitter flow control not implement  */
            lost = RC1REG;
        }  
    }
}

uInt8_t uart1_getc(uInt8_t *payload, uInt8_t echo)
{
    uInt8_t     tmp;
    
    /* circular buffer */
    if (uart1_rx_ready()) {
        tmp = uart1_rx.buffer[uart1_rx.idx_read];
        uart1_rx.nb_elt--;
        uart1_rx.idx_read++;    

        if ( uart1_rx.idx_read >= UART1_CIRC_BUFF_SIZE )
            uart1_rx.idx_read = 0;  
        
        /* software flow control 
         * enable data receiving after half buffer processing
         */
        if (uart1_rx.nb_elt == (UART1_CIRC_BUFF_SIZE >> 1)) {
            uart1_putc(UART1_XON);
        } 
            
        if (echo)
            uart1_putc(tmp); 
        
        *payload = tmp;
        return TRUE; 
    } else {      
        return FALSE;
    }
}
