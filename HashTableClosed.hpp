#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

template <typename T>
class HashTableClosed {
protected:
    vector<T> table;
    vector<bool> occupied;

public:
    int M; // table size
    int N; // number of elements
    
    explicit HashTableClosed(int size = 101)
        : M(size), N(0) {
        table.resize(M);
        occupied.assign(M, false);
    }

    virtual ~HashTableClosed() = default;

    virtual int probeIndex(const T& key, int i) const = 0;

    virtual int insert(const T& key);

    virtual pair<bool, int> search(const T& key) const;

    void display() const {
        cout << "Hash Table (size=" << M << ")\n";
        for (int i = 0; i < M; i++) {
            cout << i << ": ";
            if (occupied[i]) cout << table[i];
            else cout << "-";
            cout << "\n";
        }
    }

    int hash1(const T& key) const
    {
        return static_cast<int>(key) % M;
    }

    int size() const { return M; }
    int count() const { return N; }
    double loadFactor() const { return static_cast<double>(N)/M; }
};
#include "HashTableClosed.tpp"
