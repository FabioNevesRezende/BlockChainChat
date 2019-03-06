#include "blockchain.h"

Blockchain::Blockchain()
{
    create_genesis_block();
}

void Blockchain::add_block(ChatData data)
{
    int index = (int)chain.size();
    Block* newBlock = new Block(index, data, get_latest_block().get_block_hash());
    chain.push_back(*newBlock);
}

bool Blockchain::is_chain_valid()
{
    size_t chainLen = chain.size();
    for(vector<Block>::iterator it = chain.begin(); it != chain.end();  ++it)
    {
        if(!(*it).is_hash_valid())
            return false;

        if(chainLen > 1 && it > chain.begin())
        {
            if((*it).get_previous_hash() != (*(it -1)).get_block_hash())
                return false;
        }
    }
    return true;
}

Block Blockchain::get_latest_block()
{
    return chain.back();
}

void Blockchain::print_chain()
{
    for(vector<Block>::iterator it = chain.begin(); it != chain.end(); ++it)
    {
        Block b = *it;
        cout << "**************************************************" << endl
             << "Bloco: " + to_string(b.get_index()) << endl
             << "Hash: " + to_string(b.get_block_hash()) << endl
             << "Previous hash: " + to_string(b.get_previous_hash()) << endl
             << "isValid: " + string((b.is_hash_valid() ? "Yes" : "No")) << endl
             << "Chat message: " + b.get_data().get_chat_msg() << endl
             << "Recv key: " + b.get_data().get_receiver_key() << endl
             << "Sender key: " + b.get_data().get_sender_key() << endl
             << "Timestamp: " + to_string(b.get_data().get_timestamp()) << endl;

    }
    cout << "**************************************************" << endl;
}

void Blockchain::create_genesis_block()
{
    time_t current;
    ChatData* d = new ChatData("Hello, world!", "Genesis", "Genesis", time(&current));

    string toHashS = d->get_chat_msg() + d->get_sender_key() + d->get_receiver_key() + to_string(d->get_timestamp());

    hash<string> tDataHash;
    hash<string> prevHash;

    size_t hash = tDataHash(toHashS) ^(prevHash(to_string(0)) << 1);

    Block* genesisBlock = new Block(0, *d, hash);
    chain.push_back(*genesisBlock);

}
