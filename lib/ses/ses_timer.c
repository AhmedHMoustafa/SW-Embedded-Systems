/* INCLUDES ******************************************************************/
#include "ses_timer.h"

/* DEFINES & MACROS **********************************************************/
#define TIMER1_CYC_FOR_5MILLISEC    0x270F 
#define TIMER2_CYC_FOR_1MILLISEC	0xF9
#define TIMER5_CYC_FOR_1SEC			0xF423		

static volatile pTimerCallback timer2 = NULL;
static volatile pTimerCallback timer1 = NULL;
static volatile pTimerCallback timer5 = NULL;

/*FUNCTION DEFINITION ********************************************************/
void timer2_setCallback(pTimerCallback cb) {
	timer2 = cb;
}

void timer2_start() {

	TCNT2 = 0x00;						// Clear counter
	TCCR2A &= ~(1 << WGM20); 			//
	TCCR2A |= (1 << WGM21);				// Setting to OTC mode
	TCCR2B &= ~(1 << WGM22);			//

	TCCR2B |= (1 << CS22);				// Set prescaler to 64

	OCR2A |= TIMER2_CYC_FOR_1MILLISEC;  // Set value to interrupt every 1ms

	TIFR2 |= (1 << OCF2A); 				// Clear Compare A flag interrupt

	TIMSK2 |= (1 << OCIE2A);			// Enable Compare A match interrupt

}


void timer2_stop() {
    // TIMSK2 &= ~(1 << OCIE2A);			// Disable Compare A match interrupt
	TCCR2B &= ~(0x07 << CS20);			// No clock source
}

void timer1_setCallback(pTimerCallback cb) {
	timer1 = cb;
}


void timer1_start() {

	TCNT1 = 0x00;				// Clear counter
	TCCR1B &= ~(1 << WGM13); 	//
	TCCR1B |= (1 << WGM12); 	// Setting to OTC mode
	TCCR1A &= ~(1 << WGM11); 	//
	TCCR1A &= ~(1 << WGM10); 	//

	TCCR1B |= (1 << CS11); 		// Set prescaler to 8

	//Set value to interrupt every 5ms
	OCR1AH |= ((TIMER1_CYC_FOR_5MILLISEC & 0xFF00) >> 8); // Load high value first
	OCR1AL |= (TIMER1_CYC_FOR_5MILLISEC & 0xFF);  		  // Load rest of the bits

	TIFR1 |= (1 << OCF1A); 		// Clear Compare A flag interrupt

	TIMSK1 |= (1 << OCIE1A);	// Enable Compare A match interrupt

}

void timer1_stop() {
	// TIMSK1 &= ~(1 << OCIE1A);  	// Disable Compare A match interrupt
	TCCR1B &= ~(0x07 << CS10);			// No clock source
}

void timer5_start(){
    TCNT5 = 0x00;

	TCCR5B |= (1 << WGM52);					// CTC Mode

	TCCR5B |= (1 << CS50) | (1 << CS51);	// Set prescaler to 64

	OCR5A = TIMER5_CYC_FOR_1SEC; 			// Set OCR5A to a value for 1 second

	TIFR5 |= (1 << OCF5A); 					// Clear Compare A flag interrupt

	TIMSK5 |= (1 << OCIE5A);				// Enable Compare A match interrupt
}

void timer5_stop(){
	TCCR5B &= ~(0x07 << CS50);			// No clock source
}


void timer5_setCallback(pTimerCallback cb) {
	timer5 = cb;
}

uint16_t timer5_getCount(){
	return TCNT5;
}

// uint8_t getHour(){
// 	return time_t.hour;
// }

// void incrementHour(){
// 	(time_t.hour)++;
// }

// void setHour(uint8_t hour){
// 	time_t.hour = hour;
// }

// uint8_t getMinute(){
// 	return time_t.minute;
// }

// void incrementMinute(){
// 	(time_t.minute)++;
// }

// void setMinute(uint8_t minute){
// 	time_t.minute = minute;
// }

// uint8_t getSecond(){
// 	return time_t.second;
// }

// void incrementSecond(){
// 	(time_t.second)++;
// }

// void setSecond(uint8_t second){
// 	time_t.second = second;
// }

// uint16_t getMilli(){
// 	return time_t.milli;
// }

// void incrementMilli(){
// 	(time_t.milli)++;
// }

// void setMilli(uint16_t milli){
// 	time_t.milli = milli;
// }


ISR(TIMER5_COMPA_vect){

	if(timer5 != NULL){ 

		timer5();
		motorFreq = 0;
		arrIndex = (arrIndex + 1) % NO_OF_SAMPLES;  // Increment the index
		motorFreqArr[arrIndex] = motorFreq;
	}

}

ISR(TIMER1_COMPA_vect) {

	if(timer1 != NULL){ 
		timer1();
	}
}

ISR(TIMER2_COMPA_vect) {

	if(timer2 != NULL){ 
		timer2();
	}

	// currTime++;
	// setMilli(currTime);

	// if(getMilli() == 1000){
	// 	incrementSecond();
	// 	currTime = 0;
	// 	setMilli(currTime);

	// 	if(getSecond() == 60){
	// 		incrementMinute();
	// 		setSecond(0);

	// 		if(getMinute == 60){
	// 			incrementHour();
	// 			setMinute(0);
	// 		}
	// 	}
	// }
	
	
}
