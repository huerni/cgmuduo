
#include "chargen/chargen.h"
#include "daytime/daytime.h"
#include "discard/discard.h"
#include "echo/echoServer.h"

#include <cgmuduo/Log.h>

#include <unistd.h>

Logger::ptr g_logger = LOG_ROOT();

int main() {
    LOG_FMT_INFO(g_logger, "pid = %d", getpid());
    //LOG_INFO(g_logger) << "pid=" << getpid();
    //EventLoop loop;
    //ChargenServer chargenServer(&loop, InetAddress(2019));
    //chargenServer.start();

    //DaytimeServer daytimeServer(&loop, InetAddress(2020));
    //daytimeServer.start();

    //DiscardServer discardServer(&loop, InetAddress(2021));
    //discardServer.start();

    //EchoServer echoServer(&loop, InetAddress(2022));
    //echoServer.start();

    //loop.loop();


    
    return 0;
}