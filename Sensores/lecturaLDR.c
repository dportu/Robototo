#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wiringPi.h>
#include <mcp3004.h>
#include <wiringPiSPI.h>
#define BASE 100
#define SPI_CHAN 0

int main(int argc, char *argv[]) {}
    printf("wiringPiSPISetup RC=%d\n",wiringPiSPISetup(0,500000));
    mcp3004Setup(BASE,SPI_CHAN);
    while(1) {
        printf("Canal 0: valor %4dn",analogRead(BASE));
        printf("\n");
        usleep(500000);
    }
}
