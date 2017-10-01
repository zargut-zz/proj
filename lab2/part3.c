#include<stdio.h>
#include <math.h>

typedef struct _intfloat {
   unsigned int sign;
   int exponent;
   int fraction;
} INTFLOAT, *INTFLOAT_PTR;

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

int main()
{
   INTFLOAT x;
   INTFLOAT_PTR p = &x;
  
   x.exponent = 0x06;
   x.fraction = 0x90000000;
   int r_1 = pack_value(p); 
   INTFLOAT y;
   INTFLOAT_PTR z = &y;
  
   y.exponent = -62;
   y.fraction = 0x60000000;
   int r_2 = pack_value(z);
   return 0;
}
