#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <memory>

struct Node {
    const int _value;
    std::unique_ptr<Node> _next;

    Node(int value);
};

class LinkedList {
    std::unique_ptr<Node> _root;

public:
    LinkedList();
    LinkedList(const int value);
    void insert(const int value);
    bool find(const int value);
};

#endif // LINKEDLIST_H