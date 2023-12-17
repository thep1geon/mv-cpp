#ifndef __ARG_H
#define __ARG_H

#include <string>
#include "types.h"
struct Arg {
    enum Type {STR, NUM, IDENT};

    Type type;
    union {
        std::string str;
        i32 num;
    };

    Arg(std::string& str) : type(STR), str(str) {};
    Arg(std::string& str, Type type) : type(type), str(str) {};
    Arg(i32 val) : type(NUM), num(val) {};

    ~Arg() {
        if (type == STR) {
            str.~basic_string();
        }
    }
};

#endif  //__ARG_H
