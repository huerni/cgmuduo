#include "echoServer.h"

#include <cgmuduo/Logger.h>


#include <unistd.h>

int main(){
    LOG_INFO("pid = %d", getpid());
    EventLoop loop;
    InetAddress addr(8001);
    EchoServer server(&loop, addr);
    server.start();
    loop.loop();

    return 0;
}