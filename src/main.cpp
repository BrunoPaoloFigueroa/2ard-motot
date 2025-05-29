
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define F_CPU 16000000UL

void config_USART() {
    UBRR0 = 103;  
    UCSR0B = (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0);  
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  
}

void config_interrupciones() {
    EIMSK |= (1 << INT0) | (1 << INT1);   
    EICRA |= (1 << ISC01) | (1 << ISC11); //  bajada
}


ISR(INT0_vect) {
    while (!(UCSR0A & (1 << UDRE0))); // Espera buffer libre
    UDR0 = 0x01;              // Señal botón 1
}

ISR(INT1_vect) {
    
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = 0x02;  
}


ISR(USART_RX_vect) {
    unsigned char doto = UDR0;
    if (doto == 0x01) {
        PORTB |= 0x10; 
    } else if (doto == 0x02) {
        PORTB &= ~(0x10);
    }
}

int main() {
    DDRB |= 0x10;   
    DDRD &= ~0x0C;  
    PORTD &= ~0x0C; 

    config_USART();
    config_interrupciones();
    sei(); 


    while (1){

    };
    return 0;
}




