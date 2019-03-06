#ifndef CHATDATA_H
#define CHATDATA_H

#include <ctime>
#include <string>

using namespace std;

class ChatData
{
public:
    ChatData(string chatMsg, string senderKey, string receiverKey, time_t timestamp);

    string get_chat_msg() const;

    string get_sender_key() const;

    string get_receiver_key() const;

    time_t get_timestamp() const;

private:
    string chatMsg;
    string senderKey;
    string receiverKey;
    time_t timestamp;
};

#endif // CHATDATA_H
