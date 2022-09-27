#include "discard.h"


int main() {
    EventLoop loop;
    DiscardServer discardServer(&loop, InetAddress(8001));
    discardServer.start();
    loop.loop();

    return 0;
}