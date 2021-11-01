#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define NO_OF_BITS   8

size_t reverseBits(uint8_t var){
    uint8_t temp = 0;
    for (uint8_t i=0 ; i< NO_OF_BITS ; ++i){
        temp |= (( var >> i) & 1) << (NO_OF_BITS-1 -i);
    }
    return temp;
}
int main(void){

    uint8_t var;
    printf("please enter your variable number:  ");
    scanf("%d", &var);
    printf("the number after reversing the bits is %d\n", reverseBits(var)); 
}