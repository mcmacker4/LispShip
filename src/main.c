#include "../headers/lexer.h"
#include "../headers/parser.h"
#include "../headers/eval.h"
#include "../headers/gc.h"

#include <stdio.h>
#include <string.h>
#include <malloc.h>

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
            case TK_QUOTE:
                printf("QUOTE");
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

#define LINE_MAX 128

int main() {

    char* linebuff = malloc(LINE_MAX);
    Context ctx = eval_context_new();

    while (1) {

        printf("user> ");
        fflush(stdout);

        char* line = fgets(linebuff, LINE_MAX, stdin);

        if (strcmp(line, ".exit\n") == 0) {
            printf("Goodbye.");
            break;
        }

        List tokens = tokenize(linebuff, strlen(line));

        Node* ast = parse(&tokens);

        while (ast->type != NODE_NIL) {
            Node* result = eval(&ctx, ast->left);
            node_print(result);
            printf("\n");
            ast = ast->right;
        }

        list_free(&tokens);

        gc_cleanup(&ctx);

    }

    free(linebuff);
    context_destroy(&ctx);
    gc_cleanup_all();

    return 0;
}