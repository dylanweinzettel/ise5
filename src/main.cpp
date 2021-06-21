#include "libs/LCD.h"
#include "libs/DHT.h"

int main(void) {

    LCD lcd(2, 3, 4, 5, 6, 7);
    DHT dht(8, DHT11);

    while (1) {

        // TODO
    }

    return 0;
}