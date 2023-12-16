#ifndef __QUEUE_H
#define __QUEUE_H

#include "types.h"
#include "result.h"
#include <cstdlib>
#include <cstring>
#include <iostream>

template <typename T, usize N>
class Queue {
    i32 m_size;
    T m_data[N];
public:
    Queue() {
        m_size = 0;
    }

    ~Queue() = default;

    Result<None> push(T push_data) {
        if (m_size + 1 > (i32)N) {
            return Err("Queue Overflow");
        } 
        
        m_data[m_size++] = push_data;
        
        return Void();
    }

    Result<T> pop() {
        if (m_size - 1 < 0) {
            return Err("Queue underflow");
        }

        T* ptr = m_data;

        T popped_item = *m_data;
        
        memmove(ptr, ptr + 1, --m_size * sizeof(T));
        
        return popped_item;
    }

    void print() const {
        for (usize i = 0; i < m_size; ++i) {
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

#endif  //__QUEUE_H
