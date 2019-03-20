#ifndef THREAD_SAFE_LIST_H
#define THREAD_SAFE_LIST_H

#include <iostream>
#include <list>
#include <functional>
#include <boost/thread/mutex.hpp>

using namespace std;

template <class G>
class ThreadSafeList {

public:
  void for_each(function<void(G)> f);
  void push_back(G e);
  void remove(G e);
  size_t size();

private:
  list<G> local_list;
  boost::mutex local_list_mutex;

};

#endif // THREAD_SAFE_LIST_H