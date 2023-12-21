#ifndef __ARG_H
#define __ARG_H

#include <ostream>
#include <variant>
#include <string>
#include "types.h"

struct Arg {
    enum Type { NUM, STR, IDENT };

    Type type;
    std::variant<std::string, i32> data;

    Arg();

    Arg(std::string str, Type type);

    Arg(i32 val);

    Arg(std::string str);
    Arg(const char* str);

    ~Arg() = default;

    i32 get_num() const;
    std::string get_str() const ;

    const char* type_to_cstr() const;
};

std::ostream& operator<<(std::ostream& os, const Arg& a);

#endif  //__ARG_H

