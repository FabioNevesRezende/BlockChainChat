#include "application/application.h"

int main(int argc, char *argv[])
{
    if(argc < 5){
        Util::log_message("Invalid input, you must provide: local addres, local port, remote address, remote port" , Util::LOG_TYPE::ERROR);
        Util::log_message("./program 127.0.0.1 1300 127.0.0.1 1301" , Util::LOG_TYPE::ERROR);
        exit(0);
    }
    Application app;

    string local_address = string(argv[1]);
    string local_port = string(argv[2]);
    string remote_address = string(argv[3]);
    string remote_port = string(argv[4]);

    app.start(local_address, local_port, remote_address, remote_port);

    return 0;
}
