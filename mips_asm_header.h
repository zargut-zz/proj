/*----------------------------------------------------------------------*
 *	mips_asm Binary header (.mb) file header format.  This header	*
 *	provides for future information on mips assembler files.	*
 *									*
 *	write_header - writes mips_asm header, along with test data	*
 *									*
 *	This shows how the mips_asm header is written, and provides	*
 *	a test case (testcase1.mb) to be used for lab projects.		*
 *----------------------------------------------------------------------*/

typedef struct _mb_hdr
{
   char signature[4];		/* Signature = 0x7F, 'M', 'B", 0x00 */
   unsigned int size;		/* Size of assembler program portion, bytes */
   unsigned int entry;		/* Entry point offset of program if not zero */
   unsigned int filler1;	/* Unused ... reserved for future use. */
   unsigned char filler2[64-16];	/* Overall header is 64 bytes */
} MB_HDR, *MB_HDR_PTR;
//Structs below are the input and output relationships between each stage of the pipeline; interface between stages
typedef struct INST_RES
{
   unsigned int active;
   unsigned int opcode;
   unsigned int func;
}
typedef struct DEC_RES
{
   unsigned int active;
   unsigned int rs;
   unsigned int rt;
   unsigned int rd;
}
typedef struct EX_RES
{
   unsigned int active;
   unsigned int result;
}
typedef struct MEM_RES
{
   unsigned int active;
   unsigned int result;
}
typedef struct 
int signExtensionForJumps(int instr);
int signExtension2(int instr);
int signExtension3(int instr);
void storeInstruction(unsigned int inst);
void checkOpcode();
void checkFuncCode();
void print_vals();
void print_stats();

void instFetch();
void instDec();
void ex();
void mem();
void wb();

//Intializing Register Execute Functions
void add(unsigned int rs, unsigned int rt, unsigned int rd);
void addu(unsigned int rs, unsigned int rt, unsigned int rd);
void sub(unsigned int rs, unsigned int rt, unsigned int rd );
void subu(unsigned int rs, unsigned int rt, unsigned int rd);
void AND(unsigned int rs, unsigned int rt, unsigned int rd);
void NOR(unsigned int rs, unsigned int rt, unsigned int rd);
void OR(unsigned int rs, unsigned int rt, unsigned int rd);
void XOR(unsigned int rs, unsigned int rt, unsigned int rd);
void sll(unsigned int rs, unsigned int rt, unsigned int rd, int shamt);
void srl(unsigned int rs, unsigned int rt, unsigned int rd, int shamt);
void sra(unsigned int rs, unsigned int rt, unsigned int rd, int shamt);
void sllv(unsigned int rs, unsigned int rt, unsigned int rd);
void srlv(unsigned int rs, unsigned int rt, unsigned int rd);
void srav(unsigned int rs, unsigned int rt, unsigned int rd);
void slt(unsigned int rs, unsigned int rt, unsigned int rd);
void sltu(unsigned int rs, unsigned int rt, unsigned int rd);
void jr(int jumpTargetAddress);
void jalr(unsigned int rs, int jumpTargetAddress);
void div_a(unsigned int rs, unsigned int rt, unsigned int rd);
void divu(unsigned int rs, unsigned int rt, unsigned int rd);
void mult(unsigned int rs, unsigned int rt, unsigned int rd);
void multu(unsigned int rs, unsigned int rt, unsigned int rd);
void mfhi(unsigned int rs, unsigned int rt, unsigned int rd);
void mflo(unsigned int rs, unsigned int rt, unsigned int rd);
void addi(unsigned int rs, unsigned int rt, int immed);
void addiu(unsigned int rs, unsigned int rt, int immed); 
void andi(unsigned int rs, unsigned int rt, int immed); 
void ori(unsigned int rs, unsigned int rt, int immed); 
void xori(unsigned int rs, unsigned int rt, int immed); 
void slti(unsigned int rs, unsigned int rt, int immed); 
void beq(unsigned int rs, unsigned int rt, int immAdress); 
void bne(unsigned int rs, unsigned int rt, int immAdress);
void j(int jAdress); 
void jal(int jAdress); 
void lb(unsigned int rs, unsigned int rt, int immed); 
void lbu(unsigned int rs, unsigned int rt, int immed); 
void lh(unsigned int rs, unsigned int rt, int immed); 
void lhu(unsigned int rs, unsigned int rt, int immed); 
void lui(unsigned int rs, unsigned int rt, int immed); 
void lw(unsigned int rs, unsigned int rt, int immed); 
void sb(unsigned int rs, unsigned int rt, int immed);
void sh(unsigned int rs, unsigned int rt, int immed);
void sw(unsigned int rs, unsigned int rt, int immed);
void syscall();


/*
 
   --Either store an array/hashtable of opcodes and another for funct codes
      ^ make sure to store according to location 
 
   Check the opcode(31 to 26) first,
 
         To make sure invalid code:
         -> if op >2B and not 31, 35, 39 or 3D, then invalid instruction
                  print  “Invalid Instruction”
 
         if 0 (meaning no opcode, thus must be func code), then check the least 6 significant bits (function code)
            (i.e: thus, its a R-type instruction)
 
               - Rs field(25 to 21)
               - Rt (20 to 16)
               - Rd (15 to 11)
               - if shamt is not 0, then its a shift var (print shamt 10 to 
                  6)
 
               - print (5 to 0) <- funct code
 
         if not 0, then check manually if opcode == 02 or 03 (jump codes)
               - display effective address (sign ext. + shifted left )
               - j or jal
 
         else,
            its a I - type instruction
               - if opcode is 04 or 05, then branch instr.
 
 
*/





