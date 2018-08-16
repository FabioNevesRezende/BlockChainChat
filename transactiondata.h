#ifndef TRANSACTIONDATA_H
#define TRANSACTIONDATA_H

#include <ctime>
#include <string>

using namespace std;

class TransactionData
{
public:
    TransactionData(double amount, string senderKey, string receiverKey, time_t timestamp);

    double getAmount() const;

    string getSenderKey() const;

    string getReceiverKey() const;

    time_t getTimestamp() const;

private:
    double amount;
    string senderKey;
    string receiverKey;
    time_t timestamp;
};

#endif // TRANSACTIONDATA_H
