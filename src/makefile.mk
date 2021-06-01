MCU=atmega328p
PART=m328p
F_CPU=1000000
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-Wall -g -Os -mmcu=${MCU} -DF_CPU=${F_CPU} -I.
TARGET=bmp180
SRCS=main.cpp libs/analog.cpp libs/LCD.cpp libs/digital.cpp libs/i2c.cpp libs/bmp180.cpp
PROGRAMMER=usbasp

all:
	${CC} ${CFLAGS} -o ${TARGET}.bin ${SRCS} -lm
	${OBJCOPY} -j .text -j .data -O ihex ${TARGET}.bin ${TARGET}.hex

flash:
	avrdude -p ${PART} -c ${PROGRAMMER} -U flash:w:${TARGET}.hex:i
