cmake_minimum_required(VERSION 3.14)
project(LispShit C)

set(CMAKE_C_STANDARD 11)

add_executable(LispShit src/main.c src/lexer.c headers/lexer.h headers/list.h headers/string.h src/string.c src/list.c src/parser.c headers/parser.h headers/node.h src/map.c headers/map.h src/eval.c headers/eval.h src/context.c headers/context.h src/builtins.c headers/builtins.h src/node.c src/gc.c headers/gc.h)