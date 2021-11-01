#include <stdint.h>
#include <avr/io.h>
#include <math.h> 

void wait (uint16_t millis)
{
        uint32_t count_num= (-4 + millis * pow(10,-3) * 16 * pow(10,6)) / 7; 
        uint32_t i; 
        
    for (i = count_num; i > 0 ; i--) {
         //prevent code optimization by using inline assembler
        asm volatile ( "nop" ); // one cycle with no operation
    }       
}

int main(void) {

   DDRG |= 0x02;
	while (1) {
		wait(1000);
		PORTG ^= 0x02;
	}
	return 0;

}
