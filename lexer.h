#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include "opcodestream.h"
#include "tokenstream.h"
#include "tokentype.h"

typedef struct Lexer
{
    TokenStream* m_tokenStream;
    char* m_contents;
    long m_currPos;
    long m_contentSize;
    long m_line;
    long m_pos;
} Lexer;

Lexer* lexerOpen(TokenStream* ts, char* contents, int debug);
void lexerClose(Lexer* lex);
Token lexerNextTokenKind(Lexer* lex);

#endif
