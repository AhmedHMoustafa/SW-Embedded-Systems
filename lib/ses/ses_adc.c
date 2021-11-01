/* INCLUDES ******************************************************************/
#include "ses_common.h"
#include "ses_adc.h"


/* DEFINES & MACROS **********************************************************/
#define SENSORS_PORT       	PORTF
#define TEMP_PIN         	2
#define LIGHT_PIN         	4
#define JOYSTICK_PIN       	5
#define MICROPHONE_PIN      0

#define ADC_VREF_SRC        0xC0 // Ref. Voltage = 1.6 V

#define ADC_TEMP_FACTOR     50
#define ADC_TEMP_MAX        ADC_TEMP_FACTOR*400        
#define ADC_TEMP_RAW_MAX    256
#define ADC_TEMP_MIN        ADC_TEMP_FACTOR*200
#define ADC_TEMP_RAW_MIN    481


/* FUNCTION DEFINITION *******************************************************/

void adc_init(void){

    //Configure pins as inputs
    DDR_REGISTER(SENSORS_PORT) &= ~(1 << TEMP_PIN);
    DDR_REGISTER(SENSORS_PORT) &= ~(1 << LIGHT_PIN);
    DDR_REGISTER(SENSORS_PORT) &= ~(1 << JOYSTICK_PIN);
    DDR_REGISTER(SENSORS_PORT) &= ~(0x03 << MICROPHONE_PIN);


    //Deactivate internal pull-up resistors
    SENSORS_PORT &= ~(1 << TEMP_PIN);
    SENSORS_PORT &= ~(1 << LIGHT_PIN);
    SENSORS_PORT &= ~(1 << JOYSTICK_PIN);
    SENSORS_PORT &= ~(0x03 << MICROPHONE_PIN);

    //Disable ADC
    ADCSRA &= ~(1 << ADEN);

    //Disable power reduction mode
    PRR0 &= ~(1 << PRADC);

    //Set ADC result to be right adjusted
    ADMUX &= ~(1<<ADLAR);

    //Configure ADMUX -- Select reference voltage
    ADMUX |= ADC_VREF_SRC;

    //MUX5 Gain Selection Bit
    ADCSRB &= ~(1 << MUX5);

    //Disable auto triggering
    ADCSRA &= ~(1<<ADATE);

    //Set prescale
    ADCSRA |= ADC_PRESCALE;

    //Enable ADC
    ADCSRA |= (1 << ADEN);

}

uint16_t adc_read(uint8_t adc_channel){

    if(adc_channel  < ADC_NUM){
    
        //Clear channel
        ADMUX &= ~(0x1F<<MUX0); 

        //Select channel
        ADMUX |= (adc_channel & 0x1F);

        //Start Conversion
        ADCSRA |= (1 << ADSC);

        //Poll for conversion end
        while(((ADCSRA >> ADSC) & 1)){
        }

        return ADC;
        
    }else{
        return ADC_INVALID_CHANNEL;
    }
}

int16_t adc_getTemperature(){

    int16_t adcVal = adc_read(ADC_TEMP_CH);
    int16_t slope = (ADC_TEMP_MAX - ADC_TEMP_MIN) / (ADC_TEMP_RAW_MAX - ADC_TEMP_RAW_MIN);
    int16_t offset = ADC_TEMP_MAX - (ADC_TEMP_RAW_MAX * slope);
    return (adcVal * slope + offset) / ADC_TEMP_FACTOR;
}