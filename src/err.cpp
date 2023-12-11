#include "include/err.h"
#include "include/types.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <iostream>

Err::Err() {
    m_msg = "";
    m_type = ErrType::Err;
}

Err::Err(ErrType type, std::string msg) {
    m_type = type;
    m_msg = msg;
}

Err::Err(ErrType type) {
    m_type = type;
    m_msg = "";
}

Err::Err(std::string msg) {
    m_msg = msg;
    m_type = ErrType::Err;
}

Err::~Err() {
    m_msg = "";
    m_type = ErrType::None;
}

void Err::non_fatal() const {
    print();
}

void Err::fatal() const {
    print();
    exit(static_cast<i32>(m_type));
}

ErrType Err::get_type() const {
    return m_type;
}
std::string Err::get_msg() const {
    return m_msg;
}

std::string Err::type_to_str() const {
    switch (m_type) {
        case ErrType::None:          return "None";
        case ErrType::Err:           return "Err";
        case ErrType::StackOverflow: return "StackOverflow";
        default:                     return "Unknown Err";
    }
}

void Err::print() const {
    std::cerr << "Error!\n";
    std::cerr << "    Type      ~~> " << type_to_str() << "\n";
    std::cerr << "    Message   ~~> " << m_msg << "\n";
    std::cerr << "    Exit Code ~~> " << static_cast<i32>(m_type) << "\n";
}
