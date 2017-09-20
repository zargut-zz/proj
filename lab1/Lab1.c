#include <stdio.h>

int main()
{
   int i = 8;
   long num = 598405;
   short other = 79;
   unsigned char ch = 'c';
   printf("Byte Size: %d\n" ,sizeof(ch));
   printf("Short Int Size: %d\n", sizeof(other));
   printf("Integer Size: %d\n", sizeof(i));
   printf("Long Integer Size: %d\n", sizeof(num));
   return 0;
}
