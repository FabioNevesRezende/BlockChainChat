#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <boost/functional/hash.hpp>
#include "../util/chatdata.h"

using namespace std;

class Block
{
public:
    Block(int index, ChatData d, size_t previousHash);
    bool is_hash_valid();

    int get_index() const;

    size_t get_block_hash() const;

    size_t get_previous_hash() const;

    ChatData get_data() const;

private:
    int index;
    size_t blockHash;
    size_t previousHash;

    ChatData data;

    size_t generate_hash();

};

#endif // BLOCK_H
