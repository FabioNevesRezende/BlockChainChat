#include "blockchain.h"

Blockchain::Blockchain()
{
    createGenesisBlock();
}

void Blockchain::addBlock(TransactionData data)
{
    int index = (int)chain.size();
    Block* newBlock = new Block(index, data, getLatestBlock().getBlockHash());
    chain.push_back(*newBlock);
}

bool Blockchain::isChainValid()
{
    size_t chainLen = chain.size();
    for(vector<Block>::iterator it = chain.begin(); it != chain.end();  ++it)
    {
        if(!(*it).isHashValid())
            return false;

        if(chainLen > 1 && it > chain.begin())
        {
            if((*it).getPreviousHash() != (*(it -1)).getBlockHash())
                return false;
        }
    }
    return true;
}

Block Blockchain::getLatestBlock()
{
    return chain.back();
}

void Blockchain::printChain()
{
    for(vector<Block>::iterator it = chain.begin(); it != chain.end(); ++it)
    {
        Block b = *it;
        cout << "**************************************************" << endl
             << "Bloco: " + to_string(b.getIndex()) << endl
             << "Hash: " + to_string(b.getBlockHash()) << endl
             << "Previous hash: " + to_string(b.getPreviousHash()) << endl
             << "isValid: " + string((b.isHashValid() ? "Yes" : "No")) << endl
             << "Amount: " + to_string(b.getData().getAmount()) << endl
             << "Recv key: " + b.getData().getReceiverKey() << endl
             << "Sender key: " + b.getData().getSenderKey() << endl
             << "Timestamp: " + to_string(b.getData().getTimestamp()) << endl;

    }
    cout << "**************************************************" << endl;
}

void Blockchain::createGenesisBlock()
{
    time_t current;
    TransactionData* d = new TransactionData(0, "Genesis", "Genesis", time(&current));

    string toHashS = to_string(d->getAmount()) + d->getSenderKey() + d->getReceiverKey() + to_string(d->getTimestamp());

    hash<string> tDataHash;
    hash<string> prevHash;

    size_t hash = tDataHash(toHashS) ^(prevHash(to_string(0)) << 1);

    Block* genesisBlock = new Block(0, *d, hash);
    chain.push_back(*genesisBlock);

}
