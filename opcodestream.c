#include "opcodestream.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int opcodedebug = 0;
int debugopcode()
{
    return opcodedebug;
}

OpcodeStream* OSCreate(int debug)
{
    opcodedebug = debug;
    OpcodeStream * os = malloc(sizeof(OpcodeStream));
    os->m_index = -1;
    os->m_node = NULL;
    return os;
}

void OSInsert(OpcodeStream* os, OpcodeType opc, char* name)
{
    if(os->m_index < 0)
    {
        if(debugopcode())
            printf("%s ",name);
        OpcodeNode* nn = malloc(sizeof(OpcodeNode));
        nn->m_next = NULL;
        nn->m_prev = NULL;
        Opcode* op = malloc(sizeof(Opcode));
        op->type = opc;
        strcpy(op->name,name);
        nn->m_opcode = op;
        os->m_node = nn;
        os->m_end = nn;
        os->m_start = nn;
        os->m_index++;
    }
    else
    {
        if(debugopcode())
            printf("%s ",name);
        OpcodeNode* end = os->m_end;
        OpcodeNode* nn = malloc(sizeof(OpcodeNode));
        nn->m_next = NULL;
        nn->m_prev = end;
        Opcode* op = malloc(sizeof(Opcode));
        op->type = opc;
        strcpy(op->name,name);
        nn->m_opcode = op;
        end->m_next = nn;
        os->m_end = nn;
        os->m_index++;
    }
}

void OSStep(OpcodeStream* os)
{
    os->m_node = os->m_node->m_next;
}

int OSHasNext(OpcodeStream* os)
{
    if(os->m_node != NULL)
        return 1;
    return 0;
}

void OSClear(OpcodeStream* os)
{
    OpcodeNode* itr = os->m_start;
    os->m_start = NULL;
    os->m_end = NULL;
    
    if(itr == NULL)
        return;
    for(;itr!=NULL;itr = itr->m_next)
    {
        free(itr->m_opcode);
        free(itr); 
    }
}

void OSDestroy(OpcodeStream* os)
{
    OSClear(os);
    free(os);
}
