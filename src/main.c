#include <stdio.h>
#include <stdlib.h>

#include "../headers/lexer.h"
#include "../headers/parser.h"
#include "../headers/map.h"

void print_tokens(List* tokens) {
    for (int i = 0; i < tokens->size; i++) {
        Token* token = ((Token*) tokens->data) + i;
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
        if (i < tokens->size - 1) printf(", ");
    }
    printf("\n");
}

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

#define LINE_MAX 128

int main() {

    char* linebuff = calloc(LINE_MAX, sizeof(char));

    while (1) {

        printf("user> ");
        fflush(stdout);

        char* line = fgets(linebuff, LINE_MAX, stdin);

        if (strcmp(line, ".exit\n") == 0) {
            printf("Goodbye.");
            break;
        }

        List tokens = tokenize(linebuff, strlen(line));

        print_tokens(&tokens);
        fflush(stdout);

        Node* node = parse(&tokens);
        print_node(node);
        printf("\n");

    }

    return 0;
}