#include "ses_lcd.h"
#include "ses_uart.h"
#include <util/delay.h>



int main(void) {
    uart_init(57600);
    lcd_init();
    
    while(1){

        fprintf(uartout, "START\n");
        fprintf(lcdout, "START");
        _delay_ms(1000);

    }

}
