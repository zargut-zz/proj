#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "load_testcase.c"
//clk = clock
//Program counter variable = pc
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
void sltu(unsigned int rs, unsigned int rt, unsigned int rd, int shamt);
void jr(unsigned int rs, unsigned int rt, unsigned int rd, int shamt);
void jalr(unsigned int rs, unsigned int rt, unsigned int rd, int shamt);
void div_a(unsigned int rs, unsigned int rt, unsigned int rd);
void divu(unsigned int rs, unsigned int rt, unsigned int rd);
void mult(unsigned int rs, unsigned int rt, unsigned int rd);
void multu(unsigned int rs, unsigned int rt, unsigned int rd);
void mfhi(unsigned int rs, unsigned int rt, unsigned int rd);
void mflo(unsigned int rs, unsigned int rt, unsigned int rd);

//executes add instruction during execute cycle
void add(unsigned int rs, unsigned int rt, unsigned int rd){
	regs[rd] = reg[rs]+ reg[rt];
	clk+=3;
}

//executes addu instruction during execute cycle
void addu(unsigned int rs, unsigned int rt, unsigned int rd){
	regs[rd] = (unsigned int)regs[rs]+ (unsigned int)regs[rs];
	clk+=3;
}

//executes sub instruction during execute cycle
void sub(unsigned int rs, unsigned int rt, unsigned int rd){
	regs[rd] = regs[rs]-regs[rs];
	clk+=3;
}

//executes subu instruction during execute cycle
void addu(unsigned int rs, unsigned int rt, unsigned int rd){
	regs[rd] = (unsigned int)regs[rs]- (unsigned int)regs[rs];
	clk+=3;
}

//executes AND instruction during execute cycle
void AND(unsigned int rs, unsigned int rt, unsigned int rd){
	regs[rd] = (unsigned int)regs[rs] & (unsigned int)regs[rs];
	clk+=3;
}

//executes OR instruction during execute cycle
void OR(unsigned int rs, unsigned int rt, unsigned int rd){
	regs[rd] = (unsigned int)regs[rs] | (unsigned int)regs[rs];
	clk+=3;
}

//executes NOR instruction during execute cycle
void NOR(unsigned int rs, unsigned int rt, unsigned int rd){
	regs[rd] = !((unsigned int)regs[rs] | (unsigned int)regs[rs]);
	clk+=3;
}

//executes XOR instruction during execute cycle
void XOR(unsigned int rs, unsigned int rt, unsigned int rd){
	regs[rd] = (unsigned int)regs[rs] ^ (unsigned int)regs[rs];
	clk+=3;
}

void sll(unsigned int rs, unsigned int rt, unsigned int rd, int shamt){
	regs[rd] = regs[rs]<<shamt;
	clk+=3;
}
void srl(unsigned int rs, unsigned int rt, unsigned int rd, int shamt){
	regs[rd] = regs[rs]>>shamt;
	clk+=3;
}
void sra(unsigned int rs, unsigned int rt, unsigned int rd, int shamt){
	regs[rd] = (unsigned int)regs[rs]>>shamt;
	clk+=3;
}
void sllv(unsigned int rs, unsigned int rt, unsigned int rd){
	regs[rd] = regs[rs]<<regs[rs];
	clk+=3;
}
void srlv(unsigned int rs, unsigned int rt, unsigned int rd){
	regs[rd] = regs[rs]>>regs[rs];
	clk+=3;
}
void srav(unsigned int rs, unsigned int rt, unsigned int rd){
	regs[rd] = (unsigned int)regs[rs]>>regs[rs];
	clk+=3;
}
void slt(unsigned int rs, unsigned int rt, unsigned int rd){
	if(regs[rs]< regs[rs]){
		regs[rd] = 1;
	}else{
		regs[rd] = 0;
	}
}
void sltu(unsigned int rs, unsigned int rt, unsigned int rd, int shamt){
	if((unsigned int)regs[rs]< (unsigned int)regs[rs]){
		regs[rd] = 1;
	}else{
		regs[rd] = 0;
	}
}











