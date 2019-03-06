#include "threadsafelist.h"

template <typename G>
ThreadSafeList<G>::ThreadSafeList() : std::list<G>
{

}

template <typename G>
void ThreadSafeList<G>::push_back(G g)
{
    boost::mutex::scoped_lock lock(the_list_mutex);
    std::list<G>.push_back(g);
    
}

template <typename G>
void ThreadSafeList<G>::remove(G g)
{
    boost::mutex::scoped_lock lock(the_list_mutex);
    std::list<G>.remove(g);
}

template <typename G>
size_t ThreadSafeList<G>::size()
{
    boost::mutex::scoped_lock lock(the_list_mutex);
    return std::list<G>.size();
}