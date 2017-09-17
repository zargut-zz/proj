#include <stdio.h>

int main()
{
   unsigned char bytestring[] = {0x41, 0x33, 0x54, 0x80, 0xFF, 0x99, 0x01, 0x78,0x55, 0x20, 0xFE, 0xEE, 0x00, 0x00, 0x00, 0x00 };
   int length = sizeof(bytestring)/sizeof(bytestring[0]);
   
   short int s;
   int i;
   long int l;  
 
   for (int n = 0; n < length; n++)
   {
      printf("This is the unsigned version: %u, and it has a size of %lu\n", bytestring[n], sizeof(bytestring[n]));
      s = bytestring[n];
      printf("This is the short int version: %hd, and it has a size of %lu\n", s, sizeof(s));
      i = bytestring[n];
      printf("This is the int version: %d, and it has a size of %lu\n", i, sizeof(i));
      l = bytestring[n];
      printf("This is the long int version: %ld, and it has a size of %lu\n", l, sizeof(l));
   }
}
