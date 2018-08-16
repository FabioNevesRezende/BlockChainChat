#include <iostream>
#include "blockchain.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "hello world\n";

    // inicia blockchain
    Blockchain UFUCoin;

    time_t t1Time;
    TransactionData primeiraTransacao(1.5, "Fulano", "Ciclano", time(&t1Time));

    UFUCoin.addBlock(primeiraTransacao);
    cout << "Is chain valid?" << endl
         << UFUCoin.isChainValid() << endl;

    TransactionData segundaTransacao(12345, "Beltrano", "Ciclano", time(&t1Time));

    UFUCoin.addBlock(segundaTransacao);
    cout << "Is chain still valid?" << endl
         << UFUCoin.isChainValid() << endl;


    cout << "estado do blockchain:" << endl;
    UFUCoin.printChain();

    return 0;
}
