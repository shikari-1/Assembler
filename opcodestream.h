#ifndef OPCODESTREAM_H
#define OPCODESTREAM_H

typedef enum OpcodeType
{
    //dyadic instructions
    MOV0,
    MOV1,
    LDB0,
    LDB1,
    LDW0,
    LDW1,
    STB0,
    STB1,
    STW0,
    STW1,
    ADD0,
    ADD1,
    SUB0,
    SUB1,
    MUL0,
    MUL1,
    DIV0,
    DIV1,
    CMP0,
    CMP1,
    // monadic instructions
    CAL0,
    INC0,
    DEC0,
    JMP0,
    JMP1,
    JLT0,
    JLT1,
    JGT0,
    JGT1,
    JEQ0,
    JEQ1,
    JNE0,
    JNE1,
    PSH0,
    PSH1,
    POP0,
    POP1,
    // 0 operand instructions
    HLT0,
    RET0,
    MSF0,
    
    // Registers
    GPR0,
    GPR1,
    GPR2,
    GPR3,
    GPR4,
    GPR5,
    GPR6,
    GPR7,
    GPR8,
    GPR9,
    GPR10,
    GPR11,
    GPR12,
    GPR13,
    GPR14,
    GPR15,
    SPCLK,
    SPMKY,
    SPFLG,
    
    // extra
    INTEGER,
    STRINGVAL
    
} OpcodeType;

typedef struct Opcode{
    OpcodeType type;
    char name[10];
} Opcode;

typedef struct OpcodeNode
{
    Opcode* m_opcode;
    struct OpcodeNode* m_next;
    struct OpcodeNode* m_prev;
} OpcodeNode;

typedef struct OpcodeStream
{
    OpcodeNode* m_node;
    OpcodeNode* m_end;
    OpcodeNode* m_start;
    long m_index;
} OpcodeStream;

OpcodeStream* OSCreate();
void OSInsert(OpcodeStream* os, OpcodeType opt, char* name);
void OSStep(OpcodeStream* os);
int OSHasNext(OpcodeStream* os);
void OSClear(OpcodeStream* os);
void OSDestroy(OpcodeStream* os);

#endif
