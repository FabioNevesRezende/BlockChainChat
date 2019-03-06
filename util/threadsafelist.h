#ifndef THREAD_SAFE_LIST_H
#define THREAD_SAFE_LIST_H

#include <iostream>
#include <list>
#include <boost/thread/mutex.hpp>

using namespace std;

template <typename G>
class ThreadSafeList : public std::list<G>
{
public:
    ThreadSafeList<G>();
    void push_back(G g);
    void remove(G g);
    size_t size();
private:
    boost::mutex the_list_mutex;

};

#endif // THREAD_SAFE_LIST_H
