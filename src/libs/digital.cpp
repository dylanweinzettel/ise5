#include "digital.h"

void (*ext_ptr[2])(void);
void (*pci_ptr[23])(void);

void pinMode(uint8_t pin, uint8_t mode) {

    volatile uint8_t *ddr;
    ddr = reg(&pin, DDR);
    if (ddr) {
        (mode)? *ddr |= 1 << pin : *ddr &= ~(1 << pin);
    }
    else {
        return;
    }
}

void digitalWrite(uint8_t pin, uint8_t output) {

    volatile uint8_t *port;
    port = reg(&pin, PORT);
    if (port) {
        (output)? *port |= 1 << pin : *port &= ~(1 << pin);
    }
    else {
        return;
    }
}

uint8_t digitalRead(uint8_t pin) {

    volatile uint8_t *port;
    port = reg(&pin, PIN);
    if (port) {
        return (*port) & (1 << pin);
    }
    else {
        return 0;
    }
}

void pinToggle(uint8_t pin) {

    volatile uint8_t *port;
    port = reg(&pin, PORT);
    if (port) {
        *port ^= (1 << pin); 
    }
    else {
        return;
    }
}

uint8_t digitalToInterrupt(uint8_t pin) {

    if (pin < 8) {
        return pin + 16;
    }
    else if (pin < 14) {
        return pin - 8;
    }
    else if (pin < 20) {
        return pin - 6;
    }
    else {
        return 0;
    }
}

void attachExternalInt(uint8_t pin, void (*f)(void), uint8_t mode) {

    if (pin != 3 && pin != 2 && pin != 18 && pin != 19) {
        return;
    }

    sei();
    if (pin == 2 || pin == 18) {
        
        EICRA = (EICRA & 0xc0) | mode;
        EIMSK = 1 << INT0;
    } 
    else if (pin == 3 || pin == 19) {

        EICRA = (EICRA & 0x03) | mode;
        EIMSK = 1 << INT1;
    }
    if (pin < 18) {
        ext_ptr[pin - 2] = f;
    }
    else {
        ext_ptr[pin - 18] = f;
    }
    
}

void attachPinChangeInt(uint8_t pin, void (*f)(void)) {

    if (pin > 22) {
        return;
    }

    sei();
    if (pin < 8) {
        PCICR |= 1 << PCIE0;
        PCMSK0 |= 1 << pin;
    }
    else if (pin < 15) {
        PCICR |= 1 << PCIE1;
        PCMSK1 |= 1 << (pin - 8);
    }
    else if (pin < 23) {
        PCICR |= 1 << PCIE2;
        PCMSK2 |= 1 << (pin - 16);    
    }
    pci_ptr[pin] = f;
}

volatile uint8_t* reg(uint8_t *pin, uint8_t type) {

    if (*pin < 8) {
        switch (type) {
            case DDR:   return &DDRD;
            break;
            case PORT:  return &PORTD;
            break;
            case PIN:   return &PIND;
            break;
        }
    }
    else if (*pin < 14) {
        *pin -= 8;
        switch (type) {
            case DDR:   return &DDRB;
            break;
            case PORT:  return &PORTB;
            break;
            case PIN:   return &PINB;
            break;
        }
    }
    else if (*pin < 20) {
        *pin -= 14;
        switch (type) {
            case DDR:   return &DDRC;
            break;
            case PORT:  return &PORTC;
            break;
            case PIN:   return &PINC;
            break;
        }
    }
    return (volatile uint8_t*) 0x00;
}

ISR(INT0_vect) {

    if (ext_ptr[0]) {
        ext_ptr[0]();
    }
}

ISR(INT1_vect) {

    if (ext_ptr[1]) {
        ext_ptr[1]();
    }
}

ISR(PCINT0_vect) {

    for (int i = 0 ; i < 8 ; i++) {
        if(pci_ptr[i]) {
            pci_ptr[i]();
        }
    } 
}

ISR(PCINT1_vect) {
    
    for (int i = 8 ; i < 15 ; i++) {
        if(pci_ptr[i]) {
            pci_ptr[i]();
        }
    } 
}

ISR(PCINT2_vect) {

    for (int i = 15 ; i < 23 ; i++) {
        if(pci_ptr[i]) {
            pci_ptr[i]();
        }
    } 
}