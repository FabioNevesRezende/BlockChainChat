#include "threadsafelist.h"

template <class G>
void ThreadSafeList<G>::for_each(function<void(G)> f)
{
    boost::mutex::scoped_lock lock(local_list_mutex);
    for (G s : local_list)
    {
        f(s);
    }
}

template <class G>
void ThreadSafeList<G>::push_back(G s)
{
    boost::mutex::scoped_lock lock(local_list_mutex);
    local_list.push_back(s);
}

template <class G>
void ThreadSafeList<G>::remove(G e)
{
    boost::mutex::scoped_lock lock(local_list_mutex);
    local_list.remove(e);

}

template <class G>
size_t ThreadSafeList<G>::size()
{
    boost::mutex::scoped_lock lock(local_list_mutex);
    return local_list.size();
}