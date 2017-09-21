#include <stdio.h>

unsigned int arbitrary_byte_add(unsigned char *result, unsigned char *a1, unsigned char *a2, int size, unsigned int carry_in)
{
   *result = *a1 + *a2 + carry_in;
   unsigned int carryout = 0;

   // compare the sum to one of the operands; if it is less
   // than the operand, then a carry occurred
   if(result < a1 || result < a2)
   {
      *result = *result + 0x10;
      carryout = 1;
   }
   printf("0x%02X",*result);
   return carryout;
}

int main()
{
    unsigned char result = 0;
    unsigned char  a1 = 0x01, a2 = 0x00;
    
    unsigned int answer = arbitrary_byte_add(&result, &a1, &a2, 3, 0);
    a1 = a2 = 0x00;
    unsigned int answer1 = arbitrary_byte_add(&result, &a1, &a2, sizeof(result) + 2, answer);
    a1 = 0x00;
    a2 = 0xFF;
    unsigned int answer2 = arbitrary_byte_add(&result, &a1, &a2, sizeof(result) + 2, answer1);
    a1 = 0x00;
    a2 = 0xFF;
    unsigned int answer3 = arbitrary_byte_add(&result, &a1, &a2, sizeof(result) + 2, answer2);
    a1 = 0x44;
    a2 = 0x30;
    unsigned int answer4 = arbitrary_byte_add(&result, &a1, &a2, sizeof(result) + 2, answer3);
    //printf("\n%X", result);
    printf("\nCarry: %d \n", answer4);
    
    return 0;
}   
