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
      x -> sign = (floatbits & 0x80000000);
      //x->sign = (floatbits >> 31);
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
/*
 * PART 3: Packs the value back to IEEE 754 format. Parameter: INFLOAT_PTR
 */

int pack_value(INTFLOAT_PTR xp)
{
   int result;
   unsigned int bits;
   unsigned int  s;
   int count = 0;
   s = xp -> fraction;
   //assigns the signed bit
   s= s>>31&(0x00000001);
   //check for special condictions
   if(xp -> fraction == 0 && xp-> exponent == 0){
      result = 0x00000000;
      return result;
   }
   //expects right shift and adds bias
   int exponent = (xp -> exponent-1) + 127;
   int fraction = xp->fraction;
   bits = exponent<<23  ;
   if(s == 1){
      fraction = ~(xp->fraction)+1;
      bits = bits | 1 << 31;
   } 
   //shifts fraction section to the last 23 bits of the float
   fraction = ((fraction << 2)>>9) & 0x7FFFFF; 
   bits  = bits | fraction;
   result = bits;
   return result;   
}

int normal(int x)
{
   static unsigned int mask[] = {2147483648, 1073741824};
   if(((x & mask[0]) != 0) && (x & mask[1]) != 0)
   {
      return 0;
   }else if(((x & mask[0]) == 0) && (x & mask[1]) == 0)
   {
      return 0;
   }
   return 1;

}
void normalize(INTFLOAT_PTR x)
{
   int normalized = 0;
   int cur;
   if(x -> fraction == 0){
      normalized = 1;
   }
   while(normalized != 1){
      normalized = normal(x->fraction); 
      if(normalized == 1){
          break;
      }
      x->fraction = x->fraction<<1;
      printf("0x%X\n", x->fraction);
      x -> exponent--;
   }
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
   INTFLOAT i; 
   INTFLOAT_PTR pointer = &i;
   printf ("2a. \n");
   extract_float(pointer, 6.25000000);
   printf ("2b. \n");
   extract_float(pointer, -128.000000);
   printf ("2c. \n");
   extract_float(pointer, 0.12500000);
   printf ("2d. \n");
   extract_float(pointer, 0.33333334);
   
   //Question 3: Packing Values
   INTFLOAT x;
   INTFLOAT_PTR xp = &x; 
   
   printf ("3a. \n");
   x.exponent = 0x03;
   x.fraction = 0x60000000;
   printf("INTFLOAT fraction = 0x%X , exponent = %d\n",x.fraction, x.exponent);
   printf("IEEE 754 Hex: 0x%X\n", pack_value(xp));
   printf ("3b. \n");
   x.exponent = 0x08;
   x.fraction = 0xC0000000;
   printf("INTFLOAT fraction = %X , exponent = %X\n",x.fraction, x.exponent);
   printf("IEEE 754 Hex: 0x%X\n", pack_value(xp));
   printf ("3c. \n");
   x.exponent = -2;
   x.fraction = 0x00000000;
   printf("INTFLOAT fraction = 0x%X , exponent = %d\n",x.fraction, x.exponent);
   printf("IEEE 754 Hex: 0x%X\n", pack_value(xp));
   printf ("3d. \n");
   x.exponent = -1;
   x.fraction = 0x55555580;
   printf("INTFLOAT fraction = 0x%X , exponent = %d\n",x.fraction, x.exponent);
   printf("IEEE 754 Hex: 0x%X\n", pack_value(xp));

   //Question 4: Normalization
   INTFLOAT x_2;
   INTFLOAT_PTR xp_2 = &x_2;

   printf ("4a. \n");
   x_2.exponent = 0x01;
   x_2.fraction = 0x40000000;

   normalize(xp_2);
   printf("exponent = 0x00000001, fraction =0x40000000\nResult: exponent:0x%X fraction: 0x%X\n", x_2.exponent, x_2.fraction);

   printf ("4b. \n");
   x_2.exponent = 0x00000000;
   x_2.fraction = 0x00200000;

   normalize(xp_2);
   printf("exponent = 0x00000000, fraction = 0x00200000 \nResult: exponent:0x%X fraction: 0x%X\n", x_2.exponent, x_2.fraction);

   printf ("4c. \n");
   x_2.exponent = 0x0000000C;
   x_2.fraction = 0xFFC00000;

   normalize(xp_2);
   printf("exponent = 0x0000000C, fraction = 0xFFC00000\nResult: exponent:0x%X fraction: 0x%X\n", x_2.exponent, x_2.fraction);

   printf ("4d. \n");
   x_2.exponent = 0xFFFFFFF8;
   x_2.fraction = 0x02000000;

   normalize(xp_2);
   printf("exponent = 0xFFFFFFF8, fraction = 0x02000000\nResult: exponent:0x%X fraction: 0x%X\n", x_2.exponent, x_2.fraction);
  
  
   return 0;
}
