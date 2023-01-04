#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "linkedList.h"

template<class T>
class HashTable {
public:
    const unsigned int INITIAL_CAPACITY = 10;
    LinkedList<T> *table;
    unsigned int capacity;
    unsigned int occupancy;
    const unsigned int extend_factor;

    HashTable(const unsigned int &extend_factor = 2) : table(new LinkedList<T>[INITIAL_CAPACITY]),
                                                       capacity(INITIAL_CAPACITY),
                                                       occupancy(0), extend_factor(extend_factor) {}


    ~HashTable() {
        delete[] table;
    }

    int hashFunction(int index) {
        return index % 10;
    }

    Node<T> *findNode(int index, T data) {
        int i = hashFunction(index);
        Node<T> *currNode = table[i].getHead();
        while (currNode) {
            if (*data == *(currNode->data)) {
                return currNode;
            }
            currNode = currNode->next;
        }
        return nullptr;
    }

    T findData(int index, T d) { /// deleted * in T* 
        if (findNode(index, d) == nullptr) {
            return nullptr;
        }
        return findNode(index, d)->data; 
        //return new T(findNode(index, d)->data); 
         // return a copy of node<player>, but why do we need it?
    }

    void extend() {
        int new_capacity = capacity * extend_factor;
        LinkedList<T> *new_array = new LinkedList<T>[new_capacity];

        for (int i = 0; i < capacity; i++) {
            Node<T> *currNode = table[i].getHead();
            for (int j = 0; j < table[i].size(); j++) {
                new_array[i].insert(currNode->data);
                currNode = currNode->next;
            }
        }
        delete[] table;
        table = new_array;
        capacity = new_capacity;
    }

    // inserts a key into hash table
    void Insert(int empId, T data) {
        int index = hashFunction(empId);
        if (findNode(index, data) != nullptr) {
            throw NodeAlreadyExists();
        }
        if (occupancy + 1 == capacity) {
            extend();
        }
        table[index].insert(data);
        occupancy++;
    }

    void Remove(int playerId, T data) {
        int index = hashFunction(playerId);
        if (findNode(index, data) == nullptr) {
            throw NodeDoesntExists();
        }
        table[index].remove(data);
        occupancy--;
    }

};

#endif


