//gcc practica_1.c -program -l wiringPi
//./program

#include <stdio.h>
#include <wiringPi.h>



//BUTTONS
#define SENSOR 0


int main() {
    wiringPiSetup ();
    pinmode (SENSOR, INPUT);

    for(;;) {
        printf("Valor leido: %d\n", digitalRead(SENSOR));

        delay(1000);
    }
}