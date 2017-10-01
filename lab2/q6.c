#include<stdio.h>

typedef struct _intfloat{
   unsigned int sign;
   int exponent;
   int fraction;
   }INTFLOAT, *INTFLOAT_PTR;

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
   int count = 0;
   if(x -> fraction == 0){
      normalized = 1;
   }
   while(normalized != 1){
      count+= 1;
      printf("Count: %d\n",count);
      printf("current bit: %X\n, fraction: %X\n, exponent: %X\n", cur,x->fraction,x->exponent); 
      normalized = normal(x->fraction); 
      if(normalized == 1){
          break;
      }
      x->fraction = x->fraction<<2;
      x -> exponent--;
   }
}  

int pack_value(INTFLOAT_PTR xp)
{
   int result;
   unsigned int bits;
   unsigned int  s;
   int count = 0;
   s = xp -> fraction;
   
   s= s>>31&(0x00000001);

   if(xp -> fraction == 0 && xp-> exponent == 0){
      result = 0x00000000;
      return result;
   }
   int exponent = (xp -> exponent-1) + 127;
   int fraction = xp->fraction;
   bits = exponent<<23  ;
   if(s == 1){
      fraction = ~(xp->fraction)+1;
      bits = bits | 1 << 31;
   } 
   fraction = ((fraction << 2)>>9) & 0x7FFFFF; 
   bits  = bits | fraction;
   result = bits;
   return result;   
} 

float fsub(float a, float b)
{
   INTFLOAT ax, bx;
   INTFLOAT result;
   int diffexp;
   float retval;
   
   extract_float(&ax, a);
   extract_float(&bx, b);
   
   diffexp = (ax.exponent - bx.exponent);
   if (diffexp > 0)
   {
      bx.fraction >>= diffexp;
      bx.exponent += diffexp;
   )

   if (diffexp < 0)
   {
      ax.fraction >>= diffexp;
      ax.exponent += diffexp;
   }
   
   result.fraction = (ax.fraction << 1) - (bx.fraction << 1);
   result.exponent = ax.exponent - 1;
   
   normalize(&result);
   
   retval = pack_value(&result);

   printf("Diff: 0x%08X\n");
       
}

int main()
{
   printf("6a: 0x40400000 and 0x3F800000 (3 - 1)\n");
   printf("Diff: 0x%08X\n", fsub(0x40400000, 0x3F800000));

   printf("6b: 0x40400000 and 0xBF800000 (3 - (-1))\n");
   printf("Diff: 0x%08X\n", fsub(0x40400000, 0xBF800000));

   printf("6c: 0x40000000 and 0x40000000\n");
   printf("Diff: 0x%08X\n", fsub(0x40000000, 0x40000000));
   
   return 1;
}


