#ifndef UTIL_H
#define UTIL_H

using namespace std;

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <vector>
#include <time.h>
#include <stdexcept>
#include <ctime>
#include <cstdio>
#include <cstdlib>

#include "chatdata.h"
#include "cnxdata.h"
#include "../connection/cnx.h"

namespace Util
{

    enum LOG_TYPE{
        INFO,
        DEBUG,
        ERROR
    };

    static const string EMPTY_STRING = "";

    static const char MSG_SEPARATOR = 0x1e;

    static const string MSG_CHAT_DATA = "chdata";
    static const string MSG_CNX_DATA = "cndata";
    static const string MSG_CNX_DATA_RESPONSE = "cndtrp";
    static const string MSG_REQUEST_NODES = "rqndes";

    ChatData str_to_chat_data(string msg);
    string chat_data_to_string(ChatData data);
    vector<string> split(string s, string delim);
    vector<string> explode(string const & s, char delim);
    string get_msg_type(string msg);
    CnxData str_to_cnx_data(string msg);
    string cnx_data_to_str(CnxData data);
    int generate_random_int(int max);
    void log_message(string msg, const LOG_TYPE type);
}

#endif // UTIL_H
