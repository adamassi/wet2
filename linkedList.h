#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template<class T>
class Node {
public:
    T data;
    Node<T> *next;
    Node<T> *prev;

    Node() = default;

    Node(const T &data) : data(data), next(nullptr), prev(nullptr) {};

    ~Node() = default;

};

template<class T>
class LinkedList {
    Node<T> *head;
    Node<T> *tail;
    int length;
public:

    LinkedList() : head(nullptr), tail(nullptr), length(0) {};

    ~LinkedList() {
        Node<T> *curr = head;
        while (curr != nullptr) {
            Node<T> *temp = curr;
            curr = curr->next;
            delete temp;
        }
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    Node<T> *getHead() const {
        return head;


    }

    Node<T> *getTail() const {
        return tail;
    }

    Node<T> *insert(const T &data) {
        Node<T> *new_node = new Node<T>(data);
        if (tail == nullptr && head == nullptr) {
            head = new_node;
            tail = new_node;
        } else {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
        length++;
        return new_node;
    }

    void removeNode(Node<T> *nodeToRemove) {
        if (nodeToRemove->next) {
            nodeToRemove->next->prev = nodeToRemove->prev;
        }
        if (nodeToRemove->prev) {
            nodeToRemove->prev->next = nodeToRemove->next;
        }

        if (nodeToRemove == head) {
            head = head->next;
        }
        if (nodeToRemove == tail) {
            tail = tail->prev;
        }
        delete nodeToRemove;
        length--;
    }

    void remove(T data) {
        Node<T> *currNode = head;
        while (currNode != nullptr) {
            if (*(currNode->data) == *data) {
                removeNode(currNode);
                return;
            }
            currNode = currNode->next;
        }
        delete currNode;
    }

    int size() const {
        return this->length;
    }
};


#endif
