/*
 * Lab 2: Binary Data Representation and Arithmetic
 * Authors: Zarah Gutierrez, Rebecca Dong, Prachi Mehta
 * CPE 315
 * 
 */
#include<stdio.h>

typedef struct _intfloat{
   unsigned int sign;
   int exponent;
   int fraction;
   }INTFLOAT, *INTFLOAT_PTR;

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

void extract_float(INTFLOAT_PTR x, float f)
{
   unsigned floatbits;
   //float value;

   if (f == 0)
   {
      x -> sign = 0;
      x -> exponent = 0;
      x -> fraction = 0;
   }
   else
   {
      floatbits = * (unsigned int *) &f;
      //printf ("Floatbits: 0x%8X\n", floatbits);
      //x -> sign = (floatbits & 0x80000000);
      x->sign = (floatbits >> 31);
      //printf ("Sign: 0x%08X\n", x->sign);
      
      x -> exponent = (floatbits >> 23)& 0x000000FF;
      //printf ("exp1: 0x%08X\n", x->exponent);
      x -> exponent -= 0x0000007F;

      x -> fraction = (floatbits & 0x007FFFFF);      
      
      if (x->sign == 0x80000000)
      {
         x -> fraction = (~(x -> fraction)) + 1;
         printf("NEGATIVE, ");
      }
      
   }
   printf ("Test case: 0x%8X\n", floatbits);
   printf ("Float is: %f\n", f);
   printf ("Fraction is: 0x%08X\n", x -> fraction);
   printf ("Exponent is: %d\n", x -> exponent);
   printf("\n"); 
}

int main()
{
   //Question 1
   printf("1a: \n");
   unsigned int a = 0x0001;
   unsigned int b = 0x0001;
   umultiply(a, b);
   printf("\n");
   
   printf("1b: \n");
   a = 0x0001;
   b = 0xFFFF;
   umultiply(a, b);
   
   printf("\n");
   
   printf("1c: \n");
   a = 0x8000;
   b = 0x0001;
   umultiply(a, b);
   
   printf("\n");
   
   printf("1d: \n");
   a = 0x4000;
   b = 0x4000;
   umultiply(a, b);
   
   printf("\n");
   
   printf("1e: \n");
   a = 0x8000;
   b = 0x8000;
   umultiply(a, b);
   printf("\n");
   
   //Question 2
   INTFLOAT INTFLOAT_PTR;
   printf ("2a. \n");
   extract_float(&INTFLOAT_PTR, 6.25000000);
   printf ("2b. \n");
   extract_float(&INTFLOAT_PTR, -128.000000);
   printf ("2c. \n");
   extract_float(&INTFLOAT_PTR, 0.12500000);
   printf ("2d. \n");
   extract_float(&INTFLOAT_PTR, 0.33333334);
   
   //Question 3
  
  
   return 1;
}
