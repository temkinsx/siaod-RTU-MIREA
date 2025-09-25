#include "HashTable.h"

#include <iostream>
#include <random>

HashTable::HashTable(int initialSize) : tableSize(initialSize), count(0) {
    table.resize(tableSize);
};

int HashTable::hash(int key, size_t size) const {
    return key % size;
}

bool HashTable::insert(const Reader &reader) {
    Reader tmp;
    if (static_cast<float>(count) / tableSize >= 0.75f) {
        rehash();
    }


    if (find(reader.getTicketNumber(), tmp)) {
        return false;
    }

    int index = hash(reader.getTicketNumber(), tableSize);
    table[index].push_back(reader);

    count++;
    return true;
}

bool HashTable::remove(int key) {
    auto &l = table[hash(key, tableSize)];
    if (l.empty()) {
        return false;
    }

    for (auto it = l.begin(); it != l.end(); it++) {
        if (it->getTicketNumber() == key) {
            l.erase(it);
            return true;
        }
    }

    return false;
}

bool HashTable::find(int key, Reader &out) {
    if (table.empty()) {
        return false;
    }

    auto &l = table[hash(key, tableSize)];
    if (l.empty()) {
        return false;
    }

    for (auto it = l.begin(); it != l.end(); it++) {
        if (it->getTicketNumber() == key) {
            out = *it;
            return true;
        }
    }

    return false;
}

void HashTable::rehash() {
    size_t newTableSize = tableSize * 2;
    vector<list<Reader> > newTable(newTableSize);
    for (int i = 0; i < tableSize; i++) {
        for (auto it = table[i].begin(); it != table[i].end(); it++) {
            int newHash = hash(it->getTicketNumber(), newTableSize);
            newTable[newHash].push_back(*it);
        }
    }

    table = newTable;
    tableSize = newTableSize;
}

void HashTable::display() {
    for (int i = 0; i < tableSize; i++) {
        if (table[i].empty()) {
            continue;
        }

        for (auto it = table[i].begin(); it != table[i].end(); it++) {
            std::cout << it->getTicketNumber() << ":" << it->getFio() << ":" << it->getAddress() << std::endl;
        }
    }
}

void HashTable::fillDemo() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(10000, 99999);

    std::vector<std::string> names = {
        "Иванов Иван Иванович",
        "Петров Петр Петрович",
        "Сидорова Анна Сергеевна",
        "Кузнецов Дмитрий Андреевич",
        "Смирнова Ольга Владимировна",
        "Федоров Николай Павлович"
    };

    std::vector<std::string> addresses = {
        "ул. Ленина, д. 10",
        "ул. Пушкина, д. 25",
        "пр. Гагарина, д. 3",
        "ул. Советская, д. 42",
        "пер. Школьный, д. 7",
        "ул. Мира, д. 15"
    };

    for (int i = 0; i < names.size(); i++) {
        int ticket = dist(gen);
        string fio = names[rand() % names.size()];
        string address = addresses[rand() % addresses.size()];

        Reader r(ticket, fio, address);
        insert(r);
    }
}
