/*
 * Lab 1: Binary Data Representation and Arithmetic 
 * Authors: Zarah Gutierrez, Rebecca Dong, Prachi Mehta
 * CPE 315
 * 09/22/2017
 */
#include<stdio.h>
/*
 * Problem 1: Prints out data-types and their size
 * no return value, no parameter, simple print function
 */
void problem1()
{
   int i;
   long int num;
   short int other;
   unsigned char ch;
   printf("Byte Size: %lu\n" ,sizeof(ch));
   printf("Short Int Size: %lu\n", sizeof(other));
   printf("Integer Size: %lu\n", sizeof(i));
   printf("Long Integer Size: %lu\n", sizeof(num));
}

/*
 * Problem 2: Prints out bytes in different ordering based on data-type
 * no return value, no parameters, simple print function results
 */
void problem2()
{
   unsigned char bytestring[] = {0x41, 0x33, 0x54, 0x80, 0xFF, 0x99, 0x01, 0x78,0x55, 0x20, 0xFE, 0xEE, 0x00, 0x00, 0x00, 0x00};
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
   printf("0x%lX\n", lb[0]);

}

/*
 * Problem 3: Adds Unsigned Characters
 * no return value, two parameters: unsigned char values (b1,b2) added in the function, simple print function that prints result and carry  
 */
void addTwoUnsignedBytes(unsigned char b1, unsigned char b2)
{
   unsigned char result = b1 + b2;

   printf("0x%02X + 0x%02X = 0x%02X \n", b1, b2, result);
}

/*
 * Problem 4: Detects carry from unsigned character addition
 * no return value, two parameters: signed char values (b1,b2) added, simple print function that prints results and overflow
 */
void addTwoUnSignedBytes(unsigned char b1, unsigned char b2)
{
   unsigned char result = b1 + b2;
   int carry = 0;

   // compare the sum to one of the operands; if it is less
   // than the operand, then a carry occurred
   if(result < b1 || result < b2)
   {
      //printf("CARRY occured \n");
      carry = 1;
   }

   printf("0x%02X + 0x%02X Carry: %d \n", b1, b2, carry);
}

/*
 * Problem 5: Detects overflow from signed character addition
 */
void addTwoSignedBytes(signed char b1, signed char b2)
{
   signed char result = b1 + b2;
   int overflow = 0;

   if(b1 > 0 && b2 > 0 && result < 0)
   {
      overflow = 1;
   }
   if(b1 < 0 && b2 < 0 && result > 0)
   {
      overflow = 1;
   }

   printf("0x%02X + 0x%02X = 0x%02X Overflow: %d \n\n", b1, b2, result, overflow);
}

/*
 * Problem 6: Performs an extended field arithmetic; similar to a full adder 
 */
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
   return carryout;
}

int main()
{
   //PROBLEM #1
   printf("Part 1: Data Types and their Sizes\n");
   printf("=============================================================================================================================\n");
   problem1();
   printf("=============================================================================================================================\n");
   
   //PROBLEM $2
   printf("\nPart 2: Byte Ordering\n");
   printf("=============================================================================================================================\n");
   problem2();
   printf("***********************");
   printf("\n2e) 0x41, 0x33, 0x54, 0x80, 0xFF, 0x99, 0x01, 0x78, 0x55, 0x20, 0xFE, 0xEE, 0x00, 0x00, 0x00, 0x00\n2f) 0x4133, 0x5480, 0xFF99, 0x0178\n2g) 0x41335480, 0xFF990178 \n2h) 0x41335480FF990178\n");
   printf("=============================================================================================================================\n");
   
   //PROBLEM #3
   printf("\nPart 3: Unsigned Addition of Small Fields \n");
   printf("=============================================================================================================================\n");
   //0x20 + 0x35  (in dec: 32, 53)
   addTwoUnsignedBytes(0x20, 0x35);
   //0x80 + 0x7F
   addTwoUnsignedBytes(0x80, 0x7F);
   //0x80 + 0xFF
   addTwoUnsignedBytes(0x80, 0xFF);
   //0xFF + 0x01
   addTwoUnsignedBytes(0xFF, 0x01);

   printf("============================================================================================================================\n");
   
   // PROBLEM #4:
   printf("\nPart 4: Detecting a Carry condition\n");
   printf("=============================================================================================================================\n");
   //0x20 + 0x35  (in dec: 32, 53)
   addTwoUnSignedBytes(0x20, 0x35);
   //0x80 + 0x7F
   addTwoUnSignedBytes(0x80, 0x7F);
   //0x80 + 0xFF
   addTwoUnSignedBytes(0x80, 0xFF);
   //0xFF + 0x01
   addTwoUnSignedBytes(0xFF, 0x01);

   printf("=============================================================================================================================\n");
   
   // PROBLEM #5:
   printf("\nPart 5: Signed Addition and Overflow\n");
   printf("=============================================================================================================================\n");
   addTwoSignedBytes(0x20, 0x35);
   addTwoSignedBytes(0x80, 0x7F);
   addTwoSignedBytes(0x80, 0xFF);
   addTwoSignedBytes(0xFF, 0x01);   
   
   printf("=============================================================================================================================\n");
   //PROBLEM 6 
   printf("\nPart 6: Performing Extended Field Arithmetic\n");
   printf("=============================================================================================================================\n");
   printf("\n6a)\n");
   unsigned char array[5];
   int i = 0;
   unsigned char result = 0;
   unsigned char  a1 = 0x01, a2 = 0x00;

   unsigned int answer = arbitrary_byte_add(&result, &a1, &a2, 3, 0);
   a1 = a2 = 0x00;
   unsigned int answer1 = arbitrary_byte_add(&result, &a1, &a2, sizeof(result) + 2, answer);
   a1 = 0x00;
   a2 = 0xFF;
   unsigned int answer2 = arbitrary_byte_add(&result, &a1, &a2, sizeof(result) + 2, answer1);
   a1 = 0x00;
   a2 = 0xFF;
   unsigned int answer3 = arbitrary_byte_add(&result, &a1, &a2, sizeof(result) + 2, answer2);
   a1 = 0x44;
   a2 = 0x30;
   unsigned int answer4 = arbitrary_byte_add(&result, &a1, &a2, sizeof(result) + 2, answer3);
   //prints answer in the proper order
   for (i = 0; i < 5; i++)
   {
      printf("0x%02X ", array[i]);
   }
   printf("\nCarry: %d \n", answer4);
   
  //Question 6b
   printf("\n6b)\n");
   result = 0;
   a1 = 0x01, a2 = 0x00;
   
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
