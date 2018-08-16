#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "block.h"
#include <vector>

using namespace std;

class Blockchain
{
public:
    Blockchain();

    void addBlock(TransactionData data);
    bool isChainValid();

    Block getLatestBlock();
    void printChain();

private:
    void createGenesisBlock();
    vector<Block> chain;
};

#endif // BLOCKCHAIN_H
