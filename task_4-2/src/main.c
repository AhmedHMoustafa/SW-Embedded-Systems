/*INCLUDES ************************************************************/
#include "main.h"

/* PRIVATE VARIABLES **************************************************/
//Declare tasks
static taskDescriptor task1;
static taskDescriptor task2;
static taskDescriptor task3;
static taskDescriptor task4;

//Flags to track button presses
static bool joystickFirstPressed = false;
static bool rotaryFirstPressed = false;

//Initialize time variables for stopwatch
static uint8_t tenths = 0;
static uint8_t seconds = 0;

/*FUNCTION DEFINITION *************************************************/
void ledToggleTask (void* colorSelect){

    //select LED to toggle
    switch(*(color*)colorSelect){
        case 0: led_redToggle(); break;
        case 1: led_yellowToggle(); break;
        case 2: led_greenToggle(); break;
        default: return;
    }
}

void debounceButtonTask(){
    button_checkState();
}

void joystickPressed(){

    //check if first already presed or not pressed
    if(joystickFirstPressed){               //first already pressed
        led_yellowOff();
        joystickFirstPressed = false;
        scheduler_remove(&task3);
    }else{                                  //not pressed
        led_yellowOn();
        joystickFirstPressed = true;
        scheduler_add(&task3);
    }
}

void turnYellowOff(){
    led_yellowOff();
    joystickFirstPressed = false;
    scheduler_remove(&task3);
}

void rotaryPressed(){

    if(rotaryFirstPressed){         //stop the stopwatch if already pressed

        rotaryFirstPressed = false;
        scheduler_remove(&task4);
    }else{                          //start the stopwatch

        rotaryFirstPressed = true;
        scheduler_add(&task4);
    }
}

void stopwatchOn(){

    tenths++;

    if(tenths == 10){
        tenths = 0;
        seconds++;
    }

    LCDprint(seconds,tenths);
}

void LCDprint(uint8_t s, uint8_t t){
    lcd_clear();
	lcd_setCursor(4,1);
	fprintf(lcdout, "Time: %d.%d", s, t);
}

/* configure task1 to toggle the green led at 0.5Hz */
void task1Config(){
    color ledColor = GREEN;
	task1.task = &ledToggleTask;
	task1.param = (void *) &ledColor;
	task1.expire = 2000;
	task1.period = 2000;
    scheduler_add(&task1);
}

/* configure Task2 to debounce the buttons every 5m sec */
void task2Config(){
    task2.task = &debounceButtonTask;
	task2.param = NULL;
	task2.expire = 5;
	task2.period = 5;
    scheduler_add(&task2);
}

/* configure task3 to turn on the yellow led when joystick is pressed 
 * otherwise turns it off when the button is pressed again after 5 sec */
void task3Config(){
    button_setJoystickButtonCallback(&joystickPressed);
	task3.task = &turnYellowOff;
	task3.param = NULL;
	task3.expire = 5000;
	task3.period = 5000;
}


/* configure task4 to start&stop the stopwatch by pressing the rotary button */ 
void task4Config(){
    button_setRotaryButtonCallback(&rotaryPressed);
    task4.task = &stopwatchOn;
    task4.param = NULL;
    task4.expire = 100;
    task4.period = 100;
}

/* MAIN ****************************************************************/
int main(void) {
    
    //Initialize peripherials
    lcd_init();
    led_redInit();
    led_greenInit();
    led_yellowInit();
    button_init(true);
    
    //Configure Tasks
    task1Config();
    task2Config();
    task3Config();
    task4Config();

    //Initialize and run scheduler
    scheduler_init();
    scheduler_run();
}
