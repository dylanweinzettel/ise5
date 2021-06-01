#ifndef _BMP180_H_
#define _BMP180_H_

#include <util/delay.h>
#include "i2c.h"

#ifndef BMP180_SCL
#define BMP180_SCL 50000UL
#endif

#ifndef BMP180_PRES
#define BMP180_PRES prescaler_1
#endif

#ifndef BMP180_ADDRESS
#define BMP180_ADDRESS 0x77
#endif

#define BMP180_OSS_ULTRA_LOW_POWER 0        // Max conversion time 4.5 ms
#define BMP180_OSS_STANDARD 1               // Max conversion time 7.5 ms
#define BMP180_OSS_HIGH_RESOLUTION 2        // Max conversion time 13.5 ms
#define BMP180_OSS_ULTRA_HIGH_RESOLUTION 3  // Max conversion time 25.5 ms

#ifndef BMP180_OSS
#define BMP180_OSS  BMP180_OSS_STANDARD
#endif

#define Pa      0
#define hPa     1
#define kPa     2
#define atm     3
#define mmHg    4
#define Bar     5
#define PSI     6
#define Torr    7

typedef struct Bmp180CalibrationData {
    int16_t ac1;
    int16_t ac2;
    int16_t ac3;
    uint16_t ac4;
    uint16_t ac5;
    uint16_t ac6;
    int16_t b1;
    int16_t b2;
    int16_t mb;
    int16_t mc;
    int16_t md;
} bmp180CalibrationData_t;

typedef struct Bmp180Data {
    float temperatureC;
    long pressurePa;
} bmp180Data_t;

class BMP180 {

    I2C i2c;

    public:
        BMP180(void) :  i2c(BMP180_SCL, BMP180_PRES),   \
                        status_ok(0),                   \
                        status_error_ut(1),             \
                        status_error_up(2) { calibrate(); }
        uint8_t read(void);
        float getTemperature(void);
        long getPressure(void);
        float getPressure(uint8_t unit);

        /* BMP180 status constants */
        const int status_ok;
        const int status_error_ut;
        const int status_error_up;

    private:
        bmp180CalibrationData_t calibrationData;
        bmp180Data_t data;

        uint8_t calibrate(void);
        uint8_t readUncompensatedTemperature(uint16_t *temperature);
        float calculateTemperature(uint16_t uncompensatedTemperature, int32_t *b5);
        uint8_t readUncompensatedPressure(uint32_t *pressure);
        long calculatePressure(uint32_t uncompensatedPressure, int32_t *b5);
};

#endif /* _BMP180_H_ */