#include <wiringPi.h>
#include <unistd.h>
#include <stdlib.h>
#define PinMotor0 23 // pwm_1 BCM13 Fisico 33 CONECTAR A B13
#define PinMotor1 26 // pwm_0 BCM12 Fisico 32 CONECTAR A B12


int main() {
        if(wiringPiSetup()==-1) {
                exit(1);
        }
        // Set up de pwm
        pinMode(PinMotor0,PWM_OUTPUT);
        pinMode(PinMotor1,PWM_OUTPUT);
        pwmSetMode(PWM_MODE_MS);
        pwmSetClock(192); //clock at 50Hz
        pwmSetRange(2000); //range at 2000
        
        // Bucle de demostracion de giro en sentido horario, antihorario y parada
        while (1) {
                // Giro
                pwmWrite(PinMotor0,100);
                pwmWrite(PinMotor1,100);
                printf("Giro en sentido horario\n");
                usleep(1500000);
                // Parada
                pwmWrite(PinMotor0,150);
                pwmWrite(PinMotor1,150);
                printf("Parada\n")
                usleep(1500000);
                // Giro
                pwmWrite(PinMotor0,200);
                pwmWrite(PinMotor1,200);
                printf("Giro en sentido antihorario\n")
                usleep(1500000);
                // Parada
                pwmWrite(PinMotor0,150);
                pwmWrite(PinMotor1,150);
                printf("Parada\n")
                usleep(1500000);
        }

        return 1;
}