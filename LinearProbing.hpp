#pragma once
#include "HashTableClosed.hpp"

template <typename T>
class LinearProbing : public HashTableClosed<T> {
private:
    int skip; // skip factor
public:
    LinearProbing(int size = 101, int skipFactor = 3)
        : HashTableClosed<T>(size), skip(skipFactor) {}

    
    int probeIndex(const T& key, int i) const override {
        // h(key, i) = (h1(key) + i * skip) % M
        return (this->hash1(key) + i * this->skip) % this->M;
    }
};