#include <stdio.h>

unsigned int arbitrary_byte_add(unsigned char *result, unsigned char *a1, unsigned char *a2, int size, unsigned int carry_in)
{
   *result = *a1 + *a2 + carry_in;
   unsigned int carryout = 0;

   // compare the sum to one of the operands; if it is less
   // than the operand, then a carry occurred
   if(*result < *a1 || *result < *a2)
   {
      carryout = 1;
   }
   //printf("0x%02X",*result);
   return carryout;
}

int main()
{
    unsigned char result = 0;
    unsigned char  a1 = 0x01, a2 = 0x00;
    unsigned char array[5];
    int i = 0;
    
    //Question 6a
    unsigned int answera = arbitrary_byte_add(&result, &a1, &a2, 3, 0);
    a1 = a2 = 0;
    array[4] = result;
    unsigned int answera1 = arbitrary_byte_add(&result, &a1, &a2, sizeof(result) + 2, answera);
    a1 = 0x00;
    a2 = 0xFF;
    array[3] = result;
    unsigned int answera2 = arbitrary_byte_add(&result, &a1, &a2, sizeof(result) + 2, answera1);
    a1 = 0x00;
    a2 = 0xFF;
    array[2] = result;
    unsigned int answera3 = arbitrary_byte_add(&result, &a1, &a2, sizeof(result) + 2, answera2);
    a1 = 0x44;
    a2 = 0x30;
    array[1] = result;
    unsigned int answera4 = arbitrary_byte_add(&result, &a1, &a2, sizeof(result) + 2, answera3);
    array[0] = result;
    //printf("\n%X", result);
    for (i = 0; i < 5; i++)
    {
        printf("0x%02X ", array[i]);
    }
    printf("\nCarry: %d \n", answera4);

    //Question 6b

    a1 = 0xFF;
    a2 = 0x01;
    unsigned int answerb = arbitrary_byte_add(&result, &a1, &a2, 3, 0);
    a1 = 0xFF;
    a2 = 0x00;
    array[4] = result;
    unsigned int answerb1 = arbitrary_byte_add(&result, &a1, &a2, sizeof(result) + 2, answerb);
    a1 = 0xFF;
    a2 = 0x00;
    array[3] = result;
    unsigned int answerb2 = arbitrary_byte_add(&result, &a1, &a2, sizeof(result) + 2, answerb1);
    a1 = 0xFF;
    a2 = 0x00;
    array[2] = result;
    unsigned int answerb3 = arbitrary_byte_add(&result, &a1, &a2, sizeof(result) + 2, answerb2);
    a1 = 0xFF;
    a2 = 0x00;
    array[1] = result;
    unsigned int answerb4 = arbitrary_byte_add(&result, &a1, &a2, sizeof(result) + 2, answerb3);
    array[0] = result;
    //printf("\n%X", result);

    for (i = 0; i < 5; i++)
    {
        printf("0x%02X ", array[i]);
    }
    printf("\nCarry: %d \n", answerb4);
    
    return 0;
}   
