#include <cgmuduo/TcpServer.h>
#include <cgmuduo/Logger.h>

#include <string>
#include <unistd.h>

using std::string;

const char* g_file = nullptr;

string readFile(const char* filename) {
    string content;
    FILE* fp = ::fopen(filename, "rb");
    if(fp) {
        const int kBufSize = 1024*1024;
        char iobuf[kBufSize];

        ::setbuffer(fp, iobuf, sizeof iobuf);

        char buf[kBufSize];
        size_t nread = 0;
        while((nread = ::fread(buf, 1, sizeof buf, fp)) > 0) {
            content.append(buf, nread);
        }
        ::fclose(fp);
    }

    return content;
}


void onConnection(const TcpConnectionPtr& conn) {
    LOG_INFO("FileServer - %s -> %s is %s", 
            conn->peerAddr().toIpPort().c_str(), 
            conn->localAddr().toIpPort().c_str(), 
            (conn->connected() ? "UP" : "DOWN")
    );

    if(conn->connected()) {
        LOG_INFO("FileSerer - Sending file %s to %s", g_file, conn->peerAddr().toIpPort());

        string fileContent = readFile(g_file);
        conn->send(fileContent);
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
    InetAddress listenAddr(2021);
    TcpServer server(&loop, listenAddr, "FileServer");
    server.setConnectionCallback(onConnection);
    server.start();
    loop.loop();

}