#ifndef _ANALOG_H_
#define _ANALOG_H_

#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

// Labels
#define ADC_ON	    (ADCSRA & (1 << ADEN))
#define ADC_DONE	(ADCSRA & (1 << ADIF))
#define ADC_BUSY	!(ADCSRA & (1 << ADIF))
#define ADC_ISR     (ADCSRA & (1 << ADIE))

#define AREF	    0
#define AVCC	    1
#define INTERNAL	3

// Pseudo functions
#define ADC_On()    ADCSRA |= 1 << ADEN
#define ADC_Start()	ADCSRA |= 1 << ADSC
#define ADC_Clear()	ADCSRA |= 1 << ADIF
#define RightFormat	(ADMUX & ADLAR)
#define LeftFormat	!(ADMUX & ADLAR)

// ISR triggers
#define FREE            0
#define ANALOG_CMP      1
#define EXT_INT0        2
#define TMR0_MATCH_A    3
#define TMR0_OVF        4
#define TMR1_MATCH_A    5
#define TMR1_OVF        6
#define TMR1_CAPTURE    7

uint16_t analogRead(uint8_t pin);
void analogStart(uint8_t pin);
void analogSetPin(uint8_t pin);
void analogInterrupt(void (*f)(void), uint8_t trigger);
void analogRef(uint8_t ref);

#endif /* _ANALOG_H_ */