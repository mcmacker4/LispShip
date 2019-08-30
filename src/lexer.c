#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../headers/lexer.h"
#include "../headers/string.h"

typedef struct _Tokenizer {
    const char* source;
    size_t len;
    size_t pos;
    size_t line;
    size_t column;
    List tokens;
} Tokenizer;

Token token_str(Tokenizer* tokenizer, TokenType type, const char* str) {
    Token token;
    token.type = type;
    token.str = str;
    token.line = tokenizer->line;
    token.column = tokenizer->column;
    return token;
}

Token token_int(Tokenizer* tokenizer, TokenType type, int32_t integer) {
    Token token;
    token.type = type;
    token.integer = integer;
    token.line = tokenizer->line;
    token.column = tokenizer->column;
    return token;
}

Tokenizer tokenizer_new(const char* source, size_t len) {
    Tokenizer tokenizer;
    tokenizer.source = source;
    tokenizer.len = len;
    tokenizer.pos = 0;
    tokenizer.line = 1;
    tokenizer.column = 1;
    tokenizer.tokens = list_new(sizeof(Token));
    return tokenizer;
}

void tk_append_int(Tokenizer* tokenizer, TokenType type, int32_t integer) {
    Token token = token_int(tokenizer, type, integer);
    list_append(&tokenizer->tokens, &token, sizeof(Token));
}

void tk_append_str(Tokenizer* tokenizer, TokenType type, String str) {
    Token token = token_str(tokenizer, type, str);
    list_append(&tokenizer->tokens, &token, sizeof(Token));
}

#define tk_peek(tokenizer) ((tokenizer)->source[(tokenizer)->pos])

char tk_consume(Tokenizer* tokenizer) {
    tokenizer->column++;
    return tokenizer->source[tokenizer->pos++];
}

void tk_read_int(Tokenizer* tokenizer) {
    int32_t value = 0;
    while (tokenizer->pos < tokenizer->len && tk_peek(tokenizer) >= '0' && tk_peek(tokenizer) <= '9') {
        value = value * 10 + (tk_consume(tokenizer) - '0');
    }
    tk_append_int(tokenizer, TK_INTEGER, value);
}

void tk_read_symbol(Tokenizer* tokenizer) {
    char buffer[31];
    size_t pos = 0;
    while (tk_peek(tokenizer) >= 0x21 &&
            tk_peek(tokenizer) <= 0x7E &&
            tk_peek(tokenizer) != '(' &&
            tk_peek(tokenizer) != ')' &&
            tk_peek(tokenizer) != '.') {
        buffer[pos++] = tk_consume(tokenizer);
        if (pos > 30) {
            printf("Symbol exceeds max length of 30");
            exit(-1);
        }
    }
    buffer[pos] = 0;
    tk_append_str(tokenizer, TK_SYMBOL, string_intern(buffer));
}

void tk_skip_spaces(Tokenizer* tokenizer) {
    while (isspace(tk_peek(tokenizer))) {
        if (tk_peek(tokenizer) == '\n') {
            tokenizer->column = 1;
            tokenizer->line++;
        }
        tk_consume(tokenizer);
    }
}

List tokenize(const char* source, size_t len) {
    Tokenizer tokenizer = tokenizer_new(source, len);
    tk_skip_spaces(&tokenizer);
    while (tokenizer.pos < tokenizer.len) {
        if (tk_peek((&tokenizer)) == '(') {
            tk_consume(&tokenizer);
            tk_append_int(&tokenizer, TK_LPAREN, 0);
        } else if (tk_peek((&tokenizer)) == ')') {
            tk_consume(&tokenizer);
            tk_append_int(&tokenizer, TK_RPAREN, 0);
        } else if (tk_peek((&tokenizer)) == '.') {
            tk_consume(&tokenizer);
            tk_append_int(&tokenizer, TK_DOT, 0);
        } else if (tk_peek((&tokenizer)) >= '0' && tk_peek((&tokenizer)) <= '9') {
            tk_read_int(&tokenizer);
        } else if (tk_peek((&tokenizer)) >= 0x21 && tk_peek((&tokenizer)) <= 0x7E) {
            tk_read_symbol(&tokenizer);
        }
        tk_skip_spaces(&tokenizer);
    }
    return tokenizer.tokens;
}