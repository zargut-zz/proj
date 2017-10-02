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

/*
 * PART 2: Unpack float value from the IEEE 754 format 
 */
void extract_float(INTFLOAT_PTR x, float f)
{
   unsigned floatbits;
   //float value;
   // If float is 0
   if (f == 0)
   {
      x -> sign = 0;
      x -> exponent = 0;
      x -> fraction = 0;
   }
   else
   {
      //Casts the float as an unsigned int so can be worked on bit by bit
      floatbits = * (unsigned int *) &f;
      //printf ("Test case: 0x%8X\n", floatbits);
      //Gets sign of the float
      x -> sign = (floatbits & 0x80000000);
      //x->sign = (floatbits >> 31);
      //printf ("Sign: 0x%08X\n", x->sign);
      //Gets exponent value of the float
      x -> exponent = (floatbits >> 23)& 0x000000FF;
      //printf ("exp1: 0x%08X\n", x->exponent);
      x -> exponent -= 0x0000007F;
      //Gets fraction value of the float
      x -> fraction = (floatbits & 0x007FFFFF);      
      x -> fraction = (x->fraction<<9);
      x -> fraction = (x->fraction | 0x40000000);
      //If sign is 1, fraction value is written in 2's complement
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

/*
 * PART 4: Normalization
 */

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

/* 
 * PART 5: Add IEEE 754 formatted floats
 */


/* 
 * PART 6: IEEE 754 formatted floats subtraction
 */
float fsub(float a, float b)
{
   INTFLOAT ax, bx;
   INTFLOAT result;
   int diffexp;
   int retval;
   
   extract_float(&ax, a);
   extract_float(&bx, b);
   
   diffexp = (ax.exponent - bx.exponent);
   if (diffexp > 0)
   {
      printf ("here");
      bx.fraction >>= diffexp;
      bx.exponent += diffexp;
      printf ("Exponent: %d", bx.exponent);
   } 

   if (diffexp < 0)
   {
      printf ("b < a");
      ax.fraction >>= diffexp;
      ax.exponent += diffexp;
   }
    
   result.fraction = (ax.fraction << 1) - (bx.fraction << 1);

   //printf ("rfraction: 0x%08X\n", result.fraction);
   result.exponent = ax.exponent - 1;
   //printf ("aexponent: %d\n", ax.exponent);
   //printf ("rexponent: %d\n", result.exponent);
   normalize(&result);
   
   //printf("test: 0x%08X\n", result.fraction);   
 
   retval = pack_value(&result);

   //printf ("answer: %d\n", retval);

   //printf("Diff: 0x%08X\n");
   return retval;
       
}

int fmul(float a, float b)
{
   INTFLOAT x;
   INTFLOAT_PTR xp = &x;
   INTFLOAT y;
   INTFLOAT_PTR yp = &y;
   
   INTFLOAT result;
   INTFLOAT_PTR result_ptr = &result;
   extract_float(xp, a);
   extract_float(yp, b);
   
   printf("fraction 1: %X fractiokn 2: %X\n", ((x.fraction>>7)&0x7fffff), ((y.fraction>>7)&0x7fffff));
    
   result.fraction = (((((x.fraction>>7)&0x7fffff))+1)*(((y.fraction>>7)&0x7fffff)+1));
   printf("result: %X\n", result.fraction);
   printf("exp 1: %X exp 2: %X\n", x.exponent, y.exponent); 
   result.exponent = x.exponent+y.exponent;
   printf("result exp: %X\n", result.exponent);
   
   normalize(result_ptr);
   return pack_value(result_ptr);
      
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
   
   //Question 5
   
   //Question 6
   printf("\n6a: 0x40400000 and 0x3F800000 (3 - 1)\n");
   printf("Diff: 0x%08X\n", fsub(3, 1));

   printf("\n6b: 0x40400000 and 0xBF800000 (3 - (-1))\n");
   printf("Diff: 0x%08X\n", fsub(3, -1));

   printf("\n6c: 0x40000000 and 0x40000000\n");
   printf("Diff: 0x%08X\n", fsub(2, 2));
   
   //Question 7
   float a_7 = 2.5;

   printf("7a) 0x40200000 and 0x40200000 (2.5 x 2.5)\n Result: %X", fmul(a_7,a_7)); 
   return 0;
}
