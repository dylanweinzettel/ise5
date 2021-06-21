#include "DHT.h"

DHT::DHT(uint8_t pin_n, DHT_Type_t type) {
	
	pin = pin_n;

	if (pin < 8) {
		direction_port = &DDRD;
		write_port = &PORTD;
		read_port = &PIND;
	}
	else if (pin < 14) {
		pin -= 8;
		direction_port = &DDRB;
		write_port = &PORTB;
		read_port = &PINB;
	}
	else if (pin < 20) {
		pin -= 14;
		direction_port = &DDRC;
		write_port = &PORTC;
		read_port = &PINC;
	}

	#if (type == DHT11)
		#define DHT_Temperature_Min		0
		#define DHT_Temperature_Max		50
		#define DHT_Humidity_Min		20
		#define DHT_Humidity_Max		90
		#define DHT_Delay_Read			50
	#elif (type == DHT22)
		#define DHT_Temperature_Min		-40
		#define DHT_Temperature_Max		80
		#define DHT_Humidity_Min		0
		#define DHT_Humidity_Max		100
		#define DHT_Delay_Read			20
	#endif
	
	_delay_ms(DHT_Delay_Setup);
	status = DHT_Ok;
}

enum DHT_Status_t DHT::getStatus(void) {

	return status;
}

enum DHT_Status_t DHT::getTemperature(double *temperature) {

	double *waste = 0;
	return read(temperature, waste);
}

enum DHT_Status_t DHT::getHumidity(double *humidity) {

	double *waste = 0;
	return read(waste, humidity);
}

enum DHT_Status_t DHT::read(void) {

	uint8_t buffer[5] = { 0, 0, 0, 0, 0 };
	uint8_t retries, i;
	status = DHT_Ok;
	retries = i = 0;

	//----- Step 1 - Start communication -----
	//Request data
	*write_port &= ~(1 << pin); 			//DHT_PIN = 0
	*direction_port |= 1 << pin;			//DHT_PIN = Output
	_delay_ms(DHT_Delay_Read);

	//Setup DHT_PIN as input with pull-up resistor so as to read data
	*write_port |= 1 << pin;				//DHT_PIN = 1 (Pull-up resistor)
	*direction_port &= ~(1 << pin);			//DHT_PIN = Input
	//----------------------------------------

	//----- Step 2 - Wait for response -----
	//Response sequence began
	//Wait for the first response to finish (low for ~80us)
	retries = 0;
	while (!((*read_port) & (1 << pin))) {

		_delay_us(2);
		retries += 2;
		if (retries > 100) {
			status = DHT_Error_Timeout;
			return status;
		}
	}
	//Wait for the last response to finish (high for ~80us)
	retries = 0;
	while((*read_port) & (1 << pin)) {

		_delay_us(2);
		retries += 2;
		if (retries > 100) {
			status = DHT_Error_Timeout;
			return status;
		}
	}
	//--------------------------------------

	//----- Step 3 - Data transmission -----

	//Reading 5 bytes, bit by bit
	for (i = 0 ; i < 5 ; i++) {
		for (int8_t j = 7 ; j >= 0 ; j--) {
			//There is always a leading low level of 50 us
			retries = 0;
			while(!((*read_port) & (1 << pin))) {

				_delay_us(2);
				retries += 2;
				if (retries > 70) {
					status = DHT_Error_Timeout;
					return status;
				}
			}

			//We read data bit || 26-28us means '0' || 70us means '1'
			_delay_us(35);							//Wait for more than 28us
			if ((*read_port) & (1 << pin))			//If HIGH
				buffer[i] |= 1 << j;				//bit = '1'

			retries = 0;
			while((*read_port) & (1 << pin)) {

				_delay_us(2);
				retries += 2;
				if (retries > 100) {
					status = DHT_Error_Timeout;
					return status;
				}
			}
		}
	}
	//--------------------------------------

	//----- Step 4 - Check checksum and return data -----
	uint8_t checksum = 0;

	for (i = 0 ; i < 4 ; i++) {
		checksum += buffer[i];
	}

	if (checksum != buffer[4]) {
		status = DHT_Error_Checksum;
	}
	else {

		data.highHumidity = buffer[0];
		data.lowHumidity = buffer[1];
		data.highTemperature = buffer[2];
		data.lowTemperature = buffer[3];
		data.checksum = buffer[4];

	}
	//---------------------------------------------------

	return status;
}

enum DHT_Status_t DHT::read(double *temperature, double *humidity) {

	status = read();
	
	if (status == DHT_Ok) {

		*temperature = ExtractTemperature();
		*humidity = ExtractHumidity();

		if ((*temperature < DHT_Temperature_Min) || (*temperature > DHT_Temperature_Max))
			status = DHT_Error_Temperature;
		else if ((*humidity < DHT_Humidity_Min) || (*humidity > DHT_Humidity_Max))
			status = DHT_Error_Humidity;
	}

	return status;
}

double DHT::ExtractTemperature(void) {

	double temp;

	// TODO

	return temp;
}

double DHT::ExtractHumidity(void) {

	double hum;

	// TODO

	return hum;
}