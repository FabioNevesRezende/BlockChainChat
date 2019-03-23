#ifndef THREAD_SAFE_LIST_H
#define THREAD_SAFE_LIST_H

#include <iostream>
#include <list>
#include <functional>
#include <mutex>
 
using namespace std;

template <class G>
class ThreadSafeList {

public:
  void for_each(function<void(G)> f)
  {
    std::scoped_lock lock(local_list_mutex);
    for (G s : local_list)
    {
      f(s);
    }
  }

  void push_back(G e)
  {
    std::scoped_lock<std::mutex>  lock(local_list_mutex);
    local_list.push_back(e);
  }

  void remove(G e)
  {
    std::scoped_lock<std::mutex>  lock(local_list_mutex);
    local_list.remove(e);

  }

  size_t size()
  {
    std::scoped_lock<std::mutex>  lock(local_list_mutex);
    return local_list.size();
  }

private:
  list<G> local_list;
  mutex local_list_mutex;

};

#endif // THREAD_SAFE_LIST_H