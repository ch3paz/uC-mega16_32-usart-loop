/*
    Just a simple programm to test the USART/RS232 connection.
    It sends every 5 seconds a message ("I'm still up.") and if it receives an
    "ping" it answers with "pong".

    Thats all ;)

    Maybe you have to change values for frequency.
    (change UBRRL in usart.h also!)
*/

#define F_CPU 3686000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include "usart.h"

ISR(USART_RXC_vect) { // ISR called on incoming data
    char rxLine[5]; // Buffer to catch incoming data
    uart_getstring( rxLine, sizeof( rxLine )); // Get data

    // Repeat something on request
    if (strncmp ( rxLine, "ping",5) == 0){ // "ping" received -> repeat "pong"
        uart_sendstring("pong\n");
    }
}

int main(void)
{
    DDRA  = 0xFF; // Port A output
    PORTA = 0xFF; // Port A all pins 1

    DDRB  = 0xFF; // Port B output
    PORTB = 0xFF; // Port B all pins 1

    DDRC  = 0xFF; // Port C output
    PORTC = 0xFE; // Port C all pins 1, except PC0

    DDRD  = 0xFF; // Port D output
    PORTD = 0xFF; // Port D all pins 1

    cli(); // deactivate interrupts
        init_USART(); // activate USART global
        sei(); // activate interrupts global

    while(1){
        uart_sendstring("I'm still up.\n");
        _delay_ms(5000);
    }

    return 0;
}
