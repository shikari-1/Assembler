#ifndef TOKENSTREAM_H
#define TOKENSTREAM_H

#include "tokentype.h"

typedef struct Token
{
    TokenType kind;
    char name[10];
    long start;
    long end;
    long lineno;
} Token;

typedef struct ListNode
{
    Token m_token;
    struct ListNode* m_next;
    struct ListNode* m_prev;
} ListNode;

typedef struct TokenStream
{
    ListNode* m_start;
    ListNode* m_end;
    ListNode* m_indexNode;
    long m_index;
    long m_size;
} TokenStream;

TokenStream* TSCreate();
void TSInsert(TokenStream* ts, Token token);
TokenType TSLA(TokenStream* ts, int i);
Token TSLAToken(TokenStream* ts, int i);
TokenType TSStep(TokenStream* ts);
Token TSToken(TokenStream* ts);
long TSIndex(TokenStream* ts);
long TSSize(TokenStream* ts);
void TSClear(TokenStream* ts);
void TSDestroy(TokenStream* ts);

#endif
