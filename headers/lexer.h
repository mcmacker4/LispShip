#ifndef LISPSHIT_LEXER_H
#define LISPSHIT_LEXER_H

#include <stdint.h>

#include "list.h"
#include "string.h"

typedef enum _TokenType {
    TK_LPAREN,
    TK_RPAREN,
    TK_DOT,
    TK_QUOTE,
    TK_SYMBOL,
    TK_INTEGER,
    TK_STRING,
} TokenType;

typedef struct _Token {
    TokenType type;
    union {
        String symbol;
        const char* string;
        int32_t integer;
    };
    size_t line, column;
} Token;

List tokenize(const char* source, size_t len);

void tk_print_list(List* tokens);

#endif //LISPSHIT_LEXER_H
