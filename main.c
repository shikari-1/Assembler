#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

void help()
{
    printf("\nAssembler For a 16 Bit ISA");
    printf("\nUse : assembler path/to/input/file path/to/output/file [OPTIONS]\n");
    printf("\nOptions");
    printf("\n-v : verbose output\n");
}

int main(int argc, char **argv) {
    
    if(argc < 3)
    {
        if(argc == 1)
            printf("\nNo Input File Selected !!!\n");
        if(argc == 2)
            printf("\nNo Output File Selected !!!\n");
        help();
        return 0;
    }
    int debug = 0;
    if(argc == 4 && !strcmp(argv[3],"-v"))
    {
        debug = 1;
    }
    else
    {
        if(argc == 4)
        {
            printf("\nOption %s do not exist\n",argv[3]);
            help();
        }
        debug = 0;        
    }
    
    FILE* fptr = fopen(argv[1],"r");
    if(fptr == NULL)
    {
        printf("\nCannot Read From File %s!!!\n",argv[1]);
        help();
        return 0;
    }
    
    fseek(fptr, 0, SEEK_END);
	long tempsize = ftell(fptr);
	fseek(fptr, 0, SEEK_SET);
	char *input = malloc (sizeof (char) * tempsize);
    strcpy(input,"");
    fread(input,1,tempsize,fptr);
	fclose(fptr);
    char* output = NULL;
    
    Parser* pr = createParser(input,debug);
    output = parseOPCode(pr);
    
    if(parserContainsError(pr))
    {
        long lineno = 0;
        long pos = 0;
        long ins = 0;
        char* error = parserError(pr,&lineno,&pos,&ins);
        printf("\nError in Instruction %ld at [%ld:%ld] ",ins,lineno,pos);
        printf("\n%s\n",error);
        return 0;
    }
    
    
    
    fptr = fopen(argv[2],"w");
    if(fptr == NULL)
    {
        printf("\nCannot Write to File %s!!!\n",argv[2]);
        help();
        return 0;
    }
    tempsize = strlen(output);
    fwrite(output,1,tempsize,fptr);
	fclose(fptr);
       
    free(input);
    free(output);
    destroyParser(pr); 
    
    return 0;
}
