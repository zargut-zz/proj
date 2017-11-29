int opcode, funcCode, jumpTargetAddress = 0;
int branchEffAddress = 0;
int rsReg, rtReg, rdReg = 0;
int shamt = 0;
int immAddress = 0;
 else
   {
      printf("--> I-Type instruction\n");
      printf("Opcode value: 0x%02X \n", opcode >> 26);
      printf("Opcode value:(decimal) %d \n", opcode >> 26);
      printf("Instruction name: ");
      if(opcode == 0x04<<26){
         printf("beq");
      }else if(opcode == 0x05<<26){
         printf("bne");
      }else if(opcode == 0x08<<26){
         printf("addi");
         addi(rsReg, rtReg, signExtension2(immAddress));
      }else if(opcode == 0x09<<26){
         printf("addiu");
         addi(rsReg, rtReg, immAddress);
      }else if(opcode == 0x0C<<26){
         printf("andi");
         and(rsReg, rtReg, immAddress);
      }else if(opcode == 0x0D<<26){
         printf("ori");
         ori(rsReg, rtReg, immAddress)
      }else if(opcode == 0x0E<<26){
         printf("xori");
         xori(rsReg, rtReg, immAddress);
      }else if(opcode == 0x0F<<26){
         printf("lui");
         lui(rsReg, rtReg, immAddress);
      }else if(opcode == 0x20<<26){
         printf("lb");
      }else if(opcode == 0x21<<26){
         printf("lh");
      }else if(opcode == 0x24<<26){
         printf("lbu");
      }else if(opcode == 0x23<<26){
         printf("lw");
      }else if(opcode == 0x25<<26){
         printf("lhu");
      }else if(opcode == 0x28<<26){
         printf("sb");
      }else if(opcode == 0x29<<26){
         printf("sh");
      }else if(opcode == 0x2B<<26){
         printf("sw");
      }else if(opcode == 0x31<<26){
         printf("lwcl");
      }else if(opcode == 0x35<<26){
         printf("ldcl");
      }else if(opcode == 0x39<<26){
         printf("swcl");
      }else if(opcode == 0x3D<<26){
         printf("sdcl");
      }else{
         printf("Invalid Instruction\n");
         return;
      }
      
  
}

void addi(unsigned int rs, unsigned int rt, int immed) // effective address
{
   regs[rt] = regs[rs] + immed;
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
void ori(unsigned int rs, unsigned int rt, int immed)
{
   regs[rt] = regs[rs] | immed;
   clk += 3; 
} 
void xori(unsigned int rs, unsigned int rt, int immed)
{
   regs[rt] = regs[rs] ^ immed;
   clk += 3; 
}
void slti(unsigned int rs, unsigned int rt, int immed)
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
   if (regs[rs] == regs[rt])
   {
      pc = pc + 4 + immAdress;
   } 
   clk += 2; 
}
void bne(unsigned int rs, unsigned int rt, int immAdress)
{
   if (regs[rs] != regs[rt])
   {
      pc = pc + 4 + immAdress;
   } 
   clk += 2; 
}
void j(int jAdress)
{
   pc = jAdress;
   clk += 3;
}
void jal(int jAdress)
{
   regs[31] = pc;
   pc = jAdress;
   clk += 3;
}
// fix sign extension and number of bits according to instructions
void lb(unsigned int rs, unsigned int rt, int immed)
{
   unsigned int val;
   val = mem[(regs[rs]+immed)/4];
   regs[rt] = signExtension3(0x000000FF & val); 
   clk += 4; 
}
void lbu(unsigned int rs, unsigned int rt, int immed)
{
   regs[rt] = 0x000000FF & mem[(regs[rs]+immed)/4]; 
   clk += 4; 
}
void lh(unsigned int rs, unsigned int rt, int immed)
{
   regs[rt] = signExtension2(0x0000FFFF & mem[(regs[rs]+immed)/4]); 
   clk += 4; 
}
void lhu(unsigned int rs, unsigned int rt, int immed)
{
   regs[rt] = 0x0000FFFF & mem[(regs[rs]+immed)/4];  
   clk += 4; 
}
void lui(unsigned int rs, unsigned int rt, int immed)
{
   regs[rt] = 0xFFFF0000 & (immed<<16);  
   clk += 4; 
}
void lw(unsigned int rs, unsigned int rt, int immed)
{
   regs[rt] = mem[(regs[rs]+immed)/4]; 
   clk += 4; 
}

//helper functions
void print_vals(){
   for(int i = 0; i < 32; i++){
      printf("Register %d: %08X \n", i, regs[i]);
   }
   printf("\nPC Count:%d\n Number of Clock Cycles:%d\n Number of Instructions:%d\n", pc, clk,instr_cnt);
}






