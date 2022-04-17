#ifndef _NODE_H
#define _NODE_H

template <class T>
class Node
{
public:
    T   value;
    Node *next, *prev;

public:
    Node();
    Node(T value, Node* next = 0, Node* prev = 0);
    ~Node();
};
#endif

template <class T>
Node<T>::Node()
{
    next = 0;
    prev = 0;
}

template <class T>
Node<T>::Node(T value, Node* next, Node* prev)
{
    this->value = value;
    this->next = next;
    this->prev = prev;
}

template <class T>
Node<T>::~Node()
{}