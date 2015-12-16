#ifndef List_H
#define List_H

#include <stddef.h>

namespace ACL {

/// 单向链表
/// 可在末尾插入、可正向迭代
template <typename T>
class List {
public:
    class iterator;

    List();
    virtual ~List();
    void push(const T& value);

    bool empty() const {
        return theSize == 0;
    }

    unsigned size() const {
        return theSize;
    }

    iterator begin() const {
        return iterator(front);
    }

    iterator end() const {
        return iterator(NULL);
    }

protected:
    struct Node {
        T data;
        Node *next;
        Node(const T& value, Node *next = NULL):
            data(value), next(next)
        {}
    } *front, *back;
    unsigned theSize;
};

template <typename T>
List<T>::List(): front(NULL), back(NULL), theSize(0) {}

template <typename T>
List<T>::~List() {
    while (front) {
        Node *p = front;
        front = front->next;
        delete p;
    }
}

template <typename T>
void List<T>::push(const T& value) {
    Node *p = new Node(value);
    if (back == NULL) {
        back = front = p;
    } else {
        back->next = p;
        back = p;
    }
    ++theSize;
}


/// 正向只读迭代器
template <typename T>
class List<T>::iterator {
public:
    iterator(const iterator& i): p(i.p) {}

    const iterator& operator=(const iterator &old) {
        p = old.p;
        return *this;
    }

    const T& operator*() const {
        return p->data;
    }

    const iterator operator++() { // i++
        if (p)
            p = p->next;
        return *this;
    }

    const iterator operator++(int) { // ++i
        iterator i(p);
        if (p)
            p = p->next;
        return i;
    }

    bool operator!=(const iterator &i) const {
        return p != i.p;
    }

    bool operator==(const iterator &i) const {
        return p == i.p;
    }

private:
    List<T>::Node *p;

    iterator(List<T>::Node* ptr): p(ptr) {}

    friend iterator List<T>::begin() const;
    friend iterator List<T>::end() const;
};

} // namespace: ACL

#endif // List_h