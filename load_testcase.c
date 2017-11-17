
/*----------------------------------------------------------------------*
 * Example mips_asm program loader. This loads the mips_asm binary   *
 * named "testcase1.mb" into an array in memory. It reads      *
 * the 64-byte header, then loads the code into the mem array. *
 *                         *
 * DLR 4/18/16                   *
 *----------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mips_asm_header.h"


typedef unsigned int MIPS, *MIPS_PTR;
typedef unsigned int REG, *REG_PTR;
typedef unsigned int INSTRUCTIONS, *INSTRUCTIONS_PTR;

MB_HDR mb_hdr;       /* Header area */
MIPS mem[1024];      /* Room for 4K bytes */
REG regs[32];
INSTRUCTIONS ins[128];
//INSTRUCTIONS valid[128];
int clk = 0;
int pc = 0;
int instr_cnt = 0;
int invalid = 0;
int sim = 0;
int count = 0;

int haltflag = 0;


int opcode, funcCode, jumpTargetAddress = 0;
int branchEffAddress = 0;
int rsReg, rtReg, rdReg = 0;
int shamt = 0;
int immAddress = 0;

// Pipeline variables
RES res;


int main()
{
   FILE *fd;
   int n;
   int memp;
   int i;

   //char filename[] = "testcase1.mb"; /* This is the filename to be loaded */
   char filename[80];
   printf ("Enter an input file: ");
   scanf ("%s", filename);
   
   /* format the MIPS Binary header */

   fd = fopen(filename, "rb");
   if(fd == NULL)
   {
      printf("\nCouldn't load test case - quitting.\n");
      exit(99);
   }

   memp = 0;      /* This is the memory pointer, a byte offset */

   /* read the header and verify it. */
   fread((void *) &mb_hdr, sizeof(mb_hdr), 1, fd);
   
   if((!strcmp(mb_hdr.signature, "~MB"))==0)
   {
      printf("\nThis isn't really a mips_asm binary file - quitting.\n");
      exit(98);
   }
  
   printf("\n%s Loaded ok, program size=%d bytes.\n\n", filename, mb_hdr.size);

   /* read the binary code a word at a time */
  
   do {
      n = fread((void *) &mem[memp/4], 4, 1, fd); /* note div/4 to make word index */
      if(n)
         memp += 4;  /* Increment byte pointer by size of instr */
      else
         break;
   }
   
   while(memp < sizeof(mem)) ;

   fclose(fd);

   /* ok, now dump out the instructions loaded: */
   
   for (i = 0; i < memp; i+=4)   /* i contains byte offset addresses */
   {
      printf("Instruction@%08X : 0x%08X\n", i, mem[i/4]);
      storeInstruction(mem[i/4]);
      //ins[count] = mem[i/4];
      count++;
   }
   char response[80];

   char runString[] = "run";
   char firstThreeChars[4];
    //starts simulation mode
   sim = 1;
   //set sp to 0x7fffeffc
   regs[29] = 0x7fffeffc;
   /*while(pc/4 < count || count != 0){
      printf ("Run or Step\n");
      scanf ("%s", response);
      strncpy(firstThreeChars, response, 3);
      printf("%d",strcmp(firstThreeChars, runString));
      if(strcmp(firstThreeChars, runString) == 0)
      {
         while(pc/4 < count || count != 0){
            storeInstruction(ins[pc/4]);
            pc+= 4;
            printf("PC: %08X",pc);
         }

      }else{
         print_stats();
         storeInstruction(ins[pc/4]);
         pc+= 4;       
      }
   }*/
   printf("\n");
   print_stats();
   
   exit(0);

}

for(haltflag = 0;haltflag; clk++){
   wb();
   mem();
   ex();
   instDec();
   instFetch(pc/4);
   print_stats();
}
// instnum is the index of the instruction we want
unsigned int instFetch(instnum)
{
   inst = ins[instnum];
   res.opcode = (inst & 0xFC000000);
   res.func = (inst & 0x0000003F);
   pc += 4;
}

