#ifndef LISPSHIT_STRING_H
#define LISPSHIT_STRING_H

#include <stdint.h>
#include "list.h"

typedef const char* String;

String string_intern(String str);

#endif //LISPSHIT_STRING_H
