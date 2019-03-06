#include "application.h"

Application::Application() :
    running(true),
    recv_msg_queue(recv_msg_queue_mutex),
    send_msg_queue(send_msg_queue_mutex),
    logged_user("RandomString")
{
}

Application::~Application()
{
    if(cm)
        delete cm;
}
void Application::start(string local_address, string local_port, string ip_target, string remote_port)
{
    cm = new ConnectionManager(recv_msg_queue, send_msg_queue, local_address, local_port, ip_target, remote_port);
    thread(&Application::consume_message_queue, this).detach();
    thread(&Application::input_local, this).detach();
    cm->listen();

}

void Application::consume_message_queue()
{
    while(running)
    {
        if(recv_msg_queue.get_queue_size() > 0){
            ChatData received = recv_msg_queue.consume();
            Util::log_message("msg received on application: " + received.get_chat_msg(), Util::LOG_TYPE::INFO);
            chatBlocks.add_block(received);

        }
    }
}

void Application::input_local()
{
    char local_buffer[512];
    memset(local_buffer, 0, 512);
    string in;
    while(running)
    {
        cin.getline(local_buffer, 512);
        in = string(local_buffer);
        if(in == "") continue;
        time_t timeNow;
        send_msg_queue.add_msg(ChatData(in, logged_user.get_key(), logged_user.get_key(), time(&timeNow)));
        memset(local_buffer, 0, 512);

    }

}

