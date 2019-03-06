#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include <list>
#include <boost/thread/mutex.hpp>

#include "chatdata.h"

using namespace std;

class MessageQueue
{
public:
    MessageQueue(boost::mutex& mu);
    void add_msg(ChatData m);
    void remove_msg();
    size_t get_queue_size() const;
    ChatData consume();

private:
    boost::mutex& mu;
    list<ChatData> messages;
};

#endif // MESSAGEQUEUE_H
