#include "threadsafelist.h"

template <typename G>
void ThreadSafeList<G>::push_back(G g)
{
    boost::mutex::scoped_lock lock(the_list_mutex);
    this->push_back(g);
    
}

template <typename G>
void ThreadSafeList<G>::remove(G g)
{
    boost::mutex::scoped_lock lock(the_list_mutex);
    this->remove(g);
}

template <typename G>
size_t ThreadSafeList<G>::size()
{
    boost::mutex::scoped_lock lock(the_list_mutex);
    return this->size();
}