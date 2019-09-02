#ifndef LISPSHIT_LEXER_H
#define LISPSHIT_LEXER_H

#include <stdint.h>

#include "list.h"

typedef enum _TokenType {
    TK_LPAREN,
    TK_RPAREN,
    TK_DOT,
    TK_QUOTE,
    TK_SYMBOL,
    TK_INTEGER
} TokenType;

typedef struct _Token {
    TokenType type;
    union {
        const char* str;
        int32_t integer;
    };
    size_t line, column;
} Token;

List tokenize(const char* source, size_t len);

#endif //LISPSHIT_LEXER_H
