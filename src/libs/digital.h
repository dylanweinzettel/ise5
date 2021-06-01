#ifndef _DIGITAL_H_
#define _DIGITAL_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define INPUT   0
#define OUTPUT  1

#define LOW     0
#define HIGH    1

#define DDR     0
#define PORT    1
#define PIN     2

#define LOW     0
#define CHANGE  1
#define FALL    2
#define RISE    3

void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t output);
uint8_t digitalRead(uint8_t pin);
void pinToggle(uint8_t pin);
uint8_t digitalToInterrupt(uint8_t pin);
void attachExternalInt(uint8_t pin, void (*f)(void), uint8_t mode);
void attachPinChangeInt(uint8_t pin, void (*f)(void));
volatile uint8_t* reg(uint8_t *pin, uint8_t type);

#endif /* _DIGITAL_H_ */