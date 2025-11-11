#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wiringPi.h>
#include <mcp3004.h>
#include <wiringPiSPI.h>
#define BASE 100
#define SPI_CHAN 0

#define PinMotor0 23 // pwm_1 BCM13 Fisico 33 CONECTAR A B13
#define PinMotor1 26 // pwm_0 BCM12 Fisico 32 CONECTAR A B12

#define INFRARROJO 0
#define SHARP_DERECHA 1
#define SHARP_IZQUIERDA 2


int main(int argc, char *argv[]) {
   
    // Set up de wiring Pi
    mcp3004Setup(BASE,SPI_CHAN);
    if(wiringPiSetup()==-1) {
                exit(1);
        }

    // Set up de pwm
    pinMode(PinMotor0,PWM_OUTPUT);
    pinMode(PinMotor1,PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetClock(192); //clock at 50Hz
    pwmSetRange(2000); //range at 2000
    
    // Variables del controlador
    int error;
    int marginOfError = 20; // Definimos un margen de error para evitar comportamientos oscilatorios
    int readDistance;
    int desiredDistance = 500;
    //int K_p = 1; // Constante de ganancia
    int pwm;

    while(1) {
        // A falta de hacer un controlador PID en condiciones, hago un controlador casero 
        readDistance = analogRead(BASE+SHARP_DERECHA);
        error = desiredDistance - readDistance;
        printf("Read Distance: %d\n", readDistance);
        printf("Error: %d\n", error);

        //Controlador

        if(error > desiredDistance + marginOfError) { // Estamos demasiado lejos
            pwm = 200;
            printf("Estoy demasiado lejos\n\n");
        }
        else if(error < desiredDistance - marginOfError) { // Estamos demasiado cerca
            pwm = 100;
            printf("Estoy demasiado cerca\n\n");
        }
        else { // Estamos dentro de la zona aceptable
            pwm = 150;
            printf("Estoy en el sweet spot :)\n\n");
        }

        pwmWrite(PinMotor0,pwm);
        pwmWrite(PinMotor1,pwm);
    }
}
