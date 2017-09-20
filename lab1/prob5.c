#include <stdio.h>

/*
 * Number 5
 */
void addTwoSignedBytes(signed char b1, signed char b2)
{
   signed char result = b1 + b2;
   int overflow = 0;
   
   if(result > 0x7F)
   {
      printf("Above 127, therefore overflow");
   }
   
   if(b1 > 0 && b2 > 0 && result < 0)
   {
      printf("!!!!Overflow:\n");
      overflow = 1;
   }
   if(b1 < 0 && b2 < 0 && result > 0)
   {
      printf("!!!Overflow: \n");
      overflow = 1;
   }
   
   if(b1 > 0 && (b2 > 0x7F - b1))
   {
      printf("Above 7F, therefore overflow");
   }
   
   printf("0x%02X + 0x%02X = 0x%02X Overflow: %d \n\n", b1, b2, result, overflow);
}

/*
 * Number 4
 */
void addTwoUnSignedBytes(unsigned char b1, unsigned char b2)
{
   unsigned char result = b1 + b2;
   int carry = 0;
   
   // compare the sum to one of the operands; if it is less
   // than the operand, then a carry occurred
   if(result < b1 || result < b2)
   {
      //printf("CARRY occured \n");
      carry = 1;
   }
   
   printf("0x%02X + 0x%02X Carry: %d \n", b1, b2, carry);
}



int main()
{
   // PROBLEM #4:
   
   //0x20 + 0x35  (in dec: 32, 53)
   addTwoUnSignedBytes(0x20, 0x35);
   //0x80 + 0x7F
   addTwoUnSignedBytes(0x80, 0x7F);
   //0x80 + 0xFF
   addTwoUnSignedBytes(0x80, 0xFF);
   //0xFF + 0x01
   addTwoUnSignedBytes(0xFF, 0x01);
   
   printf("\n");
   
   
   
   // PROBLEM #5:
   
   addTwoSignedBytes(0x20, 0x35);
   addTwoSignedBytes(0x80, 0x7F);
   addTwoSignedBytes(0x80, 0xFF);
   addTwoSignedBytes(0xFF, 0x01);
   
   
   return 0;
}
