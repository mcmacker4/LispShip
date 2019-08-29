#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "lexer.h"
#include "string.h"


Token token_str(TokenType type, const char* str) {
    Token token;
    token.type = type;
    token.str = str;
    return token;
}

Token token_int(TokenType type, int32_t integer) {
    Token token;
    token.type = type;
    token.integer = integer;
    return token;
}


typedef struct _Tokenizer {
    const char* source;
    size_t pos;
    size_t len;
    List tokens;
} Tokenizer;

Tokenizer tokenizer_new(const char* source, size_t len) {
    Tokenizer tokenizer;
    tokenizer.source = source;
    tokenizer.pos = 0;
    tokenizer.len = len;
    tokenizer.tokens = list_new(sizeof(Token));
    return tokenizer;
}

void tk_append_int(Tokenizer* tokenizer, TokenType type, int32_t integer) {
    Token token = token_int(type, integer);
    list_append(&tokenizer->tokens, &token, sizeof(Token));
}

void tk_append_str(Tokenizer* tokenizer, TokenType type, String str) {
    Token token = token_str(type, str);
    list_append(&tokenizer->tokens, &token, sizeof(Token));
}

char tk_peek(Tokenizer* tokenizer) {
    return tokenizer->source[tokenizer->pos];
}

char tk_consume(Tokenizer* tokenizer) {
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
        tk_consume(tokenizer);
    }
}

List tokenize(const char* source, size_t len) {
    Tokenizer tokenizer = tokenizer_new(source, len);
    tk_skip_spaces(&tokenizer);
    while (tokenizer.pos < tokenizer.len) {
        if (tk_peek(&tokenizer) == '(') {
            tokenizer.pos++;
            tk_append_int(&tokenizer, TK_LPAREN, 0);
        } else if (tk_peek(&tokenizer) == ')') {
            tokenizer.pos++;
            tk_append_int(&tokenizer, TK_RPAREN, 0);
        } else if (tk_peek(&tokenizer) == '.') {
            tokenizer.pos++;
            tk_append_int(&tokenizer, TK_DOT, 0);
        } else if (tk_peek(&tokenizer) >= '0' && tk_peek(&tokenizer) <= '9') {
            tk_read_int(&tokenizer);
        } else if (tk_peek(&tokenizer) >= 0x21 && tk_peek(&tokenizer) <= 0x7E) {
            tk_read_symbol(&tokenizer);
        }
        tk_skip_spaces(&tokenizer);
    }
    return tokenizer.tokens;
}