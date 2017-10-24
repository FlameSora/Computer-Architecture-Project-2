/***************************************************************/
/*                                                             */
/*   MIPS-32 Instruction Level Simulator                       */
/*                                                             */
/*   CS311 KAIST                                               */
/*   run.c                                                     */
/*                                                             */
/***************************************************************/

#include <stdio.h>

#include "util.h"
#include "run.h"

/***************************************************************/
/*                                                             */
/* Procedure: get_inst_info                                    */
/*                                                             */
/* Purpose: Read insturction information                       */
/*                                                             */
/***************************************************************/
instruction* get_inst_info(uint32_t pc) 
{ 
    return &INST_INFO[(pc - MEM_TEXT_START) >> 2];
}

/***************************************************************/
/*                                                             */
/* Procedure: process_instruction                              */
/*                                                             */
/* Purpose: Process one instrction                             */
/*                                                             */
/***************************************************************/
void process_instruction(){

	instruction* instrp;
	instrp  = get_inst_info(CURRENT_STATE.PC);
	instruction instr = *instrp;
	int op = instr.opcode;
	int func = instr.func_code;
	int rs = instr.r_t.r_i.rs;
	int rt = instr.r_t.r_i.rt;
	int imm = instr.r_t.r_i.r_i.imm;
	int rd = instr.r_t.r_i.r_i.r.rd;
	int shamt = instr.r_t.r_i.r_i.r.shamt;
	int target = instr.r_t.target;
	int value = instr.value;
	int tempPC = CURRENT_STATE.PC;
//	if(counter ==0){
	if (op == 9){
		CURRENT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] + imm;
		CURRENT_STATE.PC = CURRENT_STATE.PC + 4;
	}
	
	if (op == 12) {
		CURRENT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] & imm;
		CURRENT_STATE.PC = CURRENT_STATE.PC + 4;
	}
	
	if (op == 4) {
		if (CURRENT_STATE.REGS[rs] == CURRENT_STATE.REGS[rt]) {
			CURRENT_STATE.PC = CURRENT_STATE.PC + 4 + imm*4;
		}
		else {
			CURRENT_STATE.PC = CURRENT_STATE.PC + 4;
		}
	}

	if (op == 5) {
		if (CURRENT_STATE.REGS[rs] != CURRENT_STATE.REGS[rt]) {
			CURRENT_STATE.PC = CURRENT_STATE.PC + 4 + imm*4;
		}
		else {
			CURRENT_STATE.PC = CURRENT_STATE.PC + 4;
		}
	}

	if (op == 15) {
		uint32_t data = (uint32_t) imm;
		CURRENT_STATE.REGS[rt] = data << 16;
		CURRENT_STATE.PC = CURRENT_STATE.PC + 4;
	}

	if (op == 35) {
		CURRENT_STATE.REGS[rt] = mem_read_32(CURRENT_STATE.REGS[rs] + imm);
		CURRENT_STATE.PC = CURRENT_STATE.PC + 4;
	}
	
	if (op == 13) {
		CURRENT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] | imm;
		CURRENT_STATE.PC = CURRENT_STATE.PC + 4;
	}
	
	if (op == 11) {
		uint32_t data = (uint32_t) imm;
		if (CURRENT_STATE.REGS[rs] < data) {
			CURRENT_STATE.REGS[rt] = 1;
			CURRENT_STATE.PC = CURRENT_STATE.PC + 4;
		}
		else {
			CURRENT_STATE.REGS[rt] = 0;
			CURRENT_STATE.PC = CURRENT_STATE.PC + 4;
		}
	}
	
	if (op == 43) {
		mem_write_32(CURRENT_STATE.REGS[rs] + imm, CURRENT_STATE.REGS[rt]);
		CURRENT_STATE.PC = CURRENT_STATE.PC + 4;
	}

	if(op == 0){
		if(func == 8){
		//jr
	
			CURRENT_STATE.PC  = CURRENT_STATE.REGS[rs];	
		}
		if(func== 33){
		//Addu
			CURRENT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] + CURRENT_STATE.REGS[rt];
			CURRENT_STATE.PC  = CURRENT_STATE.PC+4;	
		}
		if(func== 36){
		//And	
			
			CURRENT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] & CURRENT_STATE.REGS[rt];
			CURRENT_STATE.PC  = CURRENT_STATE.PC+4;	
		}
		if(func== 39){
		//Nor
			CURRENT_STATE.REGS[rd] = ~(CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt]);
			CURRENT_STATE.PC  = CURRENT_STATE.PC+4;	
		}
		if(func== 37){
		//Or
			CURRENT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt];
			CURRENT_STATE.PC  = CURRENT_STATE.PC+4;	
		}
		if(func== 43){
		//Sltu
			if(CURRENT_STATE.REGS[rs]<CURRENT_STATE.REGS[rt]){
				CURRENT_STATE.REGS[rd] = 1;
			}else{
				CURRENT_STATE.REGS[rd] = 0;
			} 
			CURRENT_STATE.PC  = CURRENT_STATE.PC+4;	
		}
		if(func== 0){
		//Sll
			CURRENT_STATE.REGS[rd] =CURRENT_STATE.REGS[rt]<<shamt;
			CURRENT_STATE.PC  = CURRENT_STATE.PC+4;	
		}
		if(func== 2){
		//Srl
			CURRENT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] >> CURRENT_STATE.REGS[rt];
			CURRENT_STATE.PC  = CURRENT_STATE.PC+4;	
		}
		if(func== 35){
		//Subu
			CURRENT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] - CURRENT_STATE.REGS[rt];
			CURRENT_STATE.PC  = CURRENT_STATE.PC+4;	
		}
	}
	if(op ==2){
		CURRENT_STATE.PC = target*4;
	}
	if(op== 3){
		CURRENT_STATE.REGS[31] = CURRENT_STATE.PC+8;
		CURRENT_STATE.PC = target*4; 
	}
//	instruction instrN = *get_inst_info(CURRENT_STATE.PC);
//	if(instrN.value ==0){
//		
//		CURRENT_STATE.PC = tempPC;
//		counter  = 1;
//		
//	}
//	printf("run bit is:%d\n",RUN_BIT);
	if (CURRENT_STATE.PC - MEM_TEXT_START >= 4*NUM_INST) {
	//	counter =1;
		RUN_BIT = 0;
	//	printf("tempPC when counter ==1: %x\n",tempPC);
		CURRENT_STATE.PC = tempPC+4;
	}
//	}
	//printf("testing %d\n", 88>>1);
//	printf("op code is: %d\n",instr.opcode);
//	//printf("func is: %d\n", func);
//	printf("pc is: %x\n",CURRENT_STATE.PC);
}
