#include <stdio.h>

#include "lexer.h"
#include "parser.h"


void print_node(Node* node) {
    switch (node->type) {
        case NODE_NIL:
            printf("NIL");
            break;
        case NODE_INTEGER:
            printf("%d", node->integer);
            break;
        case NODE_SYMBOL:
            printf("%s", node->symbol);
            break;
        case NODE_PAIR:
            printf("PAIR(");
            print_node(node->left);
            printf(", ");
            print_node(node->right);
            printf(")");
            break;
    }
}


int main() {

    const char* src = "(a (b . c) d e)";

    List tokens = tokenize(src, strlen(src));

    for (int i = 0; i < tokens.size; i++) {
        Token* token = ((Token*) tokens.data) + i;
        switch (token->type) {
            case TK_LPAREN:
                printf("LPAREN");
                break;
            case TK_RPAREN:
                printf("RPAREN");
                break;
            case TK_DOT:
                printf("DOT");
                break;
            case TK_INTEGER:
                printf("INTEGER(%d)", token->integer);
                break;
            case TK_SYMBOL:
                printf("SYMBOL(%s)", token->str);
                break;
        }
        if (i < tokens.size - 1) printf(", ");
    }
    printf("\n");

    Node* node = parse(&tokens);
    print_node(node);
    printf("\n");

    return 0;
}