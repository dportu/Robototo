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

#define INFRARROJO_DERECHA 3
#define SHARP_DERECHA 1
#define SHARP_IZQUIERDA 2
#define INFRARROJO_IZQUIERDA 0

#define UMBRAL_OBSTACULO 500
#define UMBRAL_INFRARROJO 150 // El umbral de infrarrojo es inverso, es decir se detecta la linea negra cuando el valor leido es menor que el umbral


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
    
 

    int pwm;
    int lecturaSharpDerecho;
    int lecturaSharpIzquierdo;
    int lecturaInfrarrojoDerecho;
    int lecturaInfrarrojoIzquierdo;

    int infraD = 1;
    int infraI = 1;

    while(1) {
        lecturaSharpDerecho = analogRead(BASE+SHARP_DERECHA);
        lecturaSharpIzquierdo = analogRead(BASE+SHARP_IZQUIERDA);
        if(lecturaSharpDerecho > UMBRAL_OBSTACULO || lecturaSharpIzquierdo > UMBRAL_OBSTACULO) {
            // Obstaculo detectado : Paramos
            pwm = 150;
        }
        else {
            // Ciclo de Control
            lecturaInfrarrojoDerecho = analogRead(BASE+INFRARROJO_DERECHA);
            lecturaInfrarrojoIzquierdo = analogRead(BASE+INFRARROJO_IZQUIERDA);

            if(lecturaInfrarrojoDerecho < UMBRAL_INFRARROJO) {
                infraD = 1;
            }
            if(lecturaInfrarrojoIzquierdo < UMBRAL_INFRARROJO) {
                infraI = 1;
            }

            
        }

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
