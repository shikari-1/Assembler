#include <stdio.h>
#include <stdlib.h>   
#include <string.h>
#include "opcodestream.h"

int convertordebug = 0;
int debugConvertor()
{
    return convertordebug;
}

char* integerToBinary(char* inp)
{
    int len = strlen(inp);
    
    return "101010";
}

char *binaryOfOpcode(OpcodeStream *OS)
{
	switch(OS->m_node->m_opcode->type)
	{
		case MOV0:
			return "00000";

		case MOV1:
			return "00001" ;

		case LDB0:
			return "00010" ;

		case LDB1:
			return "00011" ;

		case LDW0:
			return "00100" ;

		case LDW1:
			return "00101" ;

		case STB0:
			return "00110" ;

		case STB1:
			return "00111";

		case STW0:
			return "01000" ;

		case STW1:
			return "01001";   

		case ADD0:
			return "01010";

		case ADD1:
			return "01011";

		case SUB0:
			return  "01100";

		case SUB1:
			return  "01101";

		case MUL0:
			return  "01110";      

		case MUL1:
			return  "01111";

		case DIV0:
			return  "10000";

		case DIV1:
			return  "10001";

		case CMP0:
			return  "10010";

		case CMP1:
			return "10001" ;

		case CAL0:
			return "1111100000" ;

		case INC0:
			return "1111100001" ;

		case DEC0:
			return "1111100010" ;

		case JMP0:
			return "1111100011" ;

		case JMP1:
			return "1111100100" ;

		case JLT0:
			return "1111100101" ;

		case JLT1:
			return "1111100110" ;

		case JGT0:
			return "1111100111" ;

		case JGT1:
			return "1111101000" ;

		case JEQ0:
			return "1111101001" ;

		case JEQ1:
			return "1111101010" ;

		case JNE0:
			return "1111101011" ;

		case JNE1:
			return "1111101100" ;

		case PSH0:
			return "1111101101" ;

		case PSH1:
			return "1111101110" ;

		case POP0:
			return "1111101111" ;

		case POP1:
			return "1111110000" ;

		case RET0:
			return "111111111100" ;

		case HLT0:
			return "111111111101" ;

		case MSF0:
			return "111111111110" ;


		case GPR0:
			return "10000";

		case GPR1:
			return "10001";

		case GPR2:
			return "10010";

		case GPR3:
			return "10011";

		case GPR4:
			return "10100";

		case GPR5:
			return "10101";

		case GPR6:
			return "10110";

		case GPR7:
			return "10111";

		case GPR8:
			return "11000";

		case GPR9:
			return "11001";

		case GPR10:
			return "11010";

		case GPR11:
			return "11011";

		case GPR12:
			return "11100";

		case GPR13:
			return "11101";

		case GPR14:
			return "11110";

		case GPR15:
			return "11111";

		case SPCLK:
			return "00000";

		case SPMKY:
			return "00001";

		case SPFLG:
			return "00010";
            
        case INTEGER:
            return integerToBinary(OS->m_node->m_opcode->name);
	}
}   

char* convertOPCodes(OpcodeStream *OS, int debug)
{
    convertordebug = debug;
    
	int len=0,allot=100;
	char* output=(char*)malloc(allot);
    strcpy(output,"");
    char tempOut[17] = "";
    int insType = 0;
    int remainingOperands = 0;
    char bop[17];
	while(OSHasNext(OS))
	{
		len=strlen(output)+len;
		if(len+16>allot)
		{
			allot=allot*2;
			output=realloc(output,allot);
		}
		strcpy(bop,binaryOfOpcode(OS));
		strcat(tempOut,bop);
        if(remainingOperands==0)
        {
            if(strlen(bop) == 5)
            {
                insType = 0;
                remainingOperands = 2;
            }
            else if(strlen(bop) == 10)
            {
                insType = 1;
                remainingOperands = 1;
            }
            else
            {
                insType = 2;
                remainingOperands = 0;
                int len = strlen(tempOut);
                int i = 16-len;
                for(;i>0;i--)
                    strcat(tempOut,"0");
                strcat(output,tempOut);
                
                if(debugConvertor())
                    printf("\n%s",tempOut);
                
                strcpy(tempOut,"");
            }
        }
        else
        {
            if(insType == 1)
            {
                remainingOperands--;
                int len = strlen(tempOut);
                int i = 16-len;
                for(;i>0;i--)
                    strcat(tempOut,"0");
                
                strcat(output,tempOut);
                if(debugConvertor())
                    printf("\n%s",tempOut);
                strcpy(tempOut,"");
                
            }
            else if(insType == 0)
            {
                remainingOperands--;
                if(remainingOperands == 0)
                {
                    int len = strlen(tempOut);
                    int i = 16-len;
                    for(;i>0;i--)
                        strcat(tempOut,"0");
                    strcat(output,tempOut);
                    if(debugConvertor())
                        printf("\n%s",tempOut);
                    strcpy(tempOut,"");
                }
            }
        }
        
        OSStep(OS);
	}
	return output;
}

