/*
 * uart2/src/uart2_getc.c
 * one byte payload receiving
 * author 
 */

#include <uart2/include/uart2.h>

#define UART2_XON   0x11
#define UART2_XOFF  0x13

/* one byte buffer */
//uInt8_t	uart2_rx_buffer;
//uInt8_t uart2_rx_ready;

/* circular buffer */
circ_buffer_t uart2_rx;

void uart2_isr_process (void) 
{
    uInt8_t lost;
    
    if(PIR3bits.RC2IF) {
        /* one byte buffer */
//        uart2_rx_buffer = RC2REG;
//        uart2_rx_ready = TRUE;
        
        /* circular buffer */
        if ( uart2_rx.nb_elt < UART2_CIRC_BUFF_SIZE ) {
            uart2_rx.buffer[uart2_rx.idx_write] = RC2REG;
            uart2_rx.nb_elt++;
            uart2_rx.idx_write++;
            
            if ( uart2_rx.idx_write >= UART2_CIRC_BUFF_SIZE )
                uart2_rx.idx_write = 0;
            
            /* software flow control
             * Sending XOFF requires at least two characters time to transmit
             * current data transmit and XOFF
             *  */
            if ( uart2_rx.nb_elt == (UART2_CIRC_BUFF_SIZE - 4) ) {
                while(uart2_tx_busy());
                TX2REG = UART2_XOFF;
            }           
        } else {
            /* if receiver and/or transmitter flow control not implement  */
            lost = RC2REG;
        }  
    }   
}

uInt8_t uart2_getc(uInt8_t *payload, uInt8_t echo)
{
    uInt8_t     tmp;
     
    /* circular buffer */
    if (uart2_rx_ready()) {
        tmp = uart2_rx.buffer[uart2_rx.idx_read];
        uart2_rx.nb_elt--;
        uart2_rx.idx_read++;
        
        if (uart2_rx.idx_read >= UART2_CIRC_BUFF_SIZE)
            uart2_rx.idx_read = 0;

        /* software flow control 
         * enable data receiving after half buffer processing
         */
        if (uart2_rx.nb_elt == (UART2_CIRC_BUFF_SIZE >> 1)) {
            uart2_putc(UART2_XON);
        } 
        
        if (echo)
            uart2_putc(tmp); 
        
        *payload = tmp;
        return TRUE; 
    } else {      
        return FALSE;
    } 
}
