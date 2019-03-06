#include "block.h"

Block::Block(int index, ChatData d, size_t previousHash):
    data(d)
{
       this->index = index;
       this->previousHash = previousHash;
       this->blockHash = generate_hash();
}

bool Block::is_hash_valid()
{
    return get_block_hash() == generate_hash();
}

int Block::get_index() const
{
    return index;
}

size_t Block::get_block_hash() const
{
    return blockHash;
}

size_t Block::get_previous_hash() const
{
    return previousHash;
}

ChatData Block::get_data() const
{
    return data;
}

size_t Block::generate_hash()
{
    hash<string> tDataHash;
    hash<string> prevHash;

    string toHash = data.get_chat_msg()
            + data.get_receiver_key()
            + data.get_sender_key()
            + to_string(data.get_timestamp());

    return tDataHash(toHash) ^ (prevHash(to_string(previousHash)) << 1);
}
