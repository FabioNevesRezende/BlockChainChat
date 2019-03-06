#include "chatdata.h"

ChatData::ChatData(string chatMsg, string senderKey, string receiverKey, time_t timestamp):
    chatMsg(chatMsg),
    senderKey(senderKey),
    receiverKey(receiverKey),
    timestamp(timestamp)
{

}

string ChatData::get_chat_msg() const
{
    return chatMsg;
}

string ChatData::get_sender_key() const
{
    return senderKey;
}

string ChatData::get_receiver_key() const
{
    return receiverKey;
}

time_t ChatData::get_timestamp() const
{
    return timestamp;
}
