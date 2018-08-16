#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include "transactiondata.h"

using namespace std;

class Block
{
public:
    Block(int index, TransactionData d, size_t previousHash);
    bool isHashValid();

    int getIndex() const;

    size_t getBlockHash() const;

    size_t getPreviousHash() const;

    TransactionData getData() const;

private:
    int index;
    size_t blockHash;
    size_t previousHash;

    TransactionData data;

    size_t generateHash();

};

#endif // BLOCK_H
