#ifndef __STACK_H
#define __STACK_H

#include "err.h"
#include "result.h"
#include "types.h"
#include <cstdlib>
#include <iostream>

template<typename T, usize N>
class Stack {
    i32 m_size;
    T m_data[N];
public:
    Stack() {
        m_size = 0;
    }

    ~Stack() {
        m_size = 0;
    };

    Result<None> push(const T& push_data) {
        if (m_size + 1 > (i32)N) {
            return Err("Stack Overflow");
        }

        m_data[m_size++] = push_data;

        return Void();
    }

    Result<T> pop() {
        if (m_size - 1 < 0) {
            return Err("Stack Underflow");
        }

        return m_data[--m_size];
    }

    Result<T> peek() const {
        if (m_size - 1 < 0) {
            return Err("Stack Peek Error");
        }

        return m_data[m_size-1];
    }

    Result<T> at(usize index) {
        if (m_size == 0) {
            return Err("Empty stack at()");
        }

        return m_data[m_size - index - 1];
    }

    T operator[](usize index) {
        return at(index).get_ok();
    }

    void print() const {
        if (m_size == 0) {
            std::cout << "Empty Stack\n";
        }

        for (usize i = 0; i < (usize)m_size; ++i) {
            std::cout << m_data[i] << "\n";
        }
    }

    usize get_len() const {
        return m_size;
    }

    usize get_cap() const {
        return N;
    }
};

#endif  //__STACK_H
