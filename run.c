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
	if(instr.opcode == 0){
		if(func == 8){
		//jr	
		}
		if(func== 33){
		//Addu
			CURRENT_STATE.REGS[instr.r_t.r_i.r_i.r.rd];	
		}
		if(func== 36){
		//And
		}
		if(func== 39){
		//Nor
		}
		if(func== 37){
		//Or
		}
		if(func== 43){
		//Sltu
		}
		if(func== 0){
		//Sll
		}
		if(func== 2){
		//Srl
		}
		if(func== 35){
		//Subu
		}
	}
	printf("op code is: %d\n",instr.opcode);
	printf("pc is: %x\n",CURRENT_STATE.PC);
///	printf("hahahahaha");
	/** Implement this function */
}
