#include<stdio.h>

typedef struct _intfloat {
   int exponent; 
   int fraction;
} INTFLOAT, *INTFLOAT_PTR; 

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

int main(){
   int exponent = 0;
   int fraction = 0x02000000;
   INTFLOAT x;
   x.exponent =  exponent;
   x.fraction =  fraction;
   INTFLOAT_PTR y = &x;
   normalize(y);
   return 0;
}
