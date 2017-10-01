#include<stdio.h>

typedef struct _intfloat{
   unsigned int sign;
   int exponent;
   int fraction;
   }INTFLOAT, *INTFLOAT_PTR;

void extract_float(INTFLOAT_PTR x, float f)
{
   unsigned floatbits;

