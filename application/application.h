#ifndef APPLICATION_H
#define APPLICATION_H

#include <boost/thread/mutex.hpp>
#include <thread>
#include <time.h>
#include <fstream>

#include "../blockchain/blockchain.h"
#include "../connection/connectionmanager.h"
#include "../util/user.h"
#include "../util/messagequeue.h"

class Application
{
public:
    Application();
    ~Application();
    void start(string local_address, string local_port, string ip_target, string remote_port);

private:
    ConnectionManager* cm;
    Blockchain chatBlocks;
    User logged_user;
    MessageQueue recv_msg_queue;
    MessageQueue send_msg_queue;
    boost::mutex recv_msg_queue_mutex;
    boost::mutex send_msg_queue_mutex;
    bool running;

    void consume_message_queue();
    void input_local();
};

#endif // APPLICATION_H
