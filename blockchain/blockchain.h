#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "block.h"
#include <vector>

using namespace std;

class Blockchain
{
public:
    Blockchain();

    void add_block(ChatData data);
    bool is_chain_valid();

    Block get_latest_block();
    void print_chain();

private:
    void create_genesis_block();
    vector<Block> chain;
};

#endif // BLOCKCHAIN_H
