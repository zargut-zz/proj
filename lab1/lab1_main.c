#include<stdio.h>

//PROBLEM 2
void problem2()
{
   unsigned char bytestring[] = {0x41, 0x33, 0x54, 0x80, 0xFF, 0x99, 0x01, 0x78,0x55, 0x20, 0xFE, 0xEE, 0x00, 0x00, 0x00, 0x00};
   int length = sizeof(bytestring)/sizeof(bytestring[0]);

   printf("Unsigned version: \n");
   for (int n = 0; n < length; n++)
   {
      printf("0x%02X, ", bytestring[n]);
   }
   printf("\nShort int version: \n");
   unsigned short int *sb = ((unsigned short int*) (bytestring));
   for (int n = 0; n < 4; n++)
   {
      printf("0x%04X, ", sb[n]);
   }
   printf("\nInt version: \n");
   unsigned int *ib = ((unsigned int*) (bytestring));
   for (int n = 0; n < 2; n++)
   {
      printf("0x%08X, ", ib[n]);
   }
   printf("\nLong int version: \n");
   unsigned long int *lb = ((unsigned long int*) (bytestring));
   printf("0x%lX", lb[0]);

}
//PROBLEM 3
void addTwoUnsignedBytes(unsigned char b1, unsigned char b2)
{
   unsigned char result = b1 + b2;

   printf("0x%02X + 0x%02X = 0x%02X \n", b1, b2, result);
}

/*
 * Number 5
 */
void addTwoSignedBytes(signed char b1, signed char b2)
{
   signed char result = b1 + b2;
   int overflow = 0;

   if(b1 > 0 && b2 > 0 && result < 0)
   {
      overflow = 1;
   }
   if(b1 < 0 && b2 < 0 && result > 0)
   {
      overflow = 1;
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
   printf("\n**********PROBLEM 2**********\n");
   problem2();
   printf("\n");
   
   //PROBLEM #3
   printf("\n**********PROBLEM3**********\n");
   //0x20 + 0x35  (in dec: 32, 53)
   addTwoUnsignedBytes(0x20, 0x35);
   //0x80 + 0x7F
   addTwoUnsignedBytes(0x80, 0x7F);
   //0x80 + 0xFF
   addTwoUnsignedBytes(0x80, 0xFF);
   //0xFF + 0x01
   addTwoUnsignedBytes(0xFF, 0x01);

   printf("\n");
 
   // PROBLEM #4:
   printf("\n**********PROBLEM 4**********\n");
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
   printf("\n**********PROBLEM 5**********\n");
   addTwoSignedBytes(0x20, 0x35);
   addTwoSignedBytes(0x80, 0x7F);
   addTwoSignedBytes(0x80, 0xFF);
   addTwoSignedBytes(0xFF, 0x01);   
   printf("\n");


   return 0;
}
