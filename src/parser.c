#include "parser.h"
#include "lexer.h"

#include <stdio.h>
#include <stdlib.h>


typedef struct _Parser {
    List* tokens;
    size_t pos;
} Parser;

Parser parser_new(List* tokens) {
    Parser parser;
    parser.tokens = tokens;
    parser.pos = 0;
    return parser;
}

Node* node_new_nil() {
    Node* node = malloc(sizeof(Node));
    node->type = NODE_NIL;
    node->integer = 0;
    return node;
}

Node* node_new_pair(Node* left, Node* right) {
    Node* node = malloc(sizeof(Node));
    node->type = NODE_PAIR;
    node->left = left;
    node->right = right;
    return node;
}

Node* node_new_integer(int32_t integer) {
    Node* node = malloc(sizeof(Node));
    node->type = NODE_INTEGER;
    node->integer = integer;
    return node;
}

Node* node_new_symbol(String symbol) {
    Node* node = malloc(sizeof(Node));
    node->type = NODE_SYMBOL;
    node->symbol = symbol;
    return node;
}


int parser_has_next(Parser* parser) {
    return parser->pos < parser->tokens->size;
}

Token* parser_peek(Parser* parser) {
    return ((Token*) parser->tokens->data) + parser->pos;
}

Token* parser_consume(Parser* parser) {
    return ((Token*) parser->tokens->data) + parser->pos++;
}

#define SYNTAX_ERROR(str) {\
    printf(str);\
    exit(-1);\
}

#define EOF_CHECK(parser) if(!parser_has_next(parser)) SYNTAX_ERROR("Unexpected EOF.")

Node* parse_any(Parser* parser);

Node* parse_list(Parser* parser) {
    EOF_CHECK(parser)
    switch (parser_peek(parser)->type) {
        case TK_RPAREN:
            return node_new_nil();
        case TK_DOT:
            SYNTAX_ERROR("Unexpected token.")
        default: {
            Node* left = parse_any(parser);
            Node* right = parse_list(parser);
            return node_new_pair(left, right);
        }
    }
}

Node* parse_list_or_pair(Parser* parser) {
    EOF_CHECK(parser)
    switch (parser_peek(parser)->type) {
        case TK_RPAREN:
            parser_consume(parser);
            return node_new_nil();
        case TK_DOT:
            SYNTAX_ERROR("Unexpected token.")
        default: {
            Node* left = parse_any(parser);
            Node* right;
            if (parser_peek(parser)->type == TK_DOT) {
                parser_consume(parser);
                right = parse_any(parser);
            } else {
                right = parse_list(parser);
            }
            return node_new_pair(left, right);
        }
    }
}

Node* parse_any(Parser* parser) {
    EOF_CHECK(parser)
    switch (parser_peek(parser)->type) {
        case TK_LPAREN:
            parser_consume(parser);
            return parse_list_or_pair(parser);
        case TK_SYMBOL:
            return node_new_symbol(parser_consume(parser)->str);
        case TK_INTEGER:
            return node_new_integer(parser_consume(parser)->integer);
        default:
            SYNTAX_ERROR("Unexpected token.")
    }
}

Node* parse(List* tokens) {
    Parser parser = parser_new(tokens);
    return parse_any(&parser);
}