#ifndef __STACK_H
#define __STACK_H

#include "err.h"
#include "result.h"
#include "types.h"
#include <cstddef>
#include <cstdlib>
#include <iostream>

template<typename T>
class Stack {
    usize m_size;
    usize m_cap;
    T* m_data;

    Result<None> resize_stack() {
        m_cap *= 2;
        T* new_data = (T*)realloc(m_data, m_cap*sizeof(T));

        if (new_data == NULL) {
            return Err("Failed to reallocate data");
        }

        m_data = new_data;
        return Void(); 
    }

public:
    Stack() {
        m_size = 0;
        m_cap = 1024;
        m_data = (T*)malloc(m_cap * sizeof(T));
    }

    ~Stack() {
        m_size = 0;
        free(m_data);
    };

    Result<None> push(const T& push_data) {
        if (m_size + 1 >= m_cap) {
            Result r = resize_stack();
            if (r.is_err()) {return r.get_err();}
        }

        m_data[m_size++] = push_data;

        return Void();
    }

    Result<T> pop() {
        if (m_size == 0) {
            return Err("Stack Underflow");
        }

        return m_data[--m_size];
    }

    Result<T> peek() const {
        if (m_size == 0) {
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
        return m_cap;
    }
};

#endif  //__STACK_H
