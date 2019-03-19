#include "connectionlist.h"

ConnectionList::ConnectionList(boost::mutex& cnxs_mutex) :
    cnxs_mutex(cnxs_mutex)
{

}

void ConnectionList::push_back(Cnx* elem)
{
    boost::mutex::scoped_lock lock(cnxs_mutex);
    cnxs.push_back(elem);
}

void ConnectionList::remove(Cnx* elem)
{
    boost::mutex::scoped_lock lock(cnxs_mutex);
    cnxs.remove(elem);

}

void ConnectionList::broadcast(string msg_to_send)
{
    boost::mutex::scoped_lock lock(cnxs_mutex);
    for(Cnx* c: cnxs)
    {
        c->write_msg_on_socket(msg_to_send);
    }

}

size_t ConnectionList::size()
{
    boost::mutex::scoped_lock lock(cnxs_mutex);
    return cnxs.size();
}

