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

}
void Application::start(string local_address, string local_port, string ip_target, string remote_port)
{
    cm = make_unique<ConnectionManager>(recv_msg_queue, send_msg_queue, local_address, local_port, ip_target, remote_port);
    thread(&Application::consume_message_queue, this).detach();
    thread(&Application::input_local, this).detach();
    cm->listen();

}

void Application::consume_message_queue()
{
    while(running)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(THREAD_SLEEP_MILISECONDS_TIME));
        if(recv_msg_queue.get_queue_size() > 0){
            ChatData received = Util::str_to_chat_data(recv_msg_queue.consume());
            Util::log_message("msg received on application: " + received.get_chat_msg(), Util::LOG_TYPE::INFO);
            chatBlocks.add_block(received);

        }
    }
}

void Application::input_local()
{
    char local_buffer[LOCAL_INPUT_BUFFER_SIZE];
    memset(local_buffer, 0, LOCAL_INPUT_BUFFER_SIZE);
    string in;
    while(running)
    {
        cin.getline(local_buffer, LOCAL_INPUT_BUFFER_SIZE);
        in = string(local_buffer);
        if(in == "") continue;
        time_t timeNow;
        send_msg_queue.add_msg(Util::chat_data_to_string(ChatData(in, logged_user.get_key(), logged_user.get_key(), time(&timeNow))));
        memset(local_buffer, 0, LOCAL_INPUT_BUFFER_SIZE);

    }

}

