#ifndef __OPTION_H
#define __OPTION_H

#include "result.h"
#include <iostream>

template <typename T>
class Option {
    T m_value;
    bool m_has_value;
public:
    Option() {
        m_has_value = false;
    }

    Option(T val) {
        m_value = val;
        m_has_value = true;
    }

    bool has_value() const {
        return m_has_value;
    }

    Result<T> get_value() const {
        if (has_value()) {
            return m_value;
        }

        return Err("Optional value not found");
    }

    void set_value(T val) {
        m_value = val;
        m_has_value = true;
    }

    void print() const {
        std::cout << m_value << "\n";
    }
};

#endif  //__OPTION_H
