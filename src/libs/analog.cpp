#include "analog.h"

void (*adc_ptr) (void);

uint16_t analogRead(uint8_t pin) {

    analogSetPin(pin);

    if (!ADC_ON) {

        ADC_On();
    }
    if (!ADC_ISR) {

        ADC_Start();
        while (ADC_BUSY);
        ADC_Clear();
        return ADC;
    }
    else {
        return ADC;
    }
}

void analogStart(uint8_t pin) {

    if (!ADC_ON) {

        ADC_On();
    }
    analogSetPin(pin);
    ADC_Start();
}

void analogSetPin(uint8_t pin) {

    ADMUX |= (ADMUX & 0xf0) | (pin & 0x0f);
}

void analogInterrupt(void (*f)(void), uint8_t trigger) {

    ADCSRA |= 1 << ADIE;
    sei();
    if (trigger) {

        ADCSRA |= 1 << ADATE;
        ADCSRB = trigger;
    }
    adc_ptr = f;
}

void analogRef(uint8_t ref) {

    ADMUX = (ADMUX & 0x0f) | (ref << REFS0);
}

ISR(ADC_vect) {

    if(adc_ptr) {
        adc_ptr();
    }
}