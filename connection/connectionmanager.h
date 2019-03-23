#ifndef CONNECTION_MANAGER_H
#define CONNECTION_MANAGER_H

#include <thread>
#include <vector>
#include <functional>
#include <boost/thread.hpp>

#include "cnx.h"
#include "../util/util.h"
#include "../util/messagequeue.h"
#include "../util/threadsafelist.h"

class ConnectionManager{

public:
    ConnectionManager(MessageQueue& recv_msg_queue, MessageQueue& send_msg_queue,
                      string local_address, string local_port, string remote_address, string remote_port);
    ~ConnectionManager();
    void listen();

private:
    // variables
    ioservice server_io; // io service provided by boost to perform io operations on sockets when acting as a server
    ioservice client_io; // io service provided by boost to perform io operations on sockets when acting as a client

    CnxPtr client_cnx;
    tcp::acceptor acceptor; // boost tcp connection acceptor
    bool running; // is server running
    ThreadSafeList<CnxPtr> cnxs; // list of active connections
    boost::mutex cnxs_mutex;
    MessageQueue& recv_msg_queue; // list of messages received yet to be processed
    MessageQueue& send_broadcast_msg_queue; // list of messages send yet to be processed
    string local_address; // address to attempt to make first connection
    string remote_address; // address to attempt to make first connection
    string local_port; // local port to be listening on
    string remote_port; // remote port to attempt first connection

    // functions
    void receive_cnx();
    void talk_with_peer(CnxPtr cnx);
    void process_peer_message(CnxPtr cnx, string sck_msg_string);
    void connect_to_first_node();
    void send_msg_to_cnx();
    void request_known_nodes(CnxPtr client_cnx);
    void request_cnx_data(CnxPtr c);
};

#endif // CONNECTION_MANAGER_H
