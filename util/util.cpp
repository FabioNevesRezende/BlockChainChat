#include "util.h"

ChatData Util::str_to_chat_data(string msg)
{
    vector<string> msg_splitted = Util::explode(msg, Util::MSG_SEPARATOR);

    if(msg_splitted.size() < 5)
        throw std::runtime_error("Unformatted string");

    time_t t1Time = boost::lexical_cast<time_t>(msg_splitted.at(4));
    ChatData ret(msg_splitted.at(3), msg_splitted.at(1), msg_splitted.at(2), time(&t1Time));

    return ret;
}

string Util::chat_data_to_string(ChatData data)
{
    string ret("");
    string msg = data.get_chat_msg();
    string sender_key = data.get_sender_key();
    string receiver_key = data.get_receiver_key();
    time_t timestamp = data.get_timestamp();
    const char msg_separator = Util::MSG_SEPARATOR;

    ret.append(sender_key);
    ret.push_back(msg_separator);
    ret.append(receiver_key);
    ret.push_back(msg_separator);
    ret.append(msg);
    ret.push_back(msg_separator);
    ret.append(std::to_string(timestamp));
    ret.push_back(msg_separator);

    return ret;
}

vector<string> Util::split(string s, string delim)
{
    std::vector<string> strs;
    std::vector<string> ret;
    boost::split(strs, s, boost::is_any_of(delim));

    // filter out all empty strings
    std::copy_if(strs.begin(), strs.end(), std::back_inserter(ret), [](string s){return s != "";} );

    return ret;
}

vector<string> Util::explode(string const & s, char delim)
{
    vector<string> result;
    istringstream iss(s);

    for (string token; std::getline(iss, token, delim); )
    {
        result.push_back(std::move(token));
    }

    return result;
}

string Util::get_msg_type(string msg)
{
    return msg.substr(0, 6);
}


CnxData Util::str_to_cnx_data(string msg)
{
    vector<string> msg_splitted = Util::split(msg, to_string(Util::MSG_SEPARATOR));

    CnxData ret;
    ret.address = msg_splitted.at(1);
    ret.port = msg_splitted.at(2);

    return ret;
}

string Util::cnx_data_to_str(CnxData data)
{
    string ret("");

    ret.append(data.address);
    ret.append(std::to_string(Util::MSG_SEPARATOR));
    ret.append(data.port);
    return ret;
}

int Util::generate_random_int(int max)
{
    srand (time(NULL));
    return rand() % max + 1;
}

void Util::log_message(string msg, const LOG_TYPE type)
{
    if(type == Util::LOG_TYPE::ERROR)
        cerr << "[ERROR] " << msg << endl;
    else if (type == Util::LOG_TYPE::DEBUG)
        cout << "[DEBUG] " << msg << endl;
    else if (type == Util::LOG_TYPE::INFO)
        cout << "[INFO] " << msg << endl;
}

