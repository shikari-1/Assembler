#include "tokenstream.h"
#include "tokentype.h"

#include <string.h>
#include <stdlib.h>
#include <string.h>

TokenStream* TSCreate()
{
    TokenStream* ts = malloc(sizeof(TokenStream));
    ts->m_index = -1;
    ts->m_size = 0;
    ts->m_indexNode = NULL;
    return ts;
}

void TSInsert(TokenStream* ts, Token token)
{
    if(ts->m_size == 0)
    {
        ListNode* nn = malloc(sizeof(ListNode));
        nn->m_next = NULL;
        nn->m_prev = NULL;
        nn->m_token.kind = token.kind;
        nn->m_token.end = token.end;
        nn->m_token.start = token.start;
        nn->m_token.lineno = token.lineno;
        strcpy(nn->m_token.name,token.name);
        ts->m_start = nn;
        ts->m_end = nn;
        ts->m_size++;
        ts->m_indexNode;
    }
    else
    {
        ListNode* end = ts->m_end;
        ListNode* nn = malloc(sizeof(ListNode));
        nn->m_next = NULL;
        nn->m_prev = end;
        nn->m_token.kind = token.kind;
        nn->m_token.end = token.end;
        nn->m_token.start = token.start;
        nn->m_token.lineno = token.lineno;
        strcpy(nn->m_token.name,token.name);
        end->m_next = nn;
        ts->m_end = nn;
        ts->m_size++;
    }
}

TokenType TSLA(TokenStream* ts, int i)
{
    if(ts->m_index+i >= ts->m_size)
        return INVALID;
    else
    {
        ListNode* itr = ts->m_indexNode;
        if(itr != NULL)
        {
            for(;i>0;i--)
            {
                itr = itr->m_next;
                if(itr == NULL && i>0)
                    return INVALID;
            }
            
            if(itr != NULL)
            return itr->m_token.kind;
        }
    }
    return INVALID;
}

Token TSLAToken(TokenStream* ts, int i)
{
    Token t;
    t.kind = INVALID;
    if(ts->m_index+i >= ts->m_size)
        return t;
    else
    {
        ListNode* cur = ts->m_indexNode;
        if(cur == NULL)
        {
            ListNode* itr = ts->m_start;
            if(itr == NULL)
                return t;
            for(;i>0;i--)
            {
                itr = itr->m_next;
                if(itr == NULL && i>0)
                    return t;
            }
            
            if(itr == NULL)
                return t;
            
            return itr->m_token;
            
        }
    }
}

TokenType TSStep(TokenStream* ts)
{
    
    if(ts->m_index == ts->m_size-1)
        return INVALID;
    if(ts->m_index == -1)
    {
        ts->m_index++;
        ts->m_indexNode = ts->m_start;
    }
    else
    {        
        ts->m_index++;
        ts->m_indexNode = ts->m_indexNode->m_next;
    }
    return ts->m_indexNode->m_token.kind;
}

Token TSToken(TokenStream* ts)
{
    return ts->m_indexNode->m_token;
}

long TSIndex(TokenStream* ts)
{
    return ts->m_index;
}

long TSSize(TokenStream* ts)
{
    return ts->m_size;
}

void TSClear(TokenStream* ts)
{
    ListNode* itr = ts->m_start;
    ts->m_start = NULL;
    ts->m_end = NULL;
    
    if(itr == NULL)
        return;
    for(;itr!=NULL;itr = itr->m_next)
    {
        free(itr); 
    }
}

void TSDestroy(TokenStream* ts)
{
    TSClear(ts);
    free(ts);
}
