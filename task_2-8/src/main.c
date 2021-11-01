#include <ses_common.h>
#include <ses_adc.h>
#include "ses_uart.h"
int main(void) {
    
    uint16_t valLight = 0;
    int16_t valTemp = 0;
    uart_init(57600);;
    adc_init();

    while(1){

        valLight = adc_read(ADC_LIGHT_CH);
        valTemp = adc_getTemperature();
        fprintf(uartout, "Temp = %d, Light = %d \n", valTemp, valLight);
        _delay_ms(2500);
    }

}
