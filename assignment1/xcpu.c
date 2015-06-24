#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define X_INSTRUCTIONS_NOT_NEEDED

#include "xis.h"
#include "xcpu.h"

	
void xcpu_print( xcpu *c ) {
  int i;

  fprintf( stdout, "PC: %4.4x, State: %4.4x: Registers:\n", c->pc, c->state );
  for( i = 0; i < X_MAX_REGS; i++ ) {
    fprintf( stdout, " %4.4x", c->regs[i] );
  }
  fprintf( stdout, "\n" );
}

extern int xcpu_execute( xcpu *c ) {
	
  /* Your code here */
  unsigned char op = c->memory[c->pc];
  unsigned char op2 = c->memory[c->pc + 1];
  unsigned char r1 = XIS_REG1(op2);
  unsigned char r2 = XIS_REG2(op2);
  c->pc = c->pc + 2;
  unsigned char op3 = c->memory[c->pc];
  unsigned char op4 = c->memory[c->pc + 1];
  //fprintf(stdout,"r1:%4.4x\t,r2:%4.4x\t,op:%4.4x\t,pc:%d\t\n",r1, r2, op, c->pc);
  switch(op){
  	case I_BAD: 
	return 0;
  	case I_RET:
  		c->pc =(c->memory[c->regs[X_STACK_REG] + 1  ] << 8) | c->memory[c->regs[X_STACK_REG]  ];
  		//fprintf(stdout, "return instruction %4.4x\t, pc number :%4.4x \t \n", c->regs[X_STACK_REG],c->pc);
  		c->regs[X_STACK_REG] +=2 ;
  		break;	
	case I_CLD:
		c->state = c->state & 0xFFFD;
		break;
	case I_STD: 
		c->state = c->state | 0x0002;
		break;
	case I_NEG:
		c->regs[r1] = -(c->regs[r1]);
		break;
	case I_NOT:
		c->regs[r1] = !c->regs[r1];
		break;
 	case I_INC:
 		c->regs[r1] = c->regs[r1] + 1;
 		break;
	case I_DEC:
		c->regs[r1] = c->regs[r1] - 1;
		break;
	case I_PUSH:
	 	c->regs[X_STACK_REG] = c->regs[X_STACK_REG] - 2;
	 	c->memory[c->regs[X_STACK_REG] + 1 ] = c->regs[r1] & 0x00FF ;
	 	c->memory[c->regs[X_STACK_REG]  ] = c->regs[r1] >> 8;
	 	//fprintf(stdout, "c->memory[c->regs[X_STACK_REG]  + 1] instruction: %4.4x\t, c->memory[c->regs[X_STACK_REG] ]:%4.4x \t \n", c->memory[c->regs[X_STACK_REG]  + 1],c->memory[c->regs[X_STACK_REG] ]);
	 	break;
	case I_POP:
		c->regs[r1] = (c->memory[c->regs[X_STACK_REG] ] << 8 )| c->memory[c->regs[X_STACK_REG]  + 1];
		c->regs[X_STACK_REG] = c->regs[X_STACK_REG] + 2;
		break;
	case I_JMPR:
		c->pc = c->regs[r1];
		break;
	case I_CALLR:
		//fprintf(stdout, "callr instruction %4.4x\t, pc number :%4.4x \t \n", c->regs[X_STACK_REG],c->pc);
		c->regs[X_STACK_REG] = c->regs[X_STACK_REG] - 2;
		c->memory[c->regs[X_STACK_REG] ] = c->pc   & 0x00FF;
		c->memory[c->regs[X_STACK_REG]  +1] = c->pc >> 8;
		c->pc = c->regs[r1];
		
		break;
	case I_OUT:
		fprintf(stdout, "%c", c->regs[r1]);
		break;
	case I_BR:
		if((c->state & 0x0001) == 0x0001){

			c->pc = c->pc - 2 + (char)op2;
			//fprintf(stdout, "c->memory[op2]:%d\t, op: %4.4x\t\n",c->memory[op2],(op2 >> 8) &0x00FF );
			
		}
		break;
	case I_JR:
		c->pc = c->pc - 2  + (char)op2;
		break;
	case I_ADD:
		c->regs[r2] += c->regs[r1] ;
		break;
	case I_SUB:
		c->regs[r2] -= c->regs[r1];
		break;
	case I_MUL:
		c->regs[r2] *= c->regs[r1];
		break;
	case I_DIV:
		c->regs[r2] /= c->regs[r1];
		break;
	case I_AND:
		c->regs[r2] = c->regs[r2] & c->regs[r1];
		break;
	case I_OR:
		c->regs[r2] = c->regs[r2] | c->regs[r1];
		break;
	case I_XOR:
		c->regs[r2] = c->regs[r2] ^ c->regs[r1];
		break;
	case I_SHR:
		c->regs[r2] = c->regs[r2] >> c->regs[r1];
		break;
	case I_SHL:
		c->regs[r2] = c->regs[r2] << c->regs[r1];
		break;
	case I_TEST:
		if((c->regs[r1] & c->regs[r2]) != 0){
			c->state = c->state | 0x0001;
		}else{
			c->state = c->state & 0xFFFE;
		}
		break;
	case I_CMP:
		if(c->regs[r1] < c->regs[r2]){
			c->state = c->state| 0x0001;
		}else{
			c->state = c->state & 0xFFFE;
		}
		break;
	case I_EQU:
		if(c->regs[r1] == c->regs[r2]){
			c->state = c->state |0x0001;
		}else{
			c->state = c->state & 0xFFFE;
		}
		break;
	case I_MOV:
		c->regs[r2] = c->regs[r1];
		break;
	case I_LOAD:
		c->regs[r2] = (c->memory[c->regs[r1] ] << 8) | c->memory[c->regs[r1]  + 1];
		//fprintf(stdout, "c->memory[c->regs[r1]] << 8 instruction: %4.4x\t, c->memory[c->regs[r1] + 1] :%4.4x \t \n",c->memory[c->regs[r1]] ,c->memory[c->regs[r1]  + 1]);
		break; 
	case I_STOR:
		c->memory[c->regs[r2]] = c->regs[r1] >> 8;
		c->memory[c->regs[r2] + 1] = c->regs[r1] & 0x00FF;
		break;
	case I_LOADB:
		c->regs[r2] = c->memory[c->regs[r1]]  ;
		break;
	case I_STORB:
		c->memory[c->regs[r2]] = c->regs[r1]  & 0x00FF;
		break;
	case I_JMP:
		c->pc = (op3 <<8)|op4;
		break;
	case I_CALL:
		
		c->regs[X_STACK_REG] = c->regs[X_STACK_REG]  - 2;
		c->memory[c->regs[X_STACK_REG] ] = (c->pc +2)   & 0x00FF;
		c->memory[c->regs[X_STACK_REG]  +1] = (c->pc + 2) >>8; 
		//fprintf(stdout, "call instruction %4.4x\t, pc number :%4.4x \t \n", c->regs[X_STACK_REG],(c->memory[c->regs[X_STACK_REG]  +1 ] << 8) | c->memory[c->regs[X_STACK_REG] ]);
		c->pc = (op3 <<8) | op4;
		
		break;
	case I_LOADI:
		c->regs[r1] =(c->memory[ c->pc ]<< 8)| (c->memory[c->pc + 1]);
		c->pc = c->pc + 2;		
		break;
	default: 
	     return 0;
 }

  
  return 1; /* replace this as needed */
}


/* Not needed for assignment 1 */
int xcpu_exception( xcpu *c, unsigned int ex ) {
  return 0;
}
