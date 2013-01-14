/* Functions to RX/TX over USART
 *
 * init_USART()         --> initialize USART (SET CORRECT FREQUENCY!)
 * uart_sendchar()      --> Send a single char
 * uart_sendstring()    --> Send a string (needs uart_sendchar())
 * uart_getchar()       --> Receives a char
 * uart_getstring()     --> Receives a string (needs uart_getchar())
 *
 */

void init_USART(void) {
        UCSRB |= (1<<TXEN) | (1<<RXEN) | (1<<RXCIE);//UART enable RXTX and Interrupt
        UCSRC |= (1<<URSEL) | (3<<UCSZ0); //Mode asynchron 8N1
        UBRRH = 0; //Highbyte is 0
        UBRRL = 0; //103 --> 16Mhz,9600 Baud (Frequenz_in_Hz / (Baudrate * 16) - 1
}

void uart_sendchar(unsigned char c) {
        while(!(UCSRA & (1<<UDRE))) { // wait until sending is possible
    }
        UDR = c; // write to output
}

void uart_sendstring(char *s) {
        while(*s) {
        uart_sendchar(*s);
        s++;
        }
}

uint8_t uart_getchar(void) {
    while (!(UCSRA & (1<<RXC))) { // wait until char is available
        ;
        }
    return UDR; // return received char
}

void uart_getstring( char* Buffer, uint8_t MaxLen ) {
        uint8_t NextChar;
        uint8_t StringLen = 0;
        NextChar = uart_getchar(); // wait and get next received char
        while( NextChar != '\n' && StringLen < MaxLen - 1 ) {
                *Buffer++ = NextChar;
                StringLen++;
                NextChar = uart_getchar();
        }
        *Buffer = '\0'; // terminate string
}
