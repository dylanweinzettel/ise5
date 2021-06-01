#include "i2c.h" 

I2C::I2C(uint32_t scl_frequency, i2c_prescaler prescaler) {

    uint8_t pres = 1;

    if (prescaler == prescaler_1) 
        pres = 1;
    
    else if (prescaler == prescaler_4) 
        pres = 4;
    
    else if (prescaler == prescaler_16) 
        pres = 16;
    
    else if (prescaler == prescaler_64)
        pres = 64;

    TWBR = (F_CPU - 16 * scl_frequency) / (2 * pres * scl_frequency);
    TWSR = prescaler;
}

void I2C::wait(void) {

    while(!(TWCR & (1 << TWINT)));      // Espero a que el periferico este libre
}

void I2C::start(void) {
    
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);   // Limpio el flag de interrupcion ; Condicion de START
    I2C::wait();                                         
}       

void I2C::stop(void) {
    
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
    while ((TWCR & (1 << TWSTO)));
}

void I2C::send(uint8_t data) {
    
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);  // Limpiar bit de interrupcion
    I2C::wait();
}

void I2C::send(uint8_t address, uint8_t readWriteMode) {
    
    I2C::send((address << 1) | readWriteMode);
}

uint8_t I2C::readAck(void) {
    
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    I2C::wait();

    return TWDR;
}

uint8_t I2C::readNotAck(void) {
    
    TWCR = (1 << TWINT) | (1 << TWEN);
    I2C::wait();

    return TWDR;
}

uint8_t I2C::getStatus(void) {
    
    return (TWSR & 0xf8);
}