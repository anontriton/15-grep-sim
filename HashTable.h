#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <string>
#include <functional>

using namespace std;

class HashTable {
public:
    HashTable();
    
    int hashFunction(const string &key) const;
    void insert(const string &key, const string &value);
    string search(const string &key);
    void printTable() const;

private:
    static const int defaultHashGroups = 10;
    static const double loadFactor;
    int hashGroups;
    int count; // number of items in the hash table
    list<pair<string, string>> *table;

    void rehash();
};

#endif  // HASHTABLE_H
