#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

#include "result.h"
#include "types.h"
#include <cstddef>
#include <iostream>
#include <type_traits>

template <typename T>
struct Node {
    T data;
    Node<T>* next;

    Node(T data) {
        this->data = data;
        this->next = NULL;
    }

    Node() {
        this->next = NULL;
    }



    ~Node() { 
        this->next = NULL; 
    }

    void print() const {
        std::cout << "Node: " << data << "\n";
    }
};

template <typename T>
class LinkedList {
    Node<T>* m_head;
    usize m_len;
public:
    LinkedList() {
        m_head = NULL;
        m_len = 0;
    }

    ~LinkedList() {
        Node<T>* current = m_head;
        Node<T>* next;

        while (current != nullptr) {
            next = current->next;
            delete current;
            current = next;
        }

        m_head = nullptr; // Ensure that the head is set to null after deallocating all nodes
        m_len = 0;        // Reset the length to zero
    }

    Result<Node<T>*> get_head() {
        if (m_len == 0 || m_head == NULL) {
            return Err("LinkedList missing head");
        }


        return m_head;
    }

    Result<Node<T>> at(usize index) const {
        if (m_len == 0) {
            return Err("LinkedList at(): Empty LinkedList");
        }

        if (index >= m_len) {
            return Err("LinkedList at(): Invalid Index");
        }

        Node<T>* curr_node = m_head;

        usize i = 0;
        for (; i < index; ++i) {
            curr_node = curr_node->next;    
        } 

        return *curr_node;
    }

    T operator[](usize index) const {
        return at(index).get_ok().data;
    }


    void push(T data) {
        if (m_len == 0) {
            m_head = new Node<T>(data);
            m_len++;
            return;
        }

        Node<T>* curr_node = m_head; 

        while (curr_node->next != NULL) {
            curr_node = curr_node->next;
        }

        curr_node->next = new Node<T>(data);
        m_len++;
    }

    Result<T> pop() {
        if (m_len == 0) {
            return Err("Tried to pop from an empty LinkedList");
        }

        Node<T>* curr_node = m_head;
        Node<T>* prev_node = nullptr;

        // Traverse until the last node
        while (curr_node->next != nullptr) {
            prev_node = curr_node;
            curr_node = curr_node->next;
        }

        T popped_data = curr_node->data;

        if (prev_node == nullptr) {
            m_head = nullptr;  // If there was only one node
        } else {
            prev_node->next = nullptr;
        }

        delete curr_node;
        m_len--;

        return popped_data;
    }

    usize len() const {
        return m_len;
    }

    void print() const {
        if (m_len == 0) {
            std::cout << "Empty Linked List\n";
            return;
        }

        Node<T>* curr_node = m_head;

        while (curr_node != NULL) {
            T data = curr_node->data;

            std::cout << data << "\n";

            curr_node = curr_node->next;
        }
    }
};

#endif  //__LINKEDLIST_H
