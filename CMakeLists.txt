cmake_minimum_required(VERSION 3.14)
project(LispShit C)

set(CMAKE_C_STANDARD 99)

add_executable(LispShit src/main.c src/lexer.c src/lexer.h src/list.h src/string.h src/string.c src/list.c src/parser.c src/parser.h src/node.h)