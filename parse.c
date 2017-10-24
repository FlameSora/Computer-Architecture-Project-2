/***************************************************************/
/*                                                             */
/*   MIPS-32 Instruction Level Simulator                       */
/*                                                             */
/*   CS311 KAIST                                               */
/*   parse.c                                                   */
/*                                                             */
/***************************************************************/

#include <stdio.h>

#include "util.h"
#include "parse.h"

int text_size;
int data_size;

instruction parsing_instr(const char *buffer, const int index)
{
    instruction instr;
    char *op = malloc(6);
    char *func = malloc(6);
    int i;
    char *rs = malloc(5);
    char *rt = malloc(5);
    char *rd = malloc(5);
    char *imm = malloc(16);
    char *shamt = malloc(5);
    char *target = malloc(26);
    for(i=0; i<6;i++){
	op[i] = buffer[i];
    }	
    for (i = 0; i<6; i++){
	func[i] = buffer[31-5+i];
    }
    for(i=0;i<5;i++){
	rs[i] = buffer[5+i];	
    }
    for(i=0;i<5;i++){
	rt[i] = buffer[10+i];	
    }
    for(i=0;i<5;i++){
	rd[i] = buffer[15+i];	
    }
    for(i=0;i<16;i++){
	imm[i] = buffer[15+i];	
    }
    for(i=0;i<5;i++){
	shamt[i] = buffer[20+i];
    }	
    for(i=0;i<26;i++){
 	target[i] = buffer[5+i];
    }
    if(fromBinary(op) == 0){
// R type or jr
	
	if(fromBinary(func) ==8){
	//jr case
		instr.opcode = fromBinary(op); 
		instr.func_code = fromBinary(func);
		instr.r_t.r_i.rs = fromBinary(rs);
        }
	else{
   	//R type
		instr.opcode = fromBinary(op); 
		instr.func_code = fromBinary(func);
		instr.r_t.r_i.rs = fromBinary(rs);
		instr.r_t.r_i.rt = fromBinary(rt);
 		instr.r_t.r_i.r_i.r.rd = fromBinary(rd);
		instr.r_t.r_i.r_i.r.shamt = fromBinary(shamt);	
				
        }
    }
    else if((fromBinary(op) == 3)|(fromBinary(op)==2)){
 	instr.opcode = fromBinary(op);
	instr.r_t.target = fromBinary(target);
    }
    else {	
	instr.opcode = fromBinary(op); 
	instr.r_t.r_i.rs = fromBinary(rs);
 	instr.r_t.r_i.rt = fromBinary(rt);
	instr.r_t.r_i.r_i.imm = fromBinary(imm);
    }
    printf("instr's op is %d\n",instr.opcode); 
    printf("op to binary: %d, func is %d\n",fromBinary(op),fromBinary(func));		
    printf("index is %d\n",index);
    printf("buffer is %s\n", buffer);
    return instr;
}

void parsing_data(const char *buffer, const int index)
{
	char *number = (char *)malloc(32);
	int i;

	for (i = 0; i<32; i++) {
		number[i] = buffer[i];
	}

	uint32_t data = (uint32_t) fromBinary(number);
	mem_write_32(MEM_DATA_START + index, data);
}

void print_parse_result()
{
    int i;
    printf("Instruction Information\n");

    for(i = 0; i < text_size/4; i++)
    {
	printf("INST_INFO[%d].value : %x\n",i, INST_INFO[i].value);
	printf("INST_INFO[%d].opcode : %d\n",i, INST_INFO[i].opcode);

	switch(INST_INFO[i].opcode)
	{
	    //Type I
	    case 0x9:		//(0x001001)ADDIU
	    case 0xc:		//(0x001100)ANDI
	    case 0xf:		//(0x001111)LUI	
	    case 0xd:		//(0x001101)ORI
	    case 0xb:		//(0x001011)SLTIU
	    case 0x23:		//(0x100011)LW	
	    case 0x2b:		//(0x101011)SW
	    case 0x4:		//(0x000100)BEQ
	    case 0x5:		//(0x000101)BNE
		printf("INST_INFO[%d].rs : %d\n",i, INST_INFO[i].r_t.r_i.rs);
		printf("INST_INFO[%d].rt : %d\n",i, INST_INFO[i].r_t.r_i.rt);
		printf("INST_INFO[%d].imm : %d\n",i, INST_INFO[i].r_t.r_i.r_i.imm);
		break;

    	    //TYPE R
	    case 0x0:		//(0x000000)ADDU, AND, NOR, OR, SLTU, SLL, SRL, SUBU  if JR
		printf("INST_INFO[%d].func_code : %d\n",i, INST_INFO[i].func_code);
		printf("INST_INFO[%d].rs : %d\n",i, INST_INFO[i].r_t.r_i.rs);
		printf("INST_INFO[%d].rt : %d\n",i, INST_INFO[i].r_t.r_i.rt);
		printf("INST_INFO[%d].rd : %d\n",i, INST_INFO[i].r_t.r_i.r_i.r.rd);
		printf("INST_INFO[%d].shamt : %d\n",i, INST_INFO[i].r_t.r_i.r_i.r.shamt);
		break;

    	    //TYPE J
	    case 0x2:		//(0x000010)J
	    case 0x3:		//(0x000011)JAL
		printf("INST_INFO[%d].target : %d\n",i, INST_INFO[i].r_t.target);
		break;

	    default:
		printf("Not available instruction\n");
		assert(0);
	}
    }

    printf("Memory Dump - Text Segment\n");
    for(i = 0; i < text_size; i+=4)
	printf("text_seg[%d] : %x\n", i, mem_read_32(MEM_TEXT_START + i));
    for(i = 0; i < data_size; i+=4)
	printf("data_seg[%d] : %x\n", i, mem_read_32(MEM_DATA_START + i));
    printf("Current PC: %x\n", CURRENT_STATE.PC);
}
