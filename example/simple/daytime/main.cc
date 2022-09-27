#include "daytime.h"


int main() {
    EventLoop loop;
    DaytimeServer daytimeServer(&loop, InetAddress(8002));
    daytimeServer.start();
    loop.loop();

    return 0;
}