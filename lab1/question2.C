#include <stdio.h>

int main()
{
   unsigned char bytestring[] = {0x41, 0x33, 0x54, 0x80, 0xFF, 0x99, 0x01, 0x78,0x55, 0x20, 0xFE, 0xEE, 0x00, 0x00, 0x00, 0x00 };
   int length = sizeof(bytestring)/sizeof(bytestring[0]);
   
   printf("Unsigned version: ");
   for (int n = 0; n < length; n++)
   {
      printf("%02X, ", bytestring[n]);
   }
   printf("\nShort int version: ");
   unsigned short int *sb = ((unsigned short int*) (bytestring));
   for (int n = 0; n < 4; n++)
   {
      printf("%04X, ", sb[n]);
   }
   printf("\nInt version: ");
   unsigned int *ib = ((unsigned int*) (bytestring));
   for (int n = 0; n < 2; n++)
   {
      printf("%08X, ", ib[n]);
   }
   printf("\nLong int version: ");
   unsigned long int *lb = ((unsigned long int*) (bytestring));
   printf("%lX", lb[0]);
 
   
}
