#include <ses_common.h>
#include <ses_led.h>
#include <ses_timer.h>

int softwareCount = 0; // Counter to decrease toggling frequency for timer2

void softwareTimer(void){

    softwareCount++;
    if(softwareCount == 1000){ //Checks if 1000 ms reached
        softwareCount = 0;
        led_yellowToggle();
    }
}

int main(void) {

    led_yellowInit();

    pTimerCallback ledToggle = &softwareTimer;

    timer2_setCallback(ledToggle);

    timer2_start();

    sei();

    while(1){

    }
}


