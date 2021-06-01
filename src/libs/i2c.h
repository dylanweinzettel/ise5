#ifndef _I2C_H_
#define _I2C_H_

#include <avr/io.h>

typedef enum {
    i2c_write,
    i2c_read   
} i2c_mode;

typedef enum {
    start_transmitted = 0x08,
    repeated_start_transmitted = 0x10,
    arbitration_lost = 0x38
} i2c_status_codes;

typedef enum {
    write_address_ack_received = 0x18,
    write_address_ack_not_received = 0x20,
    write_data_ack_received = 0x28,
    write_data_ack_not_received = 0x30
} i2c_master_transmitter_status;

typedef enum {
    read_address_ack_sent = 0x40,
    read_address_ack_not_sent = 0x48,
    read_data_ack_sent = 0x50,
    read_data_ack_not_sent = 0x58
} i2c_master_receiver_status;

typedef enum {
    prescaler_1,
    prescaler_4,
    prescaler_16,
    prescaler_64
} i2c_prescaler;

class I2C {

    public:
        I2C(uint32_t scl_frequency, i2c_prescaler prescaler);
        void wait(void);
        void start(void);
        void stop(void);
        void send(uint8_t data);
        void send(uint8_t address, uint8_t readWriteValue);
        uint8_t readAck(void);
        uint8_t readNotAck(void);
        uint8_t getStatus(void);
};

#endif /* _I2C_H_ */