void instDec()
{
   if (res.opcode >= 0) {
      
   }
   decode.active = 1;
   storeInstruction(inst);
   decode.rs = regs[rsReg];
   decode.rt = regs[rtReg];
   decode.rd = regs[rdReg];
}

void ex(unsigned int inst)
{
   if(inst == 0x00000000)
   {
      exit(); //what happens in pipeline with nop?
   }
   else
   {
      if (opcode == 0)
      {
         checkFuncCode(inst); // these functions do ex and mem? yes?
      }  
      else
      {
         checkOpcode(inst); // should we be splitting this up?
      }
   }
}

void mem();
{

}

void wb(int regindex, int val);
{
   regs[regindex] = val;
}


void storeInstruction(unsigned int inst)
{
   /* Extracting and Storing the instruction bits here: */
   printf("\nInstruction: %X\n", inst);
   opcode = (inst & 0xFC000000);
   funcCode = (inst & 0x0000003F);
   rsReg = (inst & 0x03E00000) >> 21;
   rtReg = (inst & 0x001F0000) >> 16;
   rdReg = (inst & 0x0000F800) >> 11;
   shamt = (inst & 0x000007C0) >> 6;
   immAddress = (inst & 0x0000FFFF);
   jumpTargetAddress = (inst & 0x03FFFFFF);
   
   //Different functionality during store and simulation mode
   if(inst == 0x00000000)
   {
      if (sim ==1) 
      {
         printf("\n--> NOP Instruction\n");
      }
      ins[count] = inst;
   }
   else
   {
      if (opcode == 0)
      {
         checkFuncCode(inst); 
      }  
      else
      {
         checkOpcode(inst);
      }
   }

   if(sim == 1){
      instr_cnt++;
   }

    printf("\n ------------------------------------------------- \n");
}

/*
 * For the R-Type instructions:
 */
