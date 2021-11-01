#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

size_t setThree(uint8_t var){
    var |= (1 << 3);
    return var;
}


size_t setFourSix(uint8_t var){
    //var |= (1 << 4 );
   // var |= (1 << 6 );
   var |= 0x50;
   return var;
}

size_t clearTwo(uint8_t var){

 var &= ~(1<<2);
 return var;
}

size_t clearTwoSeven(uint8_t var){

 var &= ~(1<<2);
 var &= ~(1<<7);
 return var;
 
}

size_t toggleThree(uint8_t var){

 var ^= (1<<3);
 return var;
 
}

size_t setTwoClearFiveSeven(uint8_t var){

  var |=(1<<2);
  var &= ~(1<<5);
  var &= ~(1<<7);
  return var;
}

size_t swapBits(uint8_t var){

uint8_t result = 0;
uint8_t bit0 = (var >> 0) & 0x01; // shifting to the rightmost and then masking 
uint8_t bit2 = (var >> 2) & 0x01;
uint8_t bit3 = (var >> 3) & 0x01;
uint8_t bit5 = (var >> 5) & 0x01;

uint8_t swapBit3_5 = (bit3 ^ bit5);
swapBit3_5 = (swapBit3_5 << 3) | (swapBit3_5 << 5);

uint8_t swapBit0_2 = (bit0 ^bit2);
swapBit0_2 = (swapBit0_2 << 0) | (swapBit0_2 << 2);

result = (var ^ swapBit3_5 ) ^ (swapBit0_2);
return result;

}
 
int main(void){
    
    uint8_t var;
    printf("please enter your variable number: ");
    scanf("%d", &var);

    printf("the number after setting bit three becomes %d\n", setThree(var));
    printf("the number after setting bis four and six becomes %d\n", setFourSix(var));
    printf("the number after clearing bit two becomes %d\n", clearTwo(var));
    printf("the number after clearing bits two and seven becomes %d\n", clearTwoSeven(var));
    printf("the number after toggling bit three becomes %d\n", toggleThree(var));
    printf("the number after setting bit two and clearing bits five and seven becomes %d\n", setTwoClearFiveSeven(var));
    printf("the number after swapping bits becomes %d\n", swapBits(var)); 
}