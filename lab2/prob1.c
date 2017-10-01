#include <stdio.h>

unsigned int umultiply(unsigned int a, unsigned int b);
unsigned int umultiply2(unsigned int a, unsigned int b);

int main()
{
   unsigned int a = 0x0001;
   unsigned int b = 0x0001;
   umultiply(a, b);
   
   printf("\n");
   
   a = 0x0001;
   b = 0xFFFF;
   umultiply(a, b);
   
   printf("\n");
   
   a = 0x8000;
   b = 0x0001;
   umultiply(a, b);
   
   printf("\n");
   
   a = 0x4000;
   b = 0x4000;
   umultiply(a, b);
   
   printf("\n");
   
   a = 0x8000;
   b = 0x8000;
   umultiply(a, b);
   
   return 0;
}


unsigned int umultiply(unsigned int a, unsigned int b)
{
   unsigned int origA = a;
   unsigned int origB = b;
   
   /*
    * Shift right and add
    */
   
   unsigned int c = 0;
   while(a != 0)
   {
      if(a & 1)      // If the lowest order bit is set in A
         c += b;
      //OR        -> x <<= 1;
                  // y >>= 1;  instead of what I have down below
      a = a >> 1;
      b = b + b;  // Alternatively, left-shift by 1 bit
   }
   
   printf("%.2u * %.2u = %.2u\n", origA, origB, c);
   printf("0x%02X * 0x%02X = 0x%02X\n", origA, origB, c);
   
   return c;
   //printf("0x%02X + 0x%02X = 0x%02X \n", b1, b2, result);
}





