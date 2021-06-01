#include "bmp180.h"

uint8_t BMP180::calibrate(void) {

    i2c.start();

    uint8_t status = i2c.getStatus();

    if (status != start_transmitted) {
        return status;
    }

    i2c.send(BMP180_ADDRESS, i2c_write);
    status = i2c.getStatus();
    if (status != write_address_ack_received) {
        return status;
    }

    i2c.send(0xAA);
    status = i2c.getStatus();
    if (status != write_data_ack_received) {
        return status;
    }

    i2c.stop();

    i2c.start();
    status = i2c.getStatus();
    if (status != start_transmitted) {
        return status;
    }

    i2c.send(BMP180_ADDRESS, i2c_read);
    status = i2c.getStatus();
    if (status != read_address_ack_sent) {
        return status;
    }

    int reg;
    for (reg = 0xAA; reg <= 0xBE; reg += 2) {
        uint16_t bits = 0;
        uint8_t msb = i2c.readAck();
        status = i2c.getStatus();
        if (status != read_data_ack_sent) {
            return status;
        }

        uint8_t lsb;
        if (reg == 0xBE) {
            lsb = i2c.readNotAck();
            status = i2c.getStatus();
            if (status != read_data_ack_not_sent) {
                return status;
            }
        } else {
            lsb = i2c.readAck();
            status = i2c.getStatus();
            if (status != read_data_ack_sent) {
                return status;
            }
        }

        bits |= (msb << 8) | lsb;

        switch (reg) {
            case 0xAA:
                calibrationData.ac1 = bits;
                break;
            case 0xAC:
                calibrationData.ac2 = bits;
                break;
            case 0xAE:
                calibrationData.ac3 = bits;
                break;
            case 0xB0:
                calibrationData.ac4 = bits;
                break;
            case 0xB2:
                calibrationData.ac5 = bits;
                break;
            case 0xB4:
                calibrationData.ac6 = bits;
                break;
            case 0xB6:
                calibrationData.b1 = bits;
                break;
            case 0xB8:
                calibrationData.b2 = bits;
                break;
            case 0xBA:
                calibrationData.mb = bits;
                break;
            case 0xBC:
                calibrationData.mc = bits;
                break;
            case 0xBE:
                calibrationData.md = bits;
                break;
        }
    }

    i2c.stop();

    return status_ok;
}

uint8_t BMP180::readUncompensatedTemperature(uint16_t *temperature) {

    i2c.start();

    uint8_t status = i2c.getStatus();
    if (status != start_transmitted) {
        return status;
    }

    i2c.send(BMP180_ADDRESS, i2c_write);
    status = i2c.getStatus();
    if (status != write_address_ack_received) {
        return status;
    }

    i2c.send(0xF4);
    status = i2c.getStatus();
    if (status != write_data_ack_received) {
        return status;
    }

    i2c.send(0x2E);
    status = i2c.getStatus();
    if (status != write_data_ack_received) {
        return status;
    }

    i2c.stop();
    _delay_us(4500);

    i2c.start();
    status = i2c.getStatus();
    if (status != start_transmitted) {
        return status;
    }

    i2c.send(BMP180_ADDRESS, i2c_write);
    status = i2c.getStatus();
    if (status != write_address_ack_received) {
        return status;
    }

    i2c.send(0xF6);
    status = i2c.getStatus();
    if (status != write_data_ack_received) {
        return status;
    }

    i2c.stop();
    i2c.start();
    status = i2c.getStatus();
    if (status != start_transmitted) {
        return status;
    }

    i2c.send(BMP180_ADDRESS, i2c_read);
    status = i2c.getStatus();
    if (status != read_address_ack_sent) {
        return status;
    }

    uint8_t msb = i2c.readAck();
    status = i2c.getStatus();
    if (status != read_data_ack_sent) {
        return status;
    }

    uint8_t lsb = i2c.readNotAck();
    status = i2c.getStatus();
    if (status != read_data_ack_not_sent) {
        return status;
    }

    i2c.stop();

    uint16_t result = 0;
    result |= (msb << 8) | lsb;

    *temperature = result;

    return status_ok;
}

float BMP180::calculateTemperature(uint16_t uncompensatedTemperature, int32_t *b5) {

    int32_t x1 = ((uncompensatedTemperature - calibrationData.ac6) * (int32_t) calibrationData.ac5) >> 15;
    int32_t x2 = ((int32_t) calibrationData.mc << 11) / (x1 + calibrationData.md);
    *b5 = x1 + x2;
    float temperature = (int32_t) ((*b5 + 8) >> 4);
    temperature /= (float) 10;

    return temperature;
}

