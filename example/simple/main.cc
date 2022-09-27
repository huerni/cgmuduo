
#include "chargen/chargen.h"
#include "daytime/daytime.h"
#include "discard/discard.h"
#include "echo/echoServer.h"

#include <cgmuduo/Logger.h>

#include <unistd.h>

int main() {
    LOG_INFO("pid = %d", getpid());
    EventLoop loop;
    ChargenServer chargenServer(&loop, InetAddress(2019));
    chargenServer.start();

    DaytimeServer daytimeServer(&loop, InetAddress(2020));
    daytimeServer.start();

    DiscardServer discardServer(&loop, InetAddress(2021));
    discardServer.start();

    EchoServer echoServer(&loop, InetAddress(2022));
    echoServer.start();

    loop.loop();
    return 0;
}