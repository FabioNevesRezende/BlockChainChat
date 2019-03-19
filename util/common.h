#ifndef COMMON_H
#define COMMON_H

#include <thread>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>

using boost::asio::ip::tcp;

typedef boost::asio::io_service ioservice;

using namespace std;

#define BLOCK_CHAIN_CHAT_STD_LISTEN_PORT 1300
#define RESP_BUFFER_SIZE 2048
#define THREAD_SLEEP_MILISECONDS_TIME 600

#endif // COMMON_H
