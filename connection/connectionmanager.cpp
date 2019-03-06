#include "connectionmanager.h"

ConnectionManager::ConnectionManager(MessageQueue& recv_msg_queue, MessageQueue& send_msg_queue,
                                     string local_address, string local_port, string remote_address, string remote_port) :
    acceptor(server_io, tcp::endpoint(tcp::v4(), boost::lexical_cast<int>(local_port))),
    recv_msg_queue(recv_msg_queue),
    send_msg_queue(send_msg_queue),
    remote_address(remote_address),
    local_port(local_port),
    remote_port(remote_port),
    local_address(local_address)
{
    running = true;
}

ConnectionManager::~ConnectionManager()
{
    if(client_cnx)
        delete client_cnx;
}

void ConnectionManager::listen()
{
    thread t(&ConnectionManager::receive_cnx, this);
    thread(&ConnectionManager::connect_to_first_node, this).detach();
    thread(&ConnectionManager::send_msg_to_cnx, this).detach();

    Util::log_message("Program running, listening on " + local_address + ":" + local_port, Util::LOG_TYPE::INFO);
    t.join();
}

void ConnectionManager::receive_cnx()
{
    while(running)
    {
        Cnx* c = new Cnx(std::ref(server_io));
        acceptor.accept(c->get_socket());
        cnxs.push_back(c);
        request_cnx_data(c);
        thread(&ConnectionManager::talk_with_peer, this, c).detach();
    }
}

void ConnectionManager::talk_with_peer(Cnx* cnx)
{
    while(running && cnx->is_open())
    {
        try{
            string sck_msg_string = cnx->read_some();
            string msg_type = Util::get_msg_type(sck_msg_string);
            if(msg_type == Util::MSG_REQUEST_NODES)
            {
                Util::log_message("Received a request_nodes request", Util::LOG_TYPE::INFO);
            }
            else if(msg_type == Util::MSG_CNX_DATA)
            {
                CnxData data;
                data.address = local_address;
                data.port = local_port;
                cnx->write_msg_on_socket(
                            Util::MSG_CNX_DATA_RESPONSE + Util::MSG_SEPARATOR +
                            Util::cnx_data_to_str(data)
                            );
            }
            else if(msg_type == Util::MSG_CNX_DATA_RESPONSE)
            {
                cnx->cnx_data = Util::str_to_cnx_data(sck_msg_string);
            }
            else if(msg_type == Util::MSG_CHAT_DATA)
            {
                try
                {
                    ChatData sck_msg = Util::str_to_chat_data(sck_msg_string);
                    recv_msg_queue.add_msg(sck_msg);
                }
                catch(std::exception& e)
                {
                    Util::log_message("ConnectionManager::talk_with_peer Received a malformed chat data packet", Util::LOG_TYPE::ERROR);
                    Util::log_message(e.what(), Util::LOG_TYPE::ERROR);
                }
            }
            else
            {
                Util::log_message("Invalid message: " + sck_msg_string, Util::LOG_TYPE::ERROR);
            }
        }
        catch(std::exception& e){
            Util::log_message("Error processing message", Util::LOG_TYPE::ERROR);
            Util::log_message(e.what(), Util::LOG_TYPE::ERROR);
            cnx->close_cnx();
            break;

        }
    }
    cnxs.remove(cnx);
}

void ConnectionManager::connect_to_first_node()
{
    client_cnx = new Cnx(std::ref(client_io));
    if(client_cnx->connect_to_target(remote_address, remote_port))
    {
        Util::log_message("Connected to " + remote_address + " at port: " + remote_port, Util::LOG_TYPE::INFO);
        cnxs.push_back(client_cnx);
        thread(&ConnectionManager::talk_with_peer, this, client_cnx).detach();

        request_known_nodes(client_cnx);
    }
    else
    {
        Util::log_message("Found no connection at " + remote_address + " at port: " + remote_port , Util::LOG_TYPE::INFO);
        Util::log_message("Acting as a root node" , Util::LOG_TYPE::INFO);
    }
}
void ConnectionManager::send_msg_to_cnx()
{
    while(running)
    {
        if(send_msg_queue.get_queue_size() > 0)
        {
            ChatData data = send_msg_queue.consume();
            for(Cnx* c: cnxs)
            {
                c->write_msg_on_socket(Util::MSG_CHAT_DATA + Util::MSG_SEPARATOR + Util::chat_data_to_string(data));
            }
            Util::log_message("Sent message to " + std::to_string(cnxs.size()) + " connections" , Util::LOG_TYPE::INFO);

        }
    }
}

void ConnectionManager::request_known_nodes(Cnx* client_cnx)
{
    client_cnx->write_msg_on_socket(Util::MSG_REQUEST_NODES);
}

void ConnectionManager::request_cnx_data(Cnx* c)
{
    c->write_msg_on_socket(Util::MSG_CNX_DATA);
}