void checkFuncCode(unsigned int inst)
{
   if(sim == 1){
      printf("--> R-Type instruction\n");
   
      printf("Function code: 0x%08X \n", funcCode);
   
      printf("Instruction name: ");
   }
   //place within register instruction decoding
   if(funcCode == 0x00 && (rsReg > 0 || rdReg > 0)){
      if (sim == 1){
         printf("sll");
         sll(rsReg, rtReg, rdReg,shamt);
            
      }else{
         ins[count] = inst;
      }
      
   }else if(funcCode == 0x02){
      if (sim == 1){
         printf("srl");
         srl(rsReg, rtReg, rdReg,shamt);   
      }else{

         ins[count] = inst;
      }
      
   }else if(funcCode == 0x03){
      if (sim == 1){
         printf("sra");
         sra(rsReg, rtReg, rdReg,shamt);
            
      }else{
         ins[count] = inst;
      }

   }else if(funcCode == 0x04 && (rsReg > 0 || rtReg > 0 || rdReg > 0)){
      if (sim == 1){
         printf("sllv");
         sllv(rsReg, rtReg, rdReg);
      }else{
         ins[count] = inst;
      }
      
   }else if(funcCode == 0x06){
      if (sim == 1){
         printf("srlv");
         srlv(rsReg, rtReg, rdReg);
      }else{
         ins[count] = inst;
      }
   }else if(funcCode == 0x07){
      if (sim == 1){
         printf("srav");
         srav(rsReg, rtReg, rdReg);
      }else{
         ins[count] = inst;
      }
   }else if(funcCode == 0x08){
      if (sim == 1){
         printf("jr");
         jr(jumpTargetAddress);
       
      }else{
         ins[count] = inst;
      }
   }else if(funcCode == 0x09){
      if (sim == 1){
         printf("jalr");
         jalr(rsReg,jumpTargetAddress);
      }else{
         ins[count] = inst;
      }
   }else if(funcCode == 0x10){
      printf("mfhi");
   }else if(funcCode == 0x12){
      printf("mflo");
   }else if(funcCode == 0x1A){
      printf("div");
   }else if(funcCode == 0x01B){
      printf("divu");
   }else if(funcCode == 0x18){
      printf("mult");
   }else if(funcCode == 0x19){
      printf("multu");
   }else if(funcCode == 0x20){
      if (sim == 1){
         printf("add");
         add(rsReg, rtReg, rdReg);  
      }else{
         ins[count] = inst;
      }
   }else if(funcCode == 0x21){
      if (sim == 1){
         printf("addu");
         addu(rsReg, rtReg, rdReg);
            
      }else{  
         ins[count] = inst;
      }
   }else if(funcCode == 0x22){
      if (sim == 1){
         printf("sub");
         sub(rsReg, rtReg, rdReg);
         printf("\nAfter: %X, %X, %X \n",regs[rsReg],regs[rtReg],regs[rdReg]);
            
      }else{
         ins[count] = inst;

      }
   }else if(funcCode == 0x23){
      if (sim == 1){
         printf("subu");
         subu(rsReg, rtReg, rdReg);
      }else{
         ins[count] = inst;
      }    
   }else if(funcCode == 0x24){
      if (sim == 1){
         printf("and");
         AND(rsReg, rtReg, rdReg); 
      }else{
         ins[count] = inst;
      }  
   }else if(funcCode == 0x25){
      if (sim == 1){
         printf("or");       
         OR(rsReg, rtReg, rdReg);  
      }else{
         ins[count] = inst;

      }
   }else if(funcCode == 0x26){
      if (sim == 1){
          printf("xor");
         XOR(rsReg, rtReg, rdReg);
      }else{
         ins[count] = inst;
      }
   }else if(funcCode == 0x27){
      if (sim == 1){
         printf("nor");
         NOR(rsReg, rtReg, rdReg);
      }else{
        ins[count] = inst;
      }

   }else if(funcCode == 0x2A){
      if (sim == 1){
         printf("slt");
         slt(rsReg, rtReg, rdReg);
      }else{
         ins[count] = inst;
      }

   }else if(funcCode == 0x2B){
      if (sim == 1){
         printf("sltu");
         sltu(rsReg, rtReg, rdReg);
      }else{
         ins[count] = inst;
      }
   } else if(funcCode == 0x0C){
      if(sim==1){
        printf("Syscall");
        syscall();
      }else{
         ins[count] = inst;
      }
   }else{
      if(sim == 1){
         //acounts for the extra instruction before load instructions; happens during simulation
         printf("\nlui\n");
      }else{
         //Diregards Invalid Instructions during store mode
         count--;
      }
     
      return;
   }
   
   printf("\n");
   // print out the rs, rt, rd, shamt
   printf("Rs reg: 0x%X\n", rsReg);
   printf("Rs reg:(decimal) %d\n", rsReg);
   
   printf("Rt reg: 0x%X\n", rtReg);
   printf("Rt reg:(decimal) %d\n", rtReg);
   
   printf("Rd reg: 0x%X\n", rdReg);
   printf("Rd reg:(decimal) %d\n", rdReg);
   
   printf("Shamt : 0x%X\n", shamt);
   printf("Shamt:(decimal) %d\n", shamt);

   printf("\n");
}


/*
 * For I-Type, J-Type and one special case scenario instructions:
 */
