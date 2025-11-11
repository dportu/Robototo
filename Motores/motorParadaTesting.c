#include <wiringPi.h>
#include <unistd.h>
#include <stdlib.h>
#define PinMotor0 23 //pwm_1 BCM13 Fisico 33
#define PinMotor1 1 //for pwm_0 BCM18 Fisco12


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
        int i = 140;
        while (i < 200) {
                // Giro
                pwmWrite(PinMotor0,i);
                pwmWrite(PinMotor1,i);
                printf("Valor de i = %d\n\n", i);
                usleep(100000);
                i++;
        }
        
        return 1;
}
// 150 = stop
// 100 = full back
// 200 = full
