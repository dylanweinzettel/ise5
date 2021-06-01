#ifndef	_LCD_H_
#define _LCD_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "digital.h"

#define CMD		0
#define WRITE	1

#define RS	pins[0]
#define EN	pins[1]
#define D4	pins[2]
#define D5 	pins[3]
#define D6 	pins[4]
#define D7 	pins[5]

class LCD {

	public:

		LCD(uint8_t rs, uint8_t en, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
		void send	(uint8_t byte);
		void cmd	(uint8_t byte);
		void clear	(void);
		void setXY	(uint8_t x, uint8_t y);
		void putC	(char ch);
		void print 	(const char* str);
		void print (int32_t int32_);
		void print	(uint32_t uint32_);
		void print	(double float_);

	private:

		uint8_t pins[6];	/* RS, EN, D4, D5, D6, D7 */
};


#endif /* _LCD_H_ */