uint8_t BMP180::readUncompensatedPressure(uint32_t *pressure) {

    i2c.start();

    uint8_t status = i2c.getStatus();
    if (status != start_transmitted) {
        return status;
    }

    i2c.send(BMP180_ADDRESS, i2c_write);
    status = i2c.getStatus();
    if (status != write_address_ack_received) {
        return status;
    }

    i2c.send(0xF4);
    status = i2c.getStatus();
    if (status != write_data_ack_received) {
        return status;
    }

    i2c.send(0x34 | (BMP180_OSS << 6));
    status = i2c.getStatus();
    if (status != write_data_ack_received) {
        return status;
    }

    i2c.stop();

    switch (BMP180_OSS) {
        case BMP180_OSS_ULTRA_LOW_POWER:
            _delay_us(4500);
            break;
        case BMP180_OSS_STANDARD:
            _delay_us(7500);
            break;
        case BMP180_OSS_HIGH_RESOLUTION:
            _delay_us(13500);
            break;
        case BMP180_OSS_ULTRA_HIGH_RESOLUTION:
            _delay_us(25500);
            break;
    }

    i2c.start();
    status = i2c.getStatus();
    if (status != start_transmitted) {
        return status;
    }

    i2c.send(BMP180_ADDRESS, i2c_write);
    status = i2c.getStatus();
    if (status != write_address_ack_received) {
        return status;
    }

    i2c.send(0xF6);
    status = i2c.getStatus();
    if (status != write_data_ack_received) {
        return status;
    }

    i2c.stop();
    i2c.start();
    status = i2c.getStatus();
    if (status != start_transmitted) {
        return status;
    }

    i2c.send(BMP180_ADDRESS, i2c_read);
    status = i2c.getStatus();
    if (status != read_address_ack_sent) {
        return status;
    }

    uint8_t msb = i2c.readAck();
    status = i2c.getStatus();
    if (status != read_data_ack_sent) {
        return status;
    }

    uint8_t lsb = i2c.readAck();
    status = i2c.getStatus();
    if (status != read_data_ack_sent) {
        return status;
    }

    uint8_t xlsb = i2c.readNotAck();
    status = i2c.getStatus();
    if (status != read_data_ack_not_sent) {
        return status;
    }

    i2c.stop();

    uint32_t result = 0;
    result |= ((uint16_t) msb << 8) | lsb;
    result <<= 8;
    result |= xlsb;

    result >>= (8 - BMP180_OSS);
    *pressure = result;

    return status_ok;
}

long BMP180::calculatePressure(uint32_t uncompensatedPressure, int32_t *b5) {
    
    int32_t b6 = *b5 - 4000;
    int32_t x1 = ((int32_t) calibrationData.b2 * (b6 * b6 >> 12)) >> 11;
    int32_t x2 = (int32_t) calibrationData.ac2 * b6 >> 11;
    int32_t x3 = x1 + x2;
    int32_t b3 = ((((int32_t) calibrationData.ac1 * 4 + x3) << BMP180_OSS) + 2) >> 2;
    x1 = (int32_t) calibrationData.ac3 * b6 >> 13;
    x2 = ((int32_t) calibrationData.b1 * (b6 * b6 >> 12)) >> 16;
    x3 = ((x1 + x2) + 2) >> 2;
    uint32_t b4 = (uint32_t) calibrationData.ac4 * (x3 + 32768) >> 15;
    uint32_t b7 = ((uncompensatedPressure - b3) * (50000 >> BMP180_OSS));

    long p;
    if (b7 < 0x80000000) {
        p = ((b7 * 2) / b4);
    } else {
        p = ((b7 / b4) * 2);
    }

    x1 = (p >> 8) * (p >> 8);
    x1 = (x1 * 3038) >> 16;
    x2 = (-7357 * p) >> 16;
    p = p + ((x1 + x2 + 3791) >> 4);

    return p;
}

uint8_t BMP180::read(void) {

    uint16_t ut;
    uint8_t result = readUncompensatedTemperature(&ut);

    if (result != status_ok) {
        return status_error_ut;
    }

    uint32_t up;
    result = readUncompensatedPressure(&up);

    if (result != status_ok) {
        return status_error_up;
    }

    int32_t b5 = 0;
    
    data.temperatureC = calculateTemperature(ut, &b5);
    data.pressurePa = calculatePressure(up, &b5);
    
    return status_ok;
}

float BMP180::getTemperature(void) {

    return data.temperatureC;
}

long BMP180::getPressure(void) {
    
    return data.pressurePa;
}

float BMP180::getPressure(uint8_t unit) {

    long pressurePa = data.pressurePa;
    float pres;
    
    // TODO

    return pres;
}