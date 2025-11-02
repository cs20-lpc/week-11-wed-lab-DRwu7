#pragma once
#include "HashTableClosed.hpp"

template <typename T>
class DoubleHashing : public HashTableClosed<T> {
public:
    DoubleHashing(int size = 101)
        : HashTableClosed<T>(size) {}

    int hash2(const T& key) const {
        return 7 - (static_cast<int>(key) % 7);
    }

    int probeIndex(const T& key, int i) const override {
    //h(key, i) = (h1(key) + i * h2(key)) % M
        return (this->hash1(key) + i * hash2(key)) % this->M;        return 0;
    }
 };
