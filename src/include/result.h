#ifndef __RESULT_H
#define __RESULT_H

#include <iostream>
#include "./err.h"

typedef void* None;

template <typename T>
class Result {
    T m_ok;
    Err m_err;

    bool m_has_ok = false;
    bool m_has_err = false;
    bool m_has_void = false;

public:
    Result() {
        m_err = Ok();
        m_has_void = true;
    }

    Result(T ok) {
        m_err = Ok();
        m_ok = ok;
        m_has_ok = true;
    }

    Result(Err e) {
        m_err = e;
        m_has_err = true;
    }

    bool is_ok() const {
        return m_has_ok;
    }

    bool is_err() const {
        return m_has_err;
    }

    bool is_void() const {
        return m_has_void;
    }

    const T& get_ok() const {
        if (!is_ok()) {
            Err("Failed to get okay value from error or void result").non_fatal();
            m_err.fatal();
        }

        return m_ok;
    };

    const Err& get_err() const {
        return m_err;
    };

    void print() const {
        if (is_ok()) {
            std::cout << "Okay Value" << "\n";
            std::cout << "Value: " << m_ok << "\n";
        } else if (is_err()) {
            std::cout << "Error Value" << "\n";
            m_err.print();
        } else if (is_void()) {
            std::cout << "Void Value" << "\n";
        }
    }
};

#define Void() Result<None>()

#endif  //__RESULT_H
