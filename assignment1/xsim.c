#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xis.h"
#include "xcpu.h"


extern int xcpu_print( xcpu *c );
int main(int argc, char ** argv){
	FILE *f = fopen(*(argv+2),"rb");
	
	if(!f){
		fprintf(stderr, "unable to open file %s",*(argv+2));
		exit(1);
		return 0;
	}

    fseek(f,0L, SEEK_END);
    unsigned long filesize = ftell(f);
  //    fprintf(stdout,"file size: %ld \n" , filesize);
    fseek(f, 0L, SEEK_SET);
    
	unsigned char *buf = (unsigned char *) malloc(XIS_MEM_SIZE);
	if(!buf){
		fprintf(stderr, "memroy error!");
		fclose(f);
		exit(1);
	}
	fread(buf, filesize, 1, f);
	fclose(f);
	xcpu cpu = {buf,{0},0,0,0,0,0};
	int rounds = 0;
	int opcode;
	while(rounds < atoi(*(argv + 1))){
		opcode = xcpu_execute(&cpu);
		if(opcode == 0){
			fprintf(stdout,"CPU has halted.\n");
			break;
		}
        	if((cpu.state == 0x0002) | (cpu.state == 0x0003)) xcpu_print(&cpu);
		
		rounds++;
	}
	if(opcode){
		fprintf(stdout, "CPU ran out of time.\n");
	}
	//fprintf(stdout, "CPU has ran out of time");
	free(buf);
	
	return 0;
}
