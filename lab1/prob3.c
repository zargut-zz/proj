#include <stdio.h>

void addTwoUnsignedBytes(unsigned char b1, unsigned char b2)
{
   unsigned char result = b1 + b2;
   
   printf("0x%02X + 0x%02X = 0x%02X \n", b1, b2, result);
}

int main()
{
   //0x20 + 0x35  (in dec: 32, 53)
   addTwoUnsignedBytes(0x20, 0x35);
   //0x80 + 0x7F
   addTwoUnsignedBytes(0x80, 0x7F);
   //0x80 + 0xFF
   addTwoUnsignedBytes(0x80, 0xFF);
   //0xFF + 0x01
   addTwoUnsignedBytes(0xFF, 0x01);
   
   printf("\n");
   
   return 0;
}
