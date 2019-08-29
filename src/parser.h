#ifndef LISPSHIT_PARSER_H
#define LISPSHIT_PARSER_H

#include <stdint.h>
#include "string.h"

#include "node.h"

Node* parse(List* tokens);


#endif //LISPSHIT_PARSER_H