void checkOpcode(unsigned int inst)
{
   branchEffAddress = signExtension2(immAddress) * 4;
   
   //Checks if instruction is a jump; place before opcode check for all cases; these are the two jump codes
   if(opcode == 0x02<<26 || opcode == 0x03<<26)
   {
      if (sim == 1){
         printf("--> J-Type instruction\n");
         printf("Opcode value: 0x%02X \n", opcode >> 26);
         printf("Opcode value:(decimal) %d \n", opcode >> 26);
         printf("Instruction name: ");
         printf("jump hexadecimal address: 0x%08X , and ", jumpTargetAddress);
         jumpTargetAddress = signExtensionForJumps(jumpTargetAddress) * 4;
         printf("jump effective address: 0x%08X \n", jumpTargetAddress);
      }
      jumpTargetAddress = signExtensionForJumps(jumpTargetAddress) * 4;
      
      // will need to do sign extention + special shifting to get effective addr:
      
      // multiplying by 4 is the same as if we left shifted by 2:
      
      if(opcode == 0x02000000){
         if (sim == 1){
            printf("j\n");
            j(jumpTargetAddress);
         }else{
            ins[count] = inst;
         }
      }else{
         if (sim == 1){
            jal(jumpTargetAddress);
            printf("Instruction name: jal\n");
         }else{
            ins[count] = inst;
         }
         
      }
      
      // left shift by two: << 2
     
   }
   // special case for "move from control" R-type instruction:
   else if(opcode == 0x16<<26 && funcCode == 0x00000000 && sim == 1)
   {

      printf("--> R-Type instruction\n");
      printf("Opcode value: 0x%02X \n", opcode >> 26);
      printf("Opcode value(decimal): %d \n", opcode >> 26);
      printf("Function code: 0x%08X \n", funcCode);
      printf("Instruction name: mfc0");
      printf("\n");
      //treat this as a register operation; print rs, rt, rd fields
      printf("Rs reg: 0x%X\n", rsReg);
      printf("Rs reg:(decimal) %d\n", rsReg);
      printf("Rt reg: 0x%X\n", rtReg);
      printf("Rt reg:(decimal) %d\n", rtReg);
      printf("Rd reg: 0x%X\n", rdReg);
      printf("Rd reg:(decimal) %d\n", rdReg);
      printf("Shamt : 0x%X\n", shamt);
      printf("Shamt:(decimal) %d\n", shamt);
   }
   
   // not going into else condition for certain times
   else
   {
      if(sim == 1){
         printf("--> I-Type instruction\n");
         printf("Opcode value: 0x%02X \n", opcode >> 26);
         printf("Opcode value:(decimal) %d \n", opcode >> 26);
         printf("Instruction name: ");
      }
      
      if(opcode == 0x04<<26){
         if(sim == 1){
            beq(rsReg, rtReg, branchEffAddress);
            printf("beq");
         }else{
            ins[count] = inst;
         }
         
      }else if(opcode == 0x05<<26){
         if(sim == 1){
            printf("bne");
            bne(rsReg, rtReg, branchEffAddress);
         }else{
            ins[count] = inst;

         }
      }else if(opcode == 0x08<<26){
         if (sim == 1){
            printf("addi");
            addi(rsReg, rtReg, signExtension2(immAddress));
         }else{
            ins[count] = inst;
         }
         
      }else if(opcode == 0x09<<26){
         if (sim == 1){
          printf("addiu");
          addi(rsReg, rtReg, immAddress);  
         }else{
            ins[count] = inst;
         }
      }else if(opcode == 0x0A <<26){
         if (sim == 1){
          printf("slti");
          slti(rsReg, rtReg, immAddress);  
         }else{
            ins[count] = inst;
         }         
      }else if(opcode == 0x0C<<26){
         if (sim == 1){
            printf("andi");
            andi(rsReg, rtReg, immAddress);    
         }else{
            ins[count] = inst;
         }

         
      }else if(opcode == 0x0D<<26){
         if (sim == 1){
            printf("ori");
            ori(rsReg, rtReg, immAddress);
         }else{
            ins[count] = inst;
         }

         
      }else if(opcode == 0x0E<<26){
         if (sim == 1){
            printf("xori");
            xori(rsReg, rtReg, immAddress);
         }else{
            ins[count]= inst;
         }

         
      }else if(opcode == 0x0F<<26){
         if (sim == 1){
            printf("lui");
            lui(rsReg, rtReg, immAddress);
         }else{
            ins[count] = inst;
         }

         
      }else if(opcode == 0x20<<26){
         if (sim == 1){
           printf("lb");
           lb(rsReg, rtReg, immAddress); 
         }else{
            ins[count] = 0x01;
            count++;
            ins[count] = inst;
         }

         
      }else if(opcode == 0x21<<26){
         if (sim == 1){
           printf("lh");
            lh(rsReg, rtReg, immAddress); 
         }else{
            ins[count] = 0x01;
            count++;
            ins[count] = inst;
         }

         
      }else if(opcode == 0x24<<26){
         if (sim == 1){
            printf("lbu");
            lbu(rsReg, rtReg, immAddress);
         }else{
            ins[count] = 0x01;
            count++;
            ins[count] = inst;
         }

         
      }else if(opcode == 0x23<<26){
         if (sim == 1){
            printf("lw");
            lw(rsReg, rtReg, immAddress);
         }else{
            ins[count] = 0x01;
            count++;
            ins[count] = inst;
         }

         
      }else if(opcode == 0x25<<26){
         if (sim == 1){
            printf("lhu");
            lhu(rsReg, rtReg, immAddress);
         }else{
            ins[count] = 0x01;
            count++;
            ins[count] = inst;
         }

         
      }else if(opcode == 0x28<<26){
         if (sim == 1){
            printf("sb");
            sb(rsReg, rtReg, immAddress);
         }else{
            ins[count] = inst;
         }

         
      }else if(opcode == 0x29<<26){
         if (sim == 1){
            printf("sh");
            sh(rsReg, rtReg, immAddress);
         }else{
            ins[count] = inst;
         }

         
      }else if(opcode == 0x2B<<26){
         if (sim == 1){
            printf("sw");
            sw(rsReg, rtReg, immAddress);
         }else{
            ins[count] = inst;

         }

         
      }else{
         if(sim == 1){
            printf("\nlui\n");
         }else{
            count--;
         }
      }
      
      printf("\n");
      printf("Rs reg: 0x%X\n", rsReg);
      printf("Rs reg:(decimal) %d\n", rsReg);
      printf("Rt reg: 0x%X\n", rtReg);
      printf("Rt reg:(decimal) %d\n", rtReg);
      
      // if its a branch or not, depending on that, we do an effective address
      if(opcode == 0x04 << 26 || opcode == 0x05 << 26)
      {
         printf("Branch's Effective Address: 0x%08X \n", branchEffAddress);
      }
      else
      {
         printf("Immediate Value: 0x%08X \n", signExtension2(immAddress));
      }
      

   }
   printf("\n");
}

