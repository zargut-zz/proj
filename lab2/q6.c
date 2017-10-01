#include <stdio.h>

typedef struct _intfloat
{	
   unsigned int sign;
   int exponent;
   int fraction;
} INTFLOAT, *INTFLOAT_PTR;

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

float fsub(a,b)
{
   INTFLOAT ax, bx;
   INTFLOAT result;
   int diffexp;
   float retval;

    
}

int main()
{
   return 1;
}
