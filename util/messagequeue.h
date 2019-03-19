#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include <list>
#include <boost/thread/mutex.hpp>

using namespace std;

class MessageQueue
{
public:
    MessageQueue(boost::mutex& mu);
    void add_msg(string m);
    void remove_msg();
    size_t get_queue_size() const;
    string consume();

private:
    boost::mutex& mu;
    list<string> messages;
};

#endif // MESSAGEQUEUE_H
