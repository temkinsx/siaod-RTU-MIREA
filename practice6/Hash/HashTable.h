#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <vector>
#include <string>
#include <list>

#include "Reader.h"
using namespace std;

class HashTable {
    vector<list<Reader> > table;
    size_t tableSize = table.size();
    int count;

    int hash(int key, size_t size) const;

public:
    HashTable(int initialSize);

    bool insert(const Reader &reader);

    bool remove(int key);

    bool find(int key, Reader &out);

    void display();

    void rehash();

    void fillDemo();
};


#endif //HASHTABLE_H
