#ifndef CNX_H
#define CNX_H

#include <boost/array.hpp>
#include <algorithm>


#include "../util/cnxdata.h"
#include "../util/common.h"
#include "../util/util.h"

class Cnx
{
public:
    Cnx(ioservice& io);
    ~Cnx();

    CnxData cnx_data;
    tcp::socket& get_socket();
    bool write_msg_on_socket(string msg);
    vector<string> read_some();
    bool connect_to_target(string targetAddr, string targetPort);
    int get_id() const;
    void close_cnx();
    bool is_open();

private:
    tcp::socket sck;
    tcp::resolver* resolver;
    int id;
};

#endif // CNX_H
