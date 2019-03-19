#include "messagequeue.h"

MessageQueue::MessageQueue(boost::mutex &mu):
    mu(mu)
{

}

void MessageQueue::add_msg(string m)
{
    boost::mutex::scoped_lock lock(mu);
    messages.push_back(m);
}

void MessageQueue::remove_msg()
{
    boost::mutex::scoped_lock lock(mu);
    messages.pop_front();
}

size_t MessageQueue::get_queue_size() const
{
    boost::mutex::scoped_lock lock(mu);
    return messages.size();
}

string MessageQueue::consume()
{
    boost::mutex::scoped_lock lock(mu);
    string ret = messages.front();
    messages.pop_front();

    return ret;
}
