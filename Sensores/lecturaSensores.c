#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wiringPi.h>
#include <mcp3004.h>
#include <wiringPiSPI.h>
#define BASE 100
#define SPI_CHAN 0

#define INFRARROJO 0
#define SHARP_DERECHA 1
#define SHARP_IZQUIERDA 2

int main(int argc, char *argv[]) {
    printf("wiringPiSPISetup RC=%d\n",wiringPiSPISetup(0,500000));
    mcp3004Setup(BASE,SPI_CHAN);
    while(1) {
        printf("Infrarrojo: valor %4dn\n",analogRead(BASE+INFRARROJO));
        printf("Sharp Derecho: valor %4dn\n",analogRead(BASE+SHARP_DERECHA));
        printf("Sharp Izquierdo: valor %4dn\n",analogRead(BASE+SHARP_IZQUIERDA));
        printf("\n\n");
        usleep(150000);

    }
}
