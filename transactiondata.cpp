#include "transactiondata.h"

TransactionData::TransactionData(double amount, string senderKey, string receiverKey, time_t timestamp):
    amount(amount),
    senderKey(senderKey),
    receiverKey(receiverKey),
    timestamp(timestamp)
{

}

double TransactionData::getAmount() const
{
    return amount;
}

string TransactionData::getSenderKey() const
{
    return senderKey;
}

string TransactionData::getReceiverKey() const
{
    return receiverKey;
}

time_t TransactionData::getTimestamp() const
{
    return timestamp;
}
