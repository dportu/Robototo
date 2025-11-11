//gcc practica_1.c -program -l wiringPi
//./program

#include <stdio.h>
#include <wiringPi.h>



//BUTTONS
#define BUTTON1 30
#define BUTTON2 31
#define BUTTON3 21

//LEDS
#define LED1 22
#define LED2 24
#define LED3 28

int main() {
    wiringPiSetup ();

    //SW1
    pinMode (BUTTON1, INPUT);
    //SW2
    pinMode (BUTTON2, INPUT);
    //SW3
    pinMode (BUTTON3, INPUT);

    //LED1
    pinMode (LED1, OUTPUT);
    //LED2
    pinMode (LED2, OUTPUT);
    //LED3
    pinMode (LED3, OUTPUT);



    for(;;) {
        if(digitalRead(BUTTON1)) {
            digitalWrite(LED1, HIGH);
        }
        else {
            digitalWrite(LED1, LOW);
        }

        if(digitalRead(BUTTON2)) {
            digitalWrite(LED2, HIGH);
        }
        else {
            digitalWrite(LED2, LOW);
        }

        if(digitalRead(BUTTON3)) {
            digitalWrite(LED3, HIGH);
        }
        else {
            digitalWrite(LED3, LOW);
        }
        //delay(100);
    }
}


