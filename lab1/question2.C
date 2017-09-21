#include <stdio.h>

int main()
{
   unsigned char bytestring[] = {0x41, 0x33, 0x54, 0x80, 0xFF, 0x99, 0x01, 0x78,0x55, 0x20, 0xFE, 0xEE, 0x00, 0x00, 0x00, 0x00 };
   int length = sizeof(bytestring)/sizeof(bytestring[0]);
   
   printf("Unsigned version: \n");
   for (int n = 0; n < length; n++)
   {
      printf("0x%02X, ", bytestring[n]);
   }
   printf("\nShort int version: \n");
   unsigned short int *sb = ((unsigned short int*) (bytestring));
   for (int n = 0; n < 4; n++)
   {
      printf("0x%04X, ", sb[n]);
   }
   printf("\nInt version: \n");
   unsigned int *ib = ((unsigned int*) (bytestring));
   for (int n = 0; n < 2; n++)
   {
      printf("0x%08X, ", ib[n]);
   }
   printf("\nLong int version: \n");
   unsigned long int *lb = ((unsigned long int*) (bytestring));
   printf("0x%lX", lb[0]); 
  
   return 0;  
}
