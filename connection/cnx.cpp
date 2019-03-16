#include "cnx.h"

Cnx::Cnx(ioservice& io) :
    sck(tcp::socket(io)),
    resolver(new tcp::resolver(io)),
    id(Util::generate_random_int(65536))
{
    cnx_data.address = Util::EMPTY_STRING;
    cnx_data.port = Util::EMPTY_STRING;
}

Cnx::~Cnx()
{
    if(resolver)
        delete resolver;
}

tcp::socket& Cnx::get_socket()
{
    return std::ref(sck);
}

bool Cnx::write_msg_on_socket(string msg)
{
    boost::system::error_code error_c;
    boost::asio::write(sck, boost::asio::buffer(msg + "\r\n\x06"), error_c);

    if(error_c)
    {
        Util::log_message("Error on Cnx::write_msg_on_socket, cnx.id: " + std::to_string(id) + ", message: " + msg, Util::LOG_TYPE::ERROR);
        return false;
    }

    Util::log_message("Cnx::write_msg_on_socket, cnx.id: " + std::to_string(id) + ", message: " + msg, Util::LOG_TYPE::INFO);
    return true;
}


vector<string> Cnx::read_some()
{
    size_t len;
    vector<string> ret;
    boost::system::error_code error_c;
    boost::array<char, RESP_BUFFER_SIZE> buf;

    len = sck.read_some(boost::asio::buffer(buf), error_c);

    if(error_c)
    {
        close_cnx();
    }

    if(len > RESP_BUFFER_SIZE) return ret;

    string ret_str = std::string(buf.data());
    ret = Util::split(ret_str, "\r\n");
    for(string& r: ret)
    {
        r.erase(std::remove(r.begin(), r.end(), 6), r.end());
    }
    buf.fill(0);

    return ret;
}

bool Cnx::connect_to_target(string targetAddr, string targetPort)
{
    boost::system::error_code error_c;
    boost::asio::connect(sck, resolver->resolve({targetAddr, targetPort}), error_c);
    if(error_c)
    {
        return false;
    }
    return true;
}

int Cnx::get_id() const
{
    return id;
}

void Cnx::close_cnx()
{
    sck.close();
}

bool Cnx::is_open()
{
    return sck.is_open();
}
