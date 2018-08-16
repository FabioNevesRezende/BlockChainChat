#include "block.h"

Block::Block(int index, TransactionData d, size_t previousHash):
    data(d)
{
       this->index = index;
       this->previousHash = previousHash;
       this->blockHash = generateHash();
}

bool Block::isHashValid()
{
    return getBlockHash() == generateHash();
}

int Block::getIndex() const
{
    return index;
}

size_t Block::getBlockHash() const
{
    return blockHash;
}

size_t Block::getPreviousHash() const
{
    return previousHash;
}

TransactionData Block::getData() const
{
    return data;
}

size_t Block::generateHash()
{
    hash<string> tDataHash;
    hash<string> prevHash;

    string toHash = to_string(data.getAmount())
            + data.getReceiverKey()
            + data.getSenderKey()
            + to_string(data.getTimestamp());

    return tDataHash(toHash) ^ (prevHash(to_string(previousHash)) << 1);
}
