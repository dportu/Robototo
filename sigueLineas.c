#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wiringPi.h>
#include <mcp3004.h>
#include <wiringPiSPI.h>
#define BASE 100
#define SPI_CHAN 0

#define PinMotorDer 23 // pwm_1 BCM13 Fisico 33 CONECTAR A B13
#define PinMotorIz 26 // pwm_0 BCM12 Fisico 32 CONECTAR A B12

#define INFRARROJO_DERECHA 3
#define SHARP_DERECHA 1
#define SHARP_IZQUIERDA 2
#define INFRARROJO_IZQUIERDA 0

#define UMBRAL_OBSTACULO 500
#define UMBRAL_INFRARROJO 150 // El umbral de infrarrojo es inverso, es decir se detecta la linea negra cuando el valor leido es menor que el umbral
#define PARADA 150


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
    
 

    int pwmD = 150;
    int pwmI = 150;
    int lecturaSharpDerecho;
    int lecturaSharpIzquierdo;
    int lecturaInfrarrojoDerecho;
    int lecturaInfrarrojoIzquierdo;

    int infraD = 1;
    int infraI = 1;

    unsigned int tcontrol = 20000; //en microsegundos

    while(1) {
        lecturaSharpDerecho = analogRead(BASE+SHARP_DERECHA);
        lecturaSharpIzquierdo = analogRead(BASE+SHARP_IZQUIERDA);
        unsigned int prev_time = micros();
        
        unsigned int tstart = micros();

        if(lecturaSharpDerecho > UMBRAL_OBSTACULO || lecturaSharpIzquierdo > UMBRAL_OBSTACULO) {
            // Obstaculo detectado : Paramos
            pwmWrite(PinMotorDer,PARADA);
            pwmWrite(PinMotorIz,PARADA);
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


            if(infraD && infraI) {
                //ir recto
                pwmD = 200;
                pwmI = 100;
            }
            else if(infraD && !infraI) {
                //girar a la derecha
                pwmD = 160;
                pwmI = 100;
            }
            else if(!infraD && infraI) {
                //giro a la izquierda
                pwmD = 200;
                pwmI = 140;
            }
            else {
                //retroceso
                pwmD = 100;
                pwmI = 200;
            }

            pwmWrite(PinMotorDer,pwmD);
            pwmWrite(PinMotorIz,pwmI);
        }
        if (tcycle < tcontrol)
            usleep((tcontrol - tcycle));
        else
            printf("Ciclo más largo que el tiempo de control\n");

    }
}
