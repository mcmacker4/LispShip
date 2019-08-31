#include "../headers/parser.h"
#include "../headers/lexer.h"

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


int parser_has_next(Parser* parser) {
    return parser->pos < parser->tokens->size;
}

Token* parser_peek(Parser* parser) {
    return ((Token*) parser->tokens->data) + parser->pos;
}

Token* parser_consume(Parser* parser) {
    return ((Token*) parser->tokens->data) + parser->pos++;
}

#define SYNTAX_ERROR(str, token) {\
    printf("(%zu:%zu) %s\n", (token)->line, (token)->column, str);\
    exit(-1);\
}

#define SYNTAX_ERROR_M(str) {\
    printf("%s\n", str);\
}

#define EOF_CHECK(parser) if(!parser_has_next(parser)) SYNTAX_ERROR_M("Unexpected EOF.")

#define EXPECT_TOKEN(parser, ttype) if(parser_peek(parser)->type != (ttype)) {\
    printf("Expected token of type %d but found type %d", (ttype), parser_peek(parser)->type);\
    exit(-1);\
} else {\
    parser_consume(parser);\
}

Node* parse_any(Parser* parser);

Node* parse_list(Parser* parser) {
    EOF_CHECK(parser)
    switch (parser_peek(parser)->type) {
        case TK_RPAREN:
            parser_consume(parser);
            return node_new_nil();
        case TK_DOT:
            SYNTAX_ERROR("Unexpected dot while parsing list.", parser_peek(parser))
        default: {
            Node* left = parse_any(parser);
            Node* right = parse_list(parser);
            Node* result = node_new_pair(left, right);
            result->props |= NP_LIST;
            return result;
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
            SYNTAX_ERROR("Unexpected dot when parsing list or pair.", parser_peek(parser))
        default: {
            Node* left = parse_any(parser);
            Node* right;
            uint8_t props = 0;
            if (parser_peek(parser)->type == TK_DOT) {
                parser_consume(parser);
                right = parse_any(parser);
                EXPECT_TOKEN(parser, TK_RPAREN)
            } else {
                right = parse_list(parser);
                props |= NP_LIST;
            }
            Node* result = node_new_pair(left, right);
            result->props = props;
            return result;
        }
    }
}

Node* parse_any(Parser* parser) {
    EOF_CHECK(parser)
    switch (parser_peek(parser)->type) {
        case TK_LPAREN:
            parser_consume(parser);
            return parse_list_or_pair(parser);
        case TK_QUOTE:
            parser_consume(parser);
            Node* node = parse_any(parser);
            node->props |= NP_LITERAL;
            return node;
        case TK_SYMBOL:
            return node_new_symbol(parser_consume(parser)->str);
        case TK_INTEGER:
            return node_new_integer(parser_consume(parser)->integer);
        default:
            SYNTAX_ERROR("Unexpected token while parsing anything.", parser_peek(parser))
    }
}

Node* parse_top_list(Parser* parser) {
    Node* left = parse_any(parser);
    Node* right;
    if (parser_has_next(parser)) {
        right = parse_top_list(parser);
    } else {
        right = node_new_nil();
    }
    return node_new_pair(left, right);
}

Node* parse(List* tokens) {
    Parser parser = parser_new(tokens);
    return parse_top_list(&parser);
}