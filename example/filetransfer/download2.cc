#include <cgmuduo/TcpServer.h>
#include <cgmuduo/Logger.h>

#include <unistd.h>

const int kBufSize = 64*1024;
const char* g_file = nullptr;

void onHighWaterMark(const TcpConnectionPtr& conn, size_t len) {
    LOG_INFO("HighWaterMark %d", len);
}

void onConnection(const TcpConnectionPtr& conn) {
    LOG_INFO("FileServer - %s -> %s is %s", 
            conn->peerAddr().toIpPort().c_str(), 
            conn->localAddr().toIpPort().c_str(), 
            (conn->connected() ? "UP" : "DOWN")
    );
    if(conn->connected()) {
        LOG_INFO("FileServer -Sending file %s to %s", g_file, conn->peerAddr().toIpPort().c_str());
        conn->setHighWaterMarkCallback(onHighWaterMark, kBufSize+1);

        FILE* fp = ::fopen(g_file, "rb");
        if(fp) {
            conn->setContext(fp);
            char buf[kBufSize];
            size_t nread = ::fread(buf, 1, sizeof buf, fp);
            conn->send(buf, nread);
        }
        else {
            conn->shutdown();
            LOG_INFO("FilerServer - no such file");
        }
    }
    else {
        if(!conn->getContext().has_value()) {
            FILE* fp = std::any_cast<FILE*>(conn->getContext());
            if(fp) {
                ::fclose(fp);
            }
        }
    }
}

void onWriteComplete(const TcpConnectionPtr& conn) {
    FILE* fp = std::any_cast<FILE*>(conn->getContext());
    char buf[kBufSize];
    size_t nread = ::fread(buf, 1, sizeof buf, fp);
    if(nread > 0) {
        conn->send(buf, nread);
    }
    else {
        ::fclose(fp);
        fp = nullptr;
        conn->setContext(fp);
        conn->shutdown();
        LOG_INFO("FileServer - done");
    }
}



int main(int argc, char* argv[]) {
    LOG_INFO("pid = %d", getpid());

    if(argc < 1) {
        fprintf(stderr, "Usage: %s file_for_downloading\n", argv[0]);
        exit(1);
    }

    g_file = argv[1];

    EventLoop loop;
    TcpServer server(&loop, InetAddress(2022), "FileServer2");
    server.setConnectionCallback(onConnection);
    server.setWriteCompleteCallback(onWriteComplete);
    server.start();
    loop.loop();
}