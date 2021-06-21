#ifndef _DHT11_H_
#define _DHT11_H_

#include <util/delay.h>
#include "digital.h"

#define DHT_Delay_Setup 2000

enum DHT_Type_t {
    DHT11,
    DHT22
};

enum DHT_Status_t {
    DHT_Ok,
    DHT_Error_Humidity,
    DHT_Error_Temperature,
    DHT_Error_Checksum,
    DHT_Error_Timeout,
};

typedef struct {
    uint8_t highTemperature;
    uint8_t lowTemperature;
    uint8_t highHumidity;
    uint8_t lowHumidity;
    uint8_t checksum;
} DHT_Data_t;

class DHT {

    public:
        DHT(uint8_t pin_n, DHT_Type_t type);
        enum DHT_Status_t getStatus(void);
        enum DHT_Status_t getTemperature(double *temperature);
        enum DHT_Status_t getHumidity(double *humidity);
        enum DHT_Status_t read(void);
        enum DHT_Status_t read(double *temperature, double *humidity);

    private:
        
        volatile uint8_t *direction_port;
        volatile uint8_t *write_port;
        volatile uint8_t *read_port;
        uint8_t pin;
        
        DHT_Status_t status;
        DHT_Data_t data;

        double ExtractTemperature(void);
        double ExtractHumidity(void);
};

#endif /* _DHT11_H_ */