#include <ses_common.h>
#include <ses_button.h>
#include <ses_led.h>

int main(void) {

    led_redInit();
    led_greenInit();

    pButtonCallback redToggle = &led_redToggle;
    pButtonCallback greenToggle = &led_greenToggle;
    button_init();
    
    button_setJoystickButtonCallback(redToggle);
    button_setRotaryButtonCallback(greenToggle);
    sei();

    while(1){

    }

}
