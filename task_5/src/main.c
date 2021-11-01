#include "ses_led.h"
#include "ses_common.h"
#include "ses_scheduler.h"
#include "ses_lcd.h"
#include "ses_pwm.h"
#include "ses_motorFrequency.h"
#include "ses_button.h"
#include "ses_timer.h"

static taskDescriptor task1;
static volatile pButtonCallback joyStickCallback = NULL;
static uint8_t dutyCycle = 170;
static bool firstPressed = false;


void motor_stop(void){   
    pwm_setDutyCycle(0);
    PORTG &= ~(1<<MOTOR_CONTROL_PIN);  // Clear the pin
}

void motor_init(void){

    DDR_REGISTER(PORTG) |= (1<<MOTOR_CONTROL_PIN); // Set PG5/OC0B pin as external output
    motor_stop();

}

void motor_speed(){

    // Check if first (start motor) or second (stop motor) button press
    if(firstPressed == false){
        pwm_setDutyCycle(dutyCycle);
        firstPressed = true;
    
    } 
    else {       
        motor_stop();
        firstPressed = false;
    }
}

void lcdPrint(){
    lcd_clear();
    lcd_setCursor(4,1);
    fprintf(lcdout, "Freq: %d rpm",(motorFrequency_getRecent()*60));
    lcd_setCursor(4,2);
    fprintf(lcdout, "Median: %d rpm",(motorFrequency_getMedian()*60));
}

void task1Config(){
    task1.task = &lcdPrint;
	task1.param = NULL;
	task1.expire = 1000;
	task1.period = 1000;
    scheduler_add(&task1);
}

int main(void){

    lcd_init();
    button_init(true);
    motor_init();
    pwm_init();
    motorFrequency_init();
    timer5_setCallback(&led_greenOn);

    button_setJoystickButtonCallback(&motor_speed);
    
    task1Config();

    scheduler_init();
    scheduler_run();

}