// jump instruction - For sign extending 26 bit address to 32 bits
int signExtensionForJumps(int instr)
{
   int value = (0x03FFFFFF & instr);
   int mask = 0x02000000;
   if (mask & instr) {
      value += 0xFC000000;
   }
   return value;
}

// branch instruction - For sign extending 16 bit to 32 bits
int signExtension2(int instr)
{
   int value = (0x0000FFFF & instr);
   int mask = 0x00008000;
   if (mask & instr) {
      value = value | 0xFFFF0000;
   }
   return value;
}

// For sign extending 8 bit to 32 bits
int signExtension3(int instr)
{
   int value = (0x000000FF & instr);
   int mask = 0x00000080;
   if (mask & instr) {
      value = value | 0xFFFFFF00;
   }
   return value;
}

//Execute and Decode State Operations
void add(unsigned int rs, unsigned int rt, unsigned int rd){
   regs[rd] = (int)regs[rs]+ regs[rt];
}

//executes addu instruction during execute cycle
void addu(unsigned int rs, unsigned int rt, unsigned int rd){
   regs[rd] = (unsigned int)regs[rs]+ (unsigned int)regs[rt];
}

//executes sub instruction during execute cycle
void sub(unsigned int rs, unsigned int rt, unsigned int rd){
   regs[rd] = (int)regs[rs]-regs[rt];
   
}

//executes subu instruction during execute cycle
void subu(unsigned int rs, unsigned int rt, unsigned int rd){
   regs[rd] = (unsigned int)regs[rs]- (unsigned int)regs[rt];
   
}

