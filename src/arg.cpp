#include "include/arg.h"
#include <cassert>
#include <ostream>
#include <string>
#include <variant>

Arg::Arg() : type(NUM), data(0) {}

Arg::Arg(const std::string& str, Type type) : type(type), data(std::move(str)) {}

Arg::Arg(i32 val) : type(NUM), data(val) {}

Arg::Arg(const char* str) : type(STR), data(std::move(str)) {}

i32 Arg::get_num() const {
    return std::get<i32>(data);
}

std::string Arg::get_str() const {
    return std::get<std::string>(data);
}

const char* Arg::type_to_cstr() const {
    switch (type) {
    case Arg::NUM:
        return "NUM";
    case Arg::STR:
        return "STR";
    case Arg::IDENT:
        return "IDENT";
    default:
        assert(0 && "Unreachable");
    }
}

std::ostream& operator<<(std::ostream& os, const Arg& a) {
    os << "Arg: {type: ";
    switch (a.type) {
    case Arg::NUM:
        os << a.type_to_cstr() << ", value: " << a.get_num() << "}";
        break;
    case Arg::STR:
        os << a.type_to_cstr() << ", value: " << a.get_str() << "}";
        break;
    case Arg::IDENT:
        os << a.type_to_cstr() << ", value: " << a.get_str() << "}";
        break;
    }

    return os;
}
