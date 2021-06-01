#include "libs/analog.h"
#include "libs/LCD.h"
#include "libs/bmp180.h"

int main(void) {

    BMP180 bmp;                 // Inicializacion del sensor
    LCD lcd(2, 3, 4, 5, 6, 7);  // Inicializacion del display

    while(1) {

        uint8_t status = bmp.read();    // Hago una lectura completa y guardo el estado
        if (status == bmp.status_ok) {  // Si no hubo error en la lectura, prosigo

            // TODO

        }

    }

    return 0;
}