//executes AND instruction during execute cycle
void AND(unsigned int rs, unsigned int rt, unsigned int rd){
   regs[rd] = (unsigned int)regs[rs] & (unsigned int)regs[rt];
   
}

//executes OR instruction during execute cycle
void OR(unsigned int rs, unsigned int rt, unsigned int rd){
   regs[rd] = (unsigned int)regs[rs] | (unsigned int)regs[rt];
   
}

//executes NOR instruction during execute cycle
void NOR(unsigned int rs, unsigned int rt, unsigned int rd){
   regs[rd] = !((unsigned int)regs[rs] | (unsigned int)regs[rt]);
   
}

//executes XOR instruction during execute cycle
void XOR(unsigned int rs, unsigned int rt, unsigned int rd){
   regs[rd] = (unsigned int)regs[rs] ^ (unsigned int)regs[rt];
   
}

void sll(unsigned int rs, unsigned int rt, unsigned int rd, int shamt){
   regs[rd] = regs[rt]<<shamt;
   
}
void srl(unsigned int rs, unsigned int rt, unsigned int rd, int shamt){
   regs[rd] = regs[rt]>>shamt;
   
}
void sra(unsigned int rs, unsigned int rt, unsigned int rd, int shamt){
   regs[rd] = (int)regs[rt]>>shamt;
   
}
void sllv(unsigned int rs, unsigned int rt, unsigned int rd){
   regs[rd] = regs[rt]<<regs[rs];
   
}
void srlv(unsigned int rs, unsigned int rt, unsigned int rd){
   regs[rd] = regs[rt]>>regs[rs];
   
}
void srav(unsigned int rs, unsigned int rt, unsigned int rd){
   regs[rd] = (int)regs[rt]>>regs[rs];
   
}
void slt(unsigned int rs, unsigned int rt, unsigned int rd){
   if(regs[rs]< regs[rt]){
      regs[rd] = 1;
   }else{
      regs[rd] = 0;
   }
   clk+= 3;
}
void sltu(unsigned int rs, unsigned int rt, unsigned int rd){
   if((unsigned int)regs[rs]< (unsigned int)regs[rs]){
      regs[rd] = 1;
   }else{
      regs[rd] = 0;
   }

   clk+= 3;
}
void jr(int jumpTargetAddress){
   //accounts for incoming pc increment
   pc = regs[31]-4;
   
}
void jalr(unsigned int rs, int jumpTargetAddress){
   //accounts for incoming pc increment
   pc = regs[rs]-4;
   regs[31] = pc+4;

   
}
void div_a(unsigned int rs, unsigned int rt, unsigned int rd){
   int lo = 0x0000FFFF&(regs[rs]/regs[rt]);
   int hi = 0xFFFF0000&(regs[rs]%regs[rt]);
   regs[rd] = ((0&regs[rd]) | lo) | hi;

   clk+= 3;

}
void divu(unsigned int rs, unsigned int rt, unsigned int rd){
   unsigned int lo = 0x0000FFFF&((unsigned int)regs[rs]/(unsigned int)regs[rt]);
   unsigned int hi = 0xFFFF0000&(regs[rs]%regs[rt]);
   regs[rd] = ((0&(unsigned int)regs[rd]) | lo) | hi;

   clk+= 3;
}
void addi(unsigned int rs, unsigned int rt, int immed) // effective address
{
   regs[rt] = (int)regs[rs] + (int)immed;
   clk += 3;
}
void addiu(unsigned int rs, unsigned int rt, int immed)
{
   regs[rt] = regs[rs] + immed; 
   clk += 3; 
}
void andi(unsigned int rs, unsigned int rt, int immed)
{
   regs[rt] = regs[rs] & immed;
   clk += 3; 
}
void ori(unsigned int rs, unsigned int rt, int immed){
   regs[rt] = regs[rs] | immed;
   clk += 3; 
} 
void xori(unsigned int rs, unsigned int rt, int immed){
   regs[rt] = regs[rs] ^ immed;
   clk += 3; 
}
void slti(unsigned int rs, unsigned int rt, int immed)
{
   if (regs[rs] < immed){
      regs[rt] = 1;
   }
   else
   {
      regs[rt] = 0;
   } 
   clk += 3; 
}
void sltiu(unsigned int rs, unsigned int rt, int immed)
{
   if (regs[rs] < immed)
   {
      regs[rt] = 1;
   }
   else
   {
      regs[rt] = 0;
   }
   clk += 3; 
}
void beq(unsigned int rs, unsigned int rt, int immAdress)
{
   if (regs[rs] == regs[rt]){
      pc = pc + (branchEffAddress);
   } 
   clk += 2; 
}
void bne(unsigned int rs, unsigned int rt, int immAdress)
{
   printf("\nrt : %08X  rs: %08X",regs[rt],regs[rs] );
   if (regs[rs] != regs[rt]){
      pc = pc + (branchEffAddress);
   } 
   clk += 2; 
}
void j(int jAdress)
{
   //acounts for incoming pc increment
   pc = (jAdress&0x00000FFFF)/4;
   clk += 3;
}
void jal(int jAdress)
{
   regs[31] = pc+4;
   pc = (jAdress&0x00000FFFF)/4;
   clk += 3;
}
// fix sign extension and number of bits according to instructions
void lb(unsigned int rs, unsigned int rt, int immed)
{
   lui(rs,1,0x1001);
   unsigned int val;
   val = mem[(regs[rs]+immed)/4];
   regs[rt] = signExtension3(0x000000FF & val); 
   clk += 4; 
}
void lbu(unsigned int rs, unsigned int rt, int immed)
{
   lui(rs,1,0x1001);
   regs[rt] = 0x000000FF & mem[(regs[rs]+immed)/4]; 
   clk += 4; 
}
void lh(unsigned int rs, unsigned int rt, int immed){
   lui(rs,1,0x1001);
   regs[rt] = signExtension2(0x0000FFFF & mem[(regs[rs]+immed)/4]); 
   clk += 4; 
}
void lhu(unsigned int rs, unsigned int rt, int immed){
   lui(rs,1,0x1001);
   regs[rt] = 0x0000FFFF & mem[(regs[rs]+immed)/4];  
   clk += 4; 
}
void lui(unsigned int rs, unsigned int rt, int immed){
   regs[rt] = 0xFFFF0000 & (immed<<16);  
   clk += 4; 
}
void lw(unsigned int rs, unsigned int rt, int immed){
   lui(rs,1,0x1001);
   regs[rt] = mem[(regs[rs]+immed)/4]; 
   clk += 4; 
}
void sb(unsigned int rs, unsigned int rt, int immed){
   mem[(regs[rs]+signExtension2(immed))/4] = 0x000000FF & regs[rt];
   clk += 4;
}
void sh(unsigned int rs, unsigned int rt, int immed){
   mem[(regs[rs]+signExtension2(immed))/4] = 0x0000FFFF & regs[rt];
   clk += 4;
}
void sw(unsigned int rs, unsigned int rt, int immed){
   mem[(regs[rs]+signExtension2(immed))/4] = regs[rt];
   clk += 4;
}
void syscall(){
   if(regs[2] == 0){
      printf("\n%08X\n", regs[4]);
   }else if(regs[2] == 5){
      printf("\n%08X\n", regs[2]);
   }else if(regs[2] == 10){
      count = 0;
      haltflag = 1;
      printf("\nThe Program has Exited\n");
   }else{
   }
}

//helper functions

void print_stats(){
   for(int i = 0; i < 32; i++){
      printf("Register %d: %08X \n", i, regs[i]);
   }
   printf("\nPC Count:%08X\n Number of Clock Cycles:%d\n Number of Instructions:%d\n", pc, clk,instr_cnt);
}


