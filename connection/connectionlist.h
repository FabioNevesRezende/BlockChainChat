#ifndef CONNECTION_LIST_H
#define CONNECTION_LIST_H

#include <list>
#include <boost/thread/mutex.hpp>
#include "cnx.h"

using namespace std;

class ConnectionList
{
public:

    ConnectionList(boost::mutex& cnxs_mutex);
    void push_back(Cnx* elem);
    void remove(Cnx* elem);
    void broadcast(string msg_to_send);
    size_t size();

private:
    list<Cnx*> cnxs; // list of active connections
    boost::mutex& cnxs_mutex;
};

#endif // CONNECTION_LIST_H
