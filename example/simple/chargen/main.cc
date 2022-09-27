#include "chargen.h"

int main(){

    EventLoop loop;
    InetAddress listenAddr(8003);
    ChargenServer server(&loop, listenAddr, true);
    server.start();
    loop.loop();
    
    return 0;
}