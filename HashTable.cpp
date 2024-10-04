#include "HashTable.h"
#include "stringProcessing.h"

using namespace std;

const double HashTable::loadFactor = 0.7;

HashTable::HashTable() : hashGroups(defaultHashGroups), count(0) {
    table = new list<pair<string, string>>[hashGroups];
}

int HashTable::hashFunction(const string &key) const {
    unsigned long hash = 5381;
    for (char c : key) {
        hash = (hash << 5) + hash + c;
    }
    return hash % hashGroups;
}

void HashTable::insert(const string &key, const string &value) {
    int hashValue = hashFunction(key);
    auto &cell = table[hashValue];
    auto itr = begin(cell);
    bool keyExists = false;

    for (; itr != end(cell); itr++) {
        if (itr->first == key) {
            keyExists = true;
            itr->second = value;
            return;
        }
    }

    if (not keyExists) {
        cell.emplace_back(key, stripNonAlphaNum(value));
        count++;

        if (static_cast<double>(count) / hashGroups > loadFactor) {
            rehash();
        }
    }
}

string HashTable::search(const string &key) {
    size_t index = hashFunction(key);

    for (const auto &entry : table[index]) {
        if (entry.first == key) {
            return entry.second;
        }
    }

    return string();  // return an empty string if the key is not found
}

void HashTable::printTable() const {
    for (int i = 0; i < hashGroups; i++) {
        cout << "Bucket " << i << ": ";
        for (const auto &entry : table[i]) {
            cout << "(" << entry.first << ", " << entry.second << ") ";
        }
        cout << endl;
    }
}

void HashTable::rehash() {
    int newHG = hashGroups * 2;  // new hash group twice the size of old

    list<pair<string, string>> *newT = new list<pair<string, string>>[newHG];

    for (int i = 0; i < hashGroups; ++i) {
        for (const auto &entry : table[i]) {
            int newHashValue = hashFunction(entry.first) % newHG;
            newT[newHashValue].emplace_back(entry);
        }
    }

    delete[] table;  // deallocate memory previously occupied by old table
    table = newT;
    hashGroups = newHG;
}