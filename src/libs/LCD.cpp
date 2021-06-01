#include "LCD.h"

LCD::LCD(uint8_t rs, uint8_t en, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) {

	uint8_t p[6] = { rs, en, d4, d5, d6, d7 };

	for (uint8_t i = 0 ; i < 6 ; i++) {
		pins[i] = p[i];
		pinMode(pins[i], OUTPUT);
	} 	

	cmd(0x02);	// High nibble Function set command: 4 bit data mode
	cmd(0x02);	// send again	
	cmd(0x08);	// Low nibble Function set command: 2 line mode
	
	cmd(0x00);
	cmd(0x0C);	// Display on/off control commmand
	
	cmd(0x00);
	cmd(0x06);	// Entry mode set command
}

void LCD::send (uint8_t byte) {

	for (uint8_t i = 0 ; i < 4 ; i++) {
		digitalWrite(pins[i+2], byte & (1 << i));
	}
}

void LCD::cmd (uint8_t byte) {

	digitalWrite(RS, LOW);
	send(byte);
	digitalWrite(EN, HIGH);
	_delay_us(40);
	digitalWrite(EN, LOW);
}

void LCD::clear(void) {

	cmd(0);
	cmd(1);
	_delay_ms(4);
}

void LCD::setXY (uint8_t x, uint8_t y) {

	char aux = 0;
	if(y == 1) {
		aux = 0x80;
	}
	else if (y == 2) {
		aux = 0xC0;
	}
	cmd(aux >> 4);
	cmd(aux | (x-1));
}

void LCD::putC(char ch) {
	
	digitalWrite(RS, HIGH);
	send(ch>>4);      
	digitalWrite(EN, HIGH);
	_delay_us(40);
	digitalWrite(EN, LOW);
	send(ch & 0x0f);
	digitalWrite(EN, HIGH);
	_delay_us(40);
	digitalWrite(EN, LOW);
}

void LCD::print(const char* str) {

	while (*str) {
		putC(*str);
		str++;
	}
}

void LCD::print(int32_t int32_) {

	char word[20];
	print(ltoa(int32_,word,10));
}

void LCD::print(uint32_t uint32_) {

	char word[10];
	print(ultoa(uint32_,word,10));
}

void LCD::print(double float_) {

	char word[10];
	dtostrf(float_,3,2,word);
	print(word);
}

