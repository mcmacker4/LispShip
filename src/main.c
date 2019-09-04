#include "../headers/lexer.h"
#include "../headers/parser.h"
#include "../headers/eval.h"
#include "../headers/gc.h"

#include <stdio.h>
#include <string.h>
#include <malloc.h>

int main(int argc, const char** argv) {

    if (argc > 1) {

        const char* filename = argv[1];

        FILE* file = fopen(filename, "r");

        fseek(file, 0, SEEK_END);
        size_t length = ftell(file);
        rewind(file);

        char* buffer = malloc((length + 1) * sizeof(char));
        length = fread(buffer, sizeof(char), length, file);
        buffer[length] = 0;

        List tokens = tokenize(buffer, length);
        Node* ast = parse(&tokens);

        Context ctx = eval_context_new();

        while (ast->type != NODE_NIL) {
            eval(&ctx, node_car(ast));
            ast = node_cdr(ast);
            gc_cleanup(&ctx, ast);
        }

        list_free(&tokens);

        free(buffer);
        context_destroy(&ctx);
        gc_cleanup_all();

    } else {

#define LINE_MAX 128

        char* linebuff = malloc(LINE_MAX);
        Context ctx = eval_context_new();

        while (1) {

            printf("user=> ");
            fflush(stdout);

            char* line = fgets(linebuff, LINE_MAX, stdin);

            if (strcmp(line, ".exit\n") == 0) {
                printf("Goodbye.");
                break;
            }

            List tokens = tokenize(linebuff, strlen(line));

            Node* ast = parse(&tokens);

            while (ast->type != NODE_NIL) {
                Node* result = eval(&ctx, node_car(ast));
                node_print(result);
                printf("\n");
                ast = node_cdr(ast);
                gc_cleanup(&ctx, ast);
            }

            list_free(&tokens);

        }

        free(linebuff);
        context_destroy(&ctx);
        gc_cleanup_all();

    }

    return 0;